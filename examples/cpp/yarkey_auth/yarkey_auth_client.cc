
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "examples/cpp/yarkey_auth/protos/yarkey_auth.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::SslCredentials;

using yarkey::RegisteReq;
using yarkey::RegisterRsp;
using yarkey::AuthReq;
using yarkey::AuthRsp;
using yarkey::CheckTokenReq;
using yarkey::CheckTokenReq;
using yarkey::AuthService;

class AuthClient {
    public:
        AuthClient(std::shared_ptr<Channel> channel)
            : stub_(AuthService::NewStub(channel)) {}

  RegisterRsp * Register(const std::string& user, const std::string& password) {
    // Data we are sending to the server.
    RegisteReq request;
    request.set_name(user);
    request.set_password(password);

    // Container for the data we expect from the server.
    RegisterRsp * reply = new RegisterRsp();

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->Register(&context, request, reply);

    // Act upon its status.
    if (status.ok()) {
      std::cout << "Register Success : AccountId = " << reply->account_id() << std::endl;
      return reply;
    } else {
      std::cout << "Register Failed : " << status.error_code() << ": " << status.error_message() << std::endl;
      return nullptr;
    }
  }

  AuthRsp * Auth(const std::string& id, const std::string& password) {
    // Data we are sending to the server.
    AuthReq request;
    request.set_account_id(id);
    request.set_password(password);
    request.set_device_id("13579111315171921");

    AuthRsp * reply = new AuthRsp();
    ClientContext context;

    // The actual RPC.
    Status status = stub_->Auth(&context, request, reply);

    // Act upon its status.
    if (status.ok()) {
      std::cout
        << "Auth Success : token="
        << reply->token()
        << ", errorCode=" << reply->error().error_code()
        << ", error=" << reply->error().error_message()
        << std::endl;
      return reply;
    } else {
      std::cout << "Auth Failed : " << status.error_code() << ": " << status.error_message() << std::endl;
      return nullptr;
    }
  }

  private:
    std::unique_ptr<AuthService::Stub> stub_;
};

// TODO: 代码整理
static void read(const std::string &filename, std::string & data) {
	std::ifstream file(filename.c_str(), std::ios::in);
	if (file.is_open())	{
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		data = ss.str();
	}
}

void GetClientCredential(grpc::SslCredentialsOptions &sslOps) {
	std::string key;
	std::string cert;
	std::string root;

	read("D:\\yarkey\\github-grpc\\key_store\\client.key", key);
	read("D:\\yarkey\\github-grpc\\key_store\\client.crt", cert);
	read("D:\\yarkey\\github-grpc\\key_store\\ca.crt", root);

	sslOps.pem_private_key = key;
  sslOps.pem_cert_chain = cert;
  sslOps.pem_root_certs = root;
}

int main(int argc, char** argv) {
  
  grpc::SslCredentialsOptions sslOps;
  GetClientCredential(sslOps);
  auto credentials = grpc::SslCredentials(sslOps);

  AuthClient client(grpc::CreateChannel("localhost:50052", credentials));
  std::string user("yarkey");
  std::string password("123456");
  RegisterRsp * registerRsp = client.Register(user, password);
  AuthRsp * authRsp = client.Auth(registerRsp->account_id(), "123458");
  return 0;
}