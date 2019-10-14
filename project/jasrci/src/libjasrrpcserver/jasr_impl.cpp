/**
 * @file jasr_impl.cpp
 * @brief 语音识别能力定义
 * @author LiJianfeng
 * @date 2018年10月24日
 */
#include "jasr_impl.h"

#include <iostream>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "libtool/time_tool.h"
#include "libtool/base_64.h"
#include "libtool/log.h"
#include "error.h"

using namespace std;
using namespace boost;
using namespace boost::uuids;
using namespace jsonrpc;
using namespace jasrrpc;

static const int SID_LENGTH = 12;

JAsrImpl::JAsrImpl(HttpServer& server, const string& uri,
  const struct AudioConfig& audio_config, int stime):
  jasrrpc::JAsrRpcServer(server, uri),
  audio_config_(audio_config),
  clean_interval_(stime)
{
  clean_thread_ = std::thread([=]()
    {
      long next_interval = clean_interval_;
      {// lock
        std::unique_lock<std::mutex> clock(clean_mtx_);
        while (clean_cv_.wait_for(clock, std::chrono::seconds(next_interval))
          == std::cv_status::timeout)
        {// 每次timeout就执行下面的
          long now = getTimeStamp();
          {
            WriteLock lock(session_mtx_);
            for (TimeCleanningMap::iterator titr = clean_sids_.begin();
              titr != clean_sids_.end();)
            {
              if (now >= titr->first)
              {
                for (set<string>::iterator sitr = titr->second.begin();
                  sitr != titr->second.end(); ++sitr)
                {
                  string sid = *sitr;
                  jASR_SessionStop(sids_[sid].handle);
                  sids_.erase(sid);
                  LOG4CXX_INFO(g_log, "Session is automatically released(" + sid + ")");
                }
                clean_sids_.erase(titr++);
              }
              else
              {// 如果存在未过期的就计算新的间隔
                next_interval = titr->first - now;
                break;
              }
            }
            if (true == clean_sids_.empty())
            {// 如果过期的全删完了就重新设置默认间隔
              next_interval = clean_interval_;
            }
          }// unlock write lock
        }// notified but not timeout
      }// unlock condition variable lock

      /* 程序退出前的清理 */
      {// lock
        WriteLock lock(session_mtx_);
        for (SessionMap::iterator sitr = sids_.begin();
          sitr != sids_.end(); ++sitr)
        {
          jASR_SessionStop(sitr->second.handle);
        }
        sids_.clear();
        clean_sids_.clear();
      }//unlock write lock
    }// thread func
  );
}

JAsrImpl::~JAsrImpl()
{
  clean_cv_.notify_all();
  clean_thread_.join();
}

bool JAsrImpl::initJAsr(const string& addr)
{
  jASR_ErrCode err = JASR_ERR_NONE;
  err = jASR_Init(addr.c_str());
  if (err != JASR_ERR_NONE)
  {
    printf("jAsr init failed![%d]\n", err);
    return false;
  }
  return true;
}

bool JAsrImpl::endJAsr()
{
  jASR_ErrCode err = JASR_ERR_NONE;
  err = jASR_End();
  if (err != JASR_ERR_NONE)
  {
    printf("jAsr end failed![%d]\n", err);
    return false;
  }
  return true;
}

Json::Value JAsrImpl::startSession(const Json::Value& request)
{
  try
  {
    string engine_type = "";
    if ((request["engine_type"] == Json::nullValue) ||
      ((engine_type = request["engine_type"].asString()) == ""))
    {
      throw JsonRpcException(ERROR_JASR_NOT_PROVIDED_PARAM,
        "INVALID_PARAM: The param engine_type must be required.");
    }
    else if (ENGINE_TYPE_FREETALK != engine_type)
    {
      throw JsonRpcException(ERROR_JASR_OTHER_PARAM,
        "INVALID_PARAM: The param engine_type is not supported now.");
    }
    jASR_ErrCode err = JASR_ERR_NONE;
    jASR_Handle session = nullptr;
    {
      WriteLock lock(session_mtx_);
      err = jASR_SessionStart(engine_type.c_str(), &session);
    }
    if (err != JASR_ERR_NONE)
    {
      Json::Value jerr(Json::objectValue);
      jerr["err_no"] = err;
      throw JsonRpcException(ERROR_JASR_FROM_SERVER,
        "JASR_ERROR: Session cannot be opened.", jerr);
    }

    SessionInfo session_info;
    session_info.handle = session;
    session_info.engine_type = engine_type;
    session_info.ctime = getTimeStamp() + clean_interval_;
    string sid = "";
    {
      WriteLock lock(session_mtx_);
      do
      {
        boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
        string uuid = boost::uuids::to_string(a_uuid);
        sid = uuid.substr(uuid.length()-SID_LENGTH, uuid.length());
      }while (sids_.find(sid) != sids_.end());

      sids_[sid] = session_info;
      clean_sids_[session_info.ctime].insert(sid);
    }

    LOG4CXX_INFO(g_log, "New session is created(" + sid + ")");

    int vad_head = audio_config_.vad_head;
    int vad_tail = audio_config_.vad_tail;
    int max_seconds = audio_config_.max_seconds;
    int audio_format = audio_config_.audio_format;
    int vad_threshold = audio_config_.vad_threshold;
    int nbest_result = audio_config_.nbest_result;
    int add_punc = audio_config_.add_punc;
    int stream = audio_config_.stream;
    int result_type = audio_config_.result_type;
    int mode = audio_config_.mode;
    int channel_type = audio_config_.channel_type;
    int ft_post_process = audio_config_.ft_post_process;
    if (request["param"] != Json::nullValue)
    {
      Json::Value param = request["param"];
      if (param["vad_head"] != Json::nullValue)
      {
        vad_head = param["vad_head"].asInt();
      }
      if (param["vad_tail"] != Json::nullValue)
      {
        vad_tail = param["vad_tail"].asInt();
      }
      if (param["max_seconds"] != Json::nullValue)
      {
        max_seconds = param["max_seconds"].asInt();
      }
      if (param["audio_format"] != Json::nullValue)
      {
        audio_format = param["audio_format"].asInt();
      }
      if (param["vad_threshold"] != Json::nullValue)
      {
        vad_threshold = param["vad_threshold"].asInt();
      }
      if (param["nbest_result"] != Json::nullValue)
      {
        nbest_result = param["nbest_result"].asInt();
      }
      if (param["add_punc"] != Json::nullValue)
      {
        add_punc = param["add_punc"].asInt();
      }
      if (param["stream"] != Json::nullValue)
      {
        stream = param["stream"].asInt();
      }
      if (param["result_type"] != Json::nullValue)
      {
        result_type = param["result_type"].asInt();
      }
      if (param["mode"] != Json::nullValue)
      {
        mode = param["mode"].asInt();
      }
      if (param["channel_type"] != Json::nullValue)
      {
        channel_type = param["channel_type"].asInt();
      }
      if (param["ft_post_process"] != Json::nullValue)
      {
        ft_post_process = param["ft_post_process"].asInt();
      }
    }
  
    jASR_SetParam(session, JASR_PARAM_VAD_HEAD,
      (jASR_ParamValue)(vad_head));
    jASR_SetParam(session, JASR_PARAM_VAD_TAIL,
      (jASR_ParamValue)(vad_tail));
    jASR_SetParam(session, JASR_PARAM_MAX_SECONDS,
      (jASR_ParamValue)(max_seconds));
    jASR_SetParam(session, JASR_PARAM_AUDIOFORMAT,
      (jASR_ParamValue)(audio_format));
    jASR_SetParam(session, JASR_PARAM_VAD_THRESHOLD,
      (jASR_ParamValue)(vad_threshold));
    if (ENGINE_TYPE_GRAMMAR == engine_type)
    {
      jASR_SetParam(session, JASR_PARAM_NBEST_RESULT,
        (jASR_ParamValue)(nbest_result));
    }
    if ((ENGINE_TYPE_FREETALK == engine_type) ||
      (ENGINE_TYPE_ANALYSIS == engine_type))
    {
      jASR_SetParam(session, JASR_PARAM_ADD_PUNC,
        (jASR_ParamValue)(add_punc));
    }
    if ((ENGINE_TYPE_FREETALK == engine_type) ||
      (ENGINE_TYPE_GRAMMAR == engine_type) ||
      (ENGINE_TYPE_KEYWORDSPOT == engine_type))
    {
      jASR_SetParam(session, JASR_PARAM_STREAM,
        (jASR_ParamValue)(stream));
    }
    if ((ENGINE_TYPE_FREETALK == engine_type) ||
      (ENGINE_TYPE_ANALYSIS == engine_type))
    {
      jASR_SetParam(session, JASR_PARAM_RESULT_TYPE,
        (jASR_ParamValue)(result_type));
    }
    if (ENGINE_TYPE_ANALYSIS == engine_type)
    {
      jASR_SetParam(session, JASR_PARAM_MODE,
        (jASR_ParamValue)(mode));
      jASR_SetParam(session, JASR_PARAM_CHANNEL_TYPE,
        (jASR_ParamValue)(channel_type));
    }
    if ((ENGINE_TYPE_FREETALK == engine_type) &&
      (ft_post_process != JASR_FT_POST_PROCESS_NONE))
    {
       jASR_SetParam(session, JASR_PARAM_FT_POST_PROCESS,
        (jASR_ParamValue)(ft_post_process));
    }

    Json::Value ret(Json::objectValue);
    ret["sid"] = sid;
    return ret;
  }
  catch (const std::runtime_error&)
  {
    throw JsonRpcException(ERROR_JASR_NONE_CONVERTIBLE_PARAM,
      "INVALID_PARAM: The param format is wrong.");
  }
}

Json::Value JAsrImpl::recognizeStream(const Json::Value& request)
{
  try
  {
    string sid = "";
    if ((request["sid"] == Json::nullValue) ||
      ((sid = request["sid"].asString()) == ""))
    {
      throw JsonRpcException(ERROR_JASR_NOT_PROVIDED_PARAM,
        "INVALID_PARAM: The param sid must be required.");
    }
    int is_last = 0;
    if (request["is_last"] != Json::nullValue)
    {
      is_last = request["is_last"].asInt();
    }
    if ((0 != is_last) && (1 != is_last))
    {
      throw JsonRpcException(ERROR_JASR_OTHER_PARAM,
        "INVALID_PARAM: The param is_last is wrong.");
    }
    string data = "";
    if ((request["data"] == Json::nullValue) ||
      ((data = request["data"].asString()) == ""))
    {
      if (is_last == 0)
      {
        throw JsonRpcException(ERROR_JASR_OTHER_PARAM,
          "INVALID_PARAM: The param data or is_last is wrong.");
      }
    }
    string decoded_data = decodeWithBase64(data.c_str(), data.length());
    jASR_Handle found_session = nullptr;
    string found_engine_type = "";
    {
      ReadLock lock(session_mtx_);
      SessionMap::iterator sitr = sids_.find(sid);
      if (sitr != sids_.end())
      {
        found_session = sitr->second.handle;
        found_engine_type = sitr->second.engine_type;
      }
      else
      {
        throw JsonRpcException(ERROR_JASR_NONE_SESSION,
          "JASR_ERROR: Session corresponding cannot be found.");
      }
    }// unlock read lock

    jASR_RecogStatus status;
    jASR_ErrCode err = JASR_ERR_NONE;
    int ret_stream = JASR_STREAM_CONTINUE;
    jASR_GetParam(found_session, JASR_PARAM_STREAM,
      (jASR_ParamValue*)&ret_stream);
    if (ENGINE_TYPE_FREETALK == found_engine_type)
    {
      if (JASR_STREAM_NO == ret_stream)
      {
        if ("" != decoded_data)// 非流式识别忽略is_last参数
        {
          err = jASR_RecognizeStream(found_session,
            (char*)decoded_data.c_str(),
            decoded_data.length(), 1, &status);
        }
        else
        {
          throw JsonRpcException(ERROR_JASR_OTHER_PARAM,
            "INVALID_PARAM: The param data is null while not using stream.");
        }
      }// not stream
      else
      {
        if (("" != decoded_data) && (0 == is_last))
        {
          err = jASR_RecognizeStream(found_session,
            (char*)decoded_data.c_str(),
            decoded_data.length(), 0, &status);
        }
        else if (("" == decoded_data) && (1 == is_last))
        {
          err = jASR_RecognizeStream(found_session, nullptr, 0, 1, &status);
        }
        else
        {
          throw JsonRpcException(ERROR_JASR_OTHER_PARAM,
            "INVALID_PARAM: The param data or is_last is wrong while using stream.");
        }
      }// stream
    }// freetalk
    else// 当前只支持freetalk不可能走到这里
    {}

    if (err != JASR_ERR_NONE)
    {
      Json::Value jerr(Json::objectValue);
      jerr["err_no"] = err;
      throw JsonRpcException(ERROR_JASR_FROM_SERVER,
        "JASR_ERROR: Stream cannot be recognized.", jerr);
    }
    if (status & JASR_RECOG_STATUS_HAS_RESULT)
    {
      jASR_RecogResult* result = nullptr;
      err = jASR_GetRecogResult(found_session, &result);
      if (err != JASR_ERR_NONE)
      {
        Json::Value jerr(Json::objectValue);
        jerr["err_no"] = err;
        throw JsonRpcException(ERROR_JASR_FROM_SERVER,
          "JASR_ERROR: Result cannot be obtained.", jerr);
      }
      string tmp_result = "";
      int best = -1;
      Json::Value final_result(Json::arrayValue);
      Json::Value start_time(Json::arrayValue);
      Json::Value end_time(Json::arrayValue);
      switch(result->nEngineType)
      {
        case JASR_ENGINE_FREETALK:
        {
          jASR_Freetalk_Result& res = result->sFreetalkResult;
          for (int i = 0; i < res.nSegmentCount; ++i)
          {
            // 识别结果中每一分段的结果seg
            jASR_Freetalk_Segment& seg = res.pSegmentList[i];
            tmp_result = "";
            best = -1;
            for (int j = 0; j < seg.nResultCount; ++j)
            {
              // 识别候选结果列表
              if (best < seg.pSentenceResults[j].nScore)
              {
                best = seg.pSentenceResults[j].nScore;
                tmp_result = seg.pSentenceResults[j].pszText;
              }
            }
            LOG4CXX_INFO(g_log, "Recog result: " + tmp_result + "(" + sid + ")");
            final_result.append(tmp_result);
            start_time.append(seg.nStartTime);
            end_time.append(seg.nEndTime);
          }// segs
          break;
        }// freetalk
        default:
        {// 一般不会出现此错误
          throw JsonRpcException(ERROR_JASR_FROM_SERVER,
            "INVALID_RESULT: The result engine_type does not match.");
        }
      }// switch
      jASR_FreeRecogResult(found_session, &result);

      Json::Value ret(Json::objectValue);
      ret["sid"] = sid;
      ret["result"] = final_result;
      ret["start_time"] = start_time;
      ret["end_time"] = end_time;
      return ret;
    }// JASR_RECOG_STATUS_HAS_RESULT
    else 
    {
      Json::Value ret(Json::objectValue);
      ret["sid"] = sid;
      ret["result"] = Json::nullValue;
      ret["start_time"] = Json::nullValue;
      ret["end_time"] = Json::nullValue;
      return ret;
    }
  }
  catch (const std::runtime_error&)
  {
    throw JsonRpcException(ERROR_JASR_NONE_CONVERTIBLE_PARAM,
      "INVALID_PARAM: The param format is wrong.");
  }
}

Json::Value JAsrImpl::stopSession(const Json::Value& request)
{
  try
  {
    string sid = "";
    if ((request["sid"] == Json::nullValue) ||
      ((sid = request["sid"].asString()) == ""))
    {
      throw JsonRpcException(ERROR_JASR_NOT_PROVIDED_PARAM,
        "INVALID_PARAM: The param sid must be required.");
    }
    bool found = false;
    Json::Value ret(Json::objectValue);
    {
      WriteLock lock(session_mtx_);
      SessionMap::iterator sitr = sids_.find(sid);
      if (sitr != sids_.end())
      {
        jASR_SessionStop(sitr->second.handle);
        long ctime = sitr->second.ctime;
        clean_sids_[ctime].erase(sid);
        if (true == clean_sids_[ctime].empty())
        {
          clean_sids_.erase(ctime);
        }
        sids_.erase(sitr);
        found = true;
      }
    }
    if (true == found)
    {
      LOG4CXX_INFO(g_log, "Session is manually released(" + sid + ")");
      ret["sid"] = sid;
      ret["call_result"] = "Successfully. Session is closed.";
    }
    else
    {
      ret["sid"] = sid;
      ret["call_result"] = "Failed. Session does not exist.";
    }
    return ret;
  }
  catch (const std::runtime_error&)
  {
    throw JsonRpcException(ERROR_JASR_NONE_CONVERTIBLE_PARAM,
      "INVALID_PARAM: The param format is wrong.");
  }
}
