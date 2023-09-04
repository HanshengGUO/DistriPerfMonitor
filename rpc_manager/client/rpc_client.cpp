#include "rpc_client.h"

namespace monitor {
RpcClient::RpcClient() {
  auto channel = grpc::CreateChannel("localhost:50051",
                                     grpc::InsecureChannelCredentials());
  stub_ptr_ = monitor::proto::GrpcManager::NewStub(channel);
}
RpcClient::~RpcClient() {}

void RpcClient::SetMonitorInfo(const monitor::proto::MonitorInfo& monito_info) {
  ::grpc::ClientContext context;
  ::google::protobuf::Empty response;
  ::grpc::Status status =
      stub_ptr_->SetMonitorInfo(&context, monito_info, &response);
  if (status.ok()) {
  } else {
    std::cout << status.error_details() << std::endl;
    std::cout << "falied to connect !!!" << std::endl;
  }
}

void RpcClient::GetMonitorInfo(monitor::proto::MonitorInfo* monito_info) {
  ::grpc::ClientContext context;
  ::google::protobuf::Empty request;
  ::grpc::Status status =
      stub_ptr_->GetMonitorInfo(&context, request, monito_info);
  if (status.ok()) {
  } else {
    std::cout << status.error_details() << std::endl;
    std::cout << "falied to connect !!!" << std::endl;
  }
}
}  // namespace monitor
