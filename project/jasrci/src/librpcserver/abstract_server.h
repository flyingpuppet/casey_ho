/**
 * @file asr_capability_interface.h
 * @brief RPC服务端声明，修改自libjsonrpccpp
 * @author LiJianfeng
 * @date 2018年10月24日
 */
#pragma once

#include <map>
#include <string>
#include <vector>

#include <jsonrpccpp/common/procedure.h>
#include <jsonrpccpp/server/abstractserverconnector.h>
#include <jsonrpccpp/server/iprocedureinvokationhandler.h>
#include <jsonrpccpp/server/iclientconnectionhandler.h>
#include <jsonrpccpp/server/requesthandlerfactory.h>

#include "http_server.h"

namespace jasrrpc
{

/**
 * @brief HTTP RPC服务器
 */
template<class S>
class AbstractServer: public jsonrpc::IProcedureInvokationHandler
{
public:
  typedef void(S::*methodPointer_t)
    (const Json::Value& parameter, Json::Value& result);
  typedef void(S::*notificationPointer_t)
    (const Json::Value& parameter);

  AbstractServer(jasrrpc::HttpServer& connector, const std::string& uri,
    jsonrpc::serverVersion_t type = jsonrpc::JSONRPC_SERVER_V2):
    connection_(connector)
  {
    handler_ = jsonrpc::RequestHandlerFactory::createProtocolHandler(type,
      *this);
    connector.setUrlHandler(uri, this->handler_);
  }

  virtual ~AbstractServer()
  {
    delete this->handler_;
  }

  bool startListening()
  {
    return connection_.StartListening();
  }

  bool stopListening()
  {
    return connection_.StopListening();
  }

  virtual void HandleMethodCall(jsonrpc::Procedure& proc,
    const Json::Value& input, Json::Value& output) override
  {
    S* instance = dynamic_cast<S*>(this);
    (instance->*methods_[proc.GetProcedureName()])(input, output);
  }

  virtual void HandleNotificationCall(jsonrpc::Procedure& proc,
    const Json::Value& input) override
  {
    S* instance = dynamic_cast<S*>(this);
    (instance->*notifications_[proc.GetProcedureName()])(input);
  }

protected:
  bool bindAndAddMethod(const jsonrpc::Procedure& proc,
    methodPointer_t pointer)
  {
    if(proc.GetProcedureType() == jsonrpc::RPC_METHOD &&
      !this->symbolExists(proc.GetProcedureName()))
    {
      this->handler_->AddProcedure(proc);
      this->methods_[proc.GetProcedureName()] = pointer;
      return true;
    }
    return false;
  }

  bool bindAndAddNotification(const jsonrpc::Procedure& proc,
    notificationPointer_t pointer)
  {
    if(proc.GetProcedureType() == jsonrpc::RPC_NOTIFICATION &&
      !this->symbolExists(proc.GetProcedureName()))
    {
      this->handler_->AddProcedure(proc);
      this->notifications_[proc.GetProcedureName()] = pointer;
      return true;
    }
    return false;
  }

private:
  bool symbolExists(const std::string& name)
  {
    if (methods_.find(name) != methods_.end())
      return true;
    if (notifications_.find(name) != notifications_.end())
      return true;
    return false;
  }

  jsonrpc::AbstractServerConnector& connection_;
  jsonrpc::IProtocolHandler* handler_;
  std::map<std::string, methodPointer_t> methods_;
  std::map<std::string, notificationPointer_t> notifications_;
};// class AbstractServer

}// namespace jasrrpc
