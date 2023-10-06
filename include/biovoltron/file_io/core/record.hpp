#pragma once

#include <biovoltron/file_io/core/tuple.hpp>
#include <biovoltron/utility/istring.hpp>
#include <ranges>
#include <sstream>

namespace biovoltron {

struct Record {};
struct HeaderableRecord : Record {};

template <std::derived_from<Record> R>
inline auto operator==(const R &lhs, const R &rhs) noexcept {
  return to_tuple(lhs) == to_tuple(rhs);
}

template <class T>
inline auto &operator<<(std::ostream &os, const std::vector<T> &fields) {
  if (fields.empty())
    return os;

  os << fields.front();
  for (const auto &field : fields | std::views::drop(1))
    os << "\t" << field;
  return os;
}

template <std::derived_from<Record> R>
inline auto &operator<<(std::ostream &os, const R &record) {
  std::apply([&os](const auto &...field) { ((os << field << "\t"), ...); },
             to_tuple(record));
  return os;
}

template <class T>
inline auto &operator>>(std::istream &is, std::vector<T> &fields) {
  for (auto field = T{}; is >> field;)
    fields.push_back(std::move(field));
  return is;
}

template <std::derived_from<Record> R>
inline auto &operator>>(std::istream &is, R &record) {
  if (auto line = std::string{}; std::getline(is, line))
    std::apply([iss = std::istringstream{line}](
                   auto &...field) mutable { ((iss >> field), ...); },
               to_tuple(record = {}));
  return is;
}

} // namespace biovoltron
