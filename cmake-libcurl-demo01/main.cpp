#include <curl/curl.h>
#include <string>
#include <algorithm>
#include <new>
#include <iostream>

size_t write_callback(void *contents, size_t size, size_t nmemb, std::string *s) {
  size_t newLength = size * nmemb;
  size_t oldLength = s->size();
  try {
    s->resize(oldLength + newLength);
  }
  catch (std::bad_alloc &e) {
    return 0;
  }

  std::copy((char *) contents, (char *) contents + newLength, s->begin() + oldLength);
  return size * nmemb;
}

int main() {
  CURL *curl;
  CURLcode res;
  std::string response;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    curl_easy_cleanup(curl);
  }

  std::cout << response << std::endl;

  curl_global_cleanup();

  return 0;
}