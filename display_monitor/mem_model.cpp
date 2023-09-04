#include "mem_model.h"

namespace monitor {
MemModel::MemModel(QObject* parent) : MonitorInterModel(parent) {
  header_ << tr("used_percent");
  header_ << tr("total");
  header_ << tr("free");
  header_ << tr("avail");
  header_ << tr("buffers");
  header_ << tr("cached");
  header_ << tr("swap_cached");
  header_ << tr("active");
  header_ << tr("in_active");
  header_ << tr("active_anon");
  header_ << tr("inactive_anon");
  header_ << tr("active_file");
  header_ << tr("inactive_file");
  header_ << tr("dirty");
  header_ << tr("writeback");
  header_ << tr("anon_pages");
  header_ << tr("mapped");
  header_ << tr("kReclaimable");
  header_ << tr("sReclaimable");
  header_ << tr("sUnreclaim");
}

int MemModel::rowCount(const QModelIndex& parent) const {
  return monitor_data_.size();
}

int MemModel::columnCount(const QModelIndex& parent) const {
  return COLUMN_MAX;
}

QVariant MemModel::headerData(int section, Qt::Orientation orientation,
                              int role) const {
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
    return header_[section];
  }

  return MonitorInterModel::headerData(section, orientation, role);
}

QVariant MemModel::data(const QModelIndex& index, int role) const {
  if (index.column() < 0 || index.column() >= COLUMN_MAX) {
    return QVariant();
  }

  if (role == Qt::DisplayRole) {
    if (index.row() < monitor_data_.size() && index.column() < COLUMN_MAX)
      return monitor_data_[index.row()][index.column()];
  }
  return MonitorInterModel::data(index, role);
}

void MemModel::UpdateMonitorInfo(
    const monitor::proto::MonitorInfo& monitor_info) {
  beginResetModel();
  monitor_data_.clear();

  monitor_data_.push_back(insert_one_mem_info(monitor_info.mem_info()));
  // QModelIndex leftTop = createIndex(0, 0);
  // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_MAX);
  // emit dataChanged(leftTop, rightBottom, {});

  endResetModel();

  return;
}

std::vector<QVariant> MemModel::insert_one_mem_info(
    const monitor::proto::MemInfo& mem_info) {
  std::vector<QVariant> mem_info_list;
  for (int i = MemInfo::USED_PERCENT; i < COLUMN_MAX; i++) {
    switch (i) {
      case MemInfo::USED_PERCENT:
        mem_info_list.push_back(QVariant(mem_info.used_percent()));
        break;
      case MemInfo::TOTAL:
        mem_info_list.push_back(QVariant(mem_info.total()));
        break;
      case MemInfo::FREE:
        mem_info_list.push_back(QVariant(mem_info.free()));
        break;
      case MemInfo::AVAIL:
        mem_info_list.push_back(QVariant(mem_info.avail()));
        break;
      case MemInfo::BUFFERS:
        mem_info_list.push_back(QVariant(mem_info.buffers()));
        break;
      case MemInfo::CACHED:
        mem_info_list.push_back(QVariant(mem_info.cached()));
        break;
      case MemInfo::SWAP_CACHED:
        mem_info_list.push_back(QVariant(mem_info.swap_cached()));
        break;
      case MemInfo::ACTIVE:
        mem_info_list.push_back(QVariant(mem_info.active()));
        break;
      case MemInfo::INACTIVE:
        mem_info_list.push_back(QVariant(mem_info.inactive()));
        break;
      case MemInfo::ACTIVE_ANON:
        mem_info_list.push_back(QVariant(mem_info.active_anon()));
        break;
      case MemInfo::INACTIVE_ANON:
        mem_info_list.push_back(QVariant(mem_info.inactive_anon()));
        break;
      case MemInfo::DIRTY:
        mem_info_list.push_back(QVariant(mem_info.dirty()));
        break;
      case MemInfo::WRITEBACK:
        mem_info_list.push_back(QVariant(mem_info.writeback()));
        break;
      case MemInfo::ANON_PAGES:
        mem_info_list.push_back(QVariant(mem_info.anon_pages()));
        break;
      case MemInfo::MAPPED:
        mem_info_list.push_back(QVariant(mem_info.mapped()));
        break;
      case MemInfo::KRECLAIMABLE:
        mem_info_list.push_back(QVariant(mem_info.kreclaimable()));
        break;
      case MemInfo::SRECLAIMABLE:
        mem_info_list.push_back(QVariant(mem_info.sreclaimable()));
        break;
      case MemInfo::SUNRECLAIM:
        mem_info_list.push_back(QVariant(mem_info.sunreclaim()));
        break;
      default:
        break;
    }
  }
  return mem_info_list;
}
}  // namespace monitor
