#pragma once

#include <biovoltron/file_io/fasta.hpp>
#include <biovoltron/utility/istring.hpp>

namespace biovoltron {

/**
 * @ingroup file_io
 * @brief Manages data from FASTQ files, including sequences and quality scores,
 * for easy parsing and manipulation.
 *
 * This is a data structure for fastq file.
 * - inherit from FastaRecord
 * - for fastq file type to record reads after sequencing.
 *   - include reads and reads quality.
 */
template <bool Encoded = false> struct FastqRecord : FastaRecord<Encoded> {
  /**
   * @brief
   * Start symbol of reads
   *
   * - using "@" in fastq file type
   */
  constexpr static auto START_SYMBOL = '@';

  /**
   * @brief
   * Delimiter between reads and quality of reads
   *
   * - using "+" in fastq file type
   */
  constexpr static auto DELIM = '+';

  /**
   * @brief
   * Quality of reads
   *
   * - Quality record by character from "!" to "~"
   *   - encoded by ASCII from 33 to 126 transfer to quality 0~93
   *     - example: "!" ASCIII = (0+33), quality = 0; "?" ASCIII = (30+33),
   * quality = 30
   *   - Q = -10*log(P)
   *     - Q: quality
   *     - P: error probability
   */
  std::string qual;

  /**
   * @brief
   * Implicit conversion operator to convert a FastqRecord with one encoding to
   * another encoding.
   *
   * This operator allows the implicit conversion of a FastqRecord with one
   * encoding (either integer or string) to a FastqRecord with the opposite
   * encoding. For example, if you have an existing FastqRecord 'a' encoded as a
   * string, and you want to change its encoding to integer (or vice versa), you
   * can use this operator to perform the conversion.
   *
   * Example usage:
   * ```cpp
   * FastqRecord<false> a;     // 'a' is encoded as a std::string.
   * FastqRecord<true> b = a;  // 'b' is encoded as biovoltron::istring (using
   *                           // implicit conversion).
   * ```
   *
   * @return A FastqRecord with the opposite encoding (integer or string).
   */
  operator auto() const {
    if constexpr (Encoded)
      return FastqRecord<!Encoded>{{this->name, Codec::to_string(this->seq)},
                                   qual};
    else
      return FastqRecord<!Encoded>{{this->name, Codec::to_istring(this->seq)},
                                   qual};
  }
};

} // namespace biovoltron
