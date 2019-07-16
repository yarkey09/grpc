set PROTOC=..\.build\third_party\protobuf\Debug\protoc.exe
%PROTOC% --proto_path=..\examples\protos --grpc_out=. --plugin=protoc-gen-grpc=..\.build\Debug\grpc_cpp_plugin.exe helloworld.proto
%PROTOC% --proto_path=..\examples\protos --cpp_out=. helloworld.proto