#include "kotools/crypto/md5.h"

#include <iostream>
#include <string>

int main() {
  //   std::string to_string(std::vector<uint8_t> raw_md5);
  // std::vector<uint8_t> crypt(std::string_view input);

  using namespace kotools::crypto::md5;

  std::string test1 = "";
  std::string test2 = "hello world";
  std::string test3 = "The quick brown fox jumps over the lazy dog";

  std::cout << "MD5(\"\") = " << to_string(crypt(test1)) << std::endl;
  std::cout << "MD5(\"hello world\") = " << to_string(crypt(test2))
            << std::endl;
  std::cout << "MD5(\"The quick brown fox...\") = " << to_string(crypt(test3))
            << std::endl;
}
