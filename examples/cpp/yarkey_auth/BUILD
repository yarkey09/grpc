load("//bazel:grpc_build_system.bzl", "grpc_proto_library")
load("//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("//bazel:python_rules.bzl", "py_proto_library")

proto_library(
    name = "yarkey_auth_proto",
    srcs = ["protos/yarkey_auth.proto"],
)

cc_proto_library(
    name = "yarkey_auth_cc_proto",
    deps = [":yarkey_auth_proto"],
)

cc_grpc_library(
    name = "yarkey_auth_cc_grpc",
    srcs = [":yarkey_auth_proto"],
    grpc_only = True,
    deps = [":yarkey_auth_cc_proto"],
)

cc_binary(
    name = "yarkey_auth_client",
    srcs = ["yarkey_auth_client.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":yarkey_auth_cc_grpc",
        "//:grpc++",
    ],
)

cc_binary(
    name = "yarkey_auth_server",
    srcs = ["yarkey_auth_server.cc", "account_info.cc", "token_holder.cc", "utils.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":yarkey_auth_cc_grpc",
        "//:grpc++",
    ],
)