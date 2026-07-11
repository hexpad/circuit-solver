# DC Circuit Solver

A C++ program that solves DC circuits. It reads the circuit from a text file and prints the voltage of each node. Matrix calculations are done with the Eigen library.

<img width="1607" height="979" alt="picture" src="https://github.com/user-attachments/assets/8d45cd31-5444-4ba3-812a-40a3fc5aca90" />


## Supported components

- R : resistor
- V : voltage source
- I : current source

Node 0 is ground.

## Netlist file

Create a file named `netlist.txt` in the same folder. One component per line:

```
name  node+  node-  value
```

Example:

```
V1 1 0 3
V2 4 0 2
R1 1 2 2
R2 2 0 3
R3 2 3 4
R4 3 0 2
R5 3 4 1
```

Output:

```
--- Results ---
Node 1 Voltage : 3 V
Node 2 Voltage : 1.70455 V
Node 3 Voltage : 1.38636 V
Node 4 Voltage : 2 V
---------------
```

## Install Eigen

- Mac: `brew install eigen`
- Ubuntu: `sudo apt install libeigen3-dev`
- Windows: download from the Eigen website and extract

## Build and run

```
g++ -O2 -std=c++17 -I/opt/homebrew/include/eigen3 main.cpp -o solver
./solver
```

For Qt, add this line to the .pro file and run qmake:

```
INCLUDEPATH += /opt/homebrew/include/eigen3
```

## Notes

- Only DC analysis, no capacitor or inductor
- The circuit must be connected to ground (node 0)
- Values must be plain numbers (10k style doesn't work)

## Source Code
https://github.com/hexpad/circuit-solver/blob/main/main.cpp
