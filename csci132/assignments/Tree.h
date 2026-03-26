#ifndef TREE_H_
#define TREE_H_

#include "TreeNode.h"

template<class ItemType>
class Tree
{
private:
   TreeNode<ItemType> *rootPtr;

protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------

   int getHeightHelper(TreeNode<ItemType> *treePtr) const;

   int getNumberOfNodesHelper(TreeNode<ItemType> *treePtr) const;

   // Removes a node containing the target value from the children of the tree
   // (or subtree), along with any descendents of that node, using a preorder
   // traversl. Only the first matching node is removed. Caution: treePtr itself
   // is not checked and is never removed. Instead, only children of treePtr are
   // checked. Returns true if a matching node was found and removed, or
   // returns false if no such node was found.
   bool removeHelper(TreeNode<ItemType> *treePtr, const ItemType& target);

   // Recursively searches for target value in a tree (or subtree) using a
   // preorder traversal. Returns a pointer to a node containing that value, or
   // returns nullptr if no such node was found.
   TreeNode<ItemType>* findNodeHelper(TreeNode<ItemType> *treePtr, const ItemType& target) const;
    
   // Recursively copies the tree (or subtree) rooted at treePtr and returns a
   // pointer to the copy.
   TreeNode<ItemType> *copyTree(const TreeNode<ItemType> *originalTreePtr) const;

   // Recursively deletes all nodes from the tree (or subtree) rooted at treePtr,
   // including deleting treePtr itself.
   void destroyTree(TreeNode<ItemType> *treePtr);

//    // Recursive traversal helper methods:
//    void preorder(void visit(ItemType&), TreeNode<ItemType> *treePtr) const;
//    void inorder(void visit(ItemType&), TreeNode<ItemType> *treePtr) const;
//    void postorder(void visit(ItemType&), TreeNode<ItemType> *treePtr) const;
   
public:
   //------------------------------------------------------------
   // Constructor, Destructor, and Assignment Operator Section.
   //------------------------------------------------------------

   Tree(); // default constructor
   Tree(const ItemType& rootItem); // constructor to make a single-node tree
   Tree(const Tree<ItemType>& original); // copy constructor
   ~Tree(); // destructor
   Tree<ItemType>& operator=(const Tree<ItemType>& original); // copy assignment operator
   
   //------------------------------------------------------------
   // Public BinaryTreeInterface Methods Section.
   //------------------------------------------------------------
   bool isEmpty() const; // check whether this tree is empty
   int getHeight() const; // count the levels in this tree
   int getNumberOfNodes() const; // count the nodes in this tree

   // Get a pointer to the root node of this tree, or returns null if this tree
   // is empty.
   TreeNode<ItemType>* getRoot() const;

   // Find and return some node in this tree that matches the given target, or
   // returns null if no such node was found.
   TreeNode<ItemType>* findNode(const ItemType& target) const;

   // Find some node containing the given parent data, and add a new child node with
   // the given data to that parent node. Returns true if successful, and false
   // if no such parent node was found.
   bool addAsChild(const ItemType& newData, const ItemType &parentData);

   // Adds a new node containing the given data as the root of the tree.
   // Returns true if successful, or false if there was already a root node.
   bool addAsRoot(const ItemType& newData);

   // Find and remove a node containing the given data, along with all of that
   // node's descendants. If there are multiple matching nodes, only one of them
   // is removed. Returns true if a node was found and removed, and false if no
   // such node was found.
   bool removeNodeAndDescendants(const ItemType& data);

   // Clears all nodes.
   void clear();

   // Checks whether the tree contains a node matching the given data.
   bool contains(const ItemType& someData) const;
   
//    //------------------------------------------------------------
//    // Public Traversals Section.
//    //------------------------------------------------------------
//    void preorderTraverse(void visit(ItemType&)) const;
//    void inorderTraverse(void visit(ItemType&)) const;
//    void postorderTraverse(void visit(ItemType&)) const;
   
}; // end Tree
#include "Tree.cpp"
#endif
