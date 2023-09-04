#pragma once

#include <QApplication>
#include <thread>
#include "client/rpc_client.h"
#include "monitor_widget.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  monitor::MonitorWidget moitor_widget;
  monitor::RpcClient rpc_client;
  monitor::proto::MonitorInfo monitor_info;

  //get board name
  rpc_client.GetMonitorInfo(&monitor_info);
  std::string name = monitor_info.name();

  QWidget* widget = moitor_widget.ShowAllMonitorWidget(name);
  widget->show();

  std::unique_ptr<std::thread> thread_;
  thread_ = std::make_unique<std::thread>([&]() {
    while (true) {
      monitor_info.Clear();
      rpc_client.GetMonitorInfo(&monitor_info);

      moitor_widget.UpdateData(monitor_info);
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  });
  thread_->detach();

  return app.exec();
}