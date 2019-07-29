
#include <grpcpp/grpcpp.h>
#include "examples/cpp/yarkey_auth/protos/yarkey_auth.grpc.pb.h"

#include <iostream>
#include <fstream>
#include <sstream>

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


int autoIncreaseNumber = 0;

static void read(const std::string &filename, std::string & data) {
	std::ifstream file(filename.c_str(), std::ios::in);
	if (file.is_open())	{
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		data = ss.str();
	}
}

void GetServerCredential(grpc::SslServerCredentialsOptions &sslOps) {
	std::string key;
	std::string cert;
	std::string root;

	read("D:\\yarkey\\github-grpc\\key_store\\server.key", key);
	read("D:\\yarkey\\github-grpc\\key_store\\server.crt", cert);
	read("D:\\yarkey\\github-grpc\\key_store\\ca.crt", root);

	grpc::SslServerCredentialsOptions::PemKeyCertPair key_cert = { key, cert };
	sslOps.pem_root_certs = root;
	sslOps.pem_key_cert_pairs.push_back(key_cert);
}

class AuthServiceImpl final : public AuthService::Service {
    // 注册，生成新账户ID
    Status Register(ServerContext* context, const RegisteReq* request, RegisterRsp* response) override {
        std::cout << "Register : name=" << request->name() << ", password=" << request->password() << std::endl;
        response->set_account_id("xxx" + std::to_string((autoIncreaseNumber ++)));
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

    grpc::SslServerCredentialsOptions ssl_opts;
    GetServerCredential(ssl_opts);
    auto creds = grpc::SslServerCredentials(ssl_opts);

    builder.AddListeningPort(server_address, creds);
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