/**
 * @file time_tool.cpp
 * @brief 时间工具
 * @author LiJianfeng
 * @date 2018年08月06日
 */
#include <sys/time.h>
#include <iostream>

using namespace std;

string getLocalTime()
{
  char buf[22];
  struct timeval tv;
  gettimeofday(&tv, NULL);  
  strftime(buf, sizeof(buf)-1, "%Y-%m-%d %H:%M:%S", localtime(&tv.tv_sec));
  return buf;
}

long getTimeStamp()
{
  char buf[17];
  struct timeval tv;
  gettimeofday(&tv, NULL);  
  strftime(buf, sizeof(buf)-1, "%Y%m%d%H%M%S", localtime(&tv.tv_sec));
  return atol(buf);
}
