#ifndef SPEECH_EVAL_API_
#define SPEECH_EVAL_API_

#if defined(SPEECH_EVAL_IMPLEMENT)
#define SPEECH_EVAL_API extern "C" __attribute__((visibility("default")))
#else
#define SPEECH_EVAL_API extern "C"
#endif

struct SpeechEvaluator {

  /*
  * brief 设置评测参数
  * @param [in] param json格式
  * @param [in] param_len json字符串长度
  * @retval 1000 表示成功, 其它值表示失败，错误待完善
  */
  virtual int SetParams(const char* param, const unsigned int param_len) = 0;

  /*
  * brief 检测评测文本OOV信息
  * @param [in] ref json格式，目前只有'text'字段，内容为评测文本
  * @param [in] ref_lenght json字符串长度
  * @param [out] result json格式的返回结果。key为所有不重复单词，value为是否为oov单词
  * @param [out] result_len result的长度
  * @retval 1000 表示成功, 其它值表示失败
  */
  virtual int DetectOOV(const char *ref, const unsigned int ref_len,
                        char const **result, unsigned int *result_len) = 0;

  /*
  * brief 设置评测文本及评测相关参考信息
  * @param [in] ref json格式
  * @param [in] ref_lenght json字符串长度
  * @retval 1000 表示成功, 其它值表示失败，错误待完善
  */
  virtual int Start(const char* ref, const unsigned int ref_len) = 0;

  /*
  * brief Feed音频数据
  * @param [in] data wav格式音频数据
  * @param [in] data_length 数据长度
  * @param [in] is_end 音频是否结束
  * @param [out] result 评测结果
  * @param [out] result_len 评测结构字符长度
  * @retval 1001 中间结果; 1002 结束; 2000-2999 截停; 3000- 错误
  */
  virtual int Evaluate(const char* data, const unsigned int data_len, bool is_end,
      char const** result, unsigned int* result_len) = 0;

  /*
  * brief 重置评测实例
  * @retval 1000 表示成功, 其它值表示识别，错误待完善
  */
  virtual int Reset() = 0;

  virtual ~SpeechEvaluator() = default;
};

/*
* brief 创建评测实例
* @param [in] cfg_fn 资源配置文件路径
* @param [out] err_code 错误码
* @retval 评测实例指针
*/
SPEECH_EVAL_API SpeechEvaluator* CreateEvalInstance(const char* cfg_fn, int *err_code);

/**
 * @brief 释放评测实例
 */
SPEECH_EVAL_API void FreeEvalInstance(SpeechEvaluator *eval_instance);

#endif // SPEECH_EVAL_API_
