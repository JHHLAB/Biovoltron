#include <biovoltron/file_io/fasta.hpp>
#include <biovoltron/utility/istring.hpp>
#include <catch.hpp>
#include <sstream>

using namespace biovoltron;

TEST_CASE("FastaRecord Test", "[FastaRecord]") {
  SECTION("Default Constructor and Implicit Conversion") {
    FastaRecord<false> fastaString;
    fastaString.name = "TestSequence";
    fastaString.seq = "ACGT";

    // Test implicit conversion from string to istring
    FastaRecord<true> fastaIstring = fastaString;

    REQUIRE(fastaIstring.name == "TestSequence");
    REQUIRE(Codec::to_string(fastaIstring.seq) == "ACGT");
  }

  SECTION("Parsing from Stream") {
    std::istringstream stream(">TestSequence\nACGT");
    FastaRecord<false> fastaString;
    stream >> fastaString;

    REQUIRE(fastaString.name == "TestSequence");
    REQUIRE(fastaString.seq == "ACGT");
  }

  SECTION("Writing to Stream") {
    FastaRecord<false> fastaString;
    fastaString.name = "TestSequence";
    fastaString.seq = "ACGT";

    std::ostringstream stream;
    stream << fastaString;

    std::string expectedOutput = ">TestSequence\nACGT";
    REQUIRE(stream.str() == expectedOutput);
  }

  SECTION("Implicit Conversion from istring to string") {
    FastaRecord<true> fastaIstring;
    fastaIstring.name = "TestSequence";
    fastaIstring.seq = "0123"_s;

    // Test implicit conversion from istring to string
    FastaRecord<false> fastaString = fastaIstring;

    REQUIRE(fastaString.name == "TestSequence");
    REQUIRE(fastaString.seq == "ACGT");
  }

  SECTION("Parsing from Stream with Different Encodings") {
    std::istringstream stringStream(">TestSequence\nACGT");
    FastaRecord<false> fastaString;
    stringStream >> fastaString;

    std::istringstream istringStream(">TestSequence\nACGT");
    FastaRecord<true> fastaIstring;
    istringStream >> fastaIstring;

    REQUIRE(fastaString.name == fastaIstring.name);
    REQUIRE(fastaString.seq == Codec::to_string(fastaIstring.seq));
  }

  SECTION("Writing to Stream with Different Encodings") {
    FastaRecord<false> fastaString;
    fastaString.name = "TestSequence";
    fastaString.seq = "ACGT";

    FastaRecord<true> fastaIstring;
    fastaIstring.name = "TestSequence";
    fastaIstring.seq = "0123"_s;

    std::ostringstream stringStream;
    stringStream << fastaString;

    std::ostringstream istringStream;
    istringStream << fastaIstring;

    std::string expectedStringOutput = ">TestSequence\nACGT";
    std::string expectedIstringOutput = ">TestSequence\nACGT";

    REQUIRE(stringStream.str() == expectedStringOutput);
    REQUIRE(istringStream.str() == expectedIstringOutput);
  }
}
