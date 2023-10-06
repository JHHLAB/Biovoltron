#pragma once

#include <algorithm>
#include <istream>
#include <ostream>
#include <ranges>

namespace biovoltron {

struct Header {
  std::vector<std::string> lines;
  constexpr static auto START_SYMBOLS = std::array{""};
};

template <std::derived_from<Header> H>
inline auto operator==(const H &lhs, const H &rhs) noexcept {
  return lhs.lines == rhs.lines;
}

template <std::derived_from<Header> H>
inline auto &operator>>(std::istream &is, H &header) {
  header.lines.clear();
  auto pos = is.tellg();
  for (auto line = std::string{}; std::getline(is, line);) {
    if (std::ranges::any_of(header.START_SYMBOLS, [&line](auto symbol) {
          return line.starts_with(symbol);
        })) {
      header.lines.push_back(std::move(line));
      pos = is.tellg();
    } else
      break;
  }
  return is.seekg(pos);
}

template <std::derived_from<Header> H>
inline auto &operator<<(std::ostream &os, const H &header) {
  if (header.lines.empty())
    return os;

  os << header.lines.front();
  for (const auto &line : header.lines | std::views::drop(1))
    os << "\n" << line;
  return os;
}

} // namespace biovoltron
