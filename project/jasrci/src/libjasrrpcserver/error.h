/**
 * @file error.h
 * @brief 自定义错误声明
 * @author LiJianfeng
 * @date 2018年10月24日
 */
#pragma once

namespace jasrrpc
{

enum JasrErrors
{
  ERROR_JASR_NOT_PROVIDED_PARAM = -32060,///< 客户端未提供关键参数
  ERROR_JASR_NONE_CONVERTIBLE_PARAM = -32061,///< 客户端提供参数解析错误，例如，应该是string，客户端传来int
  ERROR_JASR_OTHER_PARAM = -32062,///< 客户端提供逻辑错误的参数，例如，应该是1，客户端传来0

  ERROR_JASR_FROM_SERVER = -32071,///< 请求算法服务器返回错误，此错误一般需要附加服务端返回值等

  ERROR_JASR_NONE_SESSION = -32081///< 未找到已开启的会话
};// enum JasrErrors

}// namespace jasrrpc
