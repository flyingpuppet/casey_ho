/**
 * @file jasr_impl.h
 * @brief 语音识别能力声明
 * @author LiJianfeng
 * @date 2018年10月24日
 */
#pragma once

#include "jasr_rpc_server.h"

#include <map>
#include <set>
#include <thread>
#include <condition_variable>

#include <jsonrpccpp/server.h>
#include <jASR.h>

#include "librpcserver/http_server.h"
#include "libtool/lock.h"
#include "common.h"

namespace jasrrpc
{

struct SessionInfo
{
  jASR_Handle handle;
  std::string engine_type;
  long ctime;
};

typedef std::map<std::string, struct SessionInfo> SessionMap;
typedef std::map<long, std::set<std::string>> TimeCleanningMap;

/**
 * @brief ASR HTTP RPC 服务器业务流
 */
class JAsrImpl: public jasrrpc::JAsrRpcServer
{
public:
  JAsrImpl(HttpServer& server, const std::string& uri,
    const struct AudioConfig& audio_config, int stime);
  ~JAsrImpl();

  bool initJAsr(const std::string& addr) override;
  bool endJAsr() override;

private:
  Json::Value startSession(const Json::Value& request) override;
  Json::Value recognizeStream(const Json::Value& request) override;
  Json::Value stopSession(const Json::Value& request) override;

  struct AudioConfig audio_config_;
  long clean_interval_;
  SharedMutex session_mtx_;
  SessionMap sids_;
  TimeCleanningMap clean_sids_;

  std::thread clean_thread_;
  std::mutex clean_mtx_;
  std::condition_variable clean_cv_;
};// class JAsrImpl

}// namespace jasrrpc
