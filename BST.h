#ifndef BST_LAB_BST_H
#define BST_LAB_BST_H


class BST {
public:
    BST();
    BST(int* array);

    ~BST();

    explicit BST(const BST& other);
    BST& operator=(const BST& other);

    explicit BST(BST&& other) noexcept;
    BST& operator=(BST&& other) noexcept;

    bool isPresented(int key) const;

    void insert(int key);
    void remove(int key);

    void show() const;

    int minValueNode(struct BstNode* node);
    int maxValueNode(struct BstNode* node);

private:
    struct BstNode {
        int key;
        struct BstNode* left;
        struct BstNode* right;
    };

    BstNode* newNode(int item = 0);

    struct BstNode* find(int key);
    void inorder(struct BstNode* root);
    void showNode(struct BstNode* node, int key) const;
};


#endif //BST_LAB_BST_H
