#ifndef RBTreeNode_H
#define RBTreeNode_H


template <typename K, typename V> struct RBTreeNode {
  K key;
  V value;
  char color; // Boolean Value whether or not RBTreeNode is Black or Red
  RBTreeNode *left;
  RBTreeNode *right;
  RBTreeNode *parent;
  RBTreeNode(const K &k, const V &v)
      : key(k), value(v), color('R'), left(nullptr), right(nullptr), parent(nullptr) {}
};

#endif
