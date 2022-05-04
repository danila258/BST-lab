#ifndef BST_LAB_BST_H
#define BST_LAB_BST_H

#include <iostream>


class BST {
public:
    BST();
    BST(int key);
    BST(int* array, size_t size);

    ~BST();

    explicit BST(const BST& other);
    BST& operator=(const BST& other);

    explicit BST(BST&& other) noexcept;
    BST& operator=(BST&& other) noexcept;

    bool isPresented(int key) const;

    void insert(int key);
    void remove(int key);

    void show() const;

    int minValueNode() const;
    int maxValueNode() const;

private:
    struct BstNode {
        int key;
        struct BstNode* left;
        struct BstNode* right;
    };

    BstNode* _root;

    struct BstNode* find(int key);
    void inorder(struct BstNode* root);
    void showNode(struct BstNode* node, int key) const;
};

#endif //BST_LAB_BST_H
