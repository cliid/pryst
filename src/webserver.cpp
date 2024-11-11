#include <cstdlib>
#include <string>
#include <memory>
#include <map>
#include <functional>
#include <httplib.h>

namespace pryst {

struct Request {
    std::string path;
    std::string method;
    std::map<std::string, std::string> headers;
    std::string body;
    std::map<std::string, std::string> queryParams;
};

struct Response {
    int status;
    std::map<std::string, std::string> headers;
    std::string body;
};

class Server {
private:
    httplib::Server server;
    int port;

public:
    Server(int port) : port(port) {}

    void get(const std::string& path, std::function<void(Request*, Response*)> handler) {
        server.Get(path, [handler](const httplib::Request& req, httplib::Response& res) {
            auto request = std::make_unique<Request>();
            auto response = std::make_unique<Response>();

            // Fill request object
            request->path = req.path;
            request->method = "GET";
            for (const auto& header : req.headers) {
                request->headers[header.first] = header.second;
            }
            request->body = req.body;
            for (const auto& param : req.params) {
                request->queryParams[param.first] = param.second;
            }

            // Call handler
            handler(request.get(), response.get());

            // Fill response
            res.status = response->status;
            for (const auto& header : response->headers) {
                res.set_header(header.first.c_str(), header.second.c_str());
            }
            res.body = response->body;
        });
    }

    void post(const std::string& path, std::function<void(Request*, Response*)> handler) {
        server.Post(path, [handler](const httplib::Request& req, httplib::Response& res) {
            auto request = std::make_unique<Request>();
            auto response = std::make_unique<Response>();

            // Fill request object
            request->path = req.path;
            request->method = "POST";
            for (const auto& header : req.headers) {
                request->headers[header.first] = header.second;
            }
            request->body = req.body;
            for (const auto& param : req.params) {
                request->queryParams[param.first] = param.second;
            }

            // Call handler
            handler(request.get(), response.get());

            // Fill response
            res.status = response->status;
            for (const auto& header : response->headers) {
                res.set_header(header.first.c_str(), header.second.c_str());
            }
            res.body = response->body;
        });
    }

    void listen() {
        server.listen("0.0.0.0", port);
    }
};

// Runtime interface
extern "C" void* Server_create(int port) {
    return new Server(port);
}

extern "C" void Server_get(void* server, const char* path, void (*handler)(void*, void*)) {
    auto srv = static_cast<Server*>(server);
    srv->get(path, [handler](Request* req, Response* res) {
        handler(req, res);
    });
}

extern "C" void Server_post(void* server, const char* path, void (*handler)(void*, void*)) {
    auto srv = static_cast<Server*>(server);
    srv->post(path, [handler](Request* req, Response* res) {
        handler(req, res);
    });
}

extern "C" void Server_listen(void* server) {
    auto srv = static_cast<Server*>(server);
    srv->listen();
}

extern "C" const char* Request_path(void* request) {
    auto req = static_cast<Request*>(request);
    return req->path.c_str();
}

extern "C" const char* Request_method(void* request) {
    auto req = static_cast<Request*>(request);
    return req->method.c_str();
}

extern "C" const char* Request_header(void* request, const char* key) {
    auto req = static_cast<Request*>(request);
    auto it = req->headers.find(key);
    return it != req->headers.end() ? it->second.c_str() : nullptr;
}

extern "C" const char* Request_query(void* request, const char* key) {
    auto req = static_cast<Request*>(request);
    auto it = req->queryParams.find(key);
    return it != req->queryParams.end() ? it->second.c_str() : nullptr;
}

extern "C" const char* Request_body(void* request) {
    auto req = static_cast<Request*>(request);
    return req->body.c_str();
}

extern "C" void* Response_status(void* response, int code) {
    auto res = static_cast<Response*>(response);
    res->status = code;
    return response;
}

extern "C" void* Response_header(void* response, const char* key, const char* value) {
    auto res = static_cast<Response*>(response);
    res->headers[key] = value;
    return response;
}

extern "C" void Response_send(void* response, const char* data) {
    auto res = static_cast<Response*>(response);
    res->body = data;
}

extern "C" void Response_json(void* response, const char* json) {
    auto res = static_cast<Response*>(response);
    res->headers["Content-Type"] = "application/json";
    res->body = json;
}

} // namespace pryst
