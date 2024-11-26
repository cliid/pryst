#include "web_types.hpp"
#include "runtime_registry.hpp"
#include "../type_registry.hpp"
#include "web.hpp"

namespace pryst {
namespace runtime {
namespace web {

extern "C" void* webserver_constructor() {
    return new runtime::web::WebServer();
}

// Static wrapper functions for Request methods
extern "C" void* request_constructor(const char* method, const char* path, const char* headers, const char* body) {
    return new pryst::runtime::web::Request(method, path, std::map<std::string, std::string>(), body);
}

extern "C" const char* request_get_method(void* request) {
    static std::string result;  // Static to ensure the c_str() remains valid
    result = static_cast<runtime::web::Request*>(request)->getMethod();
    return result.c_str();
}

extern "C" const char* request_get_path(void* request) {
    static std::string result;
    result = static_cast<runtime::web::Request*>(request)->getPath();
    return result.c_str();
}

extern "C" const char* request_get_headers(void* request) {
    static std::string result;
    result = static_cast<runtime::web::Request*>(request)->getHeaders();
    return result.c_str();
}

extern "C" const char* request_get_body(void* request) {
    static std::string result;
    result = static_cast<runtime::web::Request*>(request)->getBody();
    return result.c_str();
}

extern "C" void* response_constructor() {
    return new runtime::web::Response();
}

extern "C" void response_set_status(void* response, int status) {
    static_cast<runtime::web::Response*>(response)->status = status;
}

extern "C" void response_set_body(void* response, const char* body) {
    static_cast<runtime::web::Response*>(response)->body = body;
}

extern "C" void response_set_content_type(void* response, const char* contentType) {
    static_cast<runtime::web::Response*>(response)->contentType = contentType;
    static_cast<runtime::web::Response*>(response)->headers["Content-Type"] = contentType;
}

extern "C" void response_set_content(void* response, const char* content, const char* contentType) {
    auto resp = static_cast<runtime::web::Response*>(response);
    resp->body = content;
    resp->contentType = contentType;
    resp->headers["Content-Type"] = contentType;
}

extern "C" void webserver_get(void* server, const char* path, void* handler) {
    static_cast<runtime::web::WebServer*>(server)->get(path, *static_cast<std::function<void(runtime::web::Request&, runtime::web::Response&)>*>(handler));
}

extern "C" void webserver_start(void* server, int port) {
    static_cast<runtime::web::WebServer*>(server)->start(port);
}

void registerWebTypes(RuntimeRegistry& registry) {
    std::cout << "Debug [registerWebTypes]: Starting web types registration" << std::endl;
    auto& context = registry.getModule()->getContext();
    auto* typeRegistry = registry.getTypeRegistry();

    // Step 1: Register namespaces first
    std::cout << "Debug [registerWebTypes]: Registering namespaces" << std::endl;
    if (!typeRegistry->isNamespaceRegistered("pryst")) {
        typeRegistry->registerNamespace("pryst");
    }
    if (!typeRegistry->isNamespaceRegistered("pryst::runtime")) {
        typeRegistry->registerNamespace("pryst::runtime");
    }
    if (!typeRegistry->isNamespaceRegistered("pryst::runtime::web")) {
        typeRegistry->registerNamespace("pryst::runtime::web");
    }

    // Step 2: Create class types without LLVM types first
    std::cout << "Debug [registerWebTypes]: Creating class types" << std::endl;

    // Create LLVM types for web classes
    std::vector<std::pair<std::string, llvm::Type*>> requestMembers = {
        {"method", llvm::PointerType::get(llvm::Type::getInt8Ty(typeRegistry->getContext()), 0)},
        {"path", llvm::PointerType::get(llvm::Type::getInt8Ty(typeRegistry->getContext()), 0)},
        {"body", llvm::PointerType::get(llvm::Type::getInt8Ty(typeRegistry->getContext()), 0)}
    };
    typeRegistry->registerClass("pryst::runtime::web::Request", requestMembers);

    std::vector<std::pair<std::string, llvm::Type*>> responseMembers = {
        {"status", llvm::Type::getInt32Ty(typeRegistry->getContext())},
        {"body", llvm::PointerType::get(llvm::Type::getInt8Ty(typeRegistry->getContext()), 0)},
        {"contentType", llvm::PointerType::get(llvm::Type::getInt8Ty(typeRegistry->getContext()), 0)}
    };
    typeRegistry->registerClass("pryst::runtime::web::Response", responseMembers);

    std::vector<std::pair<std::string, llvm::Type*>> serverMembers;  // WebServer has no members, just methods
    typeRegistry->registerClass("pryst::runtime::web::WebServer", serverMembers);

    // Get the registered types
    auto requestClassType = typeRegistry->getCachedType("pryst::runtime::web::Request");
    auto responseClassType = typeRegistry->getCachedType("pryst::runtime::web::Response");
    auto serverClassType = typeRegistry->getCachedType("pryst::runtime::web::WebServer");

    // Add methods to the types
    requestClassType->addMethod("getMethod", STRING_TYPE);
    requestClassType->addMethod("getPath", STRING_TYPE);
    requestClassType->addMethod("getHeaders", STRING_TYPE);
    requestClassType->addMethod("getBody", STRING_TYPE);

    responseClassType->addMethod("setStatus", VOID_TYPE, {INT_TYPE});
    responseClassType->addMethod("setBody", VOID_TYPE, {STRING_TYPE});
    responseClassType->addMethod("setContentType", VOID_TYPE, {STRING_TYPE});
    responseClassType->addMethod("setContent", VOID_TYPE, {STRING_TYPE, STRING_TYPE});

    // Handler type for get method: function(Request, Response) -> void
    std::vector<std::shared_ptr<Type>> handlerParams = {requestClassType, responseClassType};
    auto handlerType = std::make_shared<FunctionType>(VOID_TYPE, handlerParams);

    serverClassType->addMethod("get", VOID_TYPE, {STRING_TYPE, handlerType});
    serverClassType->addMethod("start", VOID_TYPE, {INT_TYPE});

    // Register with runtime registry
    registry.registerClass("pryst::runtime::web::Request", "Request", typeRegistry->getClassType("pryst::runtime::web::Request"));
    registry.registerClass("pryst::runtime::web::Response", "Response", typeRegistry->getClassType("pryst::runtime::web::Response"));
    registry.registerClass("pryst::runtime::web::WebServer", "WebServer", typeRegistry->getClassType("pryst::runtime::web::WebServer"));

    // Create map type for headers
    auto strType = typeRegistry->getCachedType("str");
    auto headersMapType = std::make_shared<MapType>(strType, strType);
    typeRegistry->cacheType("map<str,str>", headersMapType);

    // Request members
    std::vector<std::pair<std::string, llvm::Type*>> requestFields;
    requestFields.push_back(std::make_pair("method", typeRegistry->getLLVMType(strType)));
    requestFields.push_back(std::make_pair("path", typeRegistry->getLLVMType(strType)));
    requestFields.push_back(std::make_pair("headers", typeRegistry->getLLVMType(headersMapType)));
    requestFields.push_back(std::make_pair("body", typeRegistry->getLLVMType(strType)));

    // Response members
    std::vector<std::pair<std::string, llvm::Type*>> responseFields;
    responseFields.push_back(std::make_pair("status", llvm::Type::getInt32Ty(context)));
    responseFields.push_back(std::make_pair("headers", typeRegistry->getLLVMType(headersMapType)));
    responseFields.push_back(std::make_pair("body", typeRegistry->getLLVMType(strType)));
    responseFields.push_back(std::make_pair("contentType", typeRegistry->getLLVMType(strType)));

    // WebServer members
    std::vector<std::pair<std::string, llvm::Type*>> serverFields;
    serverFields.push_back(std::make_pair("routes", typeRegistry->getLLVMType(strType)));

    // Step 5: Create LLVM struct types
    std::cout << "Debug [registerWebTypes]: Creating LLVM struct types" << std::endl;
    std::vector<llvm::Type*> requestTypeFields;
    for (const auto& member : requestMembers) {
        requestTypeFields.push_back(member.second);
    }
    auto requestType = llvm::StructType::create(context, requestTypeFields, "struct.pryst.runtime.web.Request");

    std::vector<llvm::Type*> responseTypeFields;
    for (const auto& member : responseMembers) {
        responseTypeFields.push_back(member.second);
    }
    auto responseType = llvm::StructType::create(context, responseTypeFields, "struct.pryst.runtime.web.Response");

    std::vector<llvm::Type*> serverTypeFields;
    for (const auto& member : serverMembers) {
        serverTypeFields.push_back(member.second);
    }
    auto serverType = llvm::StructType::create(context, serverTypeFields, "struct.pryst.runtime.web.WebServer");

    // Step 6: Register classes with members
    std::cout << "Debug [registerWebTypes]: Registering classes with members" << std::endl;
    typeRegistry->registerClass("pryst::web::Request", requestMembers);
    typeRegistry->registerClass("pryst::web::Response", responseMembers);
    typeRegistry->registerClass("pryst::web::WebServer", serverMembers);

    // Step 7: Register in runtime registry
    std::cout << "Debug [registerWebTypes]: Registering in runtime registry" << std::endl;
    registry.registerClass("Request", "pryst::web::Request", requestType);
    registry.registerClass("Response", "pryst::web::Response", responseType);
    registry.registerClass("WebServer", "pryst::web::WebServer", serverType);

    // Step 8: Register constructors and methods
    std::cout << "Debug [registerWebTypes]: Registering constructors and methods" << std::endl;

    // Register Request constructor
    ClassMethod requestConstructor(
        "Request",
        (void*)&request_constructor,
        std::vector<std::string>{"method", "path", "headers", "body"},
        "pryst::web::Request"
    );
    registry.registerClassMethod("Request", requestConstructor);
    registry.registerClassMethod("pryst::web::Request", requestConstructor);

    // Register Request methods
    ClassMethod requestGetMethod("getMethod", (void*)&request_get_method, std::vector<std::string>{}, "str");
    ClassMethod requestGetPath("getPath", (void*)&request_get_path, std::vector<std::string>{}, "str");
    ClassMethod requestGetHeaders("getHeaders", (void*)&request_get_headers, std::vector<std::string>{}, "str");
    ClassMethod requestGetBody("getBody", (void*)&request_get_body, std::vector<std::string>{}, "str");

    registry.registerClassMethod("pryst::web::Request", requestGetMethod);
    registry.registerClassMethod("Request", requestGetMethod);
    registry.registerClassMethod("pryst::web::Request", requestGetPath);
    registry.registerClassMethod("Request", requestGetPath);
    registry.registerClassMethod("pryst::web::Request", requestGetHeaders);
    registry.registerClassMethod("Request", requestGetHeaders);
    registry.registerClassMethod("pryst::web::Request", requestGetBody);
    registry.registerClassMethod("Request", requestGetBody);

    // Register Response constructor
    typeRegistry->registerConstructor("pryst::web::Response", std::vector<llvm::Type*>{});
    ClassMethod responseConstructor(
        "Response",
        (void*)&response_constructor,
        std::vector<std::string>{},
        "pryst::web::Response"
    );
    registry.registerClassMethod("Response", responseConstructor);
    registry.registerClassMethod("pryst::web::Response", responseConstructor);

    // Register Response methods
    ClassMethod responseSetStatus("setStatus", (void*)&response_set_status, std::vector<std::string>{"status"}, "void");
    ClassMethod responseSetBody("setBody", (void*)&response_set_body, std::vector<std::string>{"body"}, "void");
    ClassMethod responseSetContentType("setContentType", (void*)&response_set_content_type, std::vector<std::string>{"contentType"}, "void");
    ClassMethod responseSetContent("setContent", (void*)&response_set_content, std::vector<std::string>{"content", "contentType"}, "void");

    registry.registerClassMethod("pryst::web::Response", responseSetStatus);
    registry.registerClassMethod("Response", responseSetStatus);
    registry.registerClassMethod("pryst::web::Response", responseSetBody);
    registry.registerClassMethod("Response", responseSetBody);
    registry.registerClassMethod("pryst::web::Response", responseSetContentType);
    registry.registerClassMethod("Response", responseSetContentType);
    registry.registerClassMethod("pryst::web::Response", responseSetContent);
    registry.registerClassMethod("Response", responseSetContent);

    // Register WebServer constructor
    typeRegistry->registerConstructor("pryst::web::WebServer", std::vector<llvm::Type*>{});
    ClassMethod webServerConstructor(
        "WebServer",
        (void*)&webserver_constructor,
        std::vector<std::string>{},
        "pryst::web::WebServer"
    );
    registry.registerClassMethod("WebServer", webServerConstructor);
    registry.registerClassMethod("pryst::web::WebServer", webServerConstructor);

    // Register WebServer methods
    ClassMethod webserverGet("get", (void*)&webserver_get, std::vector<std::string>{"path", "handler"}, "void");
    ClassMethod webserverStart("start", (void*)&webserver_start, std::vector<std::string>{"port"}, "void");

    registry.registerClassMethod("pryst::web::WebServer", webserverGet);
    registry.registerClassMethod("WebServer", webserverGet);
    registry.registerClassMethod("pryst::web::WebServer", webserverStart);
    registry.registerClassMethod("WebServer", webserverStart);

    std::cout << "Debug [registerWebTypes]: All web types registered successfully" << std::endl;
}

} // namespace web
} // namespace runtime
} // namespace pryst
