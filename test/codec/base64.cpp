#include "kotools/codec/base64.h"

#include <iostream>

int main() {
  using namespace kotools::codec::base64;

  auto encoded = encode("1234567890");
  std::cout << encoded << std::endl;
  std::cout << decode(encoded) << std::endl << std::endl;

  encoded = encode("123qwesadewqe");
  std::cout << encoded << std::endl;
  std::cout << decode(encoded) << std::endl << std::endl;

  std::cout << decode("123#") << std::endl << std::endl;

  return 0;
}
