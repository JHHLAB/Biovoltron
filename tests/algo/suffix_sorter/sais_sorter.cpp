#define TBB_SUPPRESS_DEPRECATED_MESSAGES 1

#include <biovoltron/algo/suffix_sorter/core/suffix_sorter.hpp>
#include <biovoltron/algo/suffix_sorter/sais_sorter.hpp>
#include <biovoltron/utility/istring.hpp>
#include <catch.hpp>

using namespace biovoltron;

template <SuffixSorter sorter> void check_suffix_array(istring_view ref) {
  auto sa = sorter::get_sa(ref);
  REQUIRE(sa.size() == ref.size() + 1);
  for (auto i = size_t{}; i < ref.size(); i++)
    REQUIRE(ref.substr(sa[i], sorter::sort_len) <=
            ref.substr(sa[i + 1], sorter::sort_len));
}

TEST_CASE("SAIS sorting test", "[StableSorter]") {
  auto refs = std::vector<istring>{
      Codec::to_istring(""), Codec::to_istring("A"),
      Codec::to_istring("CGTCGTAGTGCTCGTACAC"),
      Codec::to_istring("TCTGCTGCATATTATCGCTGTTGATGCGCTACTAG")};

  for (auto &ref : refs) {
    check_suffix_array<SaisSorter<>>(ref);
    check_suffix_array<SaisSorter<>>(ref);
    check_suffix_array<SaisSorter<>>(ref);
  }
}
