/**
 * @file common.h
 * @brief 通用结构声明
 * @author LiJianfeng
 * @date 2018年10月24日
 */
#pragma once

namespace jasrrpc
{

#define ENGINE_TYPE_FREETALK "freetalk"///< 自由说识别
#define ENGINE_TYPE_GRAMMAR "grammar"///< 语法识别
#define ENGINE_TYPE_KEYWORDSPOT "keywordspot"///< 关键词检出
#define ENGINE_TYPE_ANALYSIS "analysis"///< 质检分析

/**
 * @brief 音频配置
 */
struct AudioConfig
{
  unsigned int sample_rate;///< 采样率
  unsigned int vad_head;///< 静音检测头部参数
  unsigned int vad_tail;///< 静音检测尾部参数
  unsigned int max_seconds;///< 最大的声音长度
  unsigned int audio_format;///< 音频格式
  unsigned int vad_threshold;///< 起始端点检测灵敏度
 
  // 支持grm
  unsigned int nbest_result;///<是否输出多个候选结果 

  // 支持ft, sa
  unsigned int add_punc;///< 是否加标点
 
  // 支持ft, kws, grm
  unsigned int stream;///< 是否流式识别
 
  // 支持ft, sa
  unsigned int result_type;///< 输出结果类型
 
  // 支持sa
  unsigned int mode;///< 分析处理模式
  unsigned int channel_type;///< 声道参数

  // 支持ft
  unsigned int ft_post_process;///< 文本后处理
};

}// namespace jasrrpc
