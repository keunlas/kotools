// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#ifndef KOTOOLS_CRYPTO_MD5_H
#define KOTOOLS_CRYPTO_MD5_H

#include <string_view>
#include <vector>

namespace kotools::codec::md5 {

std::vector<char> crypt(const std::string_view& input);

}  // namespace kotools::codec::md5

#endif  // !KOTOOLS_CRYPTO_MD5_H
