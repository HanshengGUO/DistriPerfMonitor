#include "net_model.h"

namespace monitor {

NetModel::NetModel(QObject* parent) : MonitorInterModel(parent) {
  header_ << tr("name");
  header_ << tr("send_rate");
  header_ << tr("rcv_rate");
  header_ << tr("send_packets_rate");
  header_ << tr("rcv_packets_rate");
}

int NetModel::rowCount(const QModelIndex& parent) const {
  return monitor_data_.size();
}

int NetModel::columnCount(const QModelIndex& parent) const {
  return COLUMN_MAX;
}

QVariant NetModel::headerData(int section, Qt::Orientation orientation,
                              int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    return header_[section];
  }

  return MonitorInterModel::headerData(section, orientation, role);
}

QVariant NetModel::data(const QModelIndex& index, int role) const {
  if (index.column() < 0 || index.column() >= COLUMN_MAX) {
    return QVariant();
  }

  if (role == Qt::DisplayRole) {
    if (index.row() < monitor_data_.size() && index.column() < COLUMN_MAX)
      return monitor_data_[index.row()][index.column()];
  }
  return MonitorInterModel::data(index, role);
}

void NetModel::UpdateMonitorInfo(
    const monitor::proto::MonitorInfo& monitor_info) {
  beginResetModel();
  monitor_data_.clear();

  for (int i = 0; i < monitor_info.net_info_size(); i++) {
    monitor_data_.push_back(insert_one_net_info(monitor_info.net_info(i)));
  }

  // QModelIndex leftTop = createIndex(0, 0);
  // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_MAX);
  // emit dataChanged(leftTop, rightBottom, {});

  endResetModel();

  return;
}

std::vector<QVariant> NetModel::insert_one_net_info(
    const monitor::proto::NetInfo& net_info) {
  std::vector<QVariant> net_info_list;
  for (int i = NetModelInfo::NAME; i < COLUMN_MAX; i++) {
    switch (i) {
      case NetModelInfo::NAME:
        net_info_list.push_back(QString::fromStdString(net_info.name()));
        break;
      case NetModelInfo::SEND_RATE:
        net_info_list.push_back(QVariant(net_info.send_rate()));
        break;
      case NetModelInfo::RCV_RATE:
        net_info_list.push_back(QVariant(net_info.rcv_rate()));
        break;
      case NetModelInfo::SEND_PACKETS_RATE:
        net_info_list.push_back(QVariant(net_info.send_packets_rate()));
        break;
      case NetModelInfo::RCV_PACKETS_RATE:
        net_info_list.push_back(QVariant(net_info.rcv_packets_rate()));
        break;
      default:
        break;
    }
  }
  return net_info_list;
}
}  // namespace monitor
