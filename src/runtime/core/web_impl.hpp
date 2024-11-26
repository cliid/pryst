#pragma once

#include "web.hpp"

extern "C" {
    // Request methods
    void* pryst_web_Request_new(const char* method, const char* path);
    const char* pryst_web_Request_getMethod(void* request);
    const char* pryst_web_Request_getPath(void* request);
    void* pryst_web_Request_getHeaders(void* request);
    const char* pryst_web_Request_getBody(void* request);

    // Response methods
    void* pryst_web_Response_new(int status, const char* body);
    void pryst_web_Response_setContent(void* response, const char* content, const char* type);
    int pryst_web_Response_getStatus(void* response);
    const char* pryst_web_Response_getBody(void* response);
    void* pryst_web_Response_getHeaders(void* response);

    // WebServer methods
    void* pryst_web_WebServer_new(const char* host, int port);
    void pryst_web_WebServer_start(void* server);
}
