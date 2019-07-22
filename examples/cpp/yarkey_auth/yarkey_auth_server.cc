
#include <grpcpp/grpcpp.h>
#include "examples/cpp/yarkey_auth/protos/yarkey_auth.grpc.pb.h"

#include <iostream>

using yarkey::AuthService;
using yarkey::RegisteReq;
using yarkey::RegisterRsp;
using yarkey::AuthReq;
using yarkey::AuthRsp;
using yarkey::CheckTokenReq;
using yarkey::CheckTokenRsp;

using grpc::Status;
using grpc::Server;
using grpc::ServerContext;
using grpc::ServerBuilder;


class AuthServiceImpl final : public AuthService::Service {
    // 注册，生成新账户ID
    Status Register(ServerContext* context, const RegisteReq* request, RegisterRsp* response) override {
        std::cout << "Register " << request << std::endl;
        return Status::OK;
    }
    // 认证登录
    Status Auth(ServerContext* context, const AuthReq* request, AuthRsp* response) override {
        std::cout << "Auth " << request << std::endl;
        return Status::OK;
    }
    // 验票
    Status CheckToken(ServerContext* context, const CheckTokenReq* request, CheckTokenRsp* response) override {
        std::cout << "CheckToken " << request << std::endl;
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50052");
    AuthServiceImpl service;

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}