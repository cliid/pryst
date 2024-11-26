#include "web_impl.hpp"
#include "web.hpp"
#include <cstring>
#include <memory>

using namespace pryst::runtime::web;

extern "C" {
    // Request methods
    void* pryst_web_Request_new(const char* method, const char* path) {
        return new Request(method, path);
    }

    const char* pryst_web_Request_getMethod(void* request) {
        auto req = static_cast<Request*>(request);
        return strdup(req->getMethod().c_str());
    }

    const char* pryst_web_Request_getPath(void* request) {
        auto req = static_cast<Request*>(request);
        return strdup(req->getPath().c_str());
    }

    void* pryst_web_Request_getHeaders(void* request) {
        auto req = static_cast<Request*>(request);
        // TODO: Convert headers to runtime map type
        return nullptr;
    }

    const char* pryst_web_Request_getBody(void* request) {
        auto req = static_cast<Request*>(request);
        return strdup(req->getBody().c_str());
    }

    // Response methods
    void* pryst_web_Response_new(int status, const char* body) {
        auto response = new Response();
        response->status = status;
        response->body = body;
        return response;
    }

    void pryst_web_Response_setContent(void* response, const char* content, const char* type) {
        auto resp = static_cast<Response*>(response);
        resp->setContent(content, type);
    }

    int pryst_web_Response_getStatus(void* response) {
        auto resp = static_cast<Response*>(response);
        return resp->status;
    }

    const char* pryst_web_Response_getBody(void* response) {
        auto resp = static_cast<Response*>(response);
        return strdup(resp->body.c_str());
    }

    void* pryst_web_Response_getHeaders(void* response) {
        auto resp = static_cast<Response*>(response);
        // TODO: Convert headers to runtime map type
        return nullptr;
    }

    // WebServer methods
    void* pryst_web_WebServer_new(const char* host, int port) {
        auto server = new WebServer();
        // TODO: Set host and port
        return server;
    }

    void pryst_web_WebServer_start(void* server) {
        auto srv = static_cast<WebServer*>(server);
        // TODO: Implement actual server start
    }
}
