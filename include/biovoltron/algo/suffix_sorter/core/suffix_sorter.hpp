#pragma once

#include <biovoltron/utility/istring.hpp>
#include <concepts>

namespace biovoltron {

/**
 * @ingroup suffix_sorter
 * @brief Concept for Suffix Sorter.
 *
 * This concept defines the requirements for a Suffix Sorter type.
 * A Suffix Sorter is expected to provide a sorting algorithm for suffix arrays.
 *
 * @tparam T The Suffix Sorter type to be checked.
 */
template <typename T>
concept SuffixSorter = requires(T t, istring_view ref) {
  std::is_integral_v<typename T::size_type>;
  T::sort_len;
  t.get_sa(ref);
};

} // namespace biovoltron
