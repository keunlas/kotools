// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#ifndef KOTOOLS_CODEC_BASE64_H
#define KOTOOLS_CODEC_BASE64_H

#include <cstdint>
#include <string>
#include <vector>
#include <string_view>

namespace kotools::codec {

std::string base64_encode(std::string_view input);
std::string base64_decode(std::string_view input);

// 可选：支持二进制数据
std::string base64_encode(const std::vector<uint8_t>& data);
std::vector<uint8_t> base64_decode_to_bytes(std::string_view input);

}  // namespace kotools::codec

#endif  // !KOTOOLS_CODEC_BASE64_H