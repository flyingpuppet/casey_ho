/**
 * @file http_server.h
 * @brief HTTP服务器声明
 * @author LiJianfeng
 * @date 2018年10月24日
 */
#pragma once

#include <jsonrpccpp/server/abstractserverconnector.h>

#include <stdarg.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <map>

#include <microhttpd.h>

namespace jasrrpc
{

/**
 * @brief HTTP服务器
 */
class HttpServer: public jsonrpc::AbstractServerConnector
{
public:
  HttpServer(int port, int threads = 50);

  virtual bool StartListening() override;
  virtual bool StopListening() override;

  bool virtual sendResponse(const std::string& response,
    void* add_info = nullptr);
  bool virtual sendOptionsResponse(void* add_info);

  void setAllowedOrigin(const std::string& origin) {allowed_origin_ = origin;}
  const std::string& getAllowedOrigin() const {return allowed_origin_;}

  void setUrlHandler(const std::string& url,
    jsonrpc::IClientConnectionHandler* handler);

private:
  jsonrpc::IClientConnectionHandler* getHandler(const std::string& url);

  static int callback(void* cls, struct MHD_Connection* connection,
    const char* url, const char* method, const char* version, 
    const char* upload_data, size_t* upload_data_size, void** con_cls);

  int port_;
  int threads_;
  bool running_;

  struct MHD_Daemon *daemon_;

  std::map<std::string, jsonrpc::IClientConnectionHandler*> urlhandler_;

  std::string allowed_origin_ = "*";///< 跨域访问
};// HttpServer

}// namespace jasrrpc
