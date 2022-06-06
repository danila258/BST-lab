#ifndef BST_H
#define BST_H

#include <utility>
#include <iostream>


template <typename Key, typename Value>
class BinarySearchTree
{
    struct Node
    {
        Node(Key key,
             Value value,
             Node* parent = nullptr,
             Node* left = nullptr,
             Node* right = nullptr);

        std::pair<Key, Value> keyValuePair;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
    };

public:
    //! Конструктор по умолчанию
    BinarySearchTree() = default;

    //! Копирование
    explicit BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree& operator=(const BinarySearchTree& other);
    //! Перемещение
    explicit BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    //! Деструктор
    ~BinarySearchTree();

    /*!
        Итератор бинарного дерева поиска

        Обходит дерево последовательно от меньшего ключа к большему
    */
    class Iterator
    {
    public:
        explicit Iterator(Node* node);

        std::pair<Key, Value>& operator*();
        const std::pair<Key, Value>& operator*() const;

        std::pair<Key, Value>* operator->();
        const std::pair<Key, Value>* operator->() const;

        Iterator operator++();
        Iterator operator++(int);

        Iterator operator--();
        Iterator operator--(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node* _node;
    };

    /*!
        Константный итератор
    */
    class ConstIterator
    {
    public:
        explicit ConstIterator(const Node* node);

        const std::pair<Key, Value>& operator*() const;

        const std::pair<Key, Value>* operator->() const;

        ConstIterator operator++();
        ConstIterator operator++(int);

        ConstIterator operator--();
        ConstIterator operator--(int);

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

    private:
        const Node* _node;
    };

    // вставить элемент с ключем key и значением value
    void insert(const Key& key, const Value& value);

    // удалить все элементы с ключем key
    void erase(const Key& key);
    void eraseNode(const Key& key, Node* node);

    // найти первый элемент в дереве, равный ключу key
    ConstIterator find(const Key& key) const;
    Iterator find(const Key& key);

    void clear(Node* node);

    // найти все элементы, у которых ключ равен key
    // первый итератор пары - первый элемент в дереве, равный key
    // второй итератор пары - первый элемент в дереве больший, чем key
    // [pair.first, pair.second) - полуинтервал, содержащий все элементы с ключем key
    std::pair<Iterator, Iterator> equalRange(const Key& key);
    std::pair<ConstIterator, ConstIterator> equalRange(const Key& key) const;

    // получить итератор на минимальное значение в дереве
    ConstIterator min(const Key& key) const;
    // получить итератор на максимальное значение в дереве
    ConstIterator max(const Key& key) const;

    Iterator begin();
    Iterator end();

    ConstIterator cbegin() const;
    ConstIterator cend() const;

    size_t size() const;
private:
    size_t _size = 0;
    Node* _root = nullptr; //!< корневой узел дерева
};


// Node //-------------------------------------------------------------------------------

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::Node::Node(Key key, Value value, BinarySearchTree::Node* parent,
                                         BinarySearchTree::Node* left, BinarySearchTree::Node* right) :
                                         keyValuePair(std::make_pair(key, value)), parent(parent), left(left),
                                         right(right)
{}

// Iterator //-------------------------------------------------------------------------------

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::Iterator::Iterator(Node *node) : _node(node)
{}

template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::Iterator::operator->()
{
    return &_node->keyValuePair;
}

template<typename Key, typename Value>
const std::pair<Key, Value>* BinarySearchTree<Key, Value>::Iterator::operator->() const
{
    return &_node->keyValuePair;
}

template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::Iterator::operator*()
{
    return _node->keyValuePair;
}

template<typename Key, typename Value>
const std::pair<Key, Value>& BinarySearchTree<Key, Value>::Iterator::operator*() const
{
    return _node->keyValuePair;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Iterator::operator==(const Iterator& other) const
{
    return _node == other._node;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Iterator::operator!=(const Iterator& other) const
{
    return _node != other._node;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator++()
{
    if (!_node)
    {
        return *this;
    }

    if (_node->right)
    {
        _node = _node->right;

        while (_node->left)
        {
            _node = _node->left;
        }
    }
    else
    {
        while (_node->parent && _node == _node->parent->right)
        {
            _node = _node->parent;
        }
        _node = _node->parent;
    }

    return *this;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator++(int)
{
    Iterator elem = *this;
    ++(*this);
    return Iterator(elem);
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator--()
{
    if (!_node)
    {
        return *this;
    }

    if (_node->left)
    {
        _node = _node->left;

        while (_node->right)
        {
            _node = _node->right;
        }
    }
    else
    {
        while (_node->parent && _node->parent->left == _node)
        {
            _node = _node->parent;
        }
        _node = _node->parent;
    }

    return *this;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::Iterator::operator--(int)
{
    Iterator elem = *this;
    --(*this);
    return elem;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::begin()
{
    return Iterator(min(_root));
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::end()
{
    return BinarySearchTree::Iterator(max(_root)->right);
}

// ConstIterator //-------------------------------------------------------------------------------

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::ConstIterator::ConstIterator(const Node* node) : _node(node)
{}

template<typename Key, typename Value>
const std::pair<Key, Value>* BinarySearchTree<Key, Value>::ConstIterator::operator->() const
{
    return &_node->keyValuePair;
}

template<typename Key, typename Value>
const std::pair<Key, Value>& BinarySearchTree<Key, Value>::ConstIterator::operator*() const
{
    return _node->keyValuePair;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator++()
{
    Iterator elem(_node);
    ++elem;
    return static_cast<ConstIterator>(elem);
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator++(int)
{
    ConstIterator elem = _node;
    ++(*this);
    return elem;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator--()
{
    Iterator elem = _node;
    --elem;
    return static_cast<ConstIterator>(elem);
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::ConstIterator::operator--(int)
{
    Iterator elem = _node;
    --(*this);
    return elem;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::ConstIterator::operator==(const ConstIterator& other) const
{
    return _node == other._node;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::ConstIterator::operator!=(const ConstIterator& other) const
{
    return _node != other._node;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::cbegin() const
{
    return Iterator(min(_root));
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::cend() const
{
    return ConstIterator(nullptr);
}

// operators //-------------------------------------------------------------------------------

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree(const BinarySearchTree& other)
{
    *this = other;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value> &BinarySearchTree<Key, Value>::operator=(const BinarySearchTree& other)
{
    if (this != other)
    {
        BinarySearchTree BSTcopy(other);
        *this = std::move(BSTcopy);
    }

    return *this;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree(BinarySearchTree&& other) noexcept
{
    *this = std::move(other);
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value> &BinarySearchTree<Key, Value>::operator=(BinarySearchTree&& other) noexcept
{
    if (this != other)
    {
        delete _root;
        _root = nullptr;
        _size = 0;
        std::swap(_root, other._root);
        std::swap(_size, other._size);
    }

    return *this;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clear(_root);
    _root = nullptr;
    _size = 0;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear(Node *CurNode)
{
    if (CurNode)
    {
        clear(CurNode->left);
        clear(CurNode->right);
        delete CurNode;
    }
}

// find //-------------------------------------------------------------------------------

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::find(const Key &key) const
{
    return static_cast<ConstIterator>(find(key));
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator BinarySearchTree<Key, Value>::find(const Key& key)
{
    Node* node = _root;

    while (node != nullptr)
    {
        if (node->keyValuePair.first > key)
        {
            if (node->left == nullptr)
            {
                return Iterator(nullptr);
            }

            node = node->left;
        }
        else if (node->keyValuePair.first < key)
        {
            if (node->right == nullptr)
            {
                return Iterator(nullptr);
            }

            node = node->right;
        }
        else
        {
            break;
        }
    }

    return Iterator(node);
}

// insert //-------------------------------------------------------------------------------

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const Key &key, const Value &value)
{
    if (!_root)
    {
        _root = new Node(key, value);
        ++_size;
        return;
    }

    Node* curNode = _root;
    Key curKey = curNode->keyValuePair.first;

    while ( (curKey >= key && curNode->left != nullptr) || (curKey < key && curNode->right != nullptr) )
    {
        if (curKey >= key)
        {
            curNode = curNode->left;
        }
        else
        {
            curNode = curNode->right;
        }

        curKey = curNode->keyValuePair.first;
    }

    if (curKey >= key)
    {
        curNode->left = new Node(key, value, curNode);
    }
    else
    {
        curNode->right = new Node(key, value, curNode);
    }

    ++_size;
}

// equalRange, max, min, size //-------------------------------------------------------------------------------

template<typename Key, typename Value>
std::pair<typename BinarySearchTree<Key, Value>::Iterator, typename BinarySearchTree<Key, Value>::Iterator>
BinarySearchTree<Key, Value>::equalRange(const Key& key)
{
    Iterator beginIter = find(key);
    Iterator endIter(beginIter);

    if ( beginIter == end() )
    {
        return std::make_pair(beginIter, endIter);
    }

    if (begin()->first == key)
    {
        return std::make_pair(begin(), ++endIter);
    }

    while (beginIter != begin() && beginIter->first == key)
    {
        --beginIter;
    }

    return std::make_pair(++beginIter, ++endIter);
}

template<typename Key, typename Value>
std::pair<typename BinarySearchTree<Key, Value>::ConstIterator, typename BinarySearchTree<Key, Value>::ConstIterator>
BinarySearchTree<Key, Value>::equalRange(const Key& key) const
{
    ConstIterator beginIter = find(key);
    ConstIterator endIter(beginIter);

    if (beginIter == cend() )
    {
        return std::make_pair(beginIter, endIter);
    }

    if (cbegin()->first == key)
    {
        return std::make_pair(cbegin(), ++endIter);
    }

    while (beginIter != cbegin() && beginIter->first == key)
    {
        --beginIter;
    }

    return std::make_pair(++beginIter, ++endIter);
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::min(const Key& key) const
{
    std::pair<ConstIterator, ConstIterator> range = equalRange(key);
    ConstIterator min = ConstIterator(range.first);

    for (ConstIterator iterator = range.first; iterator != range.second; ++iterator)
    {
        if (iterator->second < min->second)
        {
            min = iterator;
        }
    }

    return min;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator BinarySearchTree<Key, Value>::max(const Key& key) const
{
    std::pair<ConstIterator, ConstIterator> range = equalRange(key);
    ConstIterator max = ConstIterator(range.first);

    for (ConstIterator iterator = range.first; iterator != range.second; ++iterator)
    {
        if (iterator->second > max->second)
        {
            max = iterator;
        }
    }

    return max;
}

template<typename Key, typename Value>
std::size_t BinarySearchTree<Key, Value>::size() const
{
    return _size;
}

// erase, eraseNode //-------------------------------------------------------------------------------

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::erase(const Key& key)
{
    while (find(key) != Iterator(nullptr))
    {
        eraseNode(key, _root);
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::eraseNode(const Key& key, Node* node)
{
    Node* curNode = node->keyValuePair.first;

    if (!node)
    {
        return;
    }
    else if (key < curNode)
    {
        eraseNode(key, node->left);
    }
    else if (key > curNode)
    {
        eraseNode(key, node->right);
    }
    else if (key == curNode)
    {
        if (node->left == nullptr && node->right == nullptr)
        {
            if (node->parent->keyValuePair.first > node->keyValuePair.first)
            {
                node->parent->left = nullptr;
            }
            else
            {
                node->parent->right = nullptr;
            }

            delete node;
            --_size;
        }
        else if (node->left && !node->right)
        {
            node->parent->left = node->left;
            node->left->parent = node->parent;

            delete node;
            --_size;
        }
        else if (!node->left && node->right)
        {
            node->parent->right = node->right;
            node->right->parent = node->parent;

            delete node;
            --_size;
        }
        else
        {
            Node* min = min(node->right);
            node->keyValuePair = std::make_pair(min->keyValuePair.first, min->keyValuePair.second);
            node->right = min->right;
            min->right->parent = node;

            delete min;
            --_size;
        }
    }
}


#endif //BST_H
