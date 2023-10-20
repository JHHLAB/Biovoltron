#pragma once

#include <biovoltron/container/xbit_vector.hpp>
#include <biovoltron/utility/istring.hpp>

#include <tuple>
#include <vector>

namespace biovoltron {

namespace sais {

/**
 * @brief A template variable representing an empty or invalid value for a given
 * data type.
 *
 * @tparam T The data type for which the empty value is defined.
 */
template <typename T> constexpr auto EMPTY = std::numeric_limits<T>::max();

/**
 * @brief Represents the SA-IS algorithm's internal data structure, a bit
 * vector.
 */
using TypeVector = biovoltron::detail::XbitVector<1, std::uint8_t,
                                                  std::allocator<std::uint8_t>>;

/**
 * @brief Enum to represent the type of suffix (L-type or S-type).
 */
enum SUFFIX_TYPE { L_TYPE = 0, S_TYPE = 1 };

/**
 * @brief Determines if a suffix at a specific position is an LMS (Longest
 * Minimal Suffix).
 *
 * @param T The type vector representing the suffix types.
 * @param i The position of the suffix.
 * @return True if the suffix is an LMS, otherwise false.
 */
template <typename size_type = std::uint32_t>
auto is_LMS(const TypeVector &T, size_type i) {
  auto n = (size_type)T.size();
  return i == n or (i > 0 and T[i - 1] == SUFFIX_TYPE::L_TYPE and
                    T[i] == SUFFIX_TYPE::S_TYPE);
}

/**
 * @brief Computes the type vector of the input sequence.
 *
 * @param S The input sequence.
 * @return The type vector.
 */
template <typename size_type>
auto get_type(const std::ranges::random_access_range auto &S) {
  auto n = (size_type)S.size();
  auto T = TypeVector(n, L_TYPE);

  for (auto i = n - 2; ~i; i--)
    T[i] = S[i] == S[i + 1]  ? T[i + 1]
           : S[i] < S[i + 1] ? SUFFIX_TYPE::S_TYPE
                             : SUFFIX_TYPE::L_TYPE;

  return T;
}

/**
 * @brief Enum to represent the type of buckets (begin or end).
 */
enum BUCKET_TYPE { BEGIN, END };

/**
 * @brief Computes the bucket array for a given sequence and bucket type.
 *
 * @param S The input sequence.
 * @param K The size of the alphabet.
 * @return The computed bucket array.
 */
template <BUCKET_TYPE TYPE, typename size_type>
inline auto get_bucket(const std::ranges::random_access_range auto &S,
                       size_type K) {
  auto BA = std::vector<size_type>(K);
  for (auto &v : S)
    BA[v]++;

  if constexpr (TYPE == BUCKET_TYPE::BEGIN) {
    exclusive_scan(std::begin(BA), std::end(BA), std::begin(BA), 1);
  } else {
    inclusive_scan(std::begin(BA), std::end(BA), std::begin(BA),
                   std::plus<size_type>{}, 1);
  }

  return BA;
}

/**
 * @brief Populates the sorted LMS substrings into the suffix array.
 *
 * @param S The input sequence.
 * @param K The size of the alphabet.
 * @param T The type vector.
 * @param SA The suffix array to be populated.
 */
template <typename size_type = std::uint32_t>
void put_lms_substr(const std::ranges::random_access_range auto &S, size_type K,
                    const TypeVector &T,
                    std::ranges::random_access_range auto &SA) {
  auto n = (size_type)S.size();
  std::fill(std::begin(SA), std::end(SA), EMPTY<size_type>);

  auto BA = get_bucket<BUCKET_TYPE::END>(S, K);
  for (auto i = n - 1; ~i; i--)
    if (is_LMS(T, i))
      SA[--BA[S[i]]] = i;
  SA[0] = n;
}

/**
 * @brief Induces L-type suffixes into the suffix array.
 *
 * @param S The input sequence.
 * @param K The size of the alphabet.
 * @param T The type vector.
 * @param SA The suffix array to be populated.
 */
template <typename size_type = std::uint32_t>
void induceL(const std::ranges::random_access_range auto &S, size_type K,
             const TypeVector &T, std::ranges::random_access_range auto &SA) {
  auto n = (size_type)S.size();
  auto BA = get_bucket<BUCKET_TYPE::BEGIN>(S, K);
  for (auto i = size_type{0}; i < n; i++) {
    if (SA[i] == EMPTY<size_type> or SA[i] == 0)
      continue;

    auto j = SA[i] - 1;
    if (T[j] != SUFFIX_TYPE::L_TYPE)
      continue;

    SA[BA[S[j]]++] = j;
  }
}

/**
 * @brief Induces S-type suffixes into the suffix array.
 *
 * @param S The input sequence.
 * @param K The size of the alphabet.
 * @param T The type vector.
 * @param SA The suffix array to be populated.
 */
template <typename size_type = std::uint32_t>
void induceS(const std::ranges::random_access_range auto &S, size_type K,
             const TypeVector &T, std::ranges::random_access_range auto &SA) {
  auto n = (size_type)S.size();
  auto BA = get_bucket<BUCKET_TYPE::END>(S, K);
  for (auto i = n; i >= 1; i--) {
    if (SA[i] == EMPTY<size_type> or SA[i] == 0)
      continue;

    auto j = SA[i] - 1;
    if (T[j] != SUFFIX_TYPE::S_TYPE)
      continue;

    SA[--BA[S[j]]] = j;
  }
}

/**
 * @brief Sorts the suffix array based on induced L and S suffixes.
 *
 * @param S The input sequence.
 * @param K The size of the alphabet.
 * @param T The type vector.
 * @param SA The suffix array to be sorted.
 */
template <typename size_type = std::uint32_t>
void induce_sort(const std::ranges::random_access_range auto &S, size_type K,
                 const TypeVector &T,
                 std::ranges::random_access_range auto &SA) {
  induceL(S, K, T, SA);
  induceS(S, K, T, SA);
}

/**
 * @brief Determines if two substrings starting at positions x and y are the
 * same.
 *
 * @param S The input sequence.
 * @param T The type vector.
 * @param x The starting position of the first substring.
 * @param y The starting position of the second substring.
 * @return True if the substrings are the same, otherwise false.
 */
template <typename size_type = std::uint32_t>
auto is_same_substr(const std::ranges::random_access_range auto &S,
                    const TypeVector &T, size_type x, size_type y) {
  auto n = (size_type)S.size();

  do {
    if (x == n or y == n or S[x++] != S[y++])
      return false;
  } while (not is_LMS(T, x) and not is_LMS(T, y));

  return x != n and y != n and is_LMS(T, x) and is_LMS(T, y) and S[x] == S[y];
}

/**
 * @brief Computes the length of LMS substrings and the number of unique
 * characters in them.
 *
 * @param S The input sequence.
 * @param K The size of the alphabet.
 * @param T The type vector.
 * @param SA The suffix array containing LMS substrings.
 * @return A tuple containing the length of LMS substrings and the number of
 * unique characters.
 */
template <typename size_type = std::uint32_t>
auto name_lms_substr(const std::ranges::random_access_range auto &S,
                     size_type K, const TypeVector &T,
                     std::ranges::random_access_range auto &SA) {
  auto n = (size_type)S.size();
  auto n1 = size_type{};
  for (auto i = size_type{0}; i <= n; i++)
    if (is_LMS(T, SA[i]))
      SA[n1++] = SA[i];

  std::fill(std::begin(SA) + n1, std::end(SA), EMPTY<size_type>);

  auto prev = EMPTY<size_type>, name_idx = size_type{};
  for (auto i = size_type{1}; i < n1; i++) {
    auto curr = SA[i];
    name_idx +=
        prev != EMPTY<size_type> and not is_same_substr(S, T, prev, curr);
    SA[n1 + curr / 2] = name_idx;
    prev = curr;
  }

  for (auto i = n, j = n; i >= n1; i--)
    if (SA[i] != EMPTY<size_type>)
      SA[j--] = SA[i];

  // pop back tailing '\0'
  n1--;

  return std::tuple<size_type, size_type>{n1, name_idx + 1};
}

/**
 * @brief Populates the sorted LMS suffixes into the suffix array.
 *
 * @param S The input sequence.
 * @param K The size of the alphabet.
 * @param T The type vector.
 * @param S1 The sorted LMS substrings.
 * @param SA The suffix array to be populated.
 * @param SA1 The suffix array of LMS substrings.
 */
template <typename size_type = std::uint32_t>
void put_lms_suffix(const std::ranges::random_access_range auto &S, size_type K,
                    const TypeVector &T,
                    const std::ranges::random_access_range auto &S1,
                    std::ranges::random_access_range auto &SA,
                    std::ranges::random_access_range auto &SA1) {
  auto n = (size_type)S.size();
  for (auto i = size_type{}, j = size_type{}; i < n; i++)
    if (is_LMS(T, i))
      S1[j++] = i;

  auto n1 = (size_type)S1.size();
  for (auto i = 1; i <= n1; i++)
    SA1[i] = S1[SA1[i]];
  SA1[0] = n;

  std::fill(std::begin(SA) + n1 + 1, std::end(SA), EMPTY<size_type>);

  auto BA = get_bucket<BUCKET_TYPE::END>(S, K);
  for (auto i = n1; i >= 1; i--) {
    auto j = SA1[i];
    SA1[i] = EMPTY<size_type>;
    SA[--BA[S[j]]] = j;
  }
}

/**
 * @brief Constructs the suffix array of the input sequence using the SA-IS
 * algorithm.
 *
 * @param S The input sequence.
 * @param K The size of the alphabet.
 * @param SA The resulting suffix array.
 */
template <typename size_type = std::uint32_t>
void suffix_array(const std::ranges::random_access_range auto &S, size_type K,
                  std::ranges::random_access_range auto &SA) {
  // 1. get TypeVector from S
  auto T = get_type<size_type>(S);

  // 2. put LMS character into SA in any order for each bucket
  put_lms_substr(S, K, T, SA);

  // 3. induce LMS substring
  induce_sort(S, K, T, SA);

  // 4. naming LMS substring
  // |S1| = n1, |SA1| = n1 + 1
  auto [n1, K1] = name_lms_substr(S, K, T, SA);
  auto S1 = std::ranges::subrange(std::end(SA) - n1, std::end(SA));
  auto SA1 = std::ranges::subrange(std::begin(SA), std::begin(SA) + n1 + 1);

  // 5. recursively solve LMS suffix
  if (K1 < n1) {
    suffix_array(S1, K1, SA1);
  } else {
    for (auto i = size_type{}; i < n1; i++)
      SA1[S1[i] + 1] = i;
    SA1[0] = n1;
  }

  // 6. put LMS character into SA in the order of LMS suffix
  put_lms_suffix(S, K, T, S1, SA, SA1);

  // 7. induce SA from LMS suffix
  induce_sort(S, K, T, SA);
}

} // namespace sais

/**
 * @brief A template class for sorting a given string using the SA-IS algorithm.
 */
template <std::integral size_type_t = std::uint32_t> struct SaisSorter {
  using size_type = size_type_t;

  /**
   * @brief The length for sorting.
   */
  static constexpr std::size_t sort_len = istring::npos;

  /**
   * @brief Computes the suffix array for a given input string.
   *
   * @param ref The input string.
   * @param sort_len The length up to which to compute the suffix array.
   *                 Default is -1 to compute the entire array.
   * @return The computed suffix array.
   */
  static auto get_sa(istring_view ref) {
    auto SA = std::vector<size_type>(ref.size() + 1, sais::EMPTY<size_type>);

    if (ref.size() > 0)
      sais::suffix_array(ref, 128u, SA);

    return SA;
  }
};

} // namespace biovoltron
