/**
 * @file lock.h
 * @brief 锁声明
 * @author Li Jianfeng
 * @date 2018年10月24日
 */
#pragma once

#include <boost/thread.hpp>

using SharedMutex = boost::shared_mutex;
using ReadLock = boost::shared_lock<boost::shared_mutex>;
using WriteLock = boost::unique_lock<boost::shared_mutex>;
using ConditionVariable = boost::condition_variable;
