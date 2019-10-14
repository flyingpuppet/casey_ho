#ifndef __JASR_SDK_H__
#define __JASR_SDK_H__

/*************************************************************************************
注意：jASR sdk编译时未对变量字节对齐作特殊设置；因此用户编译时若修改变量字节对齐方式，需要保证jASR.h头文件使用编译器默认的字节对齐条件进行编译
**************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#define JASRAPI __stdcall 
#else
#define JASRAPI
#endif

#ifdef _MSC_VER 
//not #if defined(_WIN32) || defined(_WIN64) because we have strncasecmp in mingw
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif
/*************************************************************************************
                        枚举类型
**************************************************************************************/
/** @defgroup 错误码定义 */
/* @{ */

/**
* @brief 错误代码定义
*/
typedef enum _jASR_ErrCode
{
    JASR_ERR_NONE,								///< 0 无错误

    JASR_ERR_PARAM_INVALID,						///< 1 参数无效
    JASR_ERR_NOT_SUPPORT,						///< 2 不支持

    JASR_ERR_NOT_INIT,							///< 3 未初始化
    JASR_ERR_ALREADY_INIT,						///< 4 已初始化
    JASR_ERR_INIT_FAILED,						///< 5 初始化失败

    JASR_ERR_CAPABILITY_NOT_EXIST,				///< 6 能力不存在
    JASR_ERR_CAPABILITY_PRELOAD_FAILED,			///< 7 预加载失败
    JASR_ERR_CAPABILITY_ALREADY_LOAD,			///< 8 能力重复加载

    JASR_ERR_SESSION_INVALID,					///< 9 Session无效
    JASR_ERR_SESSION_START_FAILED,				///< 10 启动Session失败
    JASR_ERR_SESSION_STOP_FAILED,				///< 11 停止Session失败

    JASR_ERR_NO_VOICE_INPUT,					///< 12 数据段头部静音长度超过设置值
    JASR_ERR_RECOG_FAILED,						///< 13 识别失败
    JASR_ERR_RESULT_NOT_FREE,					///< 14 还有识别结果未释放,识别失败
    JASR_ERR_GET_RECOG_RESULT_FAILED,			///< 15 获取识别结果失败
    JASR_ERR_FREE_RECOG_RESULT_FAILED,			///< 16 释放识别结果失败

    JASR_ERR_LOAD_RESOURCE_FAILED,				///< 17 加载资源失败
    JASR_ERR_UNLOAD_RESOURCE_FAILED,			///< 18 卸载资源失败

    JASR_ERR_ACTIVE_RESOURCE_FAILED,			///< 19 激活资源失败
    JASR_ERR_DEACTIVE_RESOURCE_FAILED,			///< 20 反激活资源失败

    JASR_ERR_GET_PARAM_FAILED,			        ///< 21 获取参数设置失败
    JASR_ERR_SET_PARAM_FAILED,			        ///< 22 设置参数失败

    JASR_ERR_ENGINE_FAILED,                    ///< 23 引擎错误

    JASR_ERR_OPENFILE,                         ///< 24 打开文件失败
    JASR_ERR_MEMORY,                           ///< 25 内存错误

    JASR_ERR_LICENSE,                          ///< 26 授权错误
    JASR_ERR_LICENSE_FULL,                     ///< 27 授权已满
    JASR_ERR_LICENSE_EXPIRED,                  ///< 28 授权过期

    JASR_ERR_ACTIVE_SESSION_EXIST,				///< 29 还有会话未停止
    JASR_ERR_RESOURCE_NEED_UNLOAD,				///< 30 还有资源未卸载
    JASR_ERR_RESOURCE_NEED_DEACTIVE,			///< 31 还有资源需要反激活

    // 网络相关,客户端才会返回的错误
    JASR_ERR_NETWORK_FAILED,					///< 32 网络连接异常,如连接服务器失败或超时
    JASR_ERR_REALTIME_SESSION_TIMEOUT,			///< 33 实时识别时,两次识别时间间隔超过限制,实时识别中断
    JASR_ERR_ALL_SESSION_BUSY,					///< 34 服务器端所有会话都在使用中,无法处理本次请求

    JASR_ERR_LSB_QUERYCU,                      ///< 35 访问负载获取可用服务器失败,需要重试链接
    JASR_ERR_ENV_NOT_FOUND,					    ///< 36 环境变量(HCICLOUD_HOME)未设置
    JASR_ERR_ENV_NOT_VALID,					    ///< 37 环境变量(HCICLOUD_HOME)无效


    JASR_ERR_UNKNOWN = 100,					     ///< 100 未知错误
}jASR_ErrCode;									

/* @} */


typedef void * jASR_Handle;        		///< 会话句柄类型定义

/*************************************************************************************
                                识别能力列表
**************************************************************************************/
/** @defgroup 识别能力结构 */
/* @{ */

#define JASR_CAPABILITY_NAME_MAX			40		///< 能力名称最大长度
#define JASR_GRAMMAR_MAX_GRAMMAR_COUNT		256		///< 语法识别引擎加载资源最大加载个数
#define JASR_GRAMMAR_MAX_RESULT_COUNT		10		///< 打开nbest后,最大候选个数,暂时语法识别结果固定为1个识别结果
#define JASR_GRAMMAR_MAX_WORD_LEN			1000	///< 语法识别引擎,词表模式下,每个词条最大长度(字节数)
#define JASR_LANGUAGE_NAME_MAX				256		///< 语言名称最大长度
#define JASR_DOMAIN_NAME_MAX				256		///< 领域名称最大长度
#define JASR_POST_PROCESS_MAX				1024	///< 后处理串长度

/**
* @brief 识别引擎类型
*/
typedef enum _jASR_EngineType
{
    JASR_ENGINE_FREETALK,				///< 自由说识别
    JASR_ENGINE_GRAMMAR,				///< 语法识别
    JASR_ENGINE_KEYWORDSPOT,			///< 关键词检出
    JASR_ENGINE_ANALYSIS				///< 质检分析
}jASR_EngineType;

/**
* @brief 识别能力结构体
*/
typedef struct _jASR_CapabilityInfo
{
    char szCapabilityName[JASR_CAPABILITY_NAME_MAX + 1];///< 能力名称
    jASR_EngineType eEngineType;					///< 引擎类型
}jASR_CapabilityInfo;

/**
* @brief 能力信息列表结构体
*/
typedef struct _jASR_CapabilityInfoList
{
    int nCapabilityCount;							///< 能力个数
    jASR_CapabilityInfo * pCapabilityInfoList;		///< 能力列表指针
}jASR_CapabilityInfoList;

/* @} */

/*************************************************************************************
                            参数类型和值列表
**************************************************************************************/
/** @defgroup 参数类型和值列表 */
/* @{ */

// 参数值定义

/** @name JASR_PARAM_STREAM 的可选值
流式识别的概念是语音数据一次性传入,还是多次分片传入,自由说、关键词、语法识别支持此参数 
* @{ */
#define JASR_STREAM_NO			0		///< 不是流式识别 (缺省)
#define JASR_STREAM_YES			1		///< 是流式识别
#define JASR_STREAM_CONTINUE	2		///< 是流式识别,同时开启端点检测,每段话输出结果,在每次输入数据时可能输出结果
#define JASR_STREAM_CONTINUE_RT 3       ///< 是流式识别,同时开启端点检测,即时输出结果
#define JASR_STREAM_YES_RT      4       ///< 是流式识别,未开启端点检测,即时输出结果
/** @} */

/** @name JASR_PARAM_RESULT_TYPE 的可选值
自由说、质检分析引擎支持此参数
* @{ */
#define JASR_RESULT_SENTENCE	0		///< 单句输出结果 (缺省值)
#define JASR_RESULT_WORDLIST	1		///< 按分词输出的详细结果,包括每个单词的时间位置等
#define JASR_RESULT_CHARLIST	2		///< 按字符输出的详细结果,包括每个字符的时间位置等,注意：将来中英文混的时候,也有可能一个单元不是一个字符,而是一个英文单词
/** @} */

/** @name JASR_PARAM_MODE 的可选值
质检分析引擎支持设置此参数
* @{ */
#define JASR_MODE_OFFLINE		0		///< 离线分析方式,数据一次性输入,整体给出分析结果(缺省)
#define JASR_MODE_ONLINE		1		///< 在线分析方式,数据分块输入,中间可能会即时输出结果,但在线分析方式可能有些限制,例如无法给出role,无法整体给出静音段
/** @} */

/** @name JASR_PARAM_CHANNEL_TYPE 的可选值
质检分析引擎支持设置此参数
* @{ */
#define JASR_CHANNEL_MONO			0	///< 单声道
#define JASR_CHANNEL_LEFT_AGENT		1	///< 双声道,左声道为坐席
#define JASR_CHANNEL_RIGHT_AGENT	2	///< 双声道,右声道为坐席
/** @} */

/** @name JASR_PARAM_AUDIOFORMAT 的可选值
* @{ */
#define JASR_AUDIOFORMAT_PCM8K16BIT		0	///< 8k默认值
#define JASR_AUDIOFORMAT_ALAW8K			1
#define JASR_AUDIOFORMAT_ULAW8K			2
#define JASR_AUDIOFORMAT_VOX6K4BIT		3
#define JASR_AUDIOFORMAT_VOX8K4BIT		4
#define JASR_AUDIOFORMAT_GSM610         5
#define JASR_AUDIOFORMAT_PCM16K16BIT    6   ///< 仅支持16k模型 默认值
#define JASR_AUDIOFORMAT_V36K4BIT       7   ///< v3 6k4bit格式

/** @} */

/** @name JASR_PARAM_NBEST_RESULT 的可选值
语法识别引擎支持此参数
* @{ */
#define JASR_NBEST_NO			0		///< 不输出多选 (缺省)
#define JASR_NBEST_YES			1		///< 输出多选

/** @} */

/** @name JASR_PARAM_ADD_PUNC 的可选值
只有自由说、质检分析引擎支持此参数
* @{ */
#define JASR_ADD_PUNC_NO		0		///< 不增加标点符号 (缺省值)
#define JASR_ADD_PUNC_YES		1		///< 增加标点符号 (现在只增加 逗号、句号、问号 三种,只有在单句输出结果时支持)

/** @} */

/** @name JASR_PARAM_FT_POST_PROCESS 的组合值，可以组合添加
 *  * @{ */
#define JASR_FT_POST_PROCESS_NONE 0x0 ///< FT 文本后处理，不做任何处理
#define JASR_FT_POST_PROCESS_PUNCTUATE 0x01 ///< FT 文本后处理 加标点
#define JASR_FT_POST_PROCESS_NUMNORMAL 0x02 ///< FT 文本后处理 数值归一化
#define JASR_FT_POST_PROCESS_SMOOTH 0x04    ///< FT 文本后处理 文本顺滑
#define JASR_FT_POST_PROCESS_PARAGRAPH 0x08    ///< FT 文本后处理 自动文本分段
/** @} */

/** @name JASR_PARAM_PROPERTY_MODEL_TYPE 的可选值
* @{ */
#define JASR_MODEL_8K		0		///< 8K模型 (缺省值)
#define JASR_MODEL_16K		1		///< 16K模型

/** @} */

/**
* @brief 参数类型
*/
typedef enum _jASR_ParamKey
{
    // 通用参数
    JASR_PARAM_SAMPLERATE,		///< 0 采样率 (当前版本不可设置,由jASR_SDK.conf文件中sample_rate参数指定)
    JASR_PARAM_VAD_HEAD,		///< 1 静音检测头部参数,以ms为单位,缺省值10s=10000ms,范围[0-1800000]
    JASR_PARAM_VAD_TAIL,		///< 2 静音检测尾部参数,以ms为单位,缺省值500ms, 范围[0-30000]
    JASR_PARAM_MAX_SECONDS,		///< 3 最大的声音长度,以s为单位,缺省值30s,范围[1-60],grammar 默认是60S,详见@ref jASR_RecognizeStream 的注解
    JASR_PARAM_AUDIOFORMAT,		///< 4 识别时输入的音频格式,8k模型支持设置除JASR_AUDIOFORMAT_PCM16K16BIT之外的音频格式,缺省值@ref JASR_AUDIOFORMAT_PCM8K16BIT ,16k模型仅支持设置为@ref JASR_AUDIOFORMAT_PCM16K16BIT .
    JASR_PARAM_VAD_THRESHOLD,	///< 5 起始端点检测灵敏度,缺省值10,范围[1-100]

    // 支持GRM
    JASR_PARAM_NBEST_RESULT,	///< 6 是否输出多个候选结果,缺省值@ref JASR_NBEST_NO (语法识别引擎支持此参数,目前固定为只输出一个结果)

    // 支持FT,SA
    JASR_PARAM_ADD_PUNC,		///< 7 是否加标点,缺省值@ref JASR_ADD_PUNC_NO (只有自由说、质检分析引擎支持此参数)

    // 支持FT,KWS,GRM
    JASR_PARAM_STREAM,			///< 8 是否流式识别,缺省值@ref JASR_STREAM_NO （自由说、关键词、语法识别引擎支持此参数）

    // 支持FT,SA
    JASR_PARAM_RESULT_TYPE,		///< 9 输出结果类型,缺省值@ref JASR_RESULT_SENTENCE （自由说、质检分析引擎支持此参数）

    // 支持SA
    JASR_PARAM_MODE,			///< 10 分析处理模式,缺省值@ref JASR_MODE_OFFLINE （质检分析引擎支持此参数）
    JASR_PARAM_CHANNEL_TYPE,	///< 11 声道参数,缺省值@ref JASR_CHANNEL_MONO （质检分析引擎支持设置此参数）

    // 支持ALL
    JASR_PARAM_PROPERTY_LANGUAGE,		///< 12 能力属性,语言(lang),全小写字符串,长度最大为@ref JASR_LANGUAGE_NAME_MAX ,示例：chinese、english、cantonese或uighur.缺省值 chinese
    JASR_PARAM_PROPERTY_MODEL_TYPE,		///< 13 能力属性,8k/16k模型（modeltype）,缺省值@ref JASR_MODEL_8K 
    JASR_PARAM_PROPERTY_DOMAIN,			///< 14 能力属性,领域（domain）,全小写字符串,长度最大为@ref JASR_DOMAIN_NAME_MAX ,示例：common、poi、music、telecom.缺省值 common

    // 后处理
    JASR_PARAM_POST_PROCESS,			///< 15 保留参数, 请不要设置.  示例（注意qa_paramter=后面大括号内的内容需要上层base64转码后再设置）："need_nlu=yes,qa_paramter={\"address\":\"http://10.0.1.219:9080/CSRBroker/queryAction\",\"robot\"....}"

    // Freetalk 文本后处理
    JASR_PARAM_FT_POST_PROCESS,         /// 16 Freetalk 文本后处理
}jASR_ParamKey;

///	参数取值
typedef void * jASR_ParamValue;

/* @} */

/*************************************************************************************
                            识别结果结构定义
**************************************************************************************/
/** @defgroup 识别结果结构定义 */
/* @{ */

#define JASR_RECOG_FLAG_WORD_BOUNDARY	0x01	///< 结果中的元素是否是词边界

//--------------------自由说引擎识别结果----------------------
/**
* @brief ASR识别单句输出候选结果条目
*/
typedef struct _jASR_Freetalk_Sentence
{
    char * pszText;			///< 候选结果字符串,UTF-8编码,以'\0'结束
    int nScore;				///< 候选结果分值[0-65535],分值越高,越可信
} jASR_Freetalk_Sentence;

/**
* @brief ASR识别分词或分字输出的每个单位
*/ 
typedef struct _jASR_Freetalk_Element
{
    int nStartTime;			///< 本词条的起始时间,ms为单位
    int nEndTime;			///< 本词条的结束时间,ms为单位
    int nScore;				///< 本词条的可信度[0-65535],分值越高,越可信
    int nPosInText;			///< 单词或字在@ref jASR_Freetalk_Sentence 的pszText中的位置,以字节为单位
    int nCountInText;		///< 单词或字在@ref jASR_Freetalk_Sentence 的pszText中的长度,以字节为单位
    int nFlag;				///< 如果标记是@ref JASR_RECOG_FLAG_WORD_BOUNDARY ,表示是词边界,也即有这个标记的元素表示一个词的最后一个字符
                            /// 如果是 @ref JASR_RESULT_WORDLIST 情况下,所有元素都会有这个标记
} jASR_Freetalk_Element;

/**
* @brief ASR识别分词或分字输出候选结果条目
*/
typedef struct _jASR_Freetalk_ElementList
{
    int nElementCount;							///< 单词的数目
    jASR_Freetalk_Element * pElementList;		///< 分词输出的词条列表
} jASR_Freetalk_ElementList;

/**
* @brief ASR识别结果中每一分段的结果
*/
typedef struct _jASR_Freetalk_Segment
{
    int nStartTime;		///< 本段的起始时间,ms为单位
    int nEndTime;		///< 本段的结束时间,ms为单位
    int nResultCount;	///< 本段的识别候选结果数目
    jASR_Freetalk_Sentence	* pSentenceResults; 	///< 识别候选结果列表
    jASR_Freetalk_ElementList	* pElementListResults;	///< 分词输出(@ref JASR_RESULT_WORDLIST 或 @ref JASR_RESULT_CHARLIST )时才有此列表,否则为NULL

} jASR_Freetalk_Segment;

/**
* @brief 自由说识别结果结构体
*/
typedef struct _jASR_Freetalk_Result
{
    int nSegmentCount;							///< 段数,一次返回的识别结果中可能分为多段
    jASR_Freetalk_Segment * pSegmentList;		///< 每个分段的结果
}jASR_Freetalk_Result;

//--------------------关键词检出引擎识别结果----------------------
///关键词文本最大长度
#define JASR_KWS_MAX_KEYWORD_LEN		256		///< 每条关键词的最大长度

/**
* @brief ASR检出的关键词条目
*/
typedef struct _jASR_Keyword
{
    int nKeywordIndex;		                ///< 关键词在设置列表中的索引
    char szText[JASR_KWS_MAX_KEYWORD_LEN];  ///< 具体的关键词
    int nStartTime;			                ///< 本词条的起始时间,ms为单位
    int nEndTime;			                ///< 本词条的结束时间,ms为单位
    int nScore;				                ///< 本词条的可信度[0-65535],分值越高,越可信
} jASR_Keyword;

/**
* @brief ASR关键词检出结果
*/
typedef struct _jASR_Keywordspot_Result
{
    int nKeywordCount;					///< 关键词的数目
    jASR_Keyword * pKeywordResults;		///< 分词输出的词条列表
} jASR_Keywordspot_Result;


//--------------------质检分析引擎识别结果----------------------
/**
* @brief 质检分析引擎识别结果
*/
typedef struct _jASR_Analysis_Sentence
{
    char * pszText;				///< 候选结果字符串,UTF-8编码,以'\0'结束
    int nScore;					///< 候选结果分值[0-65535],分值越高,越可信
    float fSpeed;				///< 语速(字/秒)
} jASR_Analysis_Sentence;

/**
* @brief ASR识别分词或分字输出的每个单位
*/
typedef struct _jASR_Analysis_Element
{
    int nStartTime;			///< 本词条的起始时间,ms为单位
    int nEndTime;			///< 本词条的结束时间,ms为单位
    int nScore;				///< 本词条的可信度[0-65535],分值越高,越可信
    int nPosInText;			///< 单词或字在@ref jASR_Analysis_Sentence 的pszText中的位置,以字节为单位
    int nCountInText;		///< 单词或字在@ref jASR_Analysis_Sentence 的pszText中的长度,以字节为单位
    int nFlag;				///< 如果标记是 @ref JASR_RECOG_FLAG_WORD_BOUNDARY ,表示是词边界,也即有这个标记的元素表示一个词的最后一个字符.如果是 @ref JASR_RESULT_WORDLIST 情况下,所有元素都会有这个标记
} jASR_Analysis_Element;

/**
* @brief ASR识别分词或分字输出候选结果条目
*/
typedef struct _jASR_Analysis_ElementList
{
    int nElementCount;							///< 单词的数目
    jASR_Analysis_Element * pElementList;		///< 分词输出的词条列表
} jASR_Analysis_ElementList;

/**
* 情绪检测结果定义
*/
typedef enum 
{
    JASR_EMOTION_HAPPY,			///< 0 情绪检测,快乐,目前并不检测
    JASR_EMOTION_ANGRY,			///< 1 情绪检测,生气,目前仅检测此项
    JASR_EMOTION_SAD,			///< 2 情绪检测,悲伤,目前并不检测
    JASR_EMOTION_DISGUSTED,		///< 3 情绪检测,厌烦,目前并不检测
} jASR_EmotionType;

/**
* 说话人角色定义
*/
typedef enum 
{
    JASR_ROLE_UNKNOWN,			///< 未知
    JASR_ROLE_AGENT,			///< 坐席客服人员
    JASR_ROLE_USER,				///< 用户
} jASR_RoleType;

/**
*	@brief	分析结果中的静音段结果
*/
typedef struct _jASR_Analysis_Silence_Result
{
    int nStartTime;			///< 本段的起始时间,ms为单位
    int nEndTime;			///< 本段的结束时间,ms为单位

} jASR_Analysis_Silence_Result;

/**
* @brief 情绪检测结果
*/
typedef struct _jASR_Analysis_Emotion
{
    int nStartTime;				///< 本次结果的起始时间,ms为单位
    int nEndTime; 				///< 本次结果的结束时间,ms为单位
    int nScore;					///< 本次检测结果的可信度 [0-65535]
    jASR_EmotionType nEmotion; 	///< 情绪检测结果
} jASR_Analysis_Emotion;

/**
* @brief ASR识别结果中每一分段的结果
*/
typedef struct _jASR_Analysis_Segment
{
    int nStartTime;		///< 本段的起始时间,ms为单位
    int nEndTime;		///< 本段的结束时间,ms为单位
    jASR_RoleType nRole; 	///< 本段的说话人角色 在单声道情况语音下,只有在离线模式下(@ref JASR_MODE_OFFLINE )时才是具体的角色,否则均为JASR_ROLE_UNKNOWN
    int nResultCount;	///< 本段的识别候选结果数目
    jASR_Analysis_Sentence	* pSentenceResults; 	///< 识别候选结果列表
    jASR_Analysis_ElementList	* pElementListResults;	///< 分词输出(@ref JASR_RESULT_WORDLIST 或 @ref JASR_RESULT_CHARLIST )时才有此列表,否则为NULL
    int nEmotionCount;		///< 本段检测到的情绪异常数目
    jASR_Analysis_Emotion * pEmotionResults;	///< 具体的情绪异常检测结果
    int nKeywordCount;      ///< 本段检测到的关键词数目
    jASR_Keyword * pKeywordResults;		///< 具体的关键词结果

} jASR_Analysis_Segment;

/**
* @brief 分析函数的返回结果,可能是离线模式最后的一次性返回结果,也可能是在线模式中间返回的结果
*/
typedef struct _jASR_Analysis_Result
{
    /// 静音段数目,只有离线模式才会返回静音段
    int nSilenceCount;

    /// 静音段的具体结果,只有离线模式才会返回静音段
    jASR_Analysis_Silence_Result * pSilenceResults;

    /// 语音段数目,一次返回的识别结果中可能分为多段
    int nSegmentCount;

    /// 每一个语音段的具体结果
    jASR_Analysis_Segment * pSegmentResults;

}jASR_Analysis_Result;

//------------------语法识别引擎识别结果------------------------

/**
 * @brief	ASR识别候选结果条目
 */
typedef struct _jASR_Grammar_Sentence_Result
{
    /// 候选结果字符串,UTF-8编码,以'\0'结束
    char * pszText;

    /// 候选结果分值,分值越高,越可信
    int nScore;
} jASR_Grammar_Sentence_Result;

/**
 *	@brief	ASR识别结果中每一分段的结果
 */
typedef struct _jASR_Grammar_Segment_Result
{
    /// 本段的起始时间,ms为单位
    int nStartTime;

    /// 本段的结束时间,ms为单位
    int nEndTime;

    /// 识别候选结果的数目
    int nResultCount;

    /// 识别候选结果列表
    jASR_Grammar_Sentence_Result *pSentenceResults;
} jASR_Grammar_Segment_Result;

/**
 *	@brief	ASR识别函数的返回结果,可能是非连续识别时候最后的识别结果,也可能是连续识别时中间返回的识别结果
 */
typedef struct _jASR_Grammar_Result
{
    /// 段数,一次返回的识别结果中可能分为多段
    int nSegmentCount;

    /// 每一段的具体结果
    jASR_Grammar_Segment_Result * pSegmentResults;

} jASR_Grammar_Result;

//--------------------统一识别结果----------------------
/**
* @brief 识别结果结构体
*/
typedef struct _jASR_RecogResult
{
    jASR_EngineType nEngineType;				///< 识别结果引擎类型,用于区分是union中的哪一种
    union
    {
        jASR_Freetalk_Result		sFreetalkResult;
        jASR_Grammar_Result			sGrammarResult;
        jASR_Keywordspot_Result		sKeywordspotResult;
        jASR_Analysis_Result		sAnalysisResult;
    };
    ///< 识别结果列表
}jASR_RecogResult;

/* @} */

/*************************************************************************************
                        jASR SDK接口函数定义
**************************************************************************************/
/** @defgroup 函数接口定义 */
/* @{ */

/** @name 识别状态标识
* @{ */
typedef int jASR_RecogStatus;
#define JASR_RECOG_STATUS_PROCESS		0x01	///< 识别中,无识别结果
#define JASR_RECOG_STATUS_HAS_RESULT	0x02	///< 有识别结果
#define JASR_RECOG_STATUS_DETECT_BEGIN	0x04	///< 检测到起始端点
/** @} */

/**
* @brief 资源类型
*/
typedef enum _jASR_ResourceType
{
    JASR_RESOURCE_FILE,					///< 文件
    JASR_RESOURCE_BUFFER,				///< 内存缓冲区
}jASR_ResourceType;

/**
* @brief 资源格式类型
*/
typedef enum _jASR_ResourceFormatType
{
    JASR_RESOURCE_KEYWORD_LIST,			///< 0 关键词列表
    JASR_RESOURCE_GRAMMAR_WORDLIST,		///< 1 词表类型,每行一个词条
    JASR_RESOURCE_GRAMMAR_ABNF,			///< 2 ABNF格式 语法文件,暂不支持
    JASR_RESOURCE_GRAMMAR_JSGF,			///< 3 JSGF格式 语法文件
    JASR_RESOURCE_GRAMMAR_ARPA,			///< 4 ARPA格式 语言模型,暂不支持
    JASR_RESOURCE_GRAMMAR_WFST,			///< 5 WFST格式的最终建网模型
	JASR_RESOURCE_FREETALK_USERWORD,	///< 6 freetalk user word
	JASR_RESOURCE_FREETALK_OLM,			///< 7 freetalk olm, 目前不支持此类型资源, 用于占位
}jASR_ResourceFormatType;


/**  
* @brief	用于初始化识别系统.一个进程仅进行一次即可,不可重复初始化.
* @param	pszInitPath [in]	ASR引擎初始化路径,为引擎工作路径
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数无效</td></tr>
*		<tr><td>@ref JASR_ERR_ALREADY_INIT</td><td>已初始化</td></tr>
*		<tr><td>@ref JASR_ERR_INIT_FAILED</td><td>初始化失败</td></tr>
*		<tr><td>@ref JASR_ERR_ENV_NOT_FOUND</td><td>环境变量(HCICLOUD_HOME)未设置</td></tr>
*		<tr><td>@ref JASR_ERR_ENV_NOT_VALID</td><td>环境变量(HCICLOUD_HOME)无效</td></tr>
*	</table>
* @note 
*	初始化参数pszInitPath说明如下：@n
*	如果pszInitPath为NULL,"",一个绝对路径（表示语音识别引擎从此路径加载模型文件）,表示是本地调用,并使用模型目录下conf文件中的jASR_SDK.conf@n
*	如果pszInitPath为ip:port形式,表示是网络调用方式,ip和port指定Socket接口服务器的地址和端口号,例如 10.0.0.199:8234 .@n
*   如果是本地版,且pszInitPath为NULL,或"",则SDK会从环境变量(HCICLOUD_HOME)指定的路径加载引擎、模型以及配置文件 .@n
*   如果pszInitPath为"ip:port,绝对路径",表示网络调用,ip和Port指定Socket接口服务器的地址和端口号,绝对路径是客户端配置文件的绝对路径,例如 10.0.0.199:8234,/home/jASR_SDK.conf
*/
jASR_ErrCode JASRAPI jASR_Init(
    const char * pszInitPath
    );

/**  
* @brief	用于反初始化工作,释放已经加载的资源
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_ACTIVE_SESSION_EXIST</td><td>还有会话未停止</td></tr>
*		<tr><td>@ref JASR_ERR_RESOURCE_NEED_UNLOAD</td><td>还有资源未卸载</td></tr>
*		<tr><td>@ref JASR_ERR_ENGINE_FAILED</td><td>能力反初始化失败</td></tr>
*		<tr><td>@ref JASR_ERR_UNKNOWN</td><td>未知错误,一般不会发生 </td></tr>
*	</table>
* @note 
*	无
*/
jASR_ErrCode JASRAPI jASR_End();

/**  
* @brief	用于获取能力列表,分为不同识别类别以及不同语种的识别能力
* @param	pCapabilityInfoList [in]	能力信息列表指针
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数pCapabilityInfoList为NULL</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*	</table>
* @note 
*	获取成功,且能力个数不为0时,必须使用@ref jASR_ReleaseCapabilityInfoList 释放该列表,否则有内存泄露.
*/
jASR_ErrCode JASRAPI jASR_GetCapabilityInfoList(
    jASR_CapabilityInfoList * pCapabilityInfoList
    );

/**  
* @brief	释放能力列表结构空间
* @param	pCapabilityInfoList [in]	能力信息列表指针
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数pCapabilityInfoList为NULL</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*	</table>
* @note 
*	无
*/
jASR_ErrCode JASRAPI jASR_ReleaseCapabilityInfoList(
    jASR_CapabilityInfoList * pCapabilityInfoList
    );

/**  
* @brief	预加载某一个识别引擎
* @param	pcszCapabilityName [in]		能力名称标识
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_CAPABILITY_NOT_EXIST</td><td>该能力不存在</td></tr>
*		<tr><td>@ref JASR_ERR_CAPABILITY_ALREADY_LOAD</td><td>已经加载过</td></tr>
*		<tr><td>@ref JASR_ERR_LICENSE</td><td>该能力不在授权列表</td></tr>
*		<tr><td>@ref JASR_ERR_LICENSE_EXPIRED</td><td>该能力授权已过期</td></tr>
*		<tr><td>@ref JASR_ERR_CAPABILITY_PRELOAD_FAILED</td><td>预加载能力失败</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_SUPPORT</td><td>客户端SDK不支持此函数</td></tr>
*	</table>
* @note 
*	客户端不需要调用此函数,若调用,将返回@ref JASR_ERR_NOT_SUPPORT
*/
jASR_ErrCode JASRAPI jASR_PreLoad(
    const char * pcszCapabilityName
    );

/**  
* @brief	创建一次会话,并返回本次会话的句柄ID
* @param	pcszCapabilityName [in]	能力名称标识
* @param	phSession [out]	会话句柄
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_CAPABILITY_NOT_EXIST</td><td>该能力不存在</td></tr>
*		<tr><td>@ref JASR_ERR_CAPABILITY_PRELOAD_FAILED</td><td>预加载能力失败</td></tr>
*		<tr><td>@ref JASR_ERR_SESSION_START_FAILED</td><td>开启会话失败</td></tr>
*	</table>
* @note 
*	[本地版] 最大可以创建的会话数目受到授权文件的控制.如果没有预加载,本函数第一次调用该能力会自动加载.@n
*	[客户端] 不对会话创建进行授权控制,授权以服务器端为准.
*/
jASR_ErrCode JASRAPI jASR_SessionStart(
    const char * pcszCapabilityName,
    jASR_Handle * phSession
    );

/**  
* @brief	结束本次会话,释放激活的引擎资源
* @param	hSession [in]	会话句柄
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_SESSION_INVALID</td><td>会话句柄错误</td></tr>
*		<tr><td>@ref JASR_ERR_RESULT_NOT_FREE</td><td>还有识别结果未释放</td></tr>
*		<tr><td>@ref JASR_ERR_RESOURCE_NEED_DEACTIVE</td><td>还有资源未反激活</td></tr>
*		<tr><td>@ref JASR_ERR_SESSION_STOP_FAILED</td><td>会话停止失败</td></tr>
*	</table>
* @note 
*	[本地版] 如果是非预加载的引擎,如果所有的会话都已经注销,那么也会释放掉此引擎.
*/
jASR_ErrCode JASRAPI jASR_SessionStop(
    jASR_Handle hSession
    );

/**  
* @brief	识别语音流
* @param	hSession [in]		会话句柄
* @param	pData [in]			音频数据
* @param	nDataLen [in]		音频数据长度,单次发送的音频文件长度建议不要超过64MB；必须小于128MB，否则会引起异常
* @param	bIsDataOver [in]	数据结束标识,结束为1,未结束为0,非实时识别时忽略此参数
* @param	pRecogStatus [out]	识别状态,识别成功时,据此可判断是识别中还是有结果返回,若返回值为@ref JASR_ERR_NONE 或者@ref JASR_ERR_NO_VOICE_INPUT 时此参数有效
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_SESSION_INVALID</td><td>会话句柄错误</td></tr>
*		<tr><td>@ref JASR_ERR_LICENSE</td><td>该能力授权错误</td></tr>
*		<tr><td>@ref JASR_ERR_RESULT_NOT_FREE</td><td>还有识别结果未释放</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_SUPPORT</td><td>JASR_PARAM_CHANNEL_TYPE为双声道时不支持VOX格式音频</td></tr>
*		<tr><td>@ref JASR_ERR_NO_VOICE_INPUT</td><td>头部静音超过JASR_PARAM_VAD_HEAD</td></tr>
*		<tr><td>@ref JASR_ERR_RECOG_FAILED</td><td>识别失败</td></tr>
*		<tr><td>@ref JASR_ERR_ENGINE_FAILED</td><td>本地版时音频格式转换失败,或客户端时结果异常</td></tr>
*		<tr><td>@ref JASR_ERR_NETWORK_FAILED</td><td>网络连接异常</td></tr>
*		<tr><td>@ref JASR_ERR_REALTIME_SESSION_TIMEOUT</td><td>实时识别时,两次识别时间间隔超过限制,实时识别中断</td></tr>
*		<tr><td>@ref JASR_ERR_ALL_SESSION_BUSY</td><td>服务器端所有会话都在使用中,无法处理本次请求</td></tr>
*       <tr><td>@ref JASR_ERR_LOAD_RESOURCE_FAILED</td><td>网络版激活不存在的预加载资源后识别</td></tr>
*	</table>
* @note 
* <b>bIsDataOver的作用：</b>@n
*	· 在自由说和关键词检出的JASR_PARAM_STREAM为JASR_STREAM_NO时,语音质检的JASR_PARAM_MODE为JASR_MODE_OFFLINE时,忽略此参数.@n
*	其他情况时,@n
*	· 若值为0,则表示在识别过程中,传入的数据pData不能为NULL,nDataLen必须大于0.@n
*	· 若值为1,则表示识别结束,pData必须为NULL,且nDataLen必须为0.@n
*	若不传入结束数据,则认为本轮流式识别或在线识别还未完成.@n
* -------------------------------------------------------------------------------------------------------------------------------------@n
* <b>目前支持4类引擎：</b>@n
* 1) 自由说语音识别引擎@n
*  自由说语音识别引擎支持4种处理方式@n
*	* 非流式识别(@ref JASR_STREAM_NO): 每次传入音频,即返回结果.@n
*	* 流式识别(@ref JASR_STREAM_YES): 分段传入数据,传入结束数据(即bIsDataOver为1,pData为NULL,nDataLen为0)时返回结果.@n
*	* 流式识别且作端点检测(@ref JASR_STREAM_CONTINUE): 分段传入数据,每段话输出结果,每次传入数据都可能有结果返回,结束时需传入结束数据.@n
*   * 流式识别且作端点检测(@ref JASR_STREAM_CONTINUE_RT): 分段传入数据,即时输出结果,结束时需传入结束数据.@n
*   * 流式识别不做端点检测(@ref JASR_STREAM_YES_RT): 分段传入数据,即时输出结果,结束时需传入结束数据.@n
* <b> 识别结果与静音检测的说明：</b>@n
*	· 非流式识别和流式识别时,识别成功返回JASR_ERR_NONE,有无结果根据识别状态pRecogStatus判断.@n
*	· 流式识别且作端点检测时,识别成功返回JASR_ERR_NONE或JASR_ERR_NO_VOICE_INPUT,此时有无结果根据识别状态pRecogStatus判断.@n
*	头部静音(可出现在开头或者中间)超过JASR_PARAM_VAD_HEAD的值时返回JASR_ERR_NO_VOICE_INPUT,需要注意的是,若返回JASR_ERR_NO_VOICE_INPUT:@n
*		1、则本次传入的音频将被舍弃,本轮识别结束,用户应传入结束数据结束本轮识别.@n
*		2、如果之前的数据块有结果还未返回,则可能在本次识别返回,若有结果则pRecogStatus值含有JASR_RECOG_STATUS_HAS_RESULT.@n
* @note
* -------------------------------------------------------------------------------------------------------------------------------------@n
* 2) 基于语法的语音识别引擎@n
*  基于语法的语音识别引擎在首次识别前,需调用 @ref jASR_ActiveResource 激活语法,其它处理方式同以上的“自由说语音识别引擎”,不支持JASR_STREAM_CONTINUE_RT、JASR_STREAM_YES_RT处理方式 @n
* @note
* -------------------------------------------------------------------------------------------------------------------------------------@n
* 3) 语音质检分析引擎@n
*   质检分析引擎具有两种处理模式,离线模式和在线模式,可以通过 @ref JASR_PARAM_MODE 参数来进行设置.@n
*   * 离线模式(@ref JASR_MODE_OFFLINE)：一次性送入完整的语音数据,整体的分析结果一次性返回,放在 pResult 中.@n
*   * 在线模式(@ref JASR_MODE_ONLINE)：分段送入语音数据,结果会随时返回,最后一段以pData为NULL(此时nDataLen也必须同时设置为0)表示结束.@n
* @n
*	离线模式时,正常情况下都返回@ref JASR_ERR_NONE ,如果都是静音,pRecogStatus识别状态一般含有JASR_RECOG_STATUS_PROCESS,表示无结果返回,此时不需要释放结果.@n
* @n
*	在线模式时,正常情况下可能返回 @ref JASR_ERR_NONE 或@ref JASR_ERR_NO_VOICE_INPUT ,此时可根据pRecogStatus的值判断是否有结果.@n
*	当输入声音检测到语音段并进行识别了,会返回 @ref JASR_ERR_NONE ,此时有结果,这个结果里也可能有多个@ref jASR_Analysis_Segment @n
*	(比如本次送入很长语音数据的情况下,可能中间有多段)；@n
*	当在输入的声音没检测到语音,或者检测到了语音但尚未检测到语音段结束时,识别成功但不会有结果,即识别状态含有@ref JASR_RECOG_STATUS_PROCESS .@n
*	当设置的 @ref JASR_PARAM_VAD_HEAD 参数不是0的话,并且检测到静音段(无论是开头,还是中间的静音段)超过此参数规定的阈值时,@n
*	会返回 @ref JASR_ERR_NO_VOICE_INPUT ,表示在规定的时间内没有语音输入,返回此值则本轮识别结束,用户应传入结束数据结束本轮识别.@n
*	@n
*	注意：在线模式在单声道语音中无法检测角色(也即无法区分客服和用户,nRole总是会设为 @ref JASR_ROLE_UNKNOWN),也不会给出静音段列表.@n
*		  如果音频格式是 JASR_AUDIOFORMAT_VOX6K4BIT或 JASR_AUDIOFORMAT_VOX8K4BIT,JASR_PARAM_CHANNEL_TYPE设为双声道,则返回JASR_ERR_NOT_SUPPORT.@n
* @note
* -------------------------------------------------------------------------------------------------------------------------------------@n
* 4)关键词检出语音识别引擎@n
*  同 [自由说语音识别引擎]的说明,不支持JASR_STREAM_CONTINUE_RT,JASR_STREAM_YES_RT处理方式@n
* @n
* -------------------------------------------------------------------------------------------------------------------------------------@n
* <b>对于识别,有如下规则：</b>@n
* FT和KWS的JASR_PARAM_STREAM为JASR_STREAM_YES或者JASR_STREAM_CONTINUE、JASR_STREAM_CONTINUE_RT、JASR_STREAM_YES_RT,SA的JASR_PARAM_MODE为JASR_MODE_ONLINE时:@n
* 1、传入多块数据的过程中,不论成功失败,一般一轮识别都应以结束数据(即bIsDataOver为1,pData为NULL,nDataLen为0)结束本轮识别.@n
* 2、客户端时,若返回码为JASR_ERR_REALTIME_SESSION_TIMEOUT、JASR_ERR_ALL_SESSION_BUSY或JASR_ERR_RECOG_FAILED时,不需要传入结束数据.@n
* 3、客户端时,若返回码为JASR_ERR_NETWORK_FAILED,则为连接服务器失败或超时,一般本轮会话不再可用,不需要传入结束数据.@n
* 4、客户端时,仅在本轮识别第一次识别时,传递参数到服务器端,在识别过程中重新jASR_SetParam设置的参数值将被忽略,但会在下轮识别时生效.@n
* @n
* @n
* <b>关于端点检测：(FT=自由说语音识别,KWS=关键词检出,SA=语音质检分析)</b>@n
*	1、FT和KWS的JASR_PARAM_STREAM若为JASR_STREAM_NO或者JASR_STREAM_YES,则忽略JASR_PARAM_VAD_HEAD和JASR_PARAM_VAD_TAIL设置,不做端点检测@n
*   2、FT和KWS的JASR_PARAM_STREAM若为JASR_STREAM_CONTINUE、JASR_STREAM_CONTINUE_RT、JASR_STREAM_YES_RT,或者SA的JASR_PARAM_MODE为JASR_MODE_ONLINE时,进行端点检测@n
*	3、若JASR_PARAM_VAD_HEAD为0,则不做头部静音的检测,也就不会返回JASR_ERR_NO_VOICE_INPUT@n
*	4、端点检测的规则为：@n
*		· 若传入的数据中头部静音长度超过JASR_PARAM_VAD_HEAD的值,则该次识别返回JASR_ERR_NO_VOICE_INPUT,本次传入的数据被丢弃,本轮识别结束；@n
*		· 若传入的数据中,中间某段静音长度超过JASR_PARAM_VAD_TAIL的值,将作为切分返回结果的切分点@n
*		· 某一次传入的数据的尾部的静音排除JASR_PARAM_VAD_TAIL值的尾静音后的剩余部分,将参与下一次传入数据的静音头部的检测； @n
*		· 某一次传入的数据的头部静音部分,将参与前一块数据静音尾部的检测,剩余部分用于本次头部静音检测；@n
* @n
* @n
* <b>识别状态pRecogStatus的判断(status=*pRecogStatus)：</b>@n
*	1、识别状态可以是JASR_RECOG_STATUS_PROCESS、JASR_RECOG_STATUS_HAS_RESULT和JASR_RECOG_STATUS_DETECT_BEGIN的组合,若需判断是否有结果,可使用
*	if( (status & JASR_RECOG_STATUS_HAS_RESULT) != 0)或者if( status & JASR_RECOG_STATUS_HAS_RESULT )判断是否有结果,判断无结果和检测到音频起始端点同理.@n
*	2、第一次检测到音频起始端点时,status值包含JASR_RECOG_STATUS_DETECT_BEGIN.@n
* @n
* @n
* <b>参数JASR_PARAM_MAX_SECONDS值对识别的影响如下：</b>@n
*   1、若FT和KWS的JASR_PARAM_STREAM为JASR_STREAM_CONTINUE、JASR_STREAM_CONTINUE_RT, JASR_STREAM_YES_RT,或者SA的JASR_PARAM_MODE为JASR_MODE_ONLINE,则单次传入的音频时长不得超过JASR_PARAM_MAX_SECONDS设置值,否则返回识别失败；@n
*	2、若FT和KWS的JASR_PARAM_STREAM为JASR_STREAM_YES,则本轮识别传入的数据总时长不得超过JASR_PARAM_MAX_SECONDS设置值,否则返回识别失败；@n
*	3、若FT和KWS的JASR_PARAM_STREAM为JASR_STREAM_NO,则该次识别传入的数据时长不得超过JASR_PARAM_MAX_SECONDS设置值,否则返回识别失败；@n
* @n
*/
jASR_ErrCode JASRAPI jASR_RecognizeStream(
    jASR_Handle hSession,
    char * pData,
    int nDataLen,
    int bIsDataOver,
    jASR_RecogStatus * pRecogStatus
    );

/**  
* @brief	获取识别结果
* @param	hSession [in]	会话句柄
* @param	ppRecogResult [in/out]	识别结果结构体指针的指针
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_SESSION_INVALID</td><td>会话句柄错误</td></tr>
*		<tr><td>@ref JASR_ERR_GET_RECOG_RESULT_FAILED</td><td>获取识别结果失败</td></tr>
*	</table>
* @note 
*	无
*/
jASR_ErrCode JASRAPI jASR_GetRecogResult(
    jASR_Handle hSession,
    jASR_RecogResult ** ppRecogResult
    );

/**  
* @brief	释放识别结果所占用空间
* @param	hSession [in]	会话句柄
* @param	ppRecogResult [in|out]	保存结果的结构体指针的指针
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数非法</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_SESSION_INVALID</td><td>会话句柄错误</td></tr>
*		<tr><td>@ref JASR_ERR_FREE_RECOG_RESULT_FAILED</td><td>释放识别结果失败</td></tr>
*	</table>
* @note 
*	由于结果结构比较复杂,而且为内部申请空间,需要使用本函数进行释放.
*/
jASR_ErrCode JASRAPI jASR_FreeRecogResult(
    jASR_Handle hSession,
    jASR_RecogResult ** ppRecogResult
    );

/**  
* @brief	获取识别参数
* @param	hSession [in]		会话句柄
* @param	eParamKey [in]		参数类型
* @param	pParamValue [out]	参数值
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_SESSION_INVALID</td><td>会话句柄错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_SUPPORT</td><td>不支持的参数类型</td></tr>
*		<tr><td>@ref JASR_ERR_GET_PARAM_FAILED</td><td>获取参数设置失败</td></tr>
*	</table>
* @note 
*	 对于参数值,需要用户对返回的*pParamValue进行类型转换,获取应该获取的参数设置值.
*/
jASR_ErrCode JASRAPI jASR_GetParam(
    jASR_Handle hSession,
    jASR_ParamKey eParamKey,
    jASR_ParamValue * pParamValue
    );

/**  
* @brief	设置识别参数
* @param	hSession [in]		会话句柄
* @param	eParamKey [in]		参数类型
* @param	paramValue [in]	参数值
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_SESSION_INVALID</td><td>会话句柄错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_SUPPORT</td><td>不支持的参数类型</td></tr>
*		<tr><td>@ref JASR_ERR_SET_PARAM_FAILED</td><td>设置参数失败</td></tr>
*	</table>
* @note 
*	这里的参数值需要用户在传入不同参数时进行类型强制转换.例如,传入JASR_PARAM_AUDIOFORMAT,设置音频格式,@n
    需要将设置的值强制转换为jASR_ParamValue类型再传入接口函数,如(jASR_ParamValue)JASR_AUDIOFORMAT_PCM8K16BIT.
*/
jASR_ErrCode JASRAPI jASR_SetParam(
    jASR_Handle hSession,
    jASR_ParamKey eParamKey,
    jASR_ParamValue paramValue
    );

/**  
* @brief	加载资源
* @param	pszCapabilityName [in]	能力名称标识
* @param	eResourceType [in]		资源类型,请参见@ref jASR_ResourceType
* @param	pcszResourceData [in]	资源数据(UTF-8类型)
* @param	nResourceDataLen [in]	资源数据长度,只有在资源类型为内存缓冲时才需要,在资源类型为文件时将忽略此参数
* @param	eResourceFormatType [in]	资源格式类型,请参见@ref jASR_ResourceFormatType
* @param	pnResourceID [out]		资源ID
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_CAPABILITY_NOT_EXIST</td><td>该能力不存在</td></tr>
*		<tr><td>@ref JASR_ERR_CAPABILITY_PRELOAD_FAILED</td><td>预加载能力失败</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_SUPPORT</td><td>该能力不支持加载资源</td></tr>
*		<tr><td>@ref JASR_ERR_OPENFILE</td><td>打开文件失败</td></tr>
*		<tr><td>@ref JASR_ERR_MEMORY</td><td>内存错误</td></tr>
*		<tr><td>@ref JASR_ERR_LOAD_RESOURCE_FAILED</td><td>资源加载失败</td></tr>
*	</table>
* @note 
*	目前支持加载词条列表(可用于关键词检出或语法识别)以及语法文件(可用于语法识别).@n
*	当资源类型为文件时,忽略nResourceDataLen参数.@n
*	· 词条列表中每个词以"\n"分割(回车符兼容"\r","\r\n",最后一行可以没有),不能有空行,@n
      词条的最大长度有一定限制,最多@ref JASR_KWS_MAX_KEYWORD_LEN 个字节.关键词检出引擎的输出结果是列表中的顺序号,因此不能有空行,其合法性在@ref jASR_ActiveResource 时验证.@n
*	· 语法文件目前只支持jsgf格式,wordlist格式和WFST格式.支持加载最大@ref JASR_GRAMMAR_MAX_GRAMMAR_COUNT 个资源文件；如果是wordlist格式,每个词条有最大长度限制@ref JASR_GRAMMAR_MAX_WORD_LEN 个字节@n
*	· 若多次载入同一个文件或者同一块内存数据,会返回不同的资源ID.@n
*	· 对于得到的每一个资源ID,反初始化引擎前都需调用@ref jASR_UnloadResource 卸载资源,否则@ref jASR_End 返回@ref JASR_ERR_RESOURCE_NEED_UNLOAD .@n
*	· 激活的资源文件大小及个数暂无限制,内存充足即可成功.
*/
jASR_ErrCode JASRAPI jASR_LoadResource(
    const char * pszCapabilityName,
    jASR_ResourceType eResourceType,
    const char * pcszResourceData,
    int nResourceDataLen,
    jASR_ResourceFormatType eResourceFormatType,
    unsigned int * pnResourceID
    );

/**  
* @brief	卸载资源
* @param	pszCapabilityName [in]	能力名称标识
* @param	nResourceID [in]		资源ID
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_CAPABILITY_NOT_EXIST</td><td>该能力不存在</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_SUPPORT</td><td>该能力不支持加载资源</td></tr>
*		<tr><td>@ref JASR_ERR_UNLOAD_RESOURCE_FAILED</td><td>卸载资源失败</td></tr>
*	</table>
* @note 
*	无.
*/
jASR_ErrCode JASRAPI jASR_UnloadResource(
    const char * pszCapabilityName,
    unsigned int nResourceID
    );

/**  
* @brief	激活加载的资源
* @param	hSession [in]		会话句柄
* @param	nResourceID [in]	资源ID
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_SESSION_INVALID</td><td>会话句柄错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_SUPPORT</td><td>该能力不支持加载资源</td></tr>
*		<tr><td>@ref JASR_ERR_ACTIVE_RESOURCE_FAILED</td><td>激活资源失败</td></tr>
*	</table>
* @note 
*	· 一个session中可以激活不同的资源ID,但以最后一次为准,之前激活的资源会自动反激活.@n
*	· 对于关键词检出引擎(KWS),若单个词条(即每行,不包括结束符)长度超过255字节,将会被截断,超过255字节的部分舍弃.
*/
jASR_ErrCode JASRAPI jASR_ActiveResource(
    jASR_Handle hSession,
    unsigned int nResourceID
    );

/**  
* @brief	激活预加载的资源
* @param	hSession [in]		会话句柄
* @param	pcszResourceName [in]	预定义的资源标识
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数无效</td></tr>
*		<tr><td>@ref JASR_ERR_SESSION_INVALID</td><td>会话句柄错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_SUPPORT</td><td>该能力或者是本地调用不支持加载资源</td></tr>
*		<tr><td>@ref JASR_ERR_ACTIVE_RESOURCE_FAILED</td><td>激活资源失败</td></tr>
*	</table>
* @note 
*	· 一个session中可以激活不同的资源,但以最后一次为准,之前激活的资源会自动反激活.@n
*	· 仅支持激活后台语音识别服务器预加载的资源.
*/
jASR_ErrCode JASRAPI jASR_ActivePreloadResource(
    jASR_Handle hSession,
    const char * pcszResourceName
    );

/**  
* @brief	反激活资源
* @param	hSession [in]	会话句柄
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_SESSION_INVALID</td><td>会话句柄错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_SUPPORT</td><td>该能力不支持加载资源</td></tr>
*		<tr><td>@ref JASR_ERR_DEACTIVE_RESOURCE_FAILED</td><td>反激活资源失败</td></tr>
*	</table>
* @note 
*	结束会话前需要反激活该会话激活的资源,否则@ref jASR_SessionStop 返回@ref JASR_ERR_RESOURCE_NEED_DEACTIVE .
*/
jASR_ErrCode JASRAPI jASR_DeactiveResource(
    jASR_Handle hSession
    );

/**  
* @brief	保存编译后的资源为WSTF格式资源文件
* @param	pszCapabilityName	[in]	能力名称
* @param	nResourceID			[in]	资源ID
* @param	pcszFileName		[in]	WSTF资源文件名称
* @return
* @n
*	<table>
*		<tr><td>@ref JASR_ERR_NONE</td><td>成功</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_INIT</td><td>未初始化</td></tr>
*		<tr><td>@ref JASR_ERR_PARAM_INVALID</td><td>参数错误</td></tr>
*		<tr><td>@ref JASR_ERR_NOT_SUPPORT</td><td>本地非语法识别能力和网络版调用不支持此功能</td></tr>
*		<tr><td>@ref JASR_ERR_CAPABILITY_NOT_EXIST</td><td>该能力不存在</td></tr>
*		<tr><td>@ref JASR_ERR_ENGINE_FAILED</td><td>调用引擎失败</td></tr>
*	</table>
* @note 
*	使用此函数可以保存编译后的资源文件,编译后的文件可以通过@ref JASR_RESOURCE_GRAMMAR_WFST 类型的方式载入,
*	对于大的语法文件可以大大提高资源加载速度.
*/
jASR_ErrCode JASRAPI jASR_SaveCompiledResource(
    const char * pszCapabilityName,
    unsigned int nResourceID,
    const char * pcszFileName
    );

/* @} */
//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // __JASR_SDK_H__
