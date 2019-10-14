/**
 * @file log.h
 * @brief 日志声明
 * @author Li Jianfeng
 * @date 2018年10月24日
 */
#include "log.h"

#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>
#include <log4cxx/xml/domconfigurator.h>

using namespace log4cxx;
using namespace log4cxx::helpers;
using namespace log4cxx::xml;

LoggerPtr g_log;

bool initLog(const char* xml_file, const char* logger_name)
{
  DOMConfigurator::configure(xml_file);
  g_log = Logger::getLogger(logger_name);
  return true;
}
