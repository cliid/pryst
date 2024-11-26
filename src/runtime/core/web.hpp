#pragma once

#include <string>
#include <map>
#include <functional>

namespace pryst {
namespace runtime {
namespace web {

class Request {
public:
    std::string method;
    std::string path;
    std::map<std::string, std::string> headers;
    std::string body;

    Request(std::string method = "GET", std::string path = "/",
            std::map<std::string, std::string> headers = {},
            std::string body = "")
        : method(method), path(path), headers(headers), body(body) {}

    // Getter methods
    std::string getMethod() const;
    std::string getPath() const;
    std::string getHeaders() const;
    std::string getBody() const;
};

class Response {
public:
    int status;
    std::map<std::string, std::string> headers;
    std::string body;
    std::string contentType;

    Response() : status(200) {}

    void setContent(const std::string& content, const std::string& type) {
        body = content;
        contentType = type;
        headers["Content-Type"] = type;
    }
};

class WebServer {
public:
    WebServer() {}

    void get(const std::string& path, std::function<void(Request&, Response&)> handler) {
        routes[path] = handler;
    }

    void start(int port) {
        // TODO: Implement actual server startup
    }

private:
    std::map<std::string, std::function<void(Request&, Response&)>> routes;
};

} // namespace web
} // namespace runtime
} // namespace pryst
