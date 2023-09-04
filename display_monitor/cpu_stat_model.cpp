#include "cpu_stat_model.h"

namespace monitor {
CpuStatModel::CpuStatModel(QObject* parent) : MonitorInterModel(parent) {
  header_ << tr("name");
  header_ << tr("cpu_percent");
  header_ << tr("user");
  header_ << tr("system");
}

int CpuStatModel::rowCount(const QModelIndex& parent) const {
  return monitor_data_.size();
}

int CpuStatModel::columnCount(const QModelIndex& parent) const {
  return COLUMN_MAX;
}

QVariant CpuStatModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    return header_[section];
  }

  return MonitorInterModel::headerData(section, orientation, role);
}

QVariant CpuStatModel::data(const QModelIndex& index, int role) const {
  if (index.column() < 0 || index.column() >= COLUMN_MAX) {
    return QVariant();
  }

  if (role == Qt::DisplayRole) {
    if (index.row() < monitor_data_.size() && index.column() < COLUMN_MAX)
      return monitor_data_[index.row()][index.column()];
  }
  return MonitorInterModel::data(index, role);
}

void CpuStatModel::UpdateMonitorInfo(
    const monitor::proto::MonitorInfo& monitor_info) {
  beginResetModel();
  monitor_data_.clear();

  for (int i = 0; i < monitor_info.cpu_stat_size(); i++) {
    // std::cout <<monitor_info.cpu_stat(i).cpu_name()<<std::endl;
    monitor_data_.push_back(insert_one_cpu_stat(monitor_info.cpu_stat(i)));
  }
  // QModelIndex leftTop = createIndex(0, 0);
  // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_MAX);
  // emit dataChanged(leftTop, rightBottom, {});

  endResetModel();

  return;
}

std::vector<QVariant> CpuStatModel::insert_one_cpu_stat(
    const monitor::proto::CpuStat& cpu_stat) {
  std::vector<QVariant> cpu_stat_list;
  for (int i = CpuStat::CPU_NAME; i < COLUMN_MAX; i++) {
    switch (i) {
      case CpuStat::CPU_NAME:
        cpu_stat_list.push_back(QString::fromStdString(cpu_stat.cpu_name()));
        break;
      case CpuStat::CPU_PERCENT:
        cpu_stat_list.push_back(QVariant(cpu_stat.cpu_percent()));
        break;
      case CpuStat::CPU_USER_PERCENT:
        cpu_stat_list.push_back(QVariant(cpu_stat.usr_percent()));
        break;
      case CpuStat::CPU_SYSTEM_PERCENT:
        cpu_stat_list.push_back(QVariant(cpu_stat.system_percent()));
        break;
      default:
        break;
    }
  }
  return cpu_stat_list;
}
}  // namespace monitor
