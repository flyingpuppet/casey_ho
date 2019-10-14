/**
 * @file base_64.h
 * @brief Base64编解码器声明
 * @author Internet
 * @date 2018年08月06日
 */
#pragma once

#include <string>
#include <iostream>
#include <cstring>

#define BASE_64_TABLE "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
#define BASE_64_PAD '='

/**
 * @brief Base64编码
 *
 * @param str 待编码字符串
 * @param length 待编码字符串长度
 *
 * @return 编码后字符串
 */
extern std::string encodeWithBase64(const unsigned char* str, int length);

/**
 * @brief Base64解码
 *
 * @param str 待解码字符串
 * @param length 待解码字符串长度
 *
 * @return 解码后字符串
 */
extern std::string decodeWithBase64(const char* str, int length);
