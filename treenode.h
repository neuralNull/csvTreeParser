#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>
#include <QVector>

class TreeNode : public QObject
{
  Q_OBJECT

public:
  explicit TreeNode(QObject *parent = 0);

  TreeNode *parentNode();

  void setId(int id);
  void setTitle(const QString &title);

  int id();
  QString title();

  void addChild(TreeNode *child);

  int childCount();
  TreeNode *child(int index);
  void clear();

private:
  int m_id;
  QString m_title;
  QVector<TreeNode *> m_children;
};

#endif // TREENODE_H
