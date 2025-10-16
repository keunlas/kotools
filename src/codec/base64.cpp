// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#include "kotools/codec/base64.h"

#include <array>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <functional>

namespace {

constexpr std::array<char, 64> BASE64_CHARS{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

constexpr char BASE64_PADDING{'='};

inline bool is_base64_chars(char c) {
  return std::isalnum(c) || c == '+' || c == '/' || c == '=';
}

// check is base64 chars before get index
uint8_t get_base64_chars_index(char c) {
  if (c >= 'A' && c <= 'Z') return c - 'A';
  if (c >= 'a' && c <= 'z') return c - 'a' + 26;
  if (c >= '0' && c <= '9') return c - '0' + 52;
  if (c == '+') return 62;
  if (c == '/') return 63;
  return 0;
}

inline char get_base64_chars(int index) { return BASE64_CHARS.at(index); }
inline char get_base64_padding() { return BASE64_PADDING; }

}  // namespace

namespace kotools::codec {

namespace base64 {

std::string encode(const std::string_view& input) {
  std::string result;
  result.reserve(((input.size() + 2) / 3) * 4);

  auto iter = input.begin();
  for (; input.end() - iter >= 3; iter += 3) {
    auto index1 = ((*iter) & 0xfc) >> 2;
    auto index2 = (((*iter) & 0x03) << 4) + (((*(iter + 1)) & 0xf0) >> 4);
    auto index3 = (((*(iter + 1)) & 0x0f) << 2) + (((*(iter + 2)) & 0xc0) >> 6);
    auto index4 = ((*(iter + 2)) & 0x3f);
    result.push_back(get_base64_chars(index1));
    result.push_back(get_base64_chars(index2));
    result.push_back(get_base64_chars(index3));
    result.push_back(get_base64_chars(index4));
  }

  if (auto remains = input.end() - iter; remains == 1) {
    auto index1 = ((*iter) & 0xfc) >> 2;
    auto index2 = (((*iter) & 0x03) << 4);
    result.push_back(get_base64_chars(index1));
    result.push_back(get_base64_chars(index2));
    result.push_back(get_base64_padding());
    result.push_back(get_base64_padding());
  } else if (remains == 2) {
    auto index1 = ((*iter) & 0xfc) >> 2;
    auto index2 = (((*iter) & 0x03) << 4) + (((*(iter + 1)) & 0xf0) >> 4);
    auto index3 = (((*(iter + 1)) & 0x0f) << 2);
    result.push_back(get_base64_chars(index1));
    result.push_back(get_base64_chars(index2));
    result.push_back(get_base64_chars(index3));
    result.push_back(get_base64_padding());
  }

  return result;
}

std::string decode(const std::string_view& input) {
  std::string result;
  result.reserve(((input.size() + 3) / 4) * 3);

  auto iter = input.begin();
  for (; input.end() - iter > 4; iter += 4) {
    if (!is_base64_chars(*iter) || !is_base64_chars(*(iter + 1)) ||
        !is_base64_chars(*(iter + 2)) || !is_base64_chars(*(iter + 3))) {
      return "";
    }

    auto char1 = ((get_base64_chars_index(*iter) & 0x3f) << 2) |
                 ((get_base64_chars_index(*(iter + 1)) & 0x30) >> 4);
    auto char2 = ((get_base64_chars_index(*(iter + 1)) & 0x0f) << 4) |
                 ((get_base64_chars_index(*(iter + 2)) & 0x3c) >> 2);
    auto char3 = ((get_base64_chars_index(*(iter + 2)) & 0x03) << 6) |
                 (get_base64_chars_index(*(iter + 3)) & 0x3f);
    result.push_back(char1);
    result.push_back(char2);
    result.push_back(char3);
  }

  auto paddings = input.size() - input.find_first_of(BASE64_PADDING);
  if (paddings == 1) {
    if (!is_base64_chars(*iter) || !is_base64_chars(*(iter + 1)) ||
        !is_base64_chars(*(iter + 2))) {
      return "";
    }

    auto char1 = ((get_base64_chars_index(*iter) & 0x3f) << 2) |
                 ((get_base64_chars_index(*(iter + 1)) & 0x30) >> 4);
    auto char2 = ((get_base64_chars_index(*(iter + 1)) & 0x0f) << 4) |
                 ((get_base64_chars_index(*(iter + 2)) & 0x3c) >> 2);
    result.push_back(char1);
    result.push_back(char2);
  } else if (paddings == 2) {
    if (!is_base64_chars(*iter) || !is_base64_chars(*(iter + 1))) {
      return "";
    }

    auto char1 = ((get_base64_chars_index(*iter) & 0x3f) << 2) |
                 ((get_base64_chars_index(*(iter + 1)) & 0x30) >> 4);
    result.push_back(char1);
  }

  return result;
}

}  // namespace base64

}  // namespace kotools::codec
