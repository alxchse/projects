#include "TreeNode.h"

template<class ItemType>
TreeNode<ItemType>::TreeNode()
  : item(), parent(nullptr), children()
{ }  // end default constructor

template<class ItemType>
TreeNode<ItemType>::TreeNode(const ItemType& anItem)
  : item(anItem), parent(nullptr), children()
{ }  // end constructor

template<class ItemType>
TreeNode<ItemType>::TreeNode(const ItemType& anItem, TreeNode<ItemType> *aParent)
  : item(anItem), parent(aParent), children()
{ }  // end constructor

template<class ItemType>
void TreeNode<ItemType>::setItem(const ItemType& anItem)
{
  item = anItem;
}  // end setItem

template<class ItemType>
ItemType TreeNode<ItemType>::getItem() const 
{
  return item;
}  // end getItem

template<class ItemType>
bool TreeNode<ItemType>::isRoot() const
{
  return (parent == nullptr);
}

template<class ItemType>
bool TreeNode<ItemType>::isLeaf() const
{
  return children.isEmpty();
}

template<class ItemType>
int TreeNode<ItemType>::getNumChildren() const
{
  return children.getLength();
}  // end getNumChildren

template<class ItemType>
TreeNode<ItemType>* TreeNode<ItemType>::getChild(int pos) const
{
  return children.getEntry(pos+1); // WARNING: LinkedList uses 1-based indexing!
}  // end getChild

template<class ItemType>
int TreeNode<ItemType>::addChild(TreeNode<ItemType> *aChild)
{
  int pos = children.getLength();
  children.insert(pos+1, aChild); // WARNING: LinkedList uses 1-based indexing!
  return pos;
}  // end addChild

template<class ItemType>
bool TreeNode<ItemType>::removeChild(int pos)
{
  return children.remove(pos+1); // WARNING: LinkedList uses 1-based indexing!
}  // end removeChild

template<class ItemType>
TreeNode<ItemType>* TreeNode<ItemType>::getParent() const
{
  return parent;
}  // end getParent

template<class ItemType>
void TreeNode<ItemType>::setParent(TreeNode<ItemType> *aParent)
{
  parent = aParent;
}  // end setParent

