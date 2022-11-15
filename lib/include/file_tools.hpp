#ifndef __FILES_TOOLS
#define __FILES_TOOLS
#include <cstring>
#include <memory>
#include <stdexcept>
#include <fstream>
#include "util_tools.hpp"

class FILES {
private:
  static void finit(){}
  static void init(){
    std::atexit(FILES::finit);
  }
public:
  static class _init {public:_init(){FILES::init();}}_initializer;
private:
  static inline size_t read_file(FILE *d_file, char** buff, bool as_string){
    /* validate input */
    if(*buff!=NULL)
      throw std::runtime_error("Please pass a null pointer, as reference to FILES buffer");
    /* seek file end */
    fseek(d_file, 0, SEEK_END);
    /* calculate contents size */
    size_t buff_size = ftell(d_file);
    /* allocate buffer */
    *buff = ((char*) realloc(*buff, sizeof(char)*(buff_size+as_string)));
    /* validate pointer */
    if(*buff==NULL)
      throw std::runtime_error("Unable to allocate memory to read file");
    /* initialize buffer */
    memset(*buff, '\0', sizeof(char)*(buff_size+as_string));
    /* rewind binary file */
    rewind(d_file);
    /* read file */
    fread(*buff, sizeof(char), buff_size, d_file);
    /* return buffer size */
    return buff_size;
  }
public:
  static inline size_t read_text_file(const char* input_file, char** buff){
    /* open file in read-binary mode */
    FILE *text_file = fopen(input_file,"r");
    /* evaluate file */
    if(!text_file)
      throw std::runtime_error(string_format("Unable to open text file: %s",input_file).c_str());
    /* read file contents */
    size_t buff_size = FILES::read_file(text_file, buff, true);
    /* close file */
    fclose(text_file);
    /* return success */
    return buff_size;
  }
  static inline std::string read_text_file(const char* input_file){
    /* initialize null buffer */
    char* buff = NULL;
    /* initialize empty return string */
    std::string ret= std::string("");
    /* read file */
    if(FILES::read_text_file(input_file, &buff))
      ret = std::string(buff);
    /* free buffer */
    free(buff);
    /* return string */
    return ret;
  }
  static inline size_t read_binary_file(const char* input_file, char**buff){
    /* open file in read-binary mode */
    FILE *binary_file = fopen(input_file,"rb");
    /* evaluate file */
    if(!binary_file)
      throw std::runtime_error(string_format("Unable to open binary file: %s",input_file).c_str());
    /* read file contents */
    size_t buff_size = FILES::read_file(binary_file, buff, false);
    /* close file */
    fclose(binary_file);
    /* return success */
    return buff_size;
  }
};
FILES::_init FILES::_initializer;
#endif