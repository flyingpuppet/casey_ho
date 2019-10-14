/**
 * @file base_64.cpp
 * @brief Base64编解码器定义
 * @author Internet
 * @date 2018年08月06日
 */
#include "base_64.h"

std::string encodeWithBase64(const unsigned char* str, int bytes)
{
  std::string encode_result;
  const unsigned char * current;
  current = str;
  while (bytes > 2)
  {
    encode_result += BASE_64_TABLE[current[0] >> 2];
    encode_result += BASE_64_TABLE[((current[0] & 0x03) << 4) +
      (current[1] >> 4)];
    encode_result += BASE_64_TABLE[((current[1] & 0x0f) << 2) +
      (current[2] >> 6)];
    encode_result += BASE_64_TABLE[current[2] & 0x3f];
    
    current += 3;
    bytes -= 3;
  }
  if (bytes > 0)
  {
    encode_result += BASE_64_TABLE[current[0] >> 2];
    if (1 == bytes%3)
    {
      encode_result += BASE_64_TABLE[(current[0] & 0x03) << 4];
      encode_result += "==";
    }
    else if (2 == bytes%3) 
    {
      encode_result += BASE_64_TABLE[((current[0] & 0x03) << 4) +
        (current[1] >> 4)];
      encode_result += BASE_64_TABLE[(current[1] & 0x0f) << 2];
      encode_result += "=";
    }
  }
  return encode_result;
}

std::string decodeWithBase64(const char* str, int length) 
{
  // 解码表
  const char DecodeTable[] =
  {
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -1, -2, -2, -1, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 62, -2, -2, -2, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -2, -2, -2, -2, -2, -2,
    -2,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -2, -2, -2, -2, -2,
    -2, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2,
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2
  };
  int bin = 0,i=0;
  std::string decode_result;
  const char *current = str;
  char ch;
  while ((ch = *current++) != '\0' && length-- > 0)
  {
    if (ch == BASE_64_PAD)
    { // 当前一个字符是“=”号
      if (*current != '=' && 1 == (i % 4)) 
      {
        return NULL;
      }
      continue;
    }
    ch = DecodeTable[ch];
    if (ch < 0 )
    { /* 空格或其他分隔符跳过 */
      continue;
    }
    switch (i % 4)
    {
    case 0:
      bin = ch << 2;
      break;
    case 1:
      bin |= ch >> 4;
      decode_result += bin;
      bin = ( ch & 0x0f ) << 4;
      break;
    case 2:
      bin |= ch >> 2;
      decode_result += bin;
      bin = ( ch & 0x03 ) << 6;
      break;
    case 3:
      bin |= ch;
      decode_result += bin;
      break;
    }
    i++;
  }
  return decode_result;
}
