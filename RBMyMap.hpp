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
RBTreeNode<K, V>* RBMyMap<K, V>::insert_helper(RBTreeNode<K, V> * root, RBTreeNode<K, V>  *pt)
{
    if (root == nullptr)
       return pt;

    if (pt->key < root->key)
    {
        root->left  = insert_helper(root->left, pt);
        root->left->parent = root;
    }
    else if (pt->key > root->key)
    {
        root->right = insert_helper(root->right, pt);
        root->right->parent = root;
    }

    return root;
}

template <typename K, typename V>
void RBMyMap<K,V>::rotateLeft(RBTreeNode<K, V> *&pt)
{
    RBTreeNode<K, V> *pt_right = pt->right;

    pt->right = pt_right->left;

    if (pt->right != nullptr)
        pt->right->parent = pt;

    pt_right->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_right;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;

    else
        pt->parent->right = pt_right;

    pt_right->left = pt;
    pt->parent = pt_right;
}

template <typename K, typename V>
void RBMyMap<K,V>::rotateRight(RBTreeNode<K, V> *&pt)
{
    RBTreeNode<K, V> *pt_left = pt->left;

    pt->left = pt_left->right;

    if (pt->left != nullptr)
        pt->left->parent = pt;

    pt_left->parent = pt->parent;

    if (pt->parent == nullptr)
        root = pt_left;

    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;

    else
        pt->parent->right = pt_left;

    pt_left->right = pt;
    pt->parent = pt_left;
}

template <typename K, typename V>
void RBMyMap<K,V>::fixInsertViolation(RBTreeNode<K, V> *&pt)
{
    RBTreeNode<K, V> *parent_pt = nullptr;
    RBTreeNode<K, V> *grand_parent_pt = nullptr;

    while ((pt != root) && (pt->color != 'B') &&
           (pt->parent->color == 'R'))
    {

        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        /*  Case : A
            Parent of pt is left child of Grand-parent of pt */
        if (parent_pt == grand_parent_pt->left)
        {

            RBTreeNode<K, V> *uncle_pt = grand_parent_pt->right;

            /* Case : 1
               The uncle of pt is also red
               Only Recoloring required */
            if (uncle_pt != nullptr && uncle_pt->color == 'R')
            {
                grand_parent_pt->color = 'R';
                parent_pt->color = 'B';
                uncle_pt->color = 'B';
                pt = grand_parent_pt;
            }

            else
            {
                /* Case : 2
                   pt is right child of its parent
                   Left-rotation required */
                if (pt == parent_pt->right)
                {
                    rotateLeft(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                   pt is left child of its parent
                   Right-rotation required */
                rotateRight(grand_parent_pt);
                std::swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }

        /* Case : B
           Parent of pt is right child of Grand-parent of pt */
        else
        {
            RBTreeNode<K, V> *uncle_pt = grand_parent_pt->left;

            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != nullptr) && (uncle_pt->color == 'R'))
            {
                grand_parent_pt->color = 'R';
                parent_pt->color = 'B';
                uncle_pt->color = 'B';
                pt = grand_parent_pt;
            }
            else
            {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->left)
                {
                    rotateRight(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                /* Case : 3
                   pt is right child of its parent
                   Left-rotation required */
                rotateLeft(grand_parent_pt);
                std::swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = 'B';
}

template <typename K, typename V>
void RBMyMap<K, V>::erase_helper(const K &erase_key) {
    if(root == nullptr)
        return;
    RBTreeNode<K, V>* node = find(erase_key);
    deleteNode(node);

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
void RBMyMap<K, V>::deleteNode(RBTreeNode<K, V>* v)
{
    RBTreeNode<K, V> *u = BSTreplace(v);
    // True when u and v are both black
    bool uvBlack = ((u == nullptr or u->color == 'B') and (v->color == 'B'));
    RBTreeNode<K, V> *parent = v->parent;

    if (u == nullptr) {
      // u is nullptr therefore v is leaf
      if (v == root) {
        // v is root, making root nullptr
        root = nullptr;
      } else {
        if (uvBlack) {
          // u and v both black
          // v is leaf, fix double black at v
          fixDoubleBlack(v);
        } else {
          // u or v is red
          if (sibling(v) != nullptr)
            // sibling is not nullptr, make it red"
            sibling(v)->color = 'R';
        }

        // delete v from the tree
        if (isOnLeft(v)) {
          parent->left = nullptr;
        } else {
          parent->right = nullptr;
        }
      }
      delete v;
      return;
    }

    if (v->left == nullptr or v->right == nullptr) {
      // v has 1 child
      if (v == root) {
        // v is root, assign the value of u to v, and delete u
        v->key = u->key;
        v->left = v->right = nullptr;
        delete u;
      } else {
        // Detach v from tree and move u up
        if (isOnLeft(v)) {
          parent->left = u;
        } else {
          parent->right = u;
        }
        delete v;
        u->parent = parent;
        if (uvBlack) {
          // u and v both black, fix double black at u
          fixDoubleBlack(u);
        } else {
          // u or v red, color u black
          u->color = 'B';
        }
      }
      return;
    }
    //v has 2 children, swap values with successor and recurse

    std::swap(u->key, v->key);
    deleteNode(u);
}

template <typename K, typename V>
RBTreeNode<K, V> *BSTreplace(RBTreeNode<K, V> *x) {
    // when node have 2 children
    if (x->left != NULL and x->right != NULL)
        return successor(x->right);

    // when leaf
    if (x->left == NULL and x->right == NULL)
        return NULL;

    // when single child
    if (x->left != NULL)
        return x->left;
    else
        return x->right;
}

template <typename K, typename V>
RBTreeNode<K, V> *successor(RBTreeNode<K, V> *x)
{
    RBTreeNode<K, V> *temp = x;

    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}

template <typename K, typename V>
void RBMyMap<K, V>::fixDoubleBlack(RBTreeNode<K, V>* x)
{
    if (x == root)
      // Reached root
      return;
    RBTreeNode<K,V> *sibling;
    RBTreeNode<K, V> *parent = x->parent;
    if(x == x->parent->left)
        sibling = x->parent->right;
    else
        sibling = x->parent->right;
    if (sibling == NULL) {
      // No sibiling, double black pushed up
      fixDoubleBlack(parent);
    } else {
      if (sibling->color == 'R') {
        // Sibling red
        parent->color = 'R';
        sibling->color = 'B';
        if (isOnLeft(sibling)) {
          // left case
          rotateRight(parent);
        } else {
          // right case
          rotateLeft(parent);
        }
        fixDoubleBlack(x);
      } else {
        // Sibling black
        if (hasRedChild(sibling)) {
          // at least 1 red children
          if (sibling->left != NULL and sibling->left->color == 'R') {
            if (isOnLeft(sibling)) {
              // left left
              sibling->left->color = sibling->color;
              sibling->color = parent->color;
              rotateRight(parent);
            } else {
              // right left
              sibling->left->color = parent->color;
              rotateRight(sibling);
              rotateLeft(parent);
            }
          } else {
            if (isOnLeft(sibling)) {
              // left right
              sibling->right->color = parent->color;
              rotateLeft(sibling);
              rotateRight(parent);
            } else {
              // right right
              sibling->right->color = sibling->color;
              sibling->color = parent->color;
              rotateLeft(parent);
            }
          }
          parent->color = 'B';
        } else {
          // 2 black children
          sibling->color = 'R';
          if (parent->color == 'B')
            fixDoubleBlack(parent);
          else
            parent->color = 'B';
        }
      }
    }
}

template <typename K, typename V>
bool hasRedChild(RBTreeNode<K, V>* x){
        return (x->left != NULL && x->left->color == 'R') ||
           (x->right != NULL && x->right->color == 'R');
}

template <typename K, typename V>
bool isOnLeft(RBTreeNode<K, V>* x) { return x == x->parent->left; }

template <typename K, typename V>
RBTreeNode<K, V> *sibling(RBTreeNode<K, V>* x)
    {
        if(x->parent == NULL)
            return NULL;
        if (isOnLeft(x))
            return x->parent->right;

        return x->parent->left;
    }

//dont touch below
template <typename K, typename V> RBMyMap<K, V>::RBMyMap() : root(nullptr) {}

template <typename K, typename V> RBMyMap<K, V>::~RBMyMap() { clear(); }

// template <typename K, typename V> V &RBMyMap<K, V>::at(const K &access_key) {
//   return at_helper(root, access_key);
// }

// template <typename K, typename V>
// V &RBMyMap<K, V>::operator[](const K &access_key) {
//   return bracket_helper(root, access_key);
// }

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
  //insert_helper(root, new_key,new_value); 
  RBTreeNode<K,V> *pt = new RBTreeNode<K,V>(new_key,new_value);
  root = insert_helper(root,pt);
  fixInsertViolation(pt);
}

template <typename K, typename V> void RBMyMap<K, V>::erase(const K &erase_key) {
  erase_helper(erase_key);
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

// template <typename K, typename V>
// void RBMyMap<K, V>::convert_to_sorted_list(RBTreeNode<K, V> *&rt, std::vector<V> &sorted) {
//   if (rt == nullptr)
//     return;

//   convert_to_sorted_list(rt->left, sorted);
//   sorted.push_back(rt->value);
//   convert_to_sorted_list(rt->right, sorted);
// }

// // template <typename K, typename V>
// // void RBMyMap<K, V>::print_helper(RBTreeNode<K, V> *rt, std::string indent) const {
// //   if (rt == nullptrptr) {
//     cout << indent << "   [empty]" << endl;
//     return;
//   }
//   print_helper(rt->right, indent += "  ");
//   cout << indent << " [" << rt->key << "]=" << rt->value << endl;
//   print_helper(rt->left, indent);
// }

// template <typename K, typename V>
// V &RBMyMap<K, V>::at_helper(RBTreeNode<K, V> *&rt, const K &access_key) {
//   if (rt == nullptrptr) {
//     throw std::out_of_range("key not found");
//   }
//   if (access_key == rt->key)
//     return rt->value;
//   else {
//     if (access_key < rt->key)
//       return at_helper(rt->left, access_key);
//     // else if(access_key > rt->key)
//     return at_helper(rt->right, access_key);
//   }
// }

// template <typename K, typename V>
// int RBMyMap<K, V>::size_helper(RBTreeNode<K, V> *rt) const {
//   if (rt == nullptrptr)
//     return 0;
//   else {
//     return 1 + size_helper(rt->left) + size_helper(rt->right);
//   }
// }
