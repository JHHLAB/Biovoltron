#pragma once

#include <biovoltron/algo/suffix_sorter/core/suffix_sorter.hpp>
#include <biovoltron/utility/istring.hpp>
#include <execution>

namespace biovoltron {

/**
 * @ingroup suffix_sorter
 * @brief A stable sorter for suffix arrays.
 *
 * This class provides a stable sorting algorithm for suffix arrays.
 * It allows sorting based on a specified length of suffixes.
 *
 * @tparam size_type The data type for size and indices.
 * @tparam sort_len_t The length for sorting (default is istring_view::npos).
 */
template <std::integral size_type_t = std::uint32_t,
          std::size_t sort_len_t = istring_view::npos>
struct StableSorter {
  using size_type = size_type_t;

  /**
   * @brief The length for sorting.
   */
  static constexpr std::size_t sort_len = sort_len_t;

  /**
   * Get the suffix array of a given istring_view.
   *
   * @param ref The input istring_view.
   * @return The sorted suffix array.
   */
  static auto get_sa(istring_view ref) {
    auto sa = std::vector<size_type>(ref.size() + 1);
    std::iota(sa.begin(), sa.end(), 0);
    std::stable_sort(std::execution::par_unseq, sa.begin(), sa.end(),
                     [ref](auto i, auto j) {
                       return ref.substr(i, sort_len) < ref.substr(j, sort_len);
                     });
    return sa;
  }
};

} // namespace biovoltron
