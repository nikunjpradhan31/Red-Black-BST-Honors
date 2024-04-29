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
  bool ll; // Left-Left Rotation flag
  bool rr; // Right-Right Rotation flag
  bool lr; // Left-Right Rotation flag
  bool rl; // Right-Left Rotation flag

  // Returns reference to the value of a node with key `access_key`
  // If no such node exists, throws std::out_of_range exception
  V &at_helper(RBTreeNode<K, V> *&rt, const K &access_key);

  // Counts the number of nodes in the tree
  int size_helper(RBTreeNode<K, V> *rt) const;

  // De-allocates all nodes in the tree
  void clear_helper(RBTreeNode<K, V> *&rt);

  // Inserts node with key `new_key` and value `new_value`
  // Does nothing if a node with `new_key` already exists in tree
  // Search property should be maintained
void insert_helper(RBTreeNode<K, V> *&rt, const K &new_key, const V &new_value);

    bool isRed(RBTreeNode<K, V>* node);
    RBTreeNode<K, V>* rotateLeft(RBTreeNode<K, V>*& node);
    RBTreeNode<K, V>* rotateRight(RBTreeNode<K, V>*& node);
    void swapColors(RBTreeNode<K, V>* a, RBTreeNode<K, V>* b);
    void flipColors(RBTreeNode<K, V>* node);





  // Returns pointer to node with the minimum key
  RBTreeNode<K, V> *get_min(RBTreeNode<K, V> *rt);
  RBTreeNode<K, V> *get_max(RBTreeNode<K, V> *rt);
  // Removes node with key `erase_key` if it exists
  // Does nothing otherwise
  // Search property should be maintained
  void erase_helper(RBTreeNode<K, V> *&rt, const K &erase_key);

  // Returns pointer to node with key `search_key` if it exists
  // Returns nullptr otherwise
  RBTreeNode<K, V> *find_helper(RBTreeNode<K, V> *rt, const K &search_key) const;

  // Prints the elements of the tree with tree-like formatting
  void print_helper(RBTreeNode<K, V> *rt, std::string indent) const;

  // Helper Function for operator[], similar to at() except:
  // If access_key is not found, create new node with that key and return ref to
  // its value You can assume type V has default constructor available (i.e. V()
  // is valid)
  V &bracket_helper(RBTreeNode<K, V> *&rt, const K &access_key);

  // This is a helper function for the copy constructor and operator=
  // It should recursively clone the whole tree, by using new to make a new tree
  // node, whose left and right children are clones of the left and right
  // children
  RBTreeNode<K, V> *clone(const RBTreeNode<K, V> *rt);

// RBTreeNode<K,V>* rotate_left(RBTreeNode<K,V> *&rt);

// RBTreeNode<K,V>* rotate_right(RBTreeNode<K,V> *&rt);

//void fix_insertion(const K &inserted_key);

void inorderTraversalHelper(RBTreeNode<K,V>* node) {
        if (node != nullptr) {
            inorderTraversalHelper(node->left);
            std::cout << node->key << " "<<node->color;
            inorderTraversalHelper(node->right);
        }
    }
 
void printTreeHelper(const RBTreeNode<K,V>* rt, int space) {
    const int spacePerLevel = 3; // Change this to increase or decrease spacing between levels
    if (rt == nullptr) {
        // Print space for leaf node
        std::cout << std::string(space * spacePerLevel, ' ') << "NN" << std::endl;
        return;
    }
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
