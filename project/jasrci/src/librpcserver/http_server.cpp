/**
 * @file http_server.cpp
 * @brief HTTP服务器定义
 * @author LiJianfeng
 * @date 2018年10月24日
 */
#include "http_server.h"

#include <cstdlib>
#include <iostream>
#include <sstream>

#include <jsonrpccpp/common/specificationparser.h>

#include "libtool/base_64.h"

using namespace std;
using namespace jsonrpc;
using namespace jasrrpc;

#define BUFFERSIZE 65536

struct mhd_coninfo {
  struct MHD_PostProcessor* postprocessor;
  MHD_Connection* connection;
  stringstream request;
  HttpServer* server;
  int code;
};

HttpServer::HttpServer(int port, int threads):
  AbstractServerConnector(), port_(port), threads_(threads), running_(false),
  daemon_(nullptr) {}

IClientConnectionHandler* HttpServer::getHandler(const std::string& url)
{
  if (nullptr != AbstractServerConnector::GetHandler())
    return AbstractServerConnector::GetHandler();
  map<string, IClientConnectionHandler*>::iterator it =
    this->urlhandler_.find(url);
  if (it != this->urlhandler_.end())
  {
    return it->second;
  }
  return nullptr;
}

bool HttpServer::StartListening()
{
  if (!this->running_)
  {
    const bool has_epoll =
      (MHD_is_feature_supported(MHD_FEATURE_EPOLL) == MHD_YES);
    const bool has_poll =
      (MHD_is_feature_supported(MHD_FEATURE_POLL) == MHD_YES);
    unsigned int mhd_flags = 0;
    if (has_epoll)
// In MHD version 0.9.44 the flag is renamed to
// MHD_USE_EPOLL_INTERNALLY_LINUX_ONLY. In later versions both
// are deprecated.
#if defined(MHD_USE_EPOLL_INTERNALLY)
    mhd_flags = MHD_USE_EPOLL_INTERNALLY;
#else
    mhd_flags = MHD_USE_EPOLL_INTERNALLY_LINUX_ONLY;
#endif
    else if (has_poll)
    {
      mhd_flags = MHD_USE_POLL_INTERNALLY;
    }
    //TODO 支持ssl
    this->daemon_ = MHD_start_daemon(
      mhd_flags, this->port_, nullptr, nullptr, HttpServer::callback, this,
      MHD_OPTION_THREAD_POOL_SIZE, this->threads_, MHD_OPTION_END);
    if (nullptr != this->daemon_)
    {
      this->running_ = true;
    }
  }
  return this->running_;
}

bool HttpServer::StopListening()
{
  if (this->running_)
  {
    MHD_stop_daemon(this->daemon_);
    this->running_ = false;
  }
  return true;
}

bool HttpServer::sendResponse(const string& response, void* add_info)
{
  string encoded_response = encodeWithBase64(
    (const unsigned char*)response.c_str(), response.length());
  struct mhd_coninfo* client_connection =
    static_cast<struct mhd_coninfo*>(add_info);
  struct MHD_Response* result = MHD_create_response_from_buffer(
    encoded_response.size(),
    (void*)encoded_response.c_str(), MHD_RESPMEM_MUST_COPY);

  MHD_add_response_header(result, "Content-Type", "application/json");
  MHD_add_response_header(result, "Access-Control-Allow-Origin", allowed_origin_.c_str());

  int ret = MHD_queue_response(client_connection->connection,
    client_connection->code, result);
  MHD_destroy_response(result);
  return ret == MHD_YES;
}

bool HttpServer::sendOptionsResponse(void* addInfo)
{
  struct mhd_coninfo* client_connection =
    static_cast<struct mhd_coninfo*>(addInfo);
  struct MHD_Response* result =
    MHD_create_response_from_buffer(0, nullptr, MHD_RESPMEM_MUST_COPY);

  MHD_add_response_header(result, "Allow", "POST, OPTIONS");
  MHD_add_response_header(result, "Access-Control-Allow-Origin", allowed_origin_.c_str());
  MHD_add_response_header(result, "Access-Control-Allow-Headers",
    "origin, content-type, accept");
  MHD_add_response_header(result, "DAV", "1");

  int ret = MHD_queue_response(client_connection->connection,
    client_connection->code, result);
  MHD_destroy_response(result);
  return ret == MHD_YES;
}

void HttpServer::setUrlHandler(const string& url,
  IClientConnectionHandler* handler)
{
  this->urlhandler_[url] = handler;
  this->SetHandler(nullptr);
}

int HttpServer::callback(void* cls, MHD_Connection* connection,
  const char* url, const char* method, const char* version,
  const char* upload_data, size_t* upload_data_size,
  void **con_cls)
{
  (void)version;
  if (nullptr == *con_cls)
  {
    struct mhd_coninfo* client_connection = new mhd_coninfo;
    client_connection->connection = connection;
    client_connection->server = static_cast<HttpServer*>(cls);
    *con_cls = client_connection;
    return MHD_YES;
  }
  struct mhd_coninfo* client_connection =
    static_cast<struct mhd_coninfo*>(*con_cls);

  if (string("POST") == method)
  {
    if (0 != *upload_data_size)
    {
      client_connection->request.write(upload_data, *upload_data_size);
      *upload_data_size = 0;
      return MHD_YES;
    }
    else
    {
      string response;
      IClientConnectionHandler* handler =
        client_connection->server->getHandler(string(url));
      // TODO 完善异常返回
      if (nullptr == handler)
      {
        client_connection->code = MHD_HTTP_INTERNAL_SERVER_ERROR;
        client_connection->server->sendResponse(
          "No client connection handler found", client_connection);
      }
      else
      {
        client_connection->code = MHD_HTTP_OK;
        handler->HandleRequest(client_connection->request.str(), response);
        client_connection->server->sendResponse(response, client_connection);
      }
    }
  }
  else if (string("OPTIONS") == method)
  {
    client_connection->code = MHD_HTTP_OK;
    client_connection->server->sendOptionsResponse(client_connection);
  }
  else
  {
    client_connection->code = MHD_HTTP_METHOD_NOT_ALLOWED;
    client_connection->server->sendResponse("Not allowed HTTP Method",
      client_connection);
  }
  delete client_connection;
  *con_cls = nullptr;

  return MHD_YES;
}
