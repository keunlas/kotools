// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#ifndef KOTOOLS_CRYPTO_MD5_H
#define KOTOOLS_CRYPTO_MD5_H

#include <cstdint>
#include <string_view>
#include <vector>

namespace kotools::crypto::md5 {

std::string to_string(std::vector<uint8_t> raw_md5);
std::vector<uint8_t> crypt(std::string_view input);

}  // namespace kotools::crypto::md5

#endif  // !KOTOOLS_CRYPTO_MD5_H
