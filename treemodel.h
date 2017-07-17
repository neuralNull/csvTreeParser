#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>

class TreeNode;

class TreeModel : public QAbstractItemModel
{
  Q_OBJECT

public:
  explicit TreeModel(QObject *parent = 0);
  void parseCsvData(const QString &csvData);
  TreeNode *treeRoot();

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &child) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
  TreeNode *m_treeRoot;
};

#endif // TREEMODEL_H
