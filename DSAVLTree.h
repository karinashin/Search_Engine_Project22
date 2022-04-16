//
// Created by Karina Shin on 4/5/2022.
//

#ifndef INC_22S_FINAL_PROJ_DSAVLTREE_H
#define INC_22S_FINAL_PROJ_DSAVLTREE_H

#include <iostream>

template <typename T>
class Node {
private:
    T data;
    Node* left = nullptr;
    Node* right = nullptr;
    int height;

public:
    Node();
    Node(T val);
    Node& operator= (const Node& copy);

    Node*& getLeft();//returns the next node's value
    void setLeft(Node* data);
    Node*& getRight();//returns the prev node's value
    void setRight(Node* data);
    T& getData();
    void setData(const T& val);
    int getHeight();
    void setHeight(int h);
};

template <typename T>
Node<T>::Node(){}

template <typename T>
Node<T>::Node(T val)
{
    data = val;
    left = nullptr;
    right = nullptr;
    height = 0;
}

template <typename T>
Node<T>& Node<T>::operator= (const Node& copy)
{
    data = copy.data;
    height = copy.height;
    if (copy.left != nullptr){
        left = new Node(*(copy.left));
    }

    if (copy.right != nullptr){
        right = new Node(*(copy.right));
    }
}

template <typename T>
Node<T>*& Node<T>::getLeft()
{
    return left;
}

template <typename T>
void Node<T>::setLeft(Node<T>* data)
{
    left = data;
}

template <typename T>
Node<T>*& Node<T>::getRight()
{
    return right;
}

template <typename T>
void Node<T>::setRight(Node<T>* data)
{
    right = data;
}

template <typename T>
void Node<T>::setData(const T& val)
{
    data = val;
}

template <typename T>
T& Node<T>::getData()
{
    return data;
}

template <typename T>
int Node<T>::getHeight()
{
    return height;
}

template <typename T>
void Node<T>::setHeight(int h)
{
    height = h;
}


template <typename T>
class DSAVLTree {
private:
    Node<T>* root;
//    Node<T>* left;
//    Node<T>* right;
//    int height;//height of entire tree
    int count;//total number of nodes

    bool contains(Node<T>* n, T& val);//TODO test private functions?
    void insert(Node<T>*& n, T& val);
    int max(int a, int b);//get max of two integers
    int height(Node<T>* node);//get height from any starting node

public:
    DSAVLTree();//Rule of 3
    ~DSAVLTree();
    void deleteTree(Node<T>*& node);
    DSAVLTree& operator= (const DSAVLTree<T>& copy);
    Node<T>& copyHelper(Node<T>*& node);

//    int getHeight(Node<T>* node);//get height from any starting node
    void insert(T& x);//TODO doesn't accept an int
    bool contains(T& val) { return contains(root, val); }
    T& find(Node<T>* node, T& val);//given a value, find the matching object in the tree

    void balanceTree(Node<T>*& node);//balance the tree using right/left rotate
    void rightRotate(Node<T>*& k1);
    void leftRotate(Node<T>*& k2);
    void doubleLeft(Node<T>*& k3);
    void doubleRight(Node<T>*& k1);

    void inOrder(Node<T>* n);//print tree in order

    Node<T>*& getRoot() { return root; }
    int getCount() { return count; }
};

template <typename T>
DSAVLTree<T>::DSAVLTree()
{
    root = nullptr;
//    left = nullptr;
//    right = nullptr;
//    height = 0;
    count = 0;
}

template <typename T>
DSAVLTree<T>::~DSAVLTree()
{
    deleteTree(root);
}

template <typename T>
void DSAVLTree<T>::deleteTree(Node<T>*& node)
{
    if (node != nullptr){//postOrder
        deleteTree(node->getLeft());
        deleteTree(node->getRight());
        delete node;
    }
    node = nullptr;
}

template <typename T>
DSAVLTree<T>& DSAVLTree<T>::operator= (const DSAVLTree<T>& copy)
{
    //delete everything first
    deleteTree(root);
    //then copy all elements
    copyHelper(copy.root);//copy from root
    this->height = copy.height;

    return *this;
}

template <typename T>
Node<T>& DSAVLTree<T>::copyHelper(Node<T>*& node)//for recursion
{
    //TODO might be wrong
    if (node == nullptr)//preOrder
        return node;//nothing more to copy
    Node<T>* curr = new Node<T>(node->getData());
    curr->setLeft(copyHelper(node->getLeft()));
    curr->setRight(copyHelper(node->getRight()));
}

template <typename T>
int DSAVLTree<T>::max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

template <typename T>
int DSAVLTree<T>::height(Node<T>* node)
{
    if (node == nullptr)
        return -1;
    return node->getHeight();
}

template <typename T>
void DSAVLTree<T>::insert(T& x)//public
{
    insert(root, x);
    count++;
}

template <typename T>
bool DSAVLTree<T>::contains(Node<T>* n, T& val)
{
    if (n == nullptr)
        return false;
    else if (n->getData() == val)
        return true;
    else if (val < n->getData())
        return contains(n->getLeft(), val);
    else
        return contains(n->getRight(), val);
}

template <typename T>
void DSAVLTree<T>::insert(Node<T>*& n, T& val)//private
{
    if (n == nullptr){//tree is empty or at the end of a leaf
        n = new Node<T>(val);//make new node to insert
    }
    else if (val < n->getData())//go to the left for smaller
        insert(n->getLeft(), val);
    else if (n->getData() < val)//go to right for larger
        insert(n->getRight(), val);
    else
        ;//ignore duplicates

    balanceTree(n);
}

template <typename T>
T& DSAVLTree<T>::find(Node<T>* node, T& val)
{
    if (node->getData() == val)
        return node->getData();
    else if (val < node->getData())
        return find(node->getLeft(), val);
    else
        return find(node->getRight(), val);
}

template <typename T>
void DSAVLTree<T>::balanceTree(Node<T>*& node)
{
    if (node == nullptr)
        return;
    if (height(node->getLeft()) - height(node->getRight()) > 1){//Case 1 or 2
        if (height(node->getLeft()->getLeft()) >= height(node->getLeft()->getRight()))//case 1
            leftRotate(node);
        else
            doubleLeft(node);//Case 2
    }
    else if (height(node->getRight()) - height(node->getLeft()) > 1){//Case 3 or 4
        if (height(node->getRight()->getRight()) >= height(node->getRight()->getLeft()))//Case 4
            rightRotate(node);
        else
            doubleRight(node);//Case 3
    }
    node->setHeight(max(height(node->getLeft()), height(node->getRight())) + 1);
}

template <typename T>
void DSAVLTree<T>::rightRotate(Node<T>*& k1)
{
    Node<T>* k2 = k1->getRight();
    k1->setRight(k2->getLeft());
    k2->setLeft(k1);
    k1->setHeight(max(height(k1->getLeft()), height(k1->getRight())) + 1);
    k2->setHeight(max(height(k2->getRight()), k1->getHeight()) + 1);
    k1 = k2;
}

template <typename T>
void DSAVLTree<T>::leftRotate(Node<T>*& k2)
{
    Node<T>* k1 = k2->getLeft();
    k2->getLeft() = k1->getRight();
    k1->setRight(k2);
    k2->setHeight(max(height(k2->getLeft()), height(k2->getRight())) + 1);
    k1->setHeight(max(height(k1->getLeft()), k2->getHeight()) + 1);
    k2 = k1;
}

template <typename T>
void DSAVLTree<T>::doubleLeft(Node<T>*& k3)
{
    rightRotate(k3->getLeft());
    leftRotate(k3);
}

template <typename T>
void DSAVLTree<T>::doubleRight(Node<T>*& k1)
{
    leftRotate(k1->getRight());
    rightRotate(k1);
}

template <typename T>
void DSAVLTree<T>::inOrder(Node<T>* n)//visit nodes in ascending/descending order
{
    if (n != nullptr){
        inOrder(n->getLeft());
        std::cout << n->getData() << std::endl;
        inOrder(n->getRight());
    }
}


#endif //INC_22S_FINAL_PROJ_DSAVLTREE_H
