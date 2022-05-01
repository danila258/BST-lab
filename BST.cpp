#include "BST.h"


 BST::BstNode* BST::newNode(int item) {
    BstNode* temp = new struct BST::BstNode;
    temp->key = item;
    temp->left = temp->right = nullptr;
    return temp;
}

