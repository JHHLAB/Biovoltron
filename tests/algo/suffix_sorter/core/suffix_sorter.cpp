#define TBB_SUPPRESS_DEPRECATED_MESSAGES 1

#include <catch.hpp>

#include <biovoltron/algo/suffix_sorter/stable_sorter.hpp>

using namespace biovoltron;

TEST_CASE("SuffixSorter concept test", "[SuffixSorter]") {
  // Case 1: Ensure StableSorter complies with the SuffixSorter concept
  REQUIRE(SuffixSorter<StableSorter<std::uint32_t, 256>>);

  // Case 2: Ensure types that don't comply with the SuffixSorter concept fail
  REQUIRE_FALSE(SuffixSorter<int>);
}
