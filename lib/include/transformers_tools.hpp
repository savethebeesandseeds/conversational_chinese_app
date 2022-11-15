#ifndef __TRANSFORMERS_TOOLS
#define __TRANSFORMERS_TOOLS
#include <string>
#include <vector>
#include "file_tools.hpp"
#include "util_tools.hpp"
#include "url_tools.hpp"

std::string authorization_file("lib/auth.token");
std::string generate_text_url("https://api-inference.huggingface.co/models/uer/gpt2-chinese-cluecorpussmall");
std::string transcript_audio_url("https://api-inference.huggingface.co/models/ydshieh/wav2vec2-large-xlsr-53-chinese-zh-cn-gpt");
std::string translate_zh_to_en_url("https://api-inference.huggingface.co/models/Helsinki-NLP/opus-mt-zh-en");

class TextTransformerWrap {
public:
  std::vector<std::string> req_headers;
  TextTransformerWrap():
  req_headers({FILES::read_text_file(authorization_file.c_str())}){}
  virtual ~TextTransformerWrap(){}
public:
  void generate_text(const char *input, REQUESTS::memory *output){
    /* construct data */
    std::string data = string_format("{\"inputs\":\"%s\",\"parameters\": {\"max_length\": 50}}",input);
    /* consult transformer api */
    REQUESTS::query(generate_text_url, req_headers, (void *)data.c_str(), std::strlen(data.c_str()), output);
    /* clean the output */
    clean_memory(output, std::vector({"[{\"generated_text\":\"","\"}]"}));
  }
  void generate_text(std::string input, REQUESTS::memory *output){
    /* transform the input */
    generate_text(static_cast<const char*>(input.c_str()), output);
  }
  void translate_zh_to_en(const char *input, REQUESTS::memory *output){
    /* construct data */
    std::string data = string_format("{\"inputs\":\"%s\"}",input);
    /* consult transformer api */
    REQUESTS::query(translate_zh_to_en_url, req_headers, (void *)data.c_str(), std::strlen(data.c_str()), output);
    /* clean the output */
    // clean_memory(output, std::vector({"[{\"generated_text\":\"","\"}]"}));
  }
  void translate_zh_to_en(std::string input, REQUESTS::memory *output){
    /* transform the input */
    translate_zh_to_en(static_cast<const char*>(input.c_str()), output);
  }
};
class AudioTransformerWrap {
public:
  std::vector<std::string> req_headers;
  AudioTransformerWrap():
  req_headers({FILES::read_text_file(authorization_file.c_str())}){}
  virtual ~AudioTransformerWrap(){}
public:
  void transcript_audio(const char *input_file, REQUESTS::memory *output){
    /* initialize null buffer */
    char* buff = NULL;
    /* read ".flac" as a binary file */
    size_t buff_size = FILES::read_binary_file(input_file, &buff);
    /* query the transformers api */
    if(buff!=NULL)
      REQUESTS::query(transcript_audio_url, req_headers, (void *)buff, buff_size, output);
    /* free buffer */
    free(buff);
    /* clean the output */
    clean_memory(output, std::vector({"[{\"text\":\"","\"}]"}));
  }
  void transcript_audio(std::string input, REQUESTS::memory *output){
    /* transform the input */
    transcript_audio(static_cast<const char*>(input.c_str()), output);
  }
};
#endif