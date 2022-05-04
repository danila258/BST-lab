#include "BST.h"

BST::BST() {
    _root = new BST::BstNode();
    _root->left = nullptr;
    _root->right = nullptr;
    _root->key = 0;
}

BST::BST(int k) : BST() {
    _root->key = k;
}

BST::BST(int* array, size_t size) : BST() {
    for (int i = 0; i < size; ++i) {
        this->insert(array[i]);
    }
}

BST::~BST() {

}

BST::BST(const BST& other) {

}

BST& BST::operator=(const BST& other) {

}

BST::BST(BST&& other) noexcept {

}

BST& BST::operator=(BST&& other) noexcept {

}

BST::BstNode* BST::find(int key) {

}

void BST::inorder(struct BstNode* root) {

}

void BST::showNode(struct BstNode* node, int key) const {

}

bool BST::isPresented(int key) const {

}

void BST::insert(int key) {

}

void BST::remove(int key) {

}

void BST::show() const {

}

int BST::minValueNode() const {

}

int BST::maxValueNode() const {

}
