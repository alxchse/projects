#ifndef TREE_NODE_
#define TREE_NODE_

#include "LinkedList.h"

template<class ItemType>
class TreeNode
{
private:
   ItemType item;                            // Data portion
   TreeNode<ItemType> *parent;               // Pointer to parent (or nullptr if this is root of a tree)
   LinkedList<TreeNode<ItemType>*> children; // List of children (or emptylist if this is a leaf of a tree)

   // WARNING: LinkedList uses 1-based indexing, where the first element is
   // position 1 and the last element in an N-element list is position N.
   // But TreeNode and Tree use 0-based indexing, where the first element
   // is position 0 and the last element is position N-1.
   
   // A private copy-constructor, to prevent accidental copying of TreeNode objects,
   // because copying a TreeNode object is most likely a mistake.
   // Note: copying of a pointer to a TreeNode object is fine, and will not be
   // affected by the private designation for this copy-constructor. 
   TreeNode(const TreeNode<ItemType>& original); // forbidden to copy-construct a TreeNode

   // A private assignment-operator, to prevent accidental assignment of TreeNode
   // objects, because assigning a TreeNode object is most likely a mistake.
   // Note: assignmnet of a pointer to a TreeNode object is fine, and will not be
   // affected by the private designation for this assignment-operator. 
   TreeNode<ItemType>& operator=(const TreeNode<ItemType>& original); // forbidden to assign a TreeNode
   
public:

   // default constructor makes a node with no parent, no children, and an
   // uninitialized data portion.
   TreeNode();

   // one-arg constructor makes a node with the given item for the data portion,
   // but no parent and no children.
   TreeNode(const ItemType& anItem);

   // two-arg constructor makes a tree with the given item for the data portion,
   // the given parent, and no children.
   TreeNode(const ItemType& anItem, TreeNode<ItemType> *aParent);
  
   // setItem modifies the data portion of this node
   void setItem(const ItemType& anItem);

   // getItem returns a copy of the data portion of this node
   ItemType getItem() const;
   
   // isRoot returns true if this node has no parent, and false otherwise
   bool isRoot() const;
  
   // isLeaf returns true if this node has no children, and false otherwise
   bool isLeaf() const;
   
   // getNumChildren returns a count of how many children this node has
   int getNumChildren() const;

   // getChild returns a pointer to one of this node's children
   // @param pos the position of the desired child, between 0 and getNumChildren()-1,
   // inclusive.
   TreeNode<ItemType>* getChild(int pos) const;

   // addChild adds a child to this nodes's list of children and returns the
   // position of the new chiild.
   int addChild(TreeNode<ItemType> *aChild);

   // removeChild removes one of this node's children
   // @param pos the position of the desired child, between 0 and getNumChildren()-1,
   // inclusive.
   bool removeChild(int pos);

   // getParent returns a pointer to this node's parent
   TreeNode<ItemType>* getParent() const;

   // setParent sets this node's parent
   void setParent(TreeNode<ItemType> *aParent);

}; // end TreeNode

#include "TreeNode.cpp"
#endif 
