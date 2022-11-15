#include <string>
#include <curl/curl.h>

int main(int argc, char *argv[]){
  curl_global_init(CURL_GLOBAL_DEFAULT);
  CURL *curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
}