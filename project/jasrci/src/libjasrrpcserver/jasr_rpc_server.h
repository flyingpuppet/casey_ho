/**
 * @file jasr_rpc_server.h
 * @brief 语音识别能力接口声明
 * @author LiJianfeng
 * @date 2018年10月24日
 */
#pragma once

#include "librpcserver/abstract_server.h"

#include <jsonrpccpp/server.h>

#include "librpcserver/http_server.h"

namespace jasrrpc
{

/**
 * @brief JASR HTTP RPC 服务器
 */
class JAsrRpcServer: public jasrrpc::AbstractServer<JAsrRpcServer>
{
public:
  JAsrRpcServer(HttpServer& server, const std::string& uri):
    AbstractServer<JAsrRpcServer>(server, uri)
  {
    this->bindAndAddMethod(
      jsonrpc::Procedure("startSession",
        jsonrpc::PARAMS_BY_POSITION,
        jsonrpc::JSON_OBJECT,
        "param1", jsonrpc::JSON_OBJECT,
        nullptr),
      &JAsrRpcServer::startSessionI);

    this->bindAndAddMethod(
      jsonrpc::Procedure("recognizeStream",
        jsonrpc::PARAMS_BY_POSITION,
        jsonrpc::JSON_OBJECT,
        "param1", jsonrpc::JSON_OBJECT,
        nullptr),
      &JAsrRpcServer::recognizeStreamI);

    this->bindAndAddMethod(
      jsonrpc::Procedure("stopSession",
        jsonrpc::PARAMS_BY_POSITION,
        jsonrpc::JSON_OBJECT,
        "param1", jsonrpc::JSON_OBJECT,
        nullptr),
      &JAsrRpcServer::stopSessionI);
  }

  virtual bool initJAsr(const std::string& addr) = 0;
  virtual bool endJAsr() = 0;

protected:
  void startSessionI(const Json::Value& request, Json::Value& response)
  {
    response = startSession(request[0u]);
  }

  void recognizeStreamI(const Json::Value& request, Json::Value& response)
  {
    response = recognizeStream(request[0u]);
  }

  void stopSessionI(const Json::Value& request, Json::Value& response)
  {
    response = stopSession(request[0u]);
  }

  virtual Json::Value startSession(const Json::Value& request) = 0;
  virtual Json::Value recognizeStream(const Json::Value& request) = 0;
  virtual Json::Value stopSession(const Json::Value& request) = 0;
};// class JAsrRpcServer

}// namespace jasrrpc
