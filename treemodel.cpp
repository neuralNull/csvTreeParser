#include "treemodel.h"
#include "treenode.h"

#include <QDebug>
#include <QPair>

TreeModel::TreeModel(QObject *parent) :
  QAbstractItemModel(parent),
  m_treeRoot(new TreeNode(this))
{
}

TreeNode *TreeModel::treeRoot()
{
  return m_treeRoot;
}

void TreeModel::parseCsvData(const QString &csvData)
{
  beginResetModel();

  treeRoot()->clear();

  QMap<int, QPair<TreeNode *, int>> treeNodes;

  foreach (QString line, csvData.split('\n'))
  {
    QStringList lineData = line.split(';');
    if (lineData.count() < 3) continue;

    int id = lineData[0].toInt();
    if (treeNodes.contains(id)) continue;

    QString title = lineData[1];
    int parentId = lineData[2].toInt();

    TreeNode *treeNode = new TreeNode();
    treeNode->setId(id);
    treeNode->setTitle(title);

    treeNodes[id] = { treeNode, parentId };
  }

  foreach (auto pair, treeNodes.values())
  {
    TreeNode *treeNode = pair.first;
    int parentId = pair.second;

    if (treeNodes.contains(parentId))
      treeNodes[parentId].first->addChild(treeNode);
    else m_treeRoot->addChild(treeNode);
  }

  endResetModel();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid()) return QVariant();
  if (role != Qt::DisplayRole) return QVariant();

  TreeNode *item = static_cast<TreeNode*>(index.internalPointer());

  return item->title();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
  if (!index.isValid()) return 0;
  return Qt::ItemIsEnabled;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent)) return QModelIndex();

  TreeNode *parentNode;
  if (parent.isValid()) parentNode = static_cast<TreeNode *>(parent.internalPointer());
  else parentNode = m_treeRoot;

  TreeNode *childNode = parentNode->child(row);
  if (childNode) return createIndex(row, column, childNode);

  return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &child) const
{
  if (!child.isValid()) return QModelIndex();

  TreeNode *childNode = static_cast<TreeNode *>(child.internalPointer());
  TreeNode *parentNode = childNode->parentNode();

  if (parentNode == m_treeRoot) return QModelIndex();

  int row;
  for (row = 0; parentNode->parentNode()->child(row) != parentNode; row++ );

  return createIndex(row, 0, parentNode);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Horizontal &&
      role == Qt::DisplayRole && section == 0) return tr("Node");

  return QVariant();
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
  TreeNode *parentNode;

  if (parent.column() > 0) return 0;

  if (!parent.isValid()) parentNode = m_treeRoot;
  else parentNode = static_cast<TreeNode*>(parent.internalPointer());

  return parentNode->childCount();
}

int TreeModel::columnCount(const QModelIndex &) const
{
  return 1;
}
