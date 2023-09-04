#pragma once

#include <string>
#include <unordered_map>

#include "monitor/monitor_inter.h"
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
class CpuStatMonitor : public MonitorInter {
  struct CpuStat {
    std::string cpu_name;
    float user;
    float system;
    float idle;
    float nice;
    float io_wait;
    float irq;
    float soft_irq;
    float steal;
    float guest;
    float guest_nice;
  };

 public:
  CpuStatMonitor() {}
  void UpdateOnce(monitor::proto::MonitorInfo* monitor_info);
  void Stop() override {}

 private:
  std::unordered_map<std::string, struct CpuStat> cpu_stat_map_;
};

}  // namespace monitor
