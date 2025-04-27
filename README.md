# Off-by-One Errors: Static Analysis and Runtime Defenses

## Overview
This project implements a GCC plugin that statically analyzes C/C++ source code to detect **Off-by-One Errors (OBOEs)** — a common class of programming errors that can lead to memory corruption, buffer overflows, and security vulnerabilities. The plugin flags suspicious array accesses at compile-time and lays the groundwork for runtime defense mechanisms.

## Objectives
- Detect potential off-by-one errors during compilation using static analysis.
- Provide compile-time warnings highlighting problematic code areas.
- Propose basic runtime defense concepts to terminate execution on dangerous buffer operations.

## Tools and Technologies
- **Language:** C++
- **Compiler:** GCC
- **Plugin Framework:** GCC Plugin API
- **Operating System:** Linux (Tested on Kali Linux)
- **Build Tool:** Make (Makefile)

## Prerequisites
- Linux-based OS
- GCC and G++ installed (`gcc`, `g++`, `make`)
- GCC Plugin Development headers (`gcc-14-plugin-dev` or your version)

## Setup Instructions

1. **Install dependencies:**
    ```bash
    sudo apt update
    sudo apt install g++ gcc make gcc-14-plugin-dev
    ```

2. **Clone the repository:**
    ```bash
    https://github.com/PandavP3/OBOE-Detection-and-Defense.git
    cd oboe-static-analyzer
    ```

3. **Build the plugin and sample file:**
    ```bash
    make
    ```

4. **Run static analysis manually:**
    ```bash
    g++ -fplugin=./gcc_oboe_plugin.so test.cpp -o sample
    ```

## File Structure
- `gcc_oboe_plugin.cpp` — Source code for the GCC plugin implementing OBOE detection.
- `Makefile` — Automates the plugin build and test file compilation.
- `test.cpp` — Sample test program with intentional off-by-one errors.
- `sample` — Output binary compiled using the plugin.

## Sample Output
```bash
[Plugin] Initializing OBOE plugin...
test.cpp:6:16: warning: (Plugin) Potential off-by-one index access
    arr[i] = i;
