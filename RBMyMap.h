#ifndef RBMyMap_H
#define RBMyMap_H

#include "RBTreeNode.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

template <typename K, typename V> class RBMyMap {
private:
  RBTreeNode<K, V> *root = nullptr;
    void clear_helper(RBTreeNode<K, V> *&rt);
    void rotateLeft(RBTreeNode<K, V>  *&pt);
    void rotateRight(RBTreeNode<K, V>  *&pt);
    void deleteNode(RBTreeNode<K, V>  *pt);
    void fixInsertViolation(RBTreeNode<K, V>  *&pt);
    void fixDoubleBlack(RBTreeNode<K, V>  *pt);
    void erase_helper(const K &erase_key);
    RBTreeNode<K, V>* insert_helper(RBTreeNode<K, V> * root, RBTreeNode<K, V>  *pt);
    RBTreeNode<K, V>* find_helper(RBTreeNode<K, V> *rt, const K &search_key) const;
    //RBTreeNode<K, V>* inSuccessorNode(RBTreeNode<K, V> * );
    //RBTreeNode<K, V>* PredecessorNode(RBTreeNode<K, V> * );
    //void findPreSuc(RBTreeNode<K, V> *, RBTreeNode<K, V> *&, RBTreeNode<K, V> *&, int);
    void printTreeHelper(const RBTreeNode<K,V>* rt, int space) {
    const int spacePerLevel =5; // Change this to increase or decrease spacing between levels
    // if (rt == nullptr) {
    //     // Print space for leaf node
    //     std::cout << std::string(space * spacePerLevel, ' ') << "NN" << std::endl;
    //     return;
    // }
    if (rt != nullptr) {
        printTreeHelper(rt->right, space + 1); // Recur for right subtree

        // Print current node after space
        // Count of spaces is depth * spacePerLevel
        std::cout << std::string(space * spacePerLevel, ' ') << rt->key << rt->color << std::endl;

        printTreeHelper(rt->left, space + 1); // Recur for left subtree
    }
}

public:
  RBMyMap();

  ~RBMyMap();

  RBMyMap(const RBMyMap<K, V> &source);

  RBMyMap<K, V> &operator=(const RBMyMap<K, V> &source);

  RBTreeNode<K, V> *&begin();

  V &at(const K &access_key);

  V &operator[](const K &access_key);

  // Returns true if the tree has no nodes
  // Returns false otherwise
  bool empty() const;

  int size() const;

  void clear();

  void insert(const K &new_key, const V &new_value);

  void erase(const K &erase_key);

  RBTreeNode<K, V> *find(const K &search_key) const;

  void print() const;

  void convert_to_sorted_list(RBTreeNode<K, V> *&rt, std::vector<V> &sorted);

  void inorderTraversal() {
        inorderTraversalHelper(root);
    }
 
  void printTree() {
        printTreeHelper(root, 0);
    }
};

#include "RBMyMap.hpp"
#endif
