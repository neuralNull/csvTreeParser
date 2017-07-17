#include "treenode.h"

TreeNode::TreeNode(QObject *parent) :
  QObject(parent)
{
}

TreeNode *TreeNode::parentNode()
{
  return dynamic_cast<TreeNode *>(parent());
}

int TreeNode::id()
{
  return m_id;
}

QString TreeNode::title()
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

int TreeNode::childCount()
{
  return m_children.count();
}

TreeNode *TreeNode::child(int index)
{
  if (index < 0 || index >= m_children.count()) return nullptr;
  return m_children[index];
}

void TreeNode::clear()
{
  while (m_children.count())
    m_children.takeLast()->deleteLater();
}
