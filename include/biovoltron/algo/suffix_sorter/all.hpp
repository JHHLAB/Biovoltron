#pragma once

/**
 * @defgroup suffix_sorter suffix_sorter
 * @ingroup algo
 * @brief The "suffix_sorter" module offers a versatile set of algorithms
 *        for efficient sorting and manipulation of suffix arrays.
 *
 * The "suffix_sorter" module provides a comprehensive suite of algorithms
 * and techniques for sorting and managing suffix arrays, a fundamental data
 * structure used in various bioinformatics and string processing applications.
 * It offers several key features:
 *
 * - Complete Suffix Array Sorting: Implementations of full suffix array sorting
 *   using algorithms such as "psais" and "stable-sort" for accurate and
 *   complete sorting of all suffixes.
 *
 * - K-Ordered Suffix Sorting: The module includes algorithms for k-ordered
 *   suffix sorting, where only the first k characters of each suffix are
 *   considered for sorting. This is particularly useful in applications where
 *   partial suffix ordering is sufficient.
 *
 * - Parallelization: Many of the sorting algorithms are designed to take
 *   advantage of parallel processing, enabling fast and efficient sorting
 *   of large datasets.
 *
 * These features make the "suffix_sorter" module a valuable toolbox for
 * researchers and practitioners in bioinformatics and string processing,
 * facilitating various sequence analysis tasks and data manipulation needs.
 */

#include <biovoltron/algo/suffix_sorter/core/suffix_sorter.hpp>
#include <biovoltron/algo/suffix_sorter/stable_sorter.hpp>
