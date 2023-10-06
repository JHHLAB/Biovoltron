#include <biovoltron/utility/istring.hpp>
#include <catch.hpp>

#include <iostream>

using namespace biovoltron;

TEST_CASE("operator\"\"_s - Integer string literal conversion", "[utility]") {
  biovoltron::istring is = "030102030"_s;
  REQUIRE(is == biovoltron::istring{0, 3, 0, 1, 0, 2, 0, 3, 0});
}

TEST_CASE("Codec::to_int - Convert DNA character to integer", "[utility]") {
  REQUIRE(biovoltron::Codec::to_int('A') == 0);
  REQUIRE(biovoltron::Codec::to_int('C') == 1);
  REQUIRE(biovoltron::Codec::to_int('G') == 2);
  REQUIRE(biovoltron::Codec::to_int('T') == 3);
  REQUIRE(biovoltron::Codec::to_int('N') == 4);
}

TEST_CASE("Codec::is_valid - Check if character is a valid DNA character",
          "[utility]") {
  REQUIRE(biovoltron::Codec::is_valid('A') == true);
  REQUIRE(biovoltron::Codec::is_valid('C') == true);
  REQUIRE(biovoltron::Codec::is_valid('G') == true);
  REQUIRE(biovoltron::Codec::is_valid('T') == true);
  REQUIRE(biovoltron::Codec::is_valid('N') == false);
  REQUIRE(biovoltron::Codec::is_valid('X') == false);
}

TEST_CASE("Codec::to_char - Convert integer to DNA character", "[utility]") {
  REQUIRE(biovoltron::Codec::to_char(0) == 'A');
  REQUIRE(biovoltron::Codec::to_char(1) == 'C');
  REQUIRE(biovoltron::Codec::to_char(2) == 'G');
  REQUIRE(biovoltron::Codec::to_char(3) == 'T');
  REQUIRE(biovoltron::Codec::to_char(4) == 'N');
}

TEST_CASE("Codec::hash - Calculate hash value for DNA sequence", "[utility]") {
  biovoltron::istring dna_iseq = "030013023"_s;
  REQUIRE(biovoltron::Codec::hash(dna_iseq) == 49611);
}

TEST_CASE("Codec::rhash - Reverse hash key to DNA sequence", "[utility]") {
  std::size_t hash_value = 49611;
  std::size_t sequence_size = 9;
  biovoltron::istring seq = biovoltron::Codec::rhash(hash_value, sequence_size);
  REQUIRE(seq == biovoltron::istring{0, 3, 0, 0, 1, 3, 0, 2, 3});
}

TEST_CASE("Codec::rev_comp - Reverse complement a DNA sequence", "[utility]") {
  biovoltron::istring dna_iseq = "30012303"_s;
  biovoltron::istring rev_comp_iseq = biovoltron::Codec::rev_comp(dna_iseq);
  REQUIRE(rev_comp_iseq == biovoltron::Codec::to_istring("ATACGTTA"));
}

TEST_CASE(
    "Codec::to_string - Convert integer-based DNA sequence to string-based",
    "[utility]") {
  biovoltron::istring int_seq = "21033021"_s;
  std::string string_seq = biovoltron::Codec::to_string(int_seq);
  REQUIRE(string_seq == "GCATTAGC");
}

TEST_CASE(
    "Codec::to_istring - Convert string-based DNA sequence to integer-based",
    "[utility]") {
  std::string string_seq = "TCGTAGCTGCA";
  biovoltron::istring int_iseq = biovoltron::Codec::to_istring(string_seq);
  // Replace with the actual expected integer-based sequence
  REQUIRE(int_iseq == "31230213210"_s);
}

TEST_CASE("Codec::rev_comp - Reverse complement a string-based DNA sequence",
          "[utility]") {
  std::string string_seq = "TCGTCATGCTGAC";
  std::string rev_comp_iseq = biovoltron::Codec::rev_comp(string_seq);
  // Replace with the actual expected reverse complemented string-based sequence
  REQUIRE(rev_comp_iseq == "GTCAGCATGACGA"); // This is just a placeholder,
                                             // replace with the actual result
}
