#ifndef RBTreeNode_H
#define RBTreeNode_H

template <typename K, typename V> struct RBTreeNode {
  K key;
  V value;
  char color; // Boolean Value whether or not RBTreeNode is Black or Red
  RBTreeNode *left;
  RBTreeNode *right;
  RBTreeNode *parent;
  RBTreeNode(const K &k, const V &v, RBTreeNode *lc, RBTreeNode *rc, const char &col)
      : key(k), value(v), left(lc), right(rc), color(col), parent(nullptr) {}
  RBTreeNode(const K &k, const V &v)
      : key(k), value(v), left(nullptr), right(nullptr),color('R'), parent(nullptr) {}
};

#endif
