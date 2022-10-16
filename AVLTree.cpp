//Luke Kaplan
//sjd7wr
//10-12-22
//AVLTree.cpp

#include "AVLNode.h"
#include "AVLTree.h"
#include <iostream>
#include <string>
using namespace std;

AVLTree::AVLTree() {
    root = NULL;
    isBalanced = false;
}

AVLTree::~AVLTree() {
  delete root;
  root = NULL;
}

void AVLTree::cleanTree(AVLNode* node){
  if(node == NULL){
    return;
  }
  else {
    cleanTree(node->left);
    cleanTree(node->right);
    delete node;
    //node = NULL;
  }
}

// insert finds a position for x in the tree and places it there, rebalancing
// as necessary.
void AVLTree::insert(const string& x) {
  insertHelper(root,x);
  //check for unbalanced tree
  checkBalance(root);
  isBalanced = false;
  updateHeight(root);
  updateBalanceFactor(root);
  //printTree();
}

void AVLTree::insertHelper(AVLNode*& node, const string &x){
  //create the node
  if(node == nullptr){
    node = new AVLNode();
    node->value = x;
    updateHeight(root);
    updateBalanceFactor(root);
    return;
  }
  else if(x < node->value){
    insertHelper(node->left, x);
  }
  else if(x > node->value){
    insertHelper(node->right, x);
  }
  else{
    ;
  }
}

// remove finds x's position in the tree and removes it, rebalancing as
// necessary.
void AVLTree::remove(const string& x) {
    root = remove(root, x);
    checkBalance(root);
    isBalanced = false;
    updateHeight(root);
    updateBalanceFactor(root);
    //cout << "made it here" << endl;
    //printTree();
}

// pathTo finds x in the tree and returns a string representing the path it
// took to get there.
string AVLTree::pathTo(const string& x) const {
  if(find(x) == false){
    return "";
  }
  else {
    return pathToHelper(root, x);
  }
}

string AVLTree::pathToHelper(AVLNode* node, const string& x) const{
   if(x == node->value){
     return node->value;
   }
   else if (x < node->value){
     return node->value + " " + pathToHelper(node->left, x);
   }
   else if(x > node->value){
     return node->value + " " + pathToHelper(node->right, x);
   }
}

// find determines whether or not x exists in the tree.
bool AVLTree::find(const string& x) const {
   return findHelper(root,x);
}

bool AVLTree::findHelper(AVLNode* node, const string& x) const {
  if(node == nullptr){
    return false;
  }
  else if(x == node->value){
    return true;
  }
  else if(x < node->value){
    return findHelper(node->left, x);
  }
  else if(x > node->value){
    return findHelper(node->right, x);
  }
}

// numNodes returns the total number of nodes in the tree.
int AVLTree::numNodes() const {
   return numNodesHelper(root);
}

int AVLTree::numNodesHelper(AVLNode* node) const{
  if(node == NULL){
    return 0;
  }
  else {
    return 1 + numNodesHelper(node->left) + numNodesHelper(node->right);

  }
}

// balance makes sure that the subtree with root n maintains the AVL tree
// property, namely that the balance factor of n is either -1, 0, or 1.
void AVLTree::balance(AVLNode*& n) {
  if(balanceFactor(n) == 2){
    if(balanceFactor(n->right) < 0){
      rotateRight(n->right);
    }
    rotateLeft(n);
  }
  else if (balanceFactor(n) == -2){
    if(balanceFactor(n->left) > 0){
      rotateLeft(n->left);
    }
    rotateRight(n);
  }

    /* if balance factor of node is 2 we will need to rotate left:
        first, see if we should also rotate right (i.e., do a double rotation)
        if balance factor of right child is negative:
            rotate right on the right child
        endif
        rotate left on node
    else if balance factor of node is -2 we will need to rotate right:
        first, see if we should also rotate left (i.e., double rotation)
        if balance factor of left is positive:
            rotate left on the left child
        endif
        rotate right on node
	endif*/
}

void AVLTree::checkBalance(AVLNode*& n){
  if(n == NULL){
    return;
  }
  else {
    checkBalance(n->left);
    checkBalance(n->right);
    if((balanceFactor(n) >= 2 || balanceFactor(n) <= -2) && isBalanced == false){
      isBalanced = true;
      balance(n);
      //might not work
    }

  }

}



// rotateLeft performs a single rotation on node n with its right child.
AVLNode* AVLTree::rotateLeft(AVLNode*& n) {
  AVLNode* temp = NULL;
  temp = n;
  n = n->right;
  temp->right = NULL;
  if(n->left!= NULL){
    temp->right = n->left;
  }
  n->left = temp;
}

// rotateRight performs a single rotation on node n with its left child.
AVLNode* AVLTree::rotateRight(AVLNode*& n) {
  AVLNode* temp = NULL;
  temp = n;
  n = n->left;
  temp->left = NULL;
  if(n->right!= NULL){
    temp->left = n->right;
  }
  n->right = temp;
}

// private helper for remove to allow recursion over different nodes.
// Returns an AVLNode* that is assigned to the original node.
AVLNode* AVLTree::remove(AVLNode*& n, const string& x) {
    if (n == NULL) {
        return NULL;
    }

    // first look for x
    if (x == n->value) {
        // found
        if (n->left == NULL && n->right == NULL) {
            // no children
            delete n;
            n = NULL;
            return NULL;
        } else if (n->left == NULL) {
            // Single child (left)
            AVLNode* temp = n->right;
            n->right = NULL;
            delete n;
            n = NULL;
            return temp;
        } else if (n->right == NULL) {
            // Single child (right)
            AVLNode* temp = n->left;
            n->left = NULL;
            delete n;
            n = NULL;
            return temp;
        } else {
            // two children -- tree may become unbalanced after deleting n
            string sr = min(n->right);
            n->value = sr;
            n->right = remove(n->right, sr);
        }
    } else if (x < n->value) {
        n->left = remove(n->left, x);
    } else {
        n->right = remove(n->right, x);
    }

    // Recalculate heights and balance this subtree
    n->height = 1 + max(height(n->left), height(n->right));
    //used to have:
    //balance(n);
    updateHeight(root);
    updateBalanceFactor(root);


    return n;
}

// min finds the string with the smallest value in a subtree.
string AVLTree::min(AVLNode* node) const {
    // go to bottom-left node
    if (node->left == NULL) {
        return node->value;
    }
    return min(node->left);
}

// height returns the value of the height field in a node.
// If the node is null, it returns -1.
int AVLTree::height(AVLNode* node) const {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

void AVLTree::updateHeight(AVLNode* n) const{
  if(n == NULL){
    return;
  }
  else {
    updateHeight(n->left);
    updateHeight(n->right);
    n->height = 1 + max(height(n->left), height(n->right));
     
  }

}

int AVLTree::balanceFactor(AVLNode* node) const {
  if(node == NULL){
    return 0;
  }
  return node->balanceFactor;
}

void AVLTree::updateBalanceFactor(AVLNode* n) const {
  if(n == NULL){
    return;
  }
  else {
    updateBalanceFactor(n->left);
    updateBalanceFactor(n->right);
    n->balanceFactor = height(n->right) - height(n->left);

  }
}

// max returns the greater of two integers.
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

// Helper function to print branches of the binary tree
// You do not need to know how this function works.
void showTrunks(Trunk* p) {
    if (p == NULL) return;
    showTrunks(p->prev);
    cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
void AVLTree::printTree(AVLNode* root, Trunk* prev, bool isRight) {
    if (root == NULL) return;

    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isRight) {
        trunk->str = ".---";
        prev_str = "   |";
    } else {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->value << endl;

    if (prev) prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->left, trunk, false);

    delete trunk;
}

void AVLTree::printTree() {
    printTree(root, NULL, false);
}
