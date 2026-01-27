// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified:
//  Fall 2020 - Zack Fitzsimmons - removed smart pointers
//  20 April 2021 - K. Walsh - fix style and added comments,
//     removed non-standard exceptions, and removed/modified
//     a few methods that were defined in the textbook.

/** ADT binary tree: Link-based implementation.
  Listing 16-3.
  @file BinaryNodeTree.h */

#ifndef BINARY_NODE_TREE_
#define BINARY_NODE_TREE_

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include <string>

// A link-based implementation of BinaryTreeInterface. This implementation
// attempts to maintain balance whenever adding or removing nodes, though it
// does not guarantee balance in all cases when removals happen. The values
// stored in the nodes are not sorted in any particular way.
template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType> {
  protected:
    // A pointer to the root node, or nullptr if the tree is empty.
    BinaryNode<ItemType>* rootPtr;  

  protected:
    //------------------------------------------------------------
    // Protected Utility Methods Section:
    // Recursive helper methods for the public methods.
    //------------------------------------------------------------
    //
    void swapSubTreeHelper(BinaryNode<ItemType>* subTreePtr);

    // Returns largest entry in nonempty subtree rooted at subTreePtr
    ItemType getMax(const BinaryNode<ItemType>* subTreePtr) const;

    // Returns smallest entry in nonempty subtree rooted at subTreePtr
    ItemType getMin(const BinaryNode<ItemType>* subTreePtr) const;

    // Recursively check if the given subtree is a binary search tree
    bool isBSTHelper(const BinaryNode<ItemType>* subTreePtr) const;

    // Recursively calculate the height of the given subtree.
    int getHeightHelper(const BinaryNode<ItemType>* subTreePtr) const;

    // Recursively calculate the size of the given subtree.
    int getNumberOfNodesHelper(const BinaryNode<ItemType>* subTreePtr) const;

    // Recursively searches for the given target value in the given subtree
    // using a preorder traversal. This returns a pointer to the node, if found,
    // or nullptr if no such node could be located.
    virtual BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* subTreePtr,
        const ItemType& target) const;

    // Recursively makes a copy of the entire given subtree and all its
    // descendants. This returns a pointer to the root node of the copy. If the
    // original subtree was empty, then nullptr is returned instead.
    BinaryNode<ItemType>* copyHelper(BinaryNode<ItemType>* oldSubTreePtr) const;

    // Recursively deletes all nodes from the given subtree. This takes a
    // pointer to a node, and it deletes all of the descendants of that node,
    // along with the node itself. It does NOT, however, set the subtree pointer
    // to be null. The caller must do that instead, if desired.
    void destroyHelper(BinaryNode<ItemType>* subTreePtr);

    // Recursive traversal helper methods.
    void preorderHelper(void visit(ItemType), const BinaryNode<ItemType>* subTreePtr) const;
    void inorderHelper(void visit(ItemType), const BinaryNode<ItemType>* subTreePtr) const;
    void postorderHelper(void visit(ItemType), const BinaryNode<ItemType>* subTreePtr) const;

    // Recursively search the given subtree looking for a nice place to add a
    // new node somewhere below the given node, then add the new node at that
    // location in the tree. This method guarantees the tree will be balanced.
    // Or, at least, it guarantees that if the tree was balanced before adding
    // the node, then it will still be balanced once the new node is added, and
    // that adding to an unbalanced tree will make it no more unbalanced than it
    // was before.
    // @pre subTreePtr is not null
    // @param subTreePtr is a REFERENCE to a pointer to some existing node in
    //   the tree structure, or it can be nullptr to indicate this part of the
    //   overall tree structure has no nodes yet.
    // @param newNodePtr is a pointer to a newly allocated node that isn't yet
    //   part of the tree structure.
    // @post The new node is linked into structure somewhere below subtree.
    // @post The subtree will still be balanced, if it was before, or it will at
    //    least be no more unbalanced than it was, if it was unbalanced before.
    void balancedAdd(BinaryNode<ItemType>* subTreePtr,
        BinaryNode<ItemType>* newNodePtr);

    // Removes the target value from a subtree, possibly deleting and/or
    // rearranging nodes, and/or copying values from certain nodes to other
    // nodes to fill in any holes in the tree structure, and returns a pointer
    // to the root of the rearranged/modified subtree. If no nodes in this
    // subtree contain the target value, then the subtree is not modified in any
    // way, and the function instead just sets sucesss to false and returns a
    // pointer to the original subtree. The work of actually removing the value
    // and rearranging the nodes and/or values to fill in gaps in the tree
    // structure is handled by another helper method, moveValuesUpTree.
    //
    // @param subTreePtr - a subtree from which to remove the target value.
    // @param target - the target value to be removed. Only the first match will
    //   be removed in cases where multiple nodes match the target.
    // @param success - a reference to  boolean. This will be set to true or
    //   false, depending on whether the target was found (and removed) or not.
    // @pre None. The subTreePtr may be null, or non-null, and if non-null the
    //   target item might appear in that node or in one of that node's
    //   descendants, or perhaps nowhere at all.
    // @returns A pointer to a possibly modified subtree that contains all the
    //   same data as the original, except with (one copy of) the target
    //   removed. The returned pointer will be nullptr if the subtree was empty
    //   to start with, or if the subtree has become empty due to the removal of
    //   the target. Otherwise, the returned pointer will point to the
    //   same node object as the original subtree (but possibly with its value
    //   having been overwritten with a new value).
    // @post the returned subtree is identical to the original subtree, but with
    //   one copy of the target removed, and some nodes possibly rearranged.
    virtual BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr,
        const ItemType& target, bool& success);

    // Given a pointer to a node whose value is considered vacant (or "dead"),
    // this method repairs the vacancy by either (a) simply deleting the node,
    // if it was a leaf node, or (b) overwriting its value by pulling one of the
    // values upwards from one of the child nodes then recursively filling the
    // vacancy this creates in that child node. This method takes care to
    // maintain balance where possible by always pulling values up from
    // whichever child has greater height.
    //
    // @param subTreePtr - pointer to a subtree where the root node is
    //   considered to be "vacant" without a valid data value, but all other
    //   nodes below the root of the subtree have valid data values.
    // @pre subTreePtr must not be null (but it's value is considered vacant). It
    //   may be a leaf, or it may have one or more children.
    // @returns A pointer to the root of the repaired subtree, or nullptr if the
    //   entire subtree (a single leaf) was deleted.
    // @post The subtree has been repaired, with all remaining nodes now
    //   containing valid data values.
    BinaryNode<ItemType>* moveValuesUpTree(BinaryNode<ItemType>* subTreePtr);

    // Pretty-print a subtree to standard output.
    void prettyPrintHelper(std::string firstLinePrefix, std::string childLinePrefix,
        const BinaryNode<ItemType>* subtree) const;

  public:
    //------------------------------------------------------------
    // Constructor and Destructor Section.
    //------------------------------------------------------------
   
    BinaryNodeTree(); // Default constructor.
    BinaryNodeTree(const BinaryNodeTree<ItemType>& original); // Copy-constructor.
    BinaryNodeTree<ItemType>& operator=(const BinaryNodeTree<ItemType>& original); // Assignment-operator.
    virtual ~BinaryNodeTree(); // Destructor

    //------------------------------------------------------------
    // Public BinaryTreeInterface Methods Section.
    //------------------------------------------------------------
    bool isEmpty() const;
    int getHeight() const;
    int getNumberOfNodes() const;
    bool add(const ItemType& newData);
    bool remove(const ItemType& data);
    void clear();
    bool contains(const ItemType& anEntry) const;
    void preorderTraverse(void visit(ItemType)) const;
    void inorderTraverse(void visit(ItemType)) const;
    void postorderTraverse(void visit(ItemType)) const;

    //------------------------------------------------------------
    // Additional methods not present in BinaryTreeInterface.
    //------------------------------------------------------------
    void swapSubTree();
    bool isBST() const;

    // Pretty-print a tree to standard output.
    virtual void prettyPrint() const;

}; // end BinaryNodeTree
#include "BinaryNodeTree.cpp"
#endif
