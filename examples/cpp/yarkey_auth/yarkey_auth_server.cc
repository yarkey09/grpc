
#include <grpcpp/grpcpp.h>
#include "examples/cpp/yarkey_auth/protos/yarkey_auth.grpc.pb.h"

#include "account_info.h"
#include "account_info.cc"

#include "token_holder.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using yarkey::AuthService;
using yarkey::RegisteReq;
using yarkey::RegisterRsp;
using yarkey::AuthReq;
using yarkey::AuthRsp;
using yarkey::CheckTokenReq;
using yarkey::CheckTokenRsp;
using yarkey::AccountInfo;
using yarkey::AccountInfoRef;
using yarkey::TokenHolder;
using yarkey::TokenHolderRef;

using grpc::Status;
using grpc::Server;
using grpc::ServerContext;
using grpc::ServerBuilder;

using std::map;
using std::string;

// TODO: 持久化
int autoIncreaseNumber = 0;
// 注册账户
map<string, AccountInfoRef> registered_account_map;
// 登录账户
map<string, TokenHolderRef> login_token_map;

static void read(const string &filename, string & data) {
	std::ifstream file(filename.c_str(), std::ios::in);
	if (file.is_open())	{
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		data = ss.str();
	}
}

void GetServerCredential(grpc::SslServerCredentialsOptions &sslOps) {
	string key;
	string cert;
	string root;

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

        string newAccountId = "xxx" + std::to_string(autoIncreaseNumber ++);
        AccountInfoRef newAccountInfo = new AccountInfo(newAccountId, request->password(), request->name());
        registered_account_map.insert(std::pair<string, AccountInfoRef>(newAccountId, newAccountInfo));

        response->set_account_id(newAccountId);
        return Status::OK;
    }

    // 认证登录
    Status Auth(ServerContext* context, const AuthReq* request, AuthRsp* response) override {
        std::cout << "Auth " << request << std::endl;

        // 先检查身份 accountId+password
        // TODO: 这里后面改成独立一个服务，认证身份 和 换票换deviceId 独立
        auto iter = registered_account_map.find(request->account_id());
        if(iter != registered_account_map.end()) {
            string inputId = request->account_id();
            string inputPassword = request->password();
            auto accountInfoRef = iter->second;
            if (strcmp(accountInfoRef->getAccountId().c_str(), inputId.c_str()) 
                && strcmp(accountInfoRef->getPassword().c_str(), inputPassword.c_str())) {
                
                // ID+密码正确，更新 device Id, 通知下线
                auto tokenIter = login_token_map.find(request->account_id());
                if (tokenIter != login_token_map.end()) {
                    auto tokenHolderRef = tokenIter->second;
                    
                }
            }
        }
        

        request->account_id();

        return Status::OK;
    }

    // 验票
    Status CheckToken(ServerContext* context, const CheckTokenReq* request, CheckTokenRsp* response) override {
        std::cout << "CheckToken " << request << std::endl;
        return Status::OK;
    }
};

void RunServer() {
    string server_address("0.0.0.0:50052");
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