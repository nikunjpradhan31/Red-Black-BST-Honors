#include "RBMyMap.h"


//This function goes through every branch and deallocates and deletes each node
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

//This function finds where the node is to be inserted recursively
//I've changed this function to return the node when it is found, which will then go back the insert function to fixInsertViolation
template <typename K, typename V>
RBTreeNode<K, V>* RBMyMap<K, V>::insert_helper(RBTreeNode<K, V> * root, RBTreeNode<K, V>  *pt)
{
    if (root == nullptr){
       return pt; //returns the pointer to the location of the node
    }

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
    else if (pt->key == root->key) { //if duplicate node return the orginal node
      return pt;
    }

    return root;//return if node is already exists
}

//This function performs a left Rotation on a node
template <typename K, typename V>
void RBMyMap<K,V>::rotateLeft(RBTreeNode<K, V> *&pt)
{    // pt_right points to the right child of the node 'pt' which is to be rotated.

    RBTreeNode<K, V> *pt_right = pt->right;
    // The left subtree of pt_right becomes the right subtree of pt.

    pt->right = pt_right->left;
    // If the new right child of pt is not nullptr, update its parent pointer.

    if (pt->right != nullptr)
        pt->right->parent = pt;
    // The parent of pt_right now should point to the parent of pt.

    pt_right->parent = pt->parent;
    // If pt was the root of the tree, then pt_right becomes the new root.

    if (pt->parent == nullptr)
        root = pt_right;
    // If pt was a left child, update the left child pointer of its parent to pt_right.

    else if (pt == pt->parent->left)
        pt->parent->left = pt_right;
    // If pt was a right child, update the right child pointer of its parent to pt_right.

    else
        pt->parent->right = pt_right;
    // The original node pt becomes the left child of pt_right.

    pt_right->left = pt;
    // Update the parent pointer of pt to point to pt_right.

    pt->parent = pt_right;
}
//This function performs a Right Rotation on a node
template <typename K, typename V>
void RBMyMap<K,V>::rotateRight(RBTreeNode<K, V> *&pt)
{
      // pt_left points to the left child of the node 'pt' which is to be rotated.

    RBTreeNode<K, V> *pt_left = pt->left;

    // The right subtree of pt_left becomes the left subtree of pt.

    pt->left = pt_left->right;

    // If the new left child of pt is not nullptr, update its parent pointer.

    if (pt->left != nullptr)
        pt->left->parent = pt;

    // The parent of pt_left now should point to the parent of pt.

    pt_left->parent = pt->parent;

    // If pt was the root of the tree, then pt_left becomes the new root.

    if (pt->parent == nullptr)
        root = pt_left;

    // If pt was a left child, update the left child pointer of its parent to pt_left.

    else if (pt == pt->parent->left)
        pt->parent->left = pt_left;
    // If pt was a right child, update the right child pointer of its parent to pt_left.

    else
        pt->parent->right = pt_left;
    // The original node pt becomes the right child of pt_left.

    pt_left->right = pt;
        // Update the parent pointer of pt to point to pt_left.

    pt->parent = pt_left;
}
//After an insertion operation has taken place, this function rebalances / recolors the tree so that it follows the red black properties
template <typename K, typename V>
void RBMyMap<K,V>::fixInsertViolation(RBTreeNode<K, V> *&pt)
{
    RBTreeNode<K, V> *parent_pt = nullptr;
    RBTreeNode<K, V> *grand_parent_pt = nullptr;

    // Continue correcting the tree as long as pt is not the root and there is a double red problem

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
  //verify the root is always black
    root->color = 'B';
}

//I have changed this function to first use the "find" function to search for the node, and then delete the node.
template <typename K, typename V>
void RBMyMap<K, V>::erase_helper(const K &erase_key) {
    if(root == nullptr)
        return;
    RBTreeNode<K, V>* node = find(erase_key);
    if(node != nullptr)//only deletes a node if it was found
      deleteNode(node);

}

//This function find a certain node in the Tree and returns the location of the node
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

//this function has taken the functionality of erase and handles the cases where the properties of the red-black tree are violated
template <typename K, typename V>
void RBMyMap<K, V>::deleteNode(RBTreeNode<K, V>* v)
{
    RBTreeNode<K, V> *NewNode = BSTreplace(v);
    // True when NewNode and v are both black
    bool uvBlack = ((NewNode == nullptr or NewNode->color == 'B') and (v->color == 'B'));
    RBTreeNode<K, V> *parent = v->parent;

    if (NewNode == nullptr) {
      // NewNode is nullptr therefore v is leaf
      if (v == root) {
        // v is root, making root nullptr
        root = nullptr;
      } else {
        if (uvBlack) {
          // NewNode and v both black
          // v is leaf, fix double black at v
          fixDoubleBlack(v);
        } else {
          // NewNode or v is red
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
        // v is root, assign the value of NewNode to v, and delete NewNode
        v->key = NewNode->key;
        v->left = v->right = nullptr;
        delete NewNode;
      } else {
        // Detach v from tree and move NewNode up
        if (isOnLeft(v)) {
          parent->left = NewNode;
        } else {
          parent->right = NewNode;
        }
        delete v;
        NewNode->parent = parent;
        if (uvBlack) {
          // NewNode and v both black, fix double black at NewNode
          fixDoubleBlack(NewNode);
        } else {
          // NewNode or v red, color NewNode black
          NewNode->color = 'B';
        }
      }
      return;
    }
    //v has 2 children, swap values with successor and recurse

    std::swap(NewNode->key, v->key);
    deleteNode(NewNode);
}

//This function returns the node that will replace a deleted node
template <typename K, typename V>
RBTreeNode<K, V> *BSTreplace(RBTreeNode<K, V> *x) {
    // when node have 2 children
    if (x->left != NULL and x->right != NULL)
        return get_min(x->right);

    // when leaf
    if (x->left == NULL and x->right == NULL)
        return NULL;

    // when single child
    if (x->left != NULL)
        return x->left;
    else
        return x->right;
}

//This function has been changed from its recursive form to a while loop however the functionality of returning the minimum node remains
template <typename K, typename V>
RBTreeNode<K, V>* get_min(RBTreeNode<K, V> *x)
{
    RBTreeNode<K, V> *temp = x;
    //goes deeper into the tree (minimum)
    while (temp->left != nullptr)
        temp = temp->left;

    return temp;
}

//This function occurs when a violation in the properties of the Red Black, to maintain the black height it must recursively be fixed up from a deleted node to the root
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
        sibling = x->parent->left;
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

//This function checks if a node first has child and second if it the child is red
template <typename K, typename V>
bool hasRedChild(RBTreeNode<K, V>* x){
        return (x->left != NULL && x->left->color == 'R') ||
           (x->right != NULL && x->right->color == 'R');
}

//This function checks if a node is either a right child or left child
template <typename K, typename V>
bool isOnLeft(RBTreeNode<K, V>* x) { return x == x->parent->left; }

//This function returns the sibing of a node, returns nullptr if there is no sibling
template <typename K, typename V>
RBTreeNode<K, V> *sibling(RBTreeNode<K, V>* x)
    {
        if(x->parent == nullptr) //  is at the root
            return nullptr;
        if (isOnLeft(x))
            return x->parent->right;

        return x->parent->left;
    }

//This function recurively finds the total height of the tree (not black height), from the root from the farthest leaf node
template <typename K, typename V>
int RBMyMap<K,V>::getHeight(RBTreeNode<K, V>* node){

  if(node == nullptr) // reached a null node 
    return 0; // delete nullptrs from the height

  return 1 + std::max(getHeight(node->left),getHeight(node->right));

}

//This function prints out the tree in a recursive fashion that allows the user to see the children and relationship of nodes
template <typename K, typename V>
void RBMyMap<K,V>::printTreeHelper(const RBTreeNode<K,V>* rt, int space) {
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

//dont touch below
template <typename K, typename V> RBMyMap<K, V>::RBMyMap() : root(nullptr) {} // general constructor

template <typename K, typename V> RBMyMap<K, V>::~RBMyMap() { clear(); } //general destructor

template <typename K, typename V> RBTreeNode<K, V> *&RBMyMap<K, V>::begin() { //returns the pointer to the root of the tree
  return root;
}
template <typename K, typename V>
bool RBMyMap<K, V>::empty() const { // checks if there are any nodes in the tree
  return root == nullptr;
}

//returns the number of nodes in total in the BST
template <typename K, typename V>
int RBMyMap<K, V>::size() const {
  return size_helper(root);
}

//removes and deallocates all nodes from the tree
template <typename K, typename V>
void RBMyMap<K, V>::clear() {
  clear_helper(root);}

//This function has been modifed to handle all functions relating to inserting a node and fixes any violations with it
template <typename K, typename V>
void RBMyMap<K, V>::insert(const K &new_key, const V &new_value) {
  //insert_helper(root, new_key,new_value); 
  RBTreeNode<K,V> *pt = new RBTreeNode<K,V>(new_key,new_value);
  root = insert_helper(root,pt);
  fixInsertViolation(pt);

}

//This function takes in a key that the user wants to delete and then finds and deletes the function
template <typename K, typename V>
void RBMyMap<K, V>::erase(const K &erase_key) {
  erase_helper(erase_key);
}

//This function allows the user to have the data of a node of a certain search key
template <typename K, typename V>
RBTreeNode<K, V> *RBMyMap<K, V>::find(const K &search_key) const {
  return find_helper(root, search_key);
}

//This function recursively finds the number of nodes in a tree
template <typename K, typename V>
int RBMyMap<K, V>::size_helper(RBTreeNode<K, V> *rt) const {
  if (rt == nullptr)
    return 0;
  else {
    return 1 + size_helper(rt->left) + size_helper(rt->right);
  }
}
