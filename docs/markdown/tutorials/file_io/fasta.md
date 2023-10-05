# Working with FASTA files {#tutorials-fileio-fasta}

[TOC]

In this tutorial, we will explore how to effectively use biovoltron::FastaRecord from the File Input/Output module of Biovoltron. FastaRecord is designed to store and manipulate data from FASTA files, making it easier to work with nucleotide or protein sequences.

## Step 1. Include the Necessary Headers
First, you need to include the appropriate header file for FastaRecord:
```cpp
#include <biovoltron/file_io/fasta.hpp>
```

## Step 2. Creating a FastaRecord Object
You can create a biovoltron::FastaRecord object as follows:
```cpp
biovoltron::FastaRecord<false> fastaRecord;
```
Here, we've created a default biovoltron::FastaRecord object.

## Step 3. Reading Data from a FASTA File
Now, let's read data from a FASTA file into our biovoltron::FastaRecord object. You'll need an input file stream (`ifstream`) and the name of the FASTA file you want to read. Here's how to do it:
```cpp
// Open a FASTA file for reading
auto fa = std::ifstream{"hs37d5.fa"};

// Create a range view of FASTA records
auto refs = std::ranges::istream_view<FastaRecord<false>>(fa);

// Iterate through and print each FASTA record
for (const auto& ref : refs) {
  auto seqnence_name = ref.name;
  auto sequence_data = ref.seq;

  // Output FASTA record as FASTA format
  std::cout << ref << '\n';
}
```
Here, `sequence_name` will contain the name of the sequence, and `sequence_data` will contain the actual sequence data.

<span class="next_section_button">
[Read Next: FastaRecord Modules](structbiovoltron_1_1FastaRecord.html)
</span>
