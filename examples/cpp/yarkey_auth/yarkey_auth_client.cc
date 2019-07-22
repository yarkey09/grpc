
#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "examples/cpp/yarkey_auth/protos/yarkey_auth.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

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

      // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string Register(const std::string& user, const std::string& password) {
    // Data we are sending to the server.
    RegisteReq request;
    request.set_name(user);
    request.set_password(password);

    // Container for the data we expect from the server.
    RegisterRsp reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->Register(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      // std::cout << "Register : " << reply.account_id << std::endl;
      return "Yarkey"; // reply.account_id;
    } else {
      std::cout << status.error_code() << ": " << status.error_message() << std::endl;
      return "RPC failed";
    }
  }

    private:
        std::unique_ptr<AuthService::Stub> stub_;
};

int main(int argc, char** argv) {
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    AuthClient client(grpc::CreateChannel(
        "localhost:50052", grpc::InsecureChannelCredentials()));
    std::string user("yarkey");
    std::string password("123456");
    std::string reply = client.Register(user, password);
    std::cout << "Auth result : " << reply << std::endl;
    return 0;
}