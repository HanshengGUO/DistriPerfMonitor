#pragma once
#include <QAbstractTableModel>
#include <QObject>

namespace monitor {

class MonitorInterModel : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit MonitorInterModel(QObject *parent = nullptr)
      : QAbstractTableModel(parent) {}
  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role) const override;
  virtual ~MonitorInterModel() {}
};

}  // namespace monitor