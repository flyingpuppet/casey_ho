/**
 * @file time_tool.h
 * @brief 时间工具
 * @author LiJianfeng
 * @date 2018年08月06日
 */
#pragma once

#include <chrono>
#include <string>

/**
 * @brief 获取当前时间戳
 *
 * @return 当前时间戳
 */
extern std::string getLocalTime();

/**
 * @brief 获取当前时间戳
 *
 * @return 当前时间戳
 */
extern long getTimeStamp();

/**
 * @brief 计时器
 */
class Timer
{
public:
  Timer(){restart();}

  /**
   * @brief 获取计时结果
   *
   * @return 计时结果
   */
  double elapsed() const
  {
    // seconds
    return std::chrono::duration_cast<std::chrono::microseconds>(duration()).count() / 1000000.0;
  }
  /**
   * @brief 重置计时器
   */
  void restart()
  {
    time_point_ = std::chrono::high_resolution_clock::now();
  }

private:
  std::chrono::high_resolution_clock::duration duration() const 
  {
    return std::chrono::high_resolution_clock::now() - time_point_;
  }

  std::chrono::high_resolution_clock::time_point time_point_;
};// class Timer
