#include "treenode.h"

TreeNode::TreeNode(QObject *parent) :
  QObject(parent)
{
}

TreeNode *TreeNode::parentNode() const
{
  return dynamic_cast<TreeNode *>(parent());
}

int TreeNode::id() const
{
  return m_id;
}

QString TreeNode::title() const
{
  return m_title;
}

void TreeNode::setId(int id)
{
  m_id = id;
}

void TreeNode::setTitle(const QString &title)
{
  m_title = title;
}

void TreeNode::addChild(TreeNode *child)
{
  m_children.append(child);
  child->setParent(this);
}

int TreeNode::childCount() const
{
  return m_children.count();
}

TreeNode *TreeNode::child(int index) const
{
  if (index < 0 || index >= m_children.count()) return nullptr;
  return m_children[index];
}

void TreeNode::clear()
{
  while (m_children.count())
    m_children.takeLast()->deleteLater();
}
