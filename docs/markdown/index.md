# Welcome {#mainpage}

[TOC]

Welcome to Biovoltron, a modern C++ library for bioinformatics tasks and data analysis.

Drawing inspiration from the iconic Voltron, Biovoltron embraces the concept of modularity, allowing you to assemble and utilize different "modules" within the library to create a variety of applications for your bioinformatics needs.

## Introducing Biovoltron

Biovoltron is an open-source C++ library designed to simplify and accelerate bioinformatics tasks. It provides a comprehensive set of functionalities, data structures, and algorithms to work with biological data, from sequence analysis to structural biology, and everything in between. Biovoltron is developed with a focus on performance, usability, and extensibility, making it a valuable asset for researchers, developers, and educators in the bioinformatics community.

## Key Features
- **Efficiency**: Biovoltron is built with performance in mind, utilizing modern C++ features and optimization techniques to ensure your bioinformatics analyses run smoothly and quickly.
- **Versatility**: Like the modular components of Voltron, Biovoltron offers a wide range of tools and algorithms as independent "modules." You can mix and match these modules to create customized bioinformatics applications tailored to your specific needs.
- **Ease of Use**: We provide user-friendly interfaces and extensive documentation to make it easy for you to assemble and make the most of Biovoltron's modular capabilities.
- **Open Source**: Biovoltron is an open-source project, inviting contributions from the community to enhance its functionality and robustness.

## Biovoltron at a Glance
Biovoltron is a modern C++ bioinformatics library designed to provide a seamless and modular experience for working with biological data. Below, we highlight key features and showcase code snippets to demonstrate its capabilities in some bioinformatics tasks.

### File Input and Output
```cpp
#include <biovoltron/file_io/fasta.hpp>
#include <fstream>
#include <iostream>
#include <ranges>

using namespace biovoltron;

int main() {
  // Open a FASTA file for reading
  auto fa = std::ifstream{"hs37d5.fa"};

  // Create a range view of FASTA records
  auto refs = std::ranges::istream_view<FastaRecord<>>(fa);

  // Iterate through and print each FASTA record
  for (const auto& ref : refs)
    std::cout << ref << "\n";
}
```
With Biovoltron's Fasta module, you can effortlessly read and process FASTA files, making it easy to work with sequences and reference genomes.
### Align and Variant Calling
```cpp
#include <biovoltron/pipe/algo_pipe.hpp>
#include <iostream>
#include <range/v3/all.hpp>

using namespace biovoltron;

int main() {
  // Create a reference sequence record
  auto ref = FastaRecord<>{};
  std::ifstream{"chr22.fa"} >> ref;

  // Build an index for the reference sequence
  auto index = ref | pipe::build{.LOOKUP_LEN = 8};

  // Open paired-end FASTQ files
  auto fq1 = std::ifstream{"chr22.1.fq"};
  auto fq2 = std::ifstream{"chr22.2.fq"};

  // Create a range view of paired FASTQ records
  auto reads = ranges::view::zip(ranges::istream_range<FastqRecord<>>(fq1),
                                 ranges::istream_range<FastqRecord<>>(fq2));

  // Align reads to the reference, sort variants, and call variants
  const auto vars
    = reads
      | pipe::align{.ref = ref, .index = std::move(index)}
      | ranges::action::sort
      | pipe::call{.ref = ref};

  // Print the called variants
  for (const auto& var : vars)
    std::cout << var << "\n";
}
```
Biovoltron's Alignment and Variant Calling Pipeline enables you to align reads against a reference genome and call variants effortlessly. It leverages modern C++ features and pipelines for efficient and streamlined bioinformatics workflows.

### Adaptor Trimming
```cpp
#include <biovoltron/trim/adaptor_trim.hpp>
#include <iostream>
#include <ranges>

using namespace biovoltron;

int main() {
  // Load your FASTQ data
  auto fq = std::ifstream{"sample.fastq"};

  // Create a range view of FASTQ records
  auto records = std::ranges::istream_view<FastqRecord<>>(fq);

  // Perform adaptor trimming
  auto trimmed_records = records | trim::adaptor_trim{};

  // Print the trimmed records
  for (const auto& record : trimmed_records)
    std::cout << record << "\n";
}
```

Biovoltron's Adaptor Trimming Module simplifies the process of trimming adaptor sequences from your FASTQ data, ensuring cleaner and more accurate downstream analysis.

## Getting Started
To get started with Biovoltron and experience the modular power it offers, follow these simple steps:

1. **[Installation](installation.md)**: We recommend that you use CMake to build your project. Check out our [Installation Guide](installation.md) for detailed instructions.
2. **[Tutorials](tutorials/index.md)**: Dive into our step-by-step [Tutorials](tutorials/index.md) to learn how to assemble and use Biovoltron modules for various bioinformatics tasks.
3. **Documentation**: The API Documentation provides detailed information about Biovoltron's modules, classes, and functions. It's your reference guide to making the most of the modular library.
4. **[Contribute](contribute.md)**: If you're passionate about bioinformatics and C++, consider contributing to Biovoltron. Check our [Contribution Guide](contribute.md) to get started.

## Community and Support
Join our growing community of bioinformatics enthusiasts, developers, and researchers:

- **GitHub Repository**: https://github.com/JHHLAB/Biovoltron
- **Discussion Forum**: https://github.com/JHHLAB/Biovoltron/discussions
- **Bug Reports and Feature Requests**: Submit issues and ideas on our [GitHub Issues](https://github.com/JHHLAB/Biovoltron/issues) page

## License
Biovoltron is licensed under the [MIT license](https://github.com/JHHLAB/Biovoltron/blob/main/LICENSE).

<span class="next_section_button">
[Read Next: Installation](installation.md)
</span>
