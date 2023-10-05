# Installation {#installation}

This section provides guidance on installing Biovoltron. Whether you're new to Biovoltron or an experienced user, this guide will assist you in getting it up and running.

[TOC]

## Requirements {#installation-requirements}
Before installing Biovoltron, make sure your system meets the following requirements:

- git >= 11.1.0
- cmake >= 3.16
- g++ >= 11.2
- zlib >= 1.2.11
- boost >= 1.71

You can install these dependencies on a Debian-based system like Ubuntu with:
```bash
sudo apt install git cmake g++-11 zlib1g-dev libboost-all-dev
```

## Setting Up Your Project {#installation-setup-project}
We recommend organizing your project following the layout below:
```
$ tree app
app
├── CMakeLists.txt
├── Biovoltron
│   ├── CMakeLists.txt
│   ├── include
│   ├── submodules
│   └── ...
├── build
└── src
    └── main.cpp
```

To create this layout, use the following script:
```bash
mkdir app
cd app
mkdir src build
```

Clone the Biovoltron repository with submodules:
```bash
git clone --recurse-submodules https://github.com/JHHLAB/Biovoltron
```
If you prefer to manage dependencies manually, you can do so, but be prepared to modify CMake files.

## Verifying the Installation {#installation-verifying}
To ensure Biovoltron is set up correctly, run unit tests:

Navigate to the Biovoltron directory and configure the project
```bash
cd Biovoltron
mkdir build && cd build
```

Configure the project and build Biovoltron and run unit tests
```bash
cmake ..
make -j
./tests/biovoltron-test
```

## Building Your First Example {#installation-first-example}
After passing the unit tests, you can compile and run a simple example.
Let's start by creating a basic C++ program that uses Biovoltron to read a sample FASTA sequence.

### Writing the main.cpp File
Create a `main.cpp` file in the `src`directory with code like this:
```cpp
#include <iostream>
#include <sstream>
#include <biovoltron/file_io/fasta.hpp>

// Sample FASTA data
auto fasta = R"(>hello-world
ACTG)";

int main() {
  auto rec = biovoltron::FastaRecord<true>{};
  std::istringstream(fasta) >> rec;

  // Print the name and sequence
  std::cout << rec.name << '\n';
  std::cout << rec.seq << '\n';

  return 0;
}
```

### Configuring CMake
To build your C++ program with Biovoltron, create a `CMakeLists.txt` file:
```cmake
cmake_minimum_required (VERSION 3.16)

# Define your project name
project(app)

# Include Biovoltron's CMakeLists.txt
include(${PROJECT_SOURCE_DIR}/Biovoltron/CMakeLists.txt)

# Link your source code to your project
add_executable(app src/main.cpp)
target_link_libraries(app biovoltron)
```

### Compiling and Running
Compile and run your code:
```bash
cd build
cmake ..
make app -j
./app
```

The output should look like this:
```
hello-world
ACTG
```

By following these steps, you'll have a basic bioinformatics application using Biovoltron.
This serves as a foundation for more advanced tasks.

<span class="next_section_button">
[Read Next: Tutorials](tutorials/index.md)
</span>
