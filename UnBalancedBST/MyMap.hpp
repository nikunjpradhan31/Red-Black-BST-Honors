

template <typename K, typename V>
void MyMap<K, V>::clear_helper(TreeNode<K, V> *&rt) {

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
void MyMap<K, V>::insert_helper(TreeNode<K, V> *&rt, const K &new_key,
                                const V &new_value) {
  if (rt == nullptr) {
    rt = new TreeNode<K, V>(new_key, new_value);
    return;
  }

  if (new_key == rt->key)
    return;

  if (new_key < rt->key)
    insert_helper(rt->left, new_key, new_value);
  else
    insert_helper(rt->right, new_key, new_value);
}

template <typename K, typename V>
TreeNode<K, V> *MyMap<K, V>::get_min(TreeNode<K, V> *rt) {
    TreeNode<K, V> *temp = rt;
    //goes deeper into the tree (minimum)
    while (temp->left != nullptr)
        temp = temp->left;

    return temp;
}

template <typename K, typename V>
TreeNode<K, V> *MyMap<K, V>::get_max(TreeNode<K, V> *rt) {
  if (rt->right == nullptr)
    return rt;
  else
    get_min(rt->right);
}

template <typename K, typename V>
void MyMap<K, V>::erase_helper(TreeNode<K, V> *&rt, const K &erase_key) {
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
      TreeNode<K, V> *tmp = rt->left;
      delete rt;
      rt = tmp;
    } else if (rt->left == nullptr && rt->right != nullptr) { // one child
      TreeNode<K, V> *tmp = rt->right;
      delete rt;
      rt = tmp;
    } else { // two children
      TreeNode<K, V> *successor = get_min(rt->right);
      rt->value = successor->value;
      rt->key = successor->key;
      erase_helper(rt->right, rt->key);
    }
  }
}

template <typename K, typename V>
V &MyMap<K, V>::bracket_helper(TreeNode<K, V> *&rt, const K &access_key) {
  if (rt == nullptr) {
    rt = new TreeNode<K, V>(access_key, V());
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
TreeNode<K, V> *MyMap<K, V>::find_helper(TreeNode<K, V> *rt,
                                         const K &search_key) const {
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
TreeNode<K, V> *MyMap<K, V>::clone(const TreeNode<K, V> *rt) {
  if (rt == nullptr)
    return nullptr;
  else
    return new TreeNode<K, V>(rt->key, rt->value, clone(rt->left),
                              clone(rt->right));
}

template <typename K, typename V>
MyMap<K, V>::MyMap(const MyMap<K, V> &source) {
  root = nullptr;
  *this = source;
}

template <typename K, typename V>
MyMap<K, V> &MyMap<K, V>::operator=(const MyMap<K, V> &source) {
  clear();
  root = clone(source.root);
  return *this;
}

/// Do not touch below ///

template <typename K, typename V> MyMap<K, V>::MyMap() : root(nullptr) {}

template <typename K, typename V> MyMap<K, V>::~MyMap() { clear(); }

template <typename K, typename V> V &MyMap<K, V>::at(const K &access_key) {
  return at_helper(root, access_key);
}

template <typename K, typename V>
V &MyMap<K, V>::operator[](const K &access_key) {
  return bracket_helper(root, access_key);
}

template <typename K, typename V> bool MyMap<K, V>::empty() const {
  return root == nullptr;
}

template <typename K, typename V> int MyMap<K, V>::size() const {
  return size_helper(root);
}

template <typename K, typename V> void MyMap<K, V>::clear() {
  clear_helper(root);
}

template <typename K, typename V>
void MyMap<K, V>::insert(const K &new_key, const V &new_value) {
  insert_helper(root, new_key, new_value);
}

template <typename K, typename V> void MyMap<K, V>::erase(const K &erase_key) {
  erase_helper(root, erase_key);
}

template <typename K, typename V>
TreeNode<K, V> *MyMap<K, V>::find(const K &search_key) const {
  return find_helper(root, search_key);
}

template <typename K, typename V> void MyMap<K, V>::print() const {
  print_helper(root, "");
}

template <typename K, typename V> TreeNode<K, V> *&MyMap<K, V>::begin() {
  return root;
}

template <typename K, typename V>
void MyMap<K, V>::convert_to_sorted_list(TreeNode<K, V> *&rt,
                                         std::vector<V> &sorted) {
  if (rt == nullptr)
    return;

  convert_to_sorted_list(rt->left, sorted);
  sorted.push_back(rt->value);
  convert_to_sorted_list(rt->right, sorted);
}

template <typename K, typename V>
int MyMap<K,V>::getHeight(TreeNode<K, V>* node){

  if(node == nullptr)
    return 0;

  return 1 + std::max(getHeight(node->left),getHeight(node->right));

}

template <typename K, typename V>
void MyMap<K,V>::printTreeHelper(const TreeNode<K,V>* rt, int space) {
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
        std::cout << std::string(space * spacePerLevel, ' ') << rt->key << std::endl;

        printTreeHelper(rt->left, space + 1); // Recur for left subtree
    }
}

template <typename K, typename V>
void MyMap<K, V>::print_helper(TreeNode<K, V> *rt, std::string indent) const {
  if (rt == nullptr) {
    cout << indent << "   [empty]" << endl;
    return;
  }
  print_helper(rt->right, indent += "  ");
  cout << indent << " [" << rt->key << "]=" << rt->value << endl;
  print_helper(rt->left, indent);
}

template <typename K, typename V>
V &MyMap<K, V>::at_helper(TreeNode<K, V> *&rt, const K &access_key) {
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
int MyMap<K, V>::size_helper(TreeNode<K, V> *rt) const {
  if (rt == nullptr)
    return 0;
  else {
    return 1 + size_helper(rt->left) + size_helper(rt->right);
  }
}
