// Distributed under the MIT License that can be found in the LICENSE file.
// https://github.com/keunlas/kotools
//
// Author: Keunlas <keunlaz at gmail dot com>

#include "kotools/crypto/md5.h"

#include <array>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace {

// 初始化向量 (小端序)
constexpr uint32_t A = 0x67452301;
constexpr uint32_t B = 0xEFCDAB89;
constexpr uint32_t C = 0x98BADCFE;
constexpr uint32_t D = 0x10325476;

// 正弦函数常量表 T[1..64]
constexpr std::array<uint32_t, 64> T = {
    0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE, 0xF57C0FAF, 0x4787C62A,
    0xA8304613, 0xFD469501, 0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE,
    0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821, 0xF61E2562, 0xC040B340,
    0x265E5A51, 0xE9B6C7AA, 0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8,
    0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED, 0xA9E3E905, 0xFCEFA3F8,
    0x676F02D9, 0x8D2A4C8A, 0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C,
    0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70, 0x289B7EC6, 0xEAA127FA,
    0xD4EF3085, 0x04881D05, 0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665,
    0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039, 0x655B59C3, 0x8F0CCC92,
    0xFFEFF47D, 0x85845DD1, 0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1,
    0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391};

// 循环左移位数表
constexpr std::array<uint32_t, 64> S = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

// 循环左移
constexpr uint32_t left_rotate(uint32_t x, uint32_t n) {
  return (x << n) | (x >> (32 - n));
}

// 四轮非线性函数
uint32_t F(uint32_t x, uint32_t y, uint32_t z) { return (x & y) | (~x & z); }
uint32_t G(uint32_t x, uint32_t y, uint32_t z) { return (x & z) | (y & ~z); }
uint32_t H(uint32_t x, uint32_t y, uint32_t z) { return x ^ y ^ z; }
uint32_t I(uint32_t x, uint32_t y, uint32_t z) { return y ^ (x | ~z); }

// 字节序转换 (小端序)
constexpr uint32_t to_little_endian(uint32_t value) {
  return ((value & 0xFF) << 24) | ((value & 0xFF00) << 8) |
         ((value & 0xFF0000) >> 8) | ((value & 0xFF000000) >> 24);
}

std::vector<uint8_t> pad_message(std::string_view message) {
  std::vector<uint8_t> padded(message.begin(), message.end());

  // 步骤1: 添加一个 '1' 位 (0x80)
  padded.push_back(0x80);

  // 步骤2: 填充 '0' 位直到长度 ≡ 448 (mod 512)
  while ((padded.size() % 64) != 56) {
    padded.push_back(0x00);
  }

  // 步骤3: 添加原始消息长度 (64位，小端序)
  uint64_t originalBits = message.length() * 8;

  for (int i = 0; i < 8; i++) {
    padded.push_back((originalBits >> (i * 8)) & 0xFF);
  }

  return padded;
}

class MD5_impl {
 public:
  void process_block(const uint8_t block[64]) {
    uint32_t M[16];

    // 将512位块分为16个32位字
    for (int i = 0; i < 16; i++) {
      M[i] = (block[i * 4]) | (block[i * 4 + 1] << 8) |
             (block[i * 4 + 2] << 16) | (block[i * 4 + 3] << 24);
    }

    uint32_t AA = A_, BB = B_, CC = C_, DD = D_;

    // 64轮操作
    for (int i = 0; i < 64; i++) {
      uint32_t F_result, g;

      if (i < 16) {
        F_result = F(B_, C_, D_);
        g = i;
      } else if (i < 32) {
        F_result = G(B_, C_, D_);
        g = (5 * i + 1) % 16;
      } else if (i < 48) {
        F_result = H(B_, C_, D_);
        g = (3 * i + 5) % 16;
      } else {
        F_result = I(B_, C_, D_);
        g = (7 * i) % 16;
      }

      F_result = F_result + A_ + T[i] + M[g];
      A_ = D_;
      D_ = C_;
      C_ = B_;
      B_ = B_ + left_rotate(F_result, S[i]);
    }

    // 更新状态
    A_ += AA;
    B_ += BB;
    C_ += CC;
    D_ += DD;
  }

  std::vector<uint8_t> compute(std::string_view message) {
    // 数据填充
    std::vector<uint8_t> padded = pad_message(message);

    // 处理每个512位块
    for (size_t i = 0; i < padded.size(); i += 64) {
      process_block(&padded[i]);
    }

    // 小端序转大端序输出
    std::vector<uint8_t> result;
    result.push_back(to_little_endian(A_));
    result.push_back(to_little_endian(B_));
    result.push_back(to_little_endian(C_));
    result.push_back(to_little_endian(D_));
    return result;
  }

 private:
  uint32_t A_{A};
  uint32_t B_{B};
  uint32_t C_{C};
  uint32_t D_{D};
};

}  // namespace

namespace kotools::crypto::md5 {

std::vector<uint8_t> crypt(std::string_view input) {
  MD5_impl tmp;
  return tmp.compute(input);
}

std::string to_string(std::vector<uint8_t> raw_md5) {
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  for (auto&& item : raw_md5) {
    ss << std::setw(8) << item;
  }
  return ss.str();
}

}  // namespace kotools::crypto::md5
