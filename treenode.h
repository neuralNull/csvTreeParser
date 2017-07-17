#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>
#include <QVector>

class TreeNode : public QObject
{
  Q_OBJECT

public:
  explicit TreeNode(QObject *parent = 0);

  TreeNode *parentNode() const;

  void setId(int id);
  void setTitle(const QString &title);

  int id() const;
  QString title() const;

  void addChild(TreeNode *child);

  int childCount() const;
  TreeNode *child(int index) const;
  void clear();

private:
  int m_id;
  QString m_title;
  QVector<TreeNode *> m_children;
};

#endif // TREENODE_H
