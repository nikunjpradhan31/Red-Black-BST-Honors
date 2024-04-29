#include "RBMyMap.h"

template <typename K, typename V>
void RBMyMap<K, V>::clear_helper(RBTreeNode<K, V> *&rt) {

  if (rt == nullptr)
    return;
  else {
    clear_helper(rt->left);
    clear_helper(rt->right);
    delete rt;
    rt = nullptr;
  }
}



template <typename K, typename V>
bool RBMyMap<K, V>::isRed(RBTreeNode<K, V>* node) {
    if (node == nullptr) {
        return false;  // Null nodes are considered black
    }
    return node->color == 'R';
}

template <typename K, typename V>
RBTreeNode<K, V>* RBMyMap<K, V>::rotateLeft(RBTreeNode<K, V>*& node) {
    RBTreeNode<K, V>* newRoot = node->right;
    node->right = newRoot->left;
    if (newRoot->left != nullptr) {
        newRoot->left->parent = node;
    }
    newRoot->parent = node->parent;
    newRoot->left = node;
    node->parent = newRoot;
    return newRoot;
}

template <typename K, typename V>
RBTreeNode<K, V>* RBMyMap<K, V>::rotateRight(RBTreeNode<K, V>*& node) {
    RBTreeNode<K, V>* newRoot = node->left;
    node->left = newRoot->right;
    if (newRoot->right != nullptr) {
        newRoot->right->parent = node;
    }
    newRoot->parent = node->parent;
    newRoot->right = node;
    node->parent = newRoot;
    return newRoot;
}

template <typename K, typename V>
void RBMyMap<K, V>::swapColors(RBTreeNode<K, V>* a, RBTreeNode<K, V>* b) {
    char temp = a->color;
    a->color = b->color;
    b->color = temp;
}

template <typename K, typename V>
void RBMyMap<K, V>::flipColors(RBTreeNode<K, V>* node) {
    node->color = node->color == 'R' ? 'B' : 'R';
    if (node->left != nullptr) {
        node->left->color = node->left->color == 'R' ? 'B' : 'R';
    }
    if (node->right != nullptr) {
        node->right->color = node->right->color == 'R' ? 'B' : 'R';
    }
}



template <typename K, typename V>
void RBMyMap<K, V>::insert_helper(RBTreeNode<K, V>*& root, const K& new_key, const V& new_value) {
    // Normal insertion code for any Binary Search Tree
    if (root == nullptr) {
        root =  new RBTreeNode<K, V>(new_key, new_value);  // New nodes are red
    }

    // Binary search tree insertion logic
    if (new_key < root->key) {
        insert_helper(root->left, new_key, new_value);
        root->left->parent = root;  // Update parent pointer
    } else if (new_key > root->key) {
        insert_helper(root->right, new_key, new_value);
        root->right->parent = root;  // Update parent pointer
    } else {
        return;  // Key already exists, no insertion
    }

    // Case 1: Right child is red but left child is black or doesn't exist
    if (isRed(root->right) && !isRed(root->left)) {
        root = rotateLeft(root);
        swapColors(root, root->left);
    }

    // Case 2: Left child and left grandchild are red
    if (isRed(root->left) && isRed(root->left->left)) {
        root = rotateRight(root);
        swapColors(root, root->right);
    }

    // Case 3: Both left and right children are red
    if (isRed(root->left) && isRed(root->right)) {
        flipColors(root);  // Flip colors of root and its children
    }
    this->root->color = 'B';
}


// template <typename K, typename V>
// void RBMyMap<K, V>::fix_insertion(const K &inserted_key) {
//     RBTreeNode<K, V> *newNode = find(inserted_key);

//     while (newNode != root && newNode->parent->color == 'R') {
//         RBTreeNode<K, V> *parent = newNode->parent;
//         RBTreeNode<K, V> *grandparent = parent->parent;
//         if (parent == grandparent->left) {
//             RBTreeNode<K, V> *uncle = grandparent->right;
//             if (uncle != nullptr && uncle->color == 'R') {
//                 // Case 1: Uncle is red
//                 grandparent->color = 'R';
//                 parent->color = 'B';
//                 uncle->color = 'B';
//                 newNode = grandparent;
//             } else {
//                 if (newNode == parent->right) {
//                     // Case 2: Node is right child
//                     newNode = parent;
//                     rotate_left(parent);
//                 }
//                 // Case 3: Node is left child
//                 parent->color = 'B';
//                 grandparent->color = 'R';
//                 rotate_right(grandparent);
//             }
//         } else {
//             RBTreeNode<K, V> *uncle = grandparent->left;
//             if (uncle != nullptr && uncle->color == 'R') {
//                 // Symmetric cases of 1, 2, 3
//                 grandparent->color = 'R';
//                 parent->color = 'B';
//                 uncle->color = 'B';
//                 newNode = grandparent;
//             } else {
//                 if (newNode == parent->left) {
//                     newNode = parent;
//                     rotate_right(parent);
//                 }
//                 parent->color = 'B';
//                 grandparent->color = 'R';
//                 rotate_left(grandparent);
//             }
//         }
//     }

//     root->color = 'B'; // Keep root always black
// }


template <typename K, typename V>
RBTreeNode<K, V> *RBMyMap<K, V>::get_min(RBTreeNode<K, V> *rt) {
  if (rt->left == nullptr)
    return rt;
  else
    get_min(rt->left);
}

template <typename K, typename V>
RBTreeNode<K, V> *RBMyMap<K, V>::get_max(RBTreeNode<K, V> *rt) {
  if (rt->right == nullptr)
    return rt;
  else
    get_min(rt->right);
}

template <typename K, typename V>
void RBMyMap<K, V>::erase_helper(RBTreeNode<K, V> *&rt, const K &erase_key) {
  if (rt == nullptr)
    return;
  if (erase_key > rt->key)
    return erase_helper(rt->right, erase_key);
  else if (erase_key < rt->key)
    return erase_helper(rt->left, erase_key);
  else {
    if (rt->right == nullptr && rt->left == nullptr) { // no children
      delete rt;
      rt = nullptr;
    } else if (rt->right == nullptr && rt->left != nullptr) { // one child
      RBTreeNode<K, V> *tmp = rt->left;
      delete rt;
      rt = tmp;
    } else if (rt->left == nullptr && rt->right != nullptr) { // one child
      RBTreeNode<K, V> *tmp = rt->right;
      delete rt;
      rt = tmp;
    } else { // two children
      RBTreeNode<K, V> *successor = get_min(rt->right);
      rt->value = successor->value;
      rt->key = successor->key;
      erase_helper(rt->right, rt->key);
    }
  }
}

template <typename K, typename V>
V &RBMyMap<K, V>::bracket_helper(RBTreeNode<K, V> *&rt, const K &access_key) {
  if (rt == nullptr) {
    rt = new RBTreeNode<K, V>(access_key, V());
    return rt->value;
  }
  if (access_key == rt->key)
    return rt->value;
  else {
    if (access_key < rt->key)
      return bracket_helper(rt->left, access_key);
    return bracket_helper(rt->right, access_key);
  }
}

template <typename K, typename V>
RBTreeNode<K, V> *RBMyMap<K, V>::find_helper(RBTreeNode<K, V> *rt, const K &search_key) const {
  if (rt == nullptr)
    return nullptr;
  if (rt->key == search_key)
    return rt;
  else {
    if (search_key > rt->key)
      return find_helper(rt->right, search_key);
    return find_helper(rt->left, search_key);
  }
}

template <typename K, typename V>
RBTreeNode<K, V> *RBMyMap<K, V>::clone(const RBTreeNode<K, V> *rt) {
  if (rt == nullptr)
    return nullptr;
  else
    return new RBTreeNode<K, V>(rt->key, rt->value, clone(rt->left),
                              clone(rt->right));
}

template <typename K, typename V>
RBMyMap<K, V>::RBMyMap(const RBMyMap<K, V> &source) {
  root = nullptr;
  *this = source;
}

template <typename K, typename V>
RBMyMap<K, V> &RBMyMap<K, V>::operator=(const RBMyMap<K, V> &source) {
  clear();
  root = clone(source.root);
  return *this;
}

// template <typename K, typename V>
// RBTreeNode<K,V>* RBMyMap<K, V>::rotate_left(RBTreeNode<K,V> *&rt){
//         RBTreeNode<K,V>* x = rt->right;
//         RBTreeNode<K,V>* y = x->left;
//         x->left = rt;
//         rt->right = y;
//         rt->parent = x;
//         if (y != nullptr)
//             y->parent = rt;
//         return x;
// }

// template <typename K, typename V>
// RBTreeNode<K,V>* RBMyMap<K, V>::rotate_right(RBTreeNode<K,V> *&rt){
//         RBTreeNode<K,V>* x = rt->left;
//         RBTreeNode<K,V>* y = x->right;
//         x->right = rt;
//         rt->left = y;
//         rt->parent = x;
//         if (y != nullptr)
//             y->parent = rt;
//         return x;

// }


/// Do not touch below ///

template <typename K, typename V> RBMyMap<K, V>::RBMyMap() : root(nullptr) {}

template <typename K, typename V> RBMyMap<K, V>::~RBMyMap() { clear(); }

template <typename K, typename V> V &RBMyMap<K, V>::at(const K &access_key) {
  return at_helper(root, access_key);
}

template <typename K, typename V>
V &RBMyMap<K, V>::operator[](const K &access_key) {
  return bracket_helper(root, access_key);
}

template <typename K, typename V> bool RBMyMap<K, V>::empty() const {
  return root == nullptr;
}

template <typename K, typename V> int RBMyMap<K, V>::size() const {
  return size_helper(root);
}

template <typename K, typename V> void RBMyMap<K, V>::clear() {
  clear_helper(root);
}

template <typename K, typename V>
void RBMyMap<K, V>::insert(const K &new_key, const V &new_value) {
  insert_helper(root, new_key, new_value);
}

template <typename K, typename V> void RBMyMap<K, V>::erase(const K &erase_key) {
  erase_helper(root, erase_key);
}

template <typename K, typename V>
RBTreeNode<K, V> *RBMyMap<K, V>::find(const K &search_key) const {
  return find_helper(root, search_key);
}

template <typename K, typename V> void RBMyMap<K, V>::print() const {
  print_helper(root, "");
}

template <typename K, typename V> RBTreeNode<K, V> *&RBMyMap<K, V>::begin() {
  return root;
}

template <typename K, typename V>
void RBMyMap<K, V>::convert_to_sorted_list(RBTreeNode<K, V> *&rt,
                                         std::vector<V> &sorted) {
  if (rt == nullptr)
    return;

  convert_to_sorted_list(rt->left, sorted);
  sorted.push_back(rt->value);
  convert_to_sorted_list(rt->right, sorted);
}

template <typename K, typename V>
void RBMyMap<K, V>::print_helper(RBTreeNode<K, V> *rt, std::string indent) const {
  if (rt == nullptr) {
    cout << indent << "   [empty]" << endl;
    return;
  }
  print_helper(rt->right, indent += "  ");
  cout << indent << " [" << rt->key << "]=" << rt->value << endl;
  print_helper(rt->left, indent);
}

template <typename K, typename V>
V &RBMyMap<K, V>::at_helper(RBTreeNode<K, V> *&rt, const K &access_key) {
  if (rt == nullptr) {
    throw std::out_of_range("key not found");
  }
  if (access_key == rt->key)
    return rt->value;
  else {
    if (access_key < rt->key)
      return at_helper(rt->left, access_key);
    // else if(access_key > rt->key)
    return at_helper(rt->right, access_key);
  }
}

template <typename K, typename V>
int RBMyMap<K, V>::size_helper(RBTreeNode<K, V> *rt) const {
  if (rt == nullptr)
    return 0;
  else {
    return 1 + size_helper(rt->left) + size_helper(rt->right);
  }
}
