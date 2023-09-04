#include <iostream>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include "rpc_manager.h"

constexpr char kServerPortInfo[] = "0.0.0.0:50051";
void InitServer() {
  grpc::ServerBuilder builder;
  builder.AddListeningPort(kServerPortInfo, grpc::InsecureServerCredentials());

  monitor::GrpcManagerImpl grpc_server;
  builder.RegisterService(&grpc_server);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();

  return;
}

int main() {
  InitServer();
  return 0;
}