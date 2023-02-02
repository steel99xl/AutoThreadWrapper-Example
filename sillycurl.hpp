#pragma once
#include <curl/curl.h>
#include <cstring>


namespace sillycurl{
inline size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *data){
    size_t newLength = size*nmemb;
    try{
        data->append((char*)contents, newLength);
    }
    catch(std::bad_alloc &e){
        // handle memory problem
        std::cout << "bad memory allocation" << std::endl;
        return 0;
    }
    return newLength;
}

inline std::string WebHandler(const char *Link) {
    CURL *curl;
    //CURLcode res;
    std::string data;

    curl = curl_easy_init();

    if(curl){
        // takes char * and const char * for url

        curl_easy_setopt(curl, CURLOPT_URL, Link);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "nice/6.9");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        // Passed Provided string to the callback function noted above
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        // This makes the curl connection
        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);

    if(std::strcmp(data.c_str(), "") == 0){
        std::cout << "ERROR no internet connection or the sites down" << std::endl;
        data = "ERROR check your internet and the sites used by this app";
    }
    return data;
}

};