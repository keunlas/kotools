// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#ifndef KOTOOLS_CODEC_BASE64_H
#define KOTOOLS_CODEC_BASE64_H

#include <string>
#include <string_view>

namespace kotools::codec {

namespace base64 {

std::string encode(const std::string_view& input);
std::string decode(const std::string_view& input);

}  // namespace base64

}  // namespace kotools::codec

#endif  // !KOTOOLS_CODEC_BASE64_H