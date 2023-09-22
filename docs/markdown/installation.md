# Installation {#installation}

In this section, we'll guide you through the installation process for Biovoltron. Whether you're new to Biovoltron or an experienced user, this guide will help you get it up and running.

[TOC]

## Requirements
Before installing Biovoltron, make sure your system meets the following requirements:

- git
- cmake >= 3.16
- g++ >= 11.2
- zlib
- boost >= 1.71

You can install these dependencies on a Debian-based system like Ubuntu with:
```bash
# Install required dependencies
sudo apt install git cmake g++-11 zlib1g-dev libboost-all-dev
```

## Setting Up Your Project
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

To create this layout, use the script below:
```bash
# Create the app directory structure
mkdir app
cd app
mkdir src build

# Clone the Biovoltron repository with submodules
git clone --recurse-submodules https://github.com/JHHLAB/Biovoltron
```
If you prefer to manage dependencies manually, you can do so, but be prepared to modify CMake files.

## Verifying the Installation
To ensure Biovoltron is set up correctly, run unit tests:
```bash
# Navigate to the Biovoltron directory
cd Biovoltron
mkdir build && cd build

# Configure the project
cmake ..

# Build Biovoltron and run unit tests
make -j
./tests/biovoltron-test
```

## Building Your First Example
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

Your project layout should now look like this:
```bash
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

### Compiling and Running
Compile and run your code:
```bash
# Navigate to the build directory
cd build

# Configure the project
cmake ..

# Build the app
make app -j

# Run the app
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
