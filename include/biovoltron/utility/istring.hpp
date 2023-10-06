#pragma once

#include <algorithm>
#include <istream>
#include <ostream>

namespace biovoltron {

using ichar = std::int8_t;
using istring = std::basic_string<ichar>;
using istring_view = std::basic_string_view<ichar>;

/**
 * Integer string literal (like std::string_literals but
 * for integer string).
 *
 * @param s The input character string.
 * @param size The size of the input string.
 * @return An istring containing the integer values.
 *
 * example
 * ```cpp
 * auto is = "0123"_s; // Creates an istring with values {0, 1, 2, 3}.
 * ```
 */
inline auto operator""_s(const char *s, std::size_t) {
  auto is = istring{};
  for (const auto c : std::string_view{s})
    is.push_back(c - '0');
  return is;
}

/**
 * @ingroup utility
 * @brief Codec for DNA alphabet to integer conversion.
 */
struct Codec {

  constexpr static auto ints = [] {
    auto ints = std::array<ichar, 128>{};
    ints.fill(4);
    ints['a'] = ints['A'] = 0;
    ints['c'] = ints['C'] = 1;
    ints['g'] = ints['G'] = 2;
    ints['t'] = ints['T'] = 3;
    return ints;
  }();
  /**
   * DNA to integer.
   * @param DNA alphabet.
   * @return A std::int8_t, 0(A), 1(C), 2(G), 3(T).
   */
  constexpr static auto to_int(char c) noexcept { return ints[c]; }

  /**
   * Check if a character is a valid DNA alphabet character.
   * @param c Character to check.
   * @return True if the character is a valid DNA alphabet character, false
   * otherwise.
   */
  constexpr static auto is_valid(char c) noexcept { return to_int(c) != 4; }

  constexpr static auto chars = std::array{'A', 'C', 'G', 'T', 'N'};
  /**
   * Convert an integer (0-3) to its corresponding DNA alphabet character.
   * @param i Integer value (0-3).
   * @return The corresponding DNA alphabet character ('A', 'C', 'G', 'T').
   */
  constexpr static auto to_char(int i) noexcept { return chars[i]; }

  /**
   * Calculate a hash value for a DNA sequence.
   * @param seq The input DNA sequence.
   * @return The calculated hash value.
   */
  constexpr static auto hash(istring_view seq) noexcept {
    auto key = 0ull;
    for (auto i = 0; i < seq.size(); i++)
      key |= (seq[seq.size() - i - 1] & 3ull) << 2 * i;
    return key;
  };

  /**
   * Reverse hash a hash key to a DNA sequence.
   * @param key The hash key to reverse.
   * @param size The size of the DNA sequence.
   * @return The reversed DNA sequence.
   */
  static auto rhash(std::size_t key, std::size_t size) {
    auto seq = istring{};
    for (auto i = 0; i < size; i++) {
      const auto shift = (size - i - 1) * 2;
      seq += (key & 3ull << shift) >> shift;
    }
    return seq;
  }

  /**
   * Reverse complement a DNA sequence.
   * @param seq The input DNA sequence.
   * @return The reverse complemented DNA sequence.
   */
  static auto rev_comp(istring_view seq) {
    auto res = istring{};
    res.reserve(seq.size());
    std::transform(seq.rbegin(), seq.rend(), std::back_inserter(res),
                   [](const auto c) { return c == 4 ? 4 : 3 - c; });
    return res;
  }

  /**
   * Convert an istring (integer-based DNA sequence) to a string-based DNA
   * sequence.
   * @param seq The input istring sequence.
   * @return The converted string-based DNA sequence.
   */
  static auto to_string(istring_view seq) {
    auto res = std::string{};
    std::ranges::transform(seq, std::back_inserter(res), to_char);
    return res;
  }

  /**
   * Convert a string-based DNA sequence to an istring (integer-based DNA
   * sequence).
   * @param seq The input string-based DNA sequence.
   * @return The converted istring sequence.
   */
  static auto to_istring(std::string_view seq) {
    auto res = istring{};
    std::ranges::transform(seq, std::back_inserter(res), to_int);
    return res;
  }

  constexpr static auto comp = [](char c) {
    switch (c) {
    case 'a':
    case 'A':
      return 'T';
    case 'c':
    case 'C':
      return 'G';
    case 'g':
    case 'G':
      return 'C';
    case 't':
    case 'T':
      return 'A';
    default:
      return 'N';
    }
  };
  /**
   * Reverse complement a string-based DNA sequence.
   * @param seq The input string-based DNA sequence.
   * @return The reverse complemented string-based DNA sequence.
   */
  static auto rev_comp(std::string_view seq) {
    auto res = std::string{};
    res.reserve(seq.size());
    std::transform(seq.rbegin(), seq.rend(), std::back_inserter(res), comp);
    return res;
  }
};

} // namespace biovoltron

namespace std {

/**
 * Output an istring view to an output stream.
 * @param out The output stream.
 * @param s The istring view to output.
 * @return A reference to the output stream.
 *
 * example
 * ```cpp
 * istring dna_seq = "0123"_is;
 * std::cout << dna_seq << std::endl; // Outputs "ACGT" to the console.
 * ```
 */
inline auto &operator<<(ostream &out, biovoltron::istring_view s) {
  return out << biovoltron::Codec::to_string(s);
}

/**
 * Input an istring from an input stream.
 * @param in The input stream.
 * @param is The istring to populate from input.
 * @return A reference to the input stream.
 *
 * example
 * ```cpp
 * biovoltron::istring dna_seq;
 * std::istringstream input("ACGT");
 * input >> dna_seq;
 * ```
 */
inline auto &operator>>(istream &in, biovoltron::istring &is) {
  auto s = string{};
  in >> s;
  is = biovoltron::Codec::to_istring(s);
  return in;
}

} // namespace std
