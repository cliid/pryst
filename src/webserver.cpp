#include "webserver.hpp"
#include <iostream>

namespace pryst {
namespace runtime {
namespace web {

WebServer::WebServer() : server(std::make_unique<httplib::Server>()) {}

WebServer::~WebServer() {
    stop();
}

void WebServer::start(int port) {
    if (!server->listen("0.0.0.0", port)) {
        throw std::runtime_error("Failed to start server on port " + std::to_string(port));
    }
}

void WebServer::stop() {
    if (server) {
        server->stop();
    }
}

void WebServer::handleRequest(const httplib::Request& req, httplib::Response& res) {
    res.set_content("Hello from Pryst!", "text/plain");
}

void WebServer::get(const std::string& pattern,
                   std::function<void(const httplib::Request&, httplib::Response&)> handler) {
    server->Get(pattern, handler);
}

void WebServer::post(const std::string& pattern,
                    std::function<void(const httplib::Request&, httplib::Response&)> handler) {
    server->Post(pattern, handler);
}

} // namespace web
} // namespace runtime
} // namespace pryst
