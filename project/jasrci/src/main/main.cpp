/**
 * @file main.cpp
 * @brief main程序
 * @author LiJianfeng
 * @date 2018年10月24日
 */
#include <signal.h>
#include <vector>
#include <iostream>

#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/ini_parser.hpp>

#include "librpcserver/http_server.h"
#include "libjasrrpcserver/jasr_impl.h"
#include "libtool/time_tool.h"
#include "libtool/log.h"

using namespace std;
using namespace boost;
using namespace boost::property_tree;
using namespace jasrrpc;

static bool g_working = true;

/**
 * @brief 配置文件结构
 */
struct Config
{
  int jasrci_port;///< 能力接口监听端口号
  int jasrci_thread_num;///< 能力接口线程数
  string jasrci_uri;///< 能力接口uri路径
  int jasrci_session_max_existence_time;///< 能力接口会话最大持续时间 s
  string jasrs_addr;///< 算法服务器地址

  struct AudioConfig audio_config;
};

/**
 * @brief 显示帮助
 */
void showHelp(void)
{
  cout << "-help | --h\t\tshow help\n" <<
    "-version | --v\t\tshow version\n";
}

/**
 * @brief 显示版本
 */
void showVersion(void)
{
  cout << "JASRCI V1.0 via LiJianfeng\n";
}

/**
 * @brief 读配置文件
 *
 * @param config 配置文件结构
 *
 * @return 是否成功
 */
bool initConfig(struct Config& config)
{
  try
  {
    boost::property_tree::ptree m_pt, jasrci_pt, jasrs_pt;
    read_ini("../conf/jASR_CI.ini", m_pt);
    jasrci_pt = m_pt.get_child("jasrci");
    jasrs_pt = m_pt.get_child("jasrs");
    config.jasrci_port = jasrci_pt.get<int>("port", 9876);
    config.jasrci_thread_num = jasrci_pt.get<int>("thread_num", 50);
    config.jasrci_uri = jasrci_pt.get<string>("uri", "/jasr");
    config.jasrci_session_max_existence_time =
      jasrci_pt.get<int>("session_max_existence_time", 24*60*60);
    config.jasrs_addr = jasrs_pt.get<string>("addr", "127.0.0.1:12000");

    struct AudioConfig audio_config;
    boost::property_tree::ptree c_pt, cdefault_pt;
    read_ini("../conf/jASR_SDK.conf", c_pt);
    cdefault_pt = c_pt.get_child("default");
    audio_config.sample_rate = cdefault_pt.get<int>("sample_rate", 0);
    audio_config.vad_head = cdefault_pt.get<int>("vad_head", 10000);
    audio_config.vad_tail = cdefault_pt.get<int>("vad_tail", 500);
    audio_config.max_seconds = cdefault_pt.get<int>("max_seconds", 30);
    audio_config.audio_format = cdefault_pt.get<int>("audio_format", 6);
    audio_config.vad_threshold = cdefault_pt.get<int>("vad_threshold", 10);
    audio_config.nbest_result = cdefault_pt.get<int>("nbest_result", 0);
    audio_config.add_punc = cdefault_pt.get<int>("add_punc", 1);
    audio_config.stream = cdefault_pt.get<int>("stream", 2);
    audio_config.result_type = cdefault_pt.get<int>("result_type", 0);
    audio_config.mode = cdefault_pt.get<int>("mode", 0);
    audio_config.channel_type = cdefault_pt.get<int>("channel_type", 0);
    audio_config.ft_post_process = cdefault_pt.get<int>("ft_post_process", 0);
    config.audio_config = audio_config;
  }
  catch (const ptree_error&)
  {
    return false;
  }
  return true;
}

/**
 * @brief 停止信号处理器
 *
 * @param signal 信号
 */
void abortSignalHandler(int signal)
{
  //g_working = false;
}

/**
 * @brief 注册信号处理器
 *
 * @return 是否成功
 */
bool registerSingnalHandler()
{
   signal(SIGINT, abortSignalHandler);
   signal(SIGTERM, abortSignalHandler);
   return true;
}

int main(int argc, char** argv)
{
  /* 0、CLI */
  string arg = "";
  for (int i=1; i<argc; ++i)
  {
    arg = argv[i];
    if (("-help"==arg) || "--h"==arg)
    {
      showHelp();
      return 0;
    }
    else if (("-version"==arg) || "--v"==arg)
    {
      showVersion();
      return 0;
    }
    else
    {
      cout << "Bad args.\nType arg \"-help | --h\" for help" << endl;
      return -1;
    }
  }
  /* 1、读配置文件 */
  struct Config config;
  bool flag = initConfig(config);
  if (false == flag)
  {
    LOG4CXX_ERROR(g_log, "Config reading failed.");
    return -1;
  }
  /* 2、初始化日志 */
  // TODO 写入配置文件
  flag = initLog("../conf/jASR_SDK_log.xml", "jASR_SDK");
  if (false == flag)
  {
    LOG4CXX_ERROR(g_log, "Log init failed.");
    return -1;
  }
  /* 3、注册信号处理器 */
  flag = registerSingnalHandler();
  if (false == flag)
  {
    LOG4CXX_ERROR(g_log, "Signal register failed.");
    return -1;
  }
  /* 4、构造HTTP RPC服务器 */
  HttpServer http_server(config.jasrci_port, config.jasrci_thread_num);
  unique_ptr<JAsrRpcServer> jasr(new JAsrImpl(http_server, config.jasrci_uri,
    config.audio_config, config.jasrci_session_max_existence_time));
  /* 5、初始化jAsr */
  flag = jasr->initJAsr(config.jasrs_addr);
  if (false == flag)
  {
    LOG4CXX_ERROR(g_log, "JASR init failed.");
    return -1;
  }
  /* 6、开启HTTP RPC服务器监听 */
  flag = jasr->startListening();
  if (false == flag)
  {
    LOG4CXX_ERROR(g_log, "JASR RPC server startup failed.");
    return -1;
  }
  LOG4CXX_INFO(g_log, "JASR RPC server startup successfully.");

  while (true == g_working) {sleep(1);}

  // TODO 通过RPC控制停止
  jasr->stopListening();
  jasr->endJAsr();
  return 0;
}
