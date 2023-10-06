#pragma once

#include <tuple>

namespace biovoltron {

struct Record;
struct HeaderableRecord;

template <auto I> struct AnyField {
  template <typename T> operator T() noexcept;
};

template <std::derived_from<Record> R, auto... Is>
constexpr auto detect_fields_count(std::index_sequence<Is...>) noexcept {
  if constexpr (requires(Record r) { R{r, AnyField<Is>{}...}; })
    return sizeof...(Is);
  else
    return detect_fields_count<R>(
        std::make_index_sequence<sizeof...(Is) - 1>{});
}

template <std::derived_from<Record> R> constexpr auto fields_count() noexcept {
  return detect_fields_count<R>(std::make_index_sequence<sizeof(R)>{});
};

template <std::derived_from<Record> R> constexpr auto to_tuple(R &r) noexcept {
  constexpr auto count = fields_count<R>();
  constexpr auto has_header = std::derived_from<R, HeaderableRecord>;
  if constexpr (count == 21) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15,
           f16, f17, f18, f19, f20] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11,
                                 f12, f13, f14, f15, f16, f17, f18, f19, f20);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 20) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15,
           f16, f17, f18, f19] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11,
                                 f12, f13, f14, f15, f16, f17, f18, f19);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 19) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15,
           f16, f17, f18] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11,
                                 f12, f13, f14, f15, f16, f17, f18);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 18) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15,
           f16, f17] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11,
                                 f12, f13, f14, f15, f16, f17);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 17) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15,
           f16] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11,
                                 f12, f13, f14, f15, f16);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 16) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14,
           f15] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11,
                                 f12, f13, f14, f15);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 15) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14] = r;
    auto record_tuple =
        std::tie(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 14) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13] = r;
    auto record_tuple =
        std::tie(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 13) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12] = r;
    auto record_tuple =
        std::tie(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 12) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 11) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5, f6, f7, f8, f9, f10);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 10) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8, f9] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5, f6, f7, f8, f9);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 9) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7, f8] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5, f6, f7, f8);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 8) {
    auto &[f0, f1, f2, f3, f4, f5, f6, f7] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5, f6, f7);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 7) {
    auto &[f0, f1, f2, f3, f4, f5, f6] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5, f6);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 6) {
    auto &[f0, f1, f2, f3, f4, f5] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4, f5);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 5) {
    auto &[f0, f1, f2, f3, f4] = r;
    auto record_tuple = std::tie(f1, f2, f3, f4);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 4) {
    auto &[f0, f1, f2, f3] = r;
    auto record_tuple = std::tie(f1, f2, f3);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 3) {
    auto &[f0, f1, f2] = r;
    auto record_tuple = std::tie(f1, f2);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 2) {
    auto &[f0, f1] = r;
    auto record_tuple = std::tie(f1);
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  } else if constexpr (count == 1) {
    auto &[f0] = r;
    auto record_tuple = std::tie();
    if constexpr (has_header)
      return record_tuple;
    else
      return std::tuple_cat(std::tie(f0), record_tuple);
  }
}

} // namespace biovoltron
