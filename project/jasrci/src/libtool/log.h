/**
 * @file log.h
 * @brief 日志声明
 * @author Li Jianfeng
 * @date 2018年10月24日
 */
#pragma once

#include <log4cxx/logger.h>

extern log4cxx::LoggerPtr g_log;

/**
 * @brief 初始化日志
 *
 * @param xml_file 日志配置文件
 * @param logger_name 日志名
 *
 * @return 是否成功
 */
extern bool initLog(const char* xml_file, const char* logger_name);
