#include "kotools/codec/base64.h"

#include <cassert>
#include <iostream>
#include <string>

void test_str(const std::string& str) {
  using namespace kotools::codec::base64;

  auto encoded = encode(str);
  auto decoded = decode(encoded);
  assert(decoded == str);
  if (decoded != str) exit(1);

  auto encoded_nopad = encoded.substr(0, encoded.find('='));
  auto decoded_nopad = decode(encoded_nopad);
  assert(decoded_nopad == str);
  if (decoded_nopad != str) exit(1);
}

int main() {
  test_str("Hello 你好 こんにちは 안녕하세요 Γεια σας Hello 世界");
  test_str("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
  test_str("ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞß");
  test_str("АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюя");
  test_str("ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩαβγδεζηθικλμνξοπρστυφχψω");
  test_str("ｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾛﾜﾝ");
  test_str("あいうえおかるれろわをん");
  test_str("가나다라마바사아자차카타파하");
  test_str("☺♪♫☼♀♂⚡★☆");
  test_str("😀🎵🌍🔍📱💻");
  test_str("ｱｲｳｴｵｶｷｸｹｺｻｼｽｾｿﾀﾁﾂﾃﾄﾅﾆﾇﾈﾉﾊﾋﾌﾍﾎﾏﾐﾑﾒﾓﾔﾕﾖﾗﾘﾛﾜﾝ");
  test_str("Hello مرحبا 世界");
  test_str("ça va?");
  test_str("สวัสดี");
  test_str("שלום");
  return 0;
}
