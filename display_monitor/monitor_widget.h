#pragma once

#include <QStandardItemModel>
#include <QtWidgets>
#include <thread>
#include <string>

#include "cpu_load_model.h"
#include "cpu_softirq_model.h"
#include "cpu_stat_model.h"
#include "mem_model.h"
#include "net_model.h"

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"


namespace monitor {
class MonitorWidget : public QWidget {
  Q_OBJECT
 public:
  explicit MonitorWidget(QWidget* parent = nullptr);
  ~MonitorWidget() {
    // stop_ = true;
    // if (thread_->joinable()) {
    //   thread_->join();
    // }
  }
  QWidget* ShowAllMonitorWidget(const std::string& name);
  QWidget* InitCpuMonitorWidget();
  QWidget* InitSoftIrqMonitorWidget();
  QWidget* InitMemMonitorWidget();
  QWidget* InitNetMonitorWidget();
  QWidget* InitButtonMenu(const std::string& name);
  // QWidget* InitMemMonitorWidget();

  void UpdateData(const monitor::proto::MonitorInfo& monitor_info);

 private slots:
  void ClickCpuButton();
  void ClickSoftIrqButton();
  void ClickMemButton();
  void ClickNetButton();

 private:
  QTableView* monitor_view_ = nullptr;
  QTableView* cpu_load_monitor_view_ = nullptr;
  QTableView* cpu_stat_monitor_view_ = nullptr;
  QTableView* mem_monitor_view_ = nullptr;
  QTableView* net_monitor_view_ = nullptr;

  MonitorBaseModel* monitor_model_ = nullptr;
  CpuLoadModel* cpu_load_model_ = nullptr;
  CpuStatModel* cpu_stat_model_ = nullptr;
  MemModel* mem_model_ = nullptr;
  NetModel* net_model_ = nullptr;

  QStackedLayout* stack_menu_ = nullptr;

  // std::unique_ptr<std::thread> thread_;
  // bool stop = false;
};
}  // namespace monitor
