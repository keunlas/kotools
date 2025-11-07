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
#include <stdexcept>

namespace {

using namespace std::string_view_literals;

constexpr auto BASE64_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"sv;

constexpr char BASE64_PADDING = '=';

constexpr char get_char(int index) { return BASE64_CHARS.at(index); }

constexpr char get_padding() { return BASE64_PADDING; }

constexpr uint8_t get_index(char c) {
  if (c >= 'A' && c <= 'Z') return c - 'A';
  if (c >= 'a' && c <= 'z') return c - 'a' + 26;
  if (c >= '0' && c <= '9') return c - '0' + 52;
  if (c == '+') return 62;
  if (c == '/') return 63;
  return 0;
}

constexpr bool is_valid_char(char c) {
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
          (c >= '0' && c <= '9') || (c == '+') || (c == '/') || (c == '='));
}

}  // namespace

namespace kotools::codec::base64 {

std::string encode(const std::string_view& input) {
  std::string result;
  result.reserve(((input.size() + 2) / 3) * 4);

  auto iter = input.begin();
  for (; input.end() - iter >= 3; iter += 3) {
    auto index1 = ((*iter) & 0xfc) >> 2;
    auto index2 = (((*iter) & 0x03) << 4) + (((*(iter + 1)) & 0xf0) >> 4);
    auto index3 = (((*(iter + 1)) & 0x0f) << 2) + (((*(iter + 2)) & 0xc0) >> 6);
    auto index4 = ((*(iter + 2)) & 0x3f);
    result.push_back(get_char(index1));
    result.push_back(get_char(index2));
    result.push_back(get_char(index3));
    result.push_back(get_char(index4));
  }

  if (auto remains = input.end() - iter; remains == 1) {
    auto index1 = ((*iter) & 0xfc) >> 2;
    auto index2 = (((*iter) & 0x03) << 4);
    result.push_back(get_char(index1));
    result.push_back(get_char(index2));
    result.push_back(get_padding());
    result.push_back(get_padding());
  } else if (remains == 2) {
    auto index1 = ((*iter) & 0xfc) >> 2;
    auto index2 = (((*iter) & 0x03) << 4) + (((*(iter + 1)) & 0xf0) >> 4);
    auto index3 = (((*(iter + 1)) & 0x0f) << 2);
    result.push_back(get_char(index1));
    result.push_back(get_char(index2));
    result.push_back(get_char(index3));
    result.push_back(get_padding());
  }

  return result;
}

std::string decode(const std::string_view& input) {
  std::string result;
  result.reserve(((input.size() + 3) / 4) * 3);

  auto iter = input.begin();
  for (; input.end() - iter > 4; iter += 4) {
    if (!is_valid_char(*iter) || !is_valid_char(*(iter + 1)) ||
        !is_valid_char(*(iter + 2)) || !is_valid_char(*(iter + 3))) {
      throw std::logic_error("invalid base64 character");
      return "";
    }

    auto char1 = ((get_index(*iter) & 0x3f) << 2) |
                 ((get_index(*(iter + 1)) & 0x30) >> 4);
    auto char2 = ((get_index(*(iter + 1)) & 0x0f) << 4) |
                 ((get_index(*(iter + 2)) & 0x3c) >> 2);
    auto char3 = ((get_index(*(iter + 2)) & 0x03) << 6) |
                 (get_index(*(iter + 3)) & 0x3f);
    result.push_back(char1);
    result.push_back(char2);
    result.push_back(char3);
  }

  auto paddings = input.size() - input.find_first_of(BASE64_PADDING);
  if (paddings == 1) {
    if (!is_valid_char(*iter) || !is_valid_char(*(iter + 1)) ||
        !is_valid_char(*(iter + 2))) {
      throw std::logic_error("invalid base64 character");
      return "";
    }

    auto char1 = ((get_index(*iter) & 0x3f) << 2) |
                 ((get_index(*(iter + 1)) & 0x30) >> 4);
    auto char2 = ((get_index(*(iter + 1)) & 0x0f) << 4) |
                 ((get_index(*(iter + 2)) & 0x3c) >> 2);
    result.push_back(char1);
    result.push_back(char2);
  } else if (paddings == 2) {
    if (!is_valid_char(*iter) || !is_valid_char(*(iter + 1))) {
      throw std::logic_error("invalid base64 character");
      return "";
    }

    auto char1 = ((get_index(*iter) & 0x3f) << 2) |
                 ((get_index(*(iter + 1)) & 0x30) >> 4);
    result.push_back(char1);
  } else {
    throw std::logic_error("invalid base64 string");
    return "";
  }

  return result;
}

}  // namespace kotools::codec::base64
