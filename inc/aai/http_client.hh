#pragma once

#include <string>
#include <curl/curl.h>

namespace aai {

/**
 * @brief Simple HTTP client for making API calls
 * 
 * Minimal wrapper around libcurl for POST requests to AI APIs.
 * No streaming, no fancy features, just clean blocking calls.
 */
class http_client {
public:
    struct response {
        std::string body;
        long status_code;
        bool success;
    };

    /**
     * @brief Make a POST request with JSON body
     * 
     * @param url The endpoint URL
     * @param json_body The JSON request body
     * @param api_key The API key for authentication
     * @return response struct with body, status, and success flag
     */
    static response post(
        const std::string& url,
        const std::string& json_body,
        const std::string& api_key
    );

private:
    static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp);
};

} // namespace aai
