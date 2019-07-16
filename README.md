gRPC - An RPC library and framework
===================================

Fork from : https://github.com/grpc/grpc

## Setup Guide on Windows-OS

### 1. install
[visual studio](https://visualstudio.microsoft.com/zh-hans/vs/older-downloads/)  
[golang](https://golang.org/dl/)  
[cmake](https://cmake.org/download/)  
[active state perl](https://www.activestate.com/activeperl/)  
[yasm](http://yasm.tortall.net/)  
[android studio](https://developer.android.com/studio)  

### 2. get source code
```
git clone https://github.com/yarkey09/grpc.git grpc  
cd grpc  
git submodule update --init
```

### 3. build (Windows / Visual Studio)
```
md .build
cd .build
cmake .. -G "Visual Studio 15 2017"
```

open /.build/grpc.sln by Visual Studio  
build **ALL_BUILD** project  
build **INSTALL** project  

generate helloworld-proto c++ files by .bat script
```
cd yarkey_grpc_server
yarkey_generate_pb.bat
```

### 4. build (Android / Android Studio)
open "grpc\examples\android\helloworld" project (with settings.gradle) by Android Studio  
gradle sync  
download buildTools, sdk, ndk if needed  
edit gradle.properties, make sure paths to the protoc and grpc_cpp_plugin binaries

```
protoc=D\:\\yarkey_2019\\grpc\\.build\\third_party\\protobuf\\Debug\\protoc.exe
grpc_cpp_plugin=D\:\\yarkey_2019\\grpc\\.build\\Debug\\grpc_cpp_plugin.exe
```
edit build.gradle, make sure ndk.abiFilters target your test device
```
defaultConfig {
    ndk.abiFilters 'armeabi-v7a'  
}
```
gradlew assembleDebug

