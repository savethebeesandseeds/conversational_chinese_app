// #include "tools.hpp"
#include <string>
#include <curl/curl.h>

std::string input_file("lib/auth.token");
int main(int argc, char *argv[]){
  // char * buff = NULL;
  
  // fprintf(stdout,"waka[0]:%p\n",buff);

  // FILES fls = FILES();

  // size_t buff_size = fls.read_text_file(input_file, &buff);
      
  // /* test print */
  // fprintf(stdout,"[final]_:[%ld]:%s\n",buff_size,buff);

  // if(buff!=NULL)
  //   free(buff);





  // FILES fls = FILES();
  // std::string out = fls.read_text_file(input_file);
  // fprintf(stdout,"out:%s\n",out.c_str());





  // REQUESTS::memory request_response = {
  //   .response=(char*)malloc(0),
  //   .size=0
  // };

  // std::string url="www.google.com";
  // std::vector<std::string> headers = {};
  // void *data = malloc(0);
  // size_t data_size=0;

  // REQUESTS::query(url, headers, data, data_size, request_response);

  // free(data);
  // free(request_response.response);
  
  // delete[] fls;







curl_global_init(CURL_GLOBAL_DEFAULT);
CURL *curl = curl_easy_init();
if(curl) {
  curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
}
curl_global_cleanup();










  // delete[] aux0;
  // delete[] fls;
      
  // /* open file in read-binary mode */
  // FILE *d_file = fopen(input_file.c_str(),"r");
  // /* evaluate file */
  // if(!d_file)
  //   throw std::runtime_error(string_format("Unable to open text file: %s",input_file.c_str()).c_str());
  // /* seek file end */
  // fseek(d_file, 0, SEEK_END);
  // /* calculate contents size */
  // size_t buff_size = ftell(d_file);
  // /* intialize buffer */
  // char *buff = (char*)malloc(sizeof(char)*(buff_size+1));
  // /* allocate pointer */
  // if(buff==NULL)
  //   throw std::runtime_error("Unable to allocate memory to read file");
  // /* rewind binary file */
  // rewind(d_file);
  // /* read file */
  // fread(buff, sizeof(char), buff_size, d_file);
  // /* mark variable termination */
  // buff[buff_size]=0;
  // /* read file contents */
  // fclose(d_file);
  // /* print buffer */
  // fprintf(stdout,"buffer:%s\n",buff);
  // /* free the memory */
  // free(buff);
}