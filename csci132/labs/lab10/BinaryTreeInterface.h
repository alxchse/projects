// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified:
//  20 April 2021 - K. Walsh - fix style and added comments,
//     removed non-standard exceptions, and removed a few methods
//     defined in the textbook. Also added fancy 2-arg visitors.

/** Listing 15-1.
  @file BinaryTreeInterface.h */

#ifndef BINARY_TREE_INTERFACE_
#define BINARY_TREE_INTERFACE_

// BinaryTreeInterface is the API for a binary tree. The methods here are meant
// to operate on the ENTIRE tree, rather than on specific nodes within the tree.
// The detailed structure of the tree is mostly hidden from clients. This
// interface does not provide a way for clients to specify where new nodes get
// added into the tree, for example, or how the tree gets rearranged when nodes
// are removed. It is expected that implementations of this class would make
// such decisions automatically on behalf of clients. An implementation might
// add nodes in such a way as to keep the tree balanced, for example, or to keep
// it in sorted order.
template<class ItemType>
class BinaryTreeInterface {
  public:
    /** Tests whether this binary tree is empty.
      @return True if the binary tree is empty, or false if not. */
    virtual bool isEmpty() const = 0;

    /** Gets the height of this binary tree.
      @return The height of the binary tree. */
    virtual int getHeight() const = 0;

    /** Gets the number of nodes in this binary tree.
      @return The number of nodes in the binary tree. */
    virtual int getNumberOfNodes() const = 0;

    /** Adds a new node containing the given data to this binary tree.
     If the tree is currently empty, the new node will be added as the root.
     Otherwise, the new node will be added somewhere in the tree, and other
     nodes may be rearranged to make room. The placement strategy depends on the
     implementations of this class.
      @param newData  The data for the new node.
      @post  The binary tree contains a new node with the given data.
      @return  True if the addition is successful, or false not. */
    virtual bool add(const ItemType& newData) = 0;

    /** Removes the node containing the given data item from this binary tree.
     The remaining nodes of the tree may be rearranged in some way to accomodate
     the removal. The rearrangement strategy depends on the implementations of
     this class.
      @param data  The data value to remove from the binary tree.
      @return  True if the removal is successful, or false not. */
    virtual bool remove(const ItemType& data) = 0;

    /** Removes all nodes from this binary tree. */
    virtual void clear() = 0;

    /** Tests whether a given value appears in some node in this binary tree.
      @post  The binary search tree is unchanged.
      @param anEntry  The entry to find.
      @return  True if the entry occurs in the tree, or false if not. */
    virtual bool contains(const ItemType& anEntry) const = 0;

    /** Traverses this binary tree in preorder, inorder, or postorder style, and
      calls the provided visit() function upon visiting each node. For each node
      visited, the visit function is called with a copy of the data from that
      node. The visit function must be a void function, returning nothing. The
      tree is not modified.
      @param visit A client-defined function that performs some operation using
        the data in each visited node. 
      */
    virtual void preorderTraverse(void visit(ItemType)) const = 0;
    virtual void inorderTraverse(void visit(ItemType)) const = 0;
    virtual void postorderTraverse(void visit(ItemType)) const = 0;

    /** Destroys object and frees memory allocated by object. */
    virtual ~BinaryTreeInterface() {  }

    /** Gets the data that is in the root of this binary tree.
      @pre  The binary tree is not empty.
      @post  The root’s data has been returned, and the binary tree is unchanged.
      @return  The data in the root of the binary tree. */
    // This method removed by kwalsh. On the surface, this method makes no
    // sense. To get the value for most nodes, one must use the traversal
    // methods. So why should there be a specific method just to get the
    // root node's data?
    // virtual ItemType getRootData() const = 0;

    /** Replaces the data item in the root of this binary tree
      with the given data, if the tree is not empty. However, if
      the tree is empty, inserts a new root node containing the
      given data into the tree.
      @pre  None.
      @post  The data in the root of the binary tree is as given.
      @param newData  The data for the root. */
    // This method removed by kwalsh. On the surface, this method makes no
    // sense. To add nodes, one can call add(). And there are no methods to
    // change any other node in the tree, so why should there be a method to
    // change the root node's data?
    // virtual void setRootData(const ItemType& newData) = 0;

    /** Gets a specific entry in this binary tree.
      @post  The desired entry has been returned, and the binary tree
      is unchanged. If no such entry was found, an exception is thrown.
      @param anEntry  The entry to locate.
      @return  The entry in the binary tree that matches the given entry.
      @throw  NotFoundException if the given entry is not in the tree. */
    // This method removed by kwalsh. On the surface, this method makes no
    // sense: it always either fails, or returns the same value that was
    // given as the parameter. There is, however, a subtle purpose to this
    // method, but for now it will be commented out.
    // virtual ItemType getEntry(const ItemType& anEntry) const
    //                                      throw(NotFoundException) = 0;

}; // end BinaryTreeInterface
#endif
