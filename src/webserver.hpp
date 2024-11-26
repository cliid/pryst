#pragma once

#include <httplib.h>
#include <string>
#include <functional>
#include <memory>

namespace pryst {
namespace runtime {
namespace web {

class WebServer {
public:
    WebServer();
    ~WebServer();

    void start(int port);
    void stop();
    void handleRequest(const httplib::Request& req, httplib::Response& res);
    void get(const std::string& pattern, std::function<void(const httplib::Request&, httplib::Response&)> handler);
    void post(const std::string& pattern, std::function<void(const httplib::Request&, httplib::Response&)> handler);

private:
    std::unique_ptr<httplib::Server> server;
};

} // namespace web
} // namespace runtime
} // namespace pryst
