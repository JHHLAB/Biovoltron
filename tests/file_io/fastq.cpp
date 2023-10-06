#include <biovoltron/file_io/fastq.hpp>
#include <biovoltron/utility/istring.hpp>
#include <catch.hpp>
#include <sstream>

using namespace biovoltron;

TEST_CASE("FastqRecord Test", "[FastqRecord]") {
  SECTION("Default Constructor and Implicit Conversion") {
    FastqRecord<false> fastqString;
    fastqString.name = "TestSequence";
    fastqString.seq = "ACGT";
    fastqString.qual = "!@?#";

    // Test implicit conversion from string to istring
    FastqRecord<true> fastqIstring = fastqString;

    REQUIRE(fastqIstring.name == "TestSequence");
    REQUIRE(Codec::to_string(fastqIstring.seq) == "ACGT");
    REQUIRE(fastqIstring.qual == "!@?#");
  }

  SECTION("Parsing from Stream") {
    std::istringstream stream("@TestSequence\nACGT\n+\n!@?#");
    FastqRecord<false> fastqString;
    stream >> fastqString;

    REQUIRE(fastqString.name == "TestSequence");
    REQUIRE(fastqString.seq == "ACGT");
    REQUIRE(fastqString.qual == "!@?#");
  }

  SECTION("Writing to Stream") {
    FastqRecord<false> fastqString;
    fastqString.name = "TestSequence";
    fastqString.seq = "ACGT";
    fastqString.qual = "!@?#";

    std::ostringstream stream;
    stream << fastqString;

    std::string expectedOutput = "@TestSequence\nACGT\n+\n!@?#";
    REQUIRE(stream.str() == expectedOutput);
  }

  SECTION("Implicit Conversion from istring to string") {
    FastqRecord<true> fastqIstring;
    fastqIstring.name = "TestSequence";
    fastqIstring.seq = "0123"_s;
    fastqIstring.qual = "!@?#";

    // Test implicit conversion from istring to string
    FastqRecord<false> fastqString = fastqIstring;

    REQUIRE(fastqString.name == "TestSequence");
    REQUIRE(fastqString.seq == "ACGT");
    REQUIRE(fastqString.qual == "!@?#");
  }

  SECTION("Parsing from Stream with Different Encodings") {
    std::istringstream stringStream("@TestSequence\nACGT\n+\n!@?#");
    FastqRecord<false> fastqString;
    stringStream >> fastqString;

    std::istringstream istringStream("@TestSequence\nACGT\n+\n!@?#");
    FastqRecord<true> fastqIstring;
    istringStream >> fastqIstring;

    REQUIRE(fastqString.name == fastqIstring.name);
    REQUIRE(fastqString.seq == Codec::to_string(fastqIstring.seq));
    REQUIRE(fastqString.qual == fastqIstring.qual);
  }

  SECTION("Writing to Stream with Different Encodings") {
    FastqRecord<false> fastqString;
    fastqString.name = "TestSequence";
    fastqString.seq = "ACGT";
    fastqString.qual = "!@?#";

    FastqRecord<true> fastqIstring;
    fastqIstring.name = "TestSequence";
    fastqIstring.seq = "0123"_s;
    fastqIstring.qual = "!@?#";

    std::ostringstream stringStream;
    stringStream << fastqString;

    std::ostringstream istringStream;
    istringStream << fastqIstring;

    std::string expectedStringOutput = "@TestSequence\nACGT\n+\n!@?#";
    std::string expectedIstringOutput = "@TestSequence\nACGT\n+\n!@?#";

    REQUIRE(stringStream.str() == expectedStringOutput);
    REQUIRE(istringStream.str() == expectedIstringOutput);
  }
}
