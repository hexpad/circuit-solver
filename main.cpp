#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Eigen/Dense>

struct Component {
    char type;
    int node1;
    int node2;
    double value;
};

class Circuit {
public:
    std::vector<Component> components;
    int numNodes = 0;
    int numSources = 0;

    void readFile(std::string filename) {
        std::ifstream file(filename);
        std::string line, name;

        while (std::getline(file, line)) {
            if (line == "" || line[0] == '#') continue;

            std::stringstream ss(line);
            Component c;

            ss >> name >> c.node1 >> c.node2 >> c.value;
            c.type = std::toupper(name[0]);

            components.push_back(c);

            if (c.node1 > numNodes) numNodes = c.node1;
            if (c.node2 > numNodes) numNodes = c.node2;

            if (c.type == 'V') numSources++;
        }
    }

    void solve() {
        if (numNodes == 0) {
            std::cout << "No components in circuit or file could not be read!" << std::endl;
            return;
        }

        int size = numNodes + numSources;
        Eigen::MatrixXd A = Eigen::MatrixXd::Zero(size, size);
        Eigen::VectorXd B = Eigen::VectorXd::Zero(size);

        int v_row = numNodes;

        for (size_t k = 0; k < components.size(); k++) {
            Component c = components[k];

            int i = c.node1 - 1;
            int j = c.node2 - 1;

            if (c.type == 'R') {
                double g = 1.0 / c.value;
                if (i >= 0) A(i, i) += g;
                if (j >= 0) A(j, j) += g;
                if (i >= 0 && j >= 0) { A(i, j) -= g; A(j, i) -= g; }
            }
            else if (c.type == 'I') {
                if (i >= 0) B(i) -= c.value;
                if (j >= 0) B(j) += c.value;
            }
            else if (c.type == 'V') {
                if (i >= 0) { A(i, v_row) = 1; A(v_row, i) = 1; }
                if (j >= 0) { A(j, v_row) = -1; A(v_row, j) = -1; }
                B(v_row) = c.value;
                v_row++;
            }
        }

        Eigen::VectorXd result = A.fullPivLu().solve(B);

        std::cout << "\n--- Results ---\n";
        for (int i = 0; i < numNodes; i++) {
            std::cout << "Node " << i + 1 << " Voltage : " << result(i) << " V\n";
        }
        std::cout << "---------------\n";
    }
};

int main() {
    Circuit myCircuit;

    myCircuit.readFile("netlist.txt");
    myCircuit.solve();

    return 0;
}
