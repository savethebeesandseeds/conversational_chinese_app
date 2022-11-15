#ifndef __URL_TOOLS
#define __URL_TOOLS
#include <curl/curl.h>
#include <stdexcept>
#include <memory>
#include <vector>
#include <cstring>

pthread_mutex_t curl_lock;

class REQUESTS {
private:
  static void finit(){
    curl_global_cleanup();
  }
  static void init(){
    curl_global_init(CURL_GLOBAL_DEFAULT);
    std::atexit(REQUESTS::finit);
  }
public:
  static class _init {public:_init(){REQUESTS::init();}}_initializer;
  struct memory {
    char *response;
    size_t size;
  };
private:
  static size_t cb_text(void *data, size_t size, size_t nmemb, void *userp){
    /* calculate incoming memory size */
    size_t realsize = size * nmemb;
    /* cast struct */
    struct REQUESTS::memory *mem = (struct REQUESTS::memory *)userp;
    /* reallocate memory */
    char *ptr = (char*)realloc(mem->response, mem->size + realsize + 1);
    /* validate memory allocation */
    if(ptr == NULL)
      return 0;  /* out of memory! */
    /* assign data */
    mem->response = ptr;
    /* transfer the old data */
    memcpy(&(mem->response[mem->size]), data, realsize);
    /* assign size */
    mem->size += realsize;
    /* mark termination byte */
    mem->response[mem->size] = 0;
    /* return success */
    return realsize;
  }
public:
  static void query(std::string &url, std::vector<std::string> &headers, void *data, size_t data_size, REQUESTS::memory *request_response){
    /* create a handle */
    CURL *curl_handle=curl_easy_init();
    /* check the handle */
    if(!curl_handle)
      throw std::runtime_error("curl is not initialzied");
    /* configure url */
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    /* size of the POST data */
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, data_size);
    /* size of the POST headers */
    struct curl_slist *curl_list = NULL;
    for(std::string ch: headers)
      curl_list = curl_slist_append(curl_list, ch.c_str());
    if(curl_list!=NULL)
      curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, curl_list);
    /* pass in a pointer to the data - libcurl will not copy */
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, data);
    /* capture the data */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, REQUESTS::cb_text);
    /* write data to result */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)request_response);
    /* lock thread */
    pthread_mutex_lock(&curl_lock);
    /* perform the operation */
    CURLcode curl_code=curl_easy_perform(curl_handle);
    /* unlock thread */
		pthread_mutex_unlock(&curl_lock);
    /* free the headers list */
    curl_slist_free_all(curl_list);
    /* check for errors */
    if(curl_code!=CURLE_OK)
      fprintf(stderr,"[Error:] curl failed to perform: %s\n",curl_easy_strerror(curl_code));
    /* clean the handle */
    curl_easy_cleanup(curl_handle);
  }
};
REQUESTS::_init REQUESTS::_initializer;

void clean_memory(REQUESTS::memory *mem, std::vector<const char*> marks){
  /* temporal transform to string */
  std::string temp(mem->response);
  /* clean the response object */
  for(const char* ch: marks){
    while(temp.find(ch)!=std::string::npos)
      temp.replace(temp.find(ch), std::strlen(ch), "");
  }
  /* reallocate the mem */
  mem->response = (char*)realloc(mem->response, sizeof(char)*(temp.size()+1));
  /* initialize */
  memset(mem->response, '\0', sizeof(char)*(temp.size()+1));
  /* transfer the data */
  memcpy(mem->response, temp.c_str(), temp.size());
  /* update the size */
  mem->size=temp.size();
}
#endif