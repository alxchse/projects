
#include "Tree.h" 
#include "TreeNode.h" 
#include <cassert>


//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType>
int Tree<ItemType>::getHeightHelper(TreeNode<ItemType> *treePtr) const
{
  if (treePtr == nullptr)
    return 0;

  int maxChildHeight = 0;
  int n = treePtr->getNumChildren();
  for (int i = 0; i < n; i++) {
    int childHeight = getHeightHelper(treePtr->getChild(i));
    if (childHeight > maxChildHeight)
      maxChildHeight = childHeight;
  }
  return 1 + maxChildHeight;
}  // end getHeightHelper

template<class ItemType>
int Tree<ItemType>::getNumberOfNodesHelper(TreeNode<ItemType> *treePtr) const
{
  if (treePtr == nullptr)
    return 0;

  int numDescendents = 0;
  int n = treePtr->getNumChildren();
  for (int i = 0; i < n; i++) {
    numDescendents += getNumberOfNodesHelper(treePtr->getChild(i));
  }
  return 1 + numDescendents;
}  // end getNumberOfNodesHelper

template<class ItemType>
bool Tree<ItemType>::removeHelper(TreeNode<ItemType> *treePtr, const ItemType& target)
{
  assert(treePtr != nullptr);

  bool removed = false;
  int n = treePtr->getNumChildren();
  for (int i = 0; i < n && !removed; i++) {
    TreeNode<ItemType> *child = treePtr->getChild(i);
    if (child->getItem() == target) { // target found as one of direct children
      treePtr->removeChild(i);
      deleteTree(child);
      removed = true;
    } else {
      // check if target is a descendent of this child
      removed = removeHelper(child, target);
    }
  }  // end for
  return removed;
}  // end removeHelper

template<class ItemType>
TreeNode<ItemType>* Tree<ItemType>::findNodeHelper(
    TreeNode<ItemType> *treePtr,
    const ItemType& target) const
{
  if (treePtr == nullptr) // not found here because subtree is empty
    return nullptr;

  if (treePtr->getItem() == target) // found it at the root of subtree
    return treePtr;

  // check each child
  TreeNode<ItemType> *match = nullptr;
  int n = treePtr->getNumChildren();
  for (int i = 0; i < n && match == nullptr; i++) {
      match = findNodeHelper(treePtr->getChild(i), target);
  }
  return match;
}  // end findNodeHelper

template<class ItemType>
TreeNode<ItemType> *Tree<ItemType>::copyTree(const TreeNode<ItemType> *originalTreePtr) const
{
   TreeNode<ItemType> *newTreePtr = nullptr;
   
   // Copy subtree tree nodes during a preorder traversal
   if (originalTreePtr != nullptr)
   {
      // Copy the subtree root
      newTreePtr = new TreeNode<ItemType>(originalTreePtr->getItem());
      // Copy all of the children
      int n = originalTreePtr->getNumChildren();
      for (int i = 0; i < n; i++) {
        TreeNode<ItemType> *copiedChild = copyTree(originalTreePtr->getChild(i));
        newTreePtr->addChild(copiedChild);
      }
   }  // end if
   
   return newTreePtr;
}  // end copyTree

template<class ItemType>
void Tree<ItemType>::destroyTree(TreeNode<ItemType> *treePtr)
{
   if (treePtr != nullptr)
   {
     int n = treePtr->getNumChildren();
     for (int i = 0; i < n; i++) {
      destroyTree(treePtr->getChild(i));
     }
     delete treePtr;
   }  // end if
}  // end destroyTree

// //////////////////////////////////////////////////////////////
// //      Protected Tree Traversal Sub-Section
// //////////////////////////////////////////////////////////////
// 
// template<class ItemType>
// void Tree<ItemType>::preorder(void visit(ItemType&), TreeNode<ItemType> *treePtr) const
// {
//    if (treePtr != nullptr)
//    {
//       ItemType theItem = treePtr->getItem();
//       visit(theItem);
// //      visit(treePtr->getItem());
//       preorder(visit, treePtr->getLeftChildPtr());
//       preorder(visit, treePtr->getRightChildPtr());
//    }  // end if
// }  // end preorder
// 
// template<class ItemType>
// void Tree<ItemType>::inorder(void visit(ItemType&), TreeNode<ItemType> *treePtr) const
// {
//    if (treePtr != nullptr)
//    {
//       inorder(visit, treePtr->getLeftChildPtr());
//       ItemType theItem = treePtr->getItem();
//       visit(theItem);
//       inorder(visit, treePtr->getRightChildPtr());
//    }  // end if
// }  // end inorder
// 
// template<class ItemType>
// void Tree<ItemType>::postorder(void visit(ItemType&), TreeNode<ItemType> *treePtr) const
// {
//    if (treePtr != nullptr)
//    {
//       postorder(visit, treePtr->getLeftChildPtr());
//       postorder(visit, treePtr->getRightChildPtr());
//       ItemType theItem = treePtr->getItem();
//       visit(theItem);
//    } // end if
// }  // end postorder
// 
// //////////////////////////////////////////////////////////////
// //      PUBLIC METHODS BEGIN HERE
// //////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

template<class ItemType>
Tree<ItemType>::Tree()
  : rootPtr(nullptr)
{  }  // end default constructor

template<class ItemType>
Tree<ItemType>::Tree(const ItemType& rootItem)
  : rootPtr(new TreeNode<ItemType>(rootItem))
{  }  // end constructor

template<class ItemType>
Tree<ItemType>::Tree(const Tree<ItemType>& original)
{
  rootPtr = copyTree(original.rootPtr);
}  // end copy constructor

template<class ItemType>
Tree<ItemType>::~Tree()
{
  clear();
}  // end destructor

template<class ItemType>
Tree<ItemType>& Tree<ItemType>::operator=(const Tree<ItemType>& original)
{
  if (this != &original) {
    clear();
    rootPtr = copyTree(original.rootPtr);
  }
  return *this;
}  // end operator=


//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////


template<class ItemType>
bool Tree<ItemType>::isEmpty() const
{
  return rootPtr == nullptr;
}  // end isEmpty

template<class ItemType>
int Tree<ItemType>::getHeight() const
{
  return getHeightHelper(rootPtr);
}  // end getHeight

template<class ItemType>
int Tree<ItemType>::getNumberOfNodes() const
{
  return getNumberOfNodesHelper(rootPtr);
}  // end getNumberOfNodes

template<class ItemType>
void Tree<ItemType>::clear()
{
  destroyTree(rootPtr);
  rootPtr = nullptr;
}  // end clear

template<class ItemType>
TreeNode<ItemType>* Tree<ItemType>::getRoot() const
{
  return rootPtr;
}  // end getRoot

template<class ItemType>
bool Tree<ItemType>::addAsRoot(const ItemType& newData)
{
  if (rootPtr != nullptr)
    return false;
  rootPtr = new TreeNode<ItemType>(newData);
  return true;
}  // end addAsRoot

template<class ItemType>
TreeNode<ItemType>* Tree<ItemType>::findNode(const ItemType& anItem) const
{
  return findNodeHelper(rootPtr, anItem);
}  // end findNode

template<class ItemType>
bool Tree<ItemType>::addAsChild(const ItemType& newData, const ItemType &parentData)
{
  TreeNode<ItemType> *parent = findNodeHelper(rootPtr, parentData);
  if (parent == nullptr) {
    return false;
  } else {
    TreeNode<ItemType> *child = new TreeNode<ItemType>(newData, parent);
    parent->addChild(child);
    return true;
  }
}  // end addAsChild

template<class ItemType>
bool Tree<ItemType>::removeNodeAndDescendants(const ItemType& target)
{
  if (isEmpty()) {
    return false;
  } else if (rootPtr->getItem() == target) {
    clear();
  } else {
    return removeHelper(rootPtr, target);
  }
}  // end removeNodeAndDescendants

template<class ItemType>
bool Tree<ItemType>:: contains(const ItemType& someData) const
{
  return findNodeHelper(rootPtr, someData) != nullptr;
}  // end contains

// //////////////////////////////////////////////////////////////
// //      Public Traversals Section
// //////////////////////////////////////////////////////////////
// 
// template<class ItemType>
// void Tree<ItemType>::preorderTraverse(void visit(ItemType&)) const
// {
//   preorder(visit, rootPtr);
// }  // end preorderTraverse
// 
// template<class ItemType>
// void Tree<ItemType>::inorderTraverse(void visit(ItemType&)) const
// {
//   inorder(visit, rootPtr);
// }  // end inorderTraverse
// 
// template<class ItemType>
// void Tree<ItemType>::postorderTraverse(void visit(ItemType&)) const
// {
//   postorder(visit, rootPtr);
// }  // end postorderTraverse
// 
