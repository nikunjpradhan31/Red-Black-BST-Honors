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
    int size_helper(RBTreeNode<K, V> *rt) const;
    RBTreeNode<K, V>* find_helper(RBTreeNode<K, V> *rt, const K &search_key) const;
    //RBTreeNode<K, V> *get_min(RBTreeNode<K, V> *x);
    void printTreeHelper(const RBTreeNode<K,V>* rt, int space);

public:

  RBMyMap();
  ~RBMyMap();
  RBMyMap(const RBMyMap<K, V> &source);
  RBMyMap<K, V> &operator=(const RBMyMap<K, V> &source);
  RBTreeNode<K, V> *&begin();
  bool empty() const;
  int size() const;
  void clear();
  void insert(const K &new_key, const V &new_value);
  void erase(const K &erase_key);
  RBTreeNode<K, V> *find(const K &search_key) const;
  int getHeight(RBTreeNode<K, V>* node);
  void printTree() {
        printTreeHelper(root, 0);
    }};



#include "RBMyMap.hpp"
#endif
