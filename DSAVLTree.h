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

    Node* getLeft();//returns the next node's value
    void setLeft(Node* data);
    Node* getRight();//returns the prev node's value
    void setRight(Node* data);
    T& getData();
    void setData(const T& val);
    int getHeight();
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
Node<T>* Node<T>::getLeft()
{
    return left;
}

template <typename T>
void Node<T>::setLeft(Node<T>* data)
{
    left = data;
}

template <typename T>
Node<T>* Node<T>::getRight()
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
class DSAVLTree {
private:
    Node<T>* root;
    Node<T>* left;
    Node<T>* right;
    int height;//height of entire tree
    int count;//total number of nodes

    bool contains(Node<T>* n, T& val);
    void insert(Node<T>*& n, T& val);

public:
    DSAVLTree();//Rule of 3
    ~DSAVLTree();
    void deleteTree(Node<T>* node);
    DSAVLTree& operator= (const DSAVLTree<T>& copy);
    Node<T>& copyHelper(Node<T>*& node);

    int getHeight(Node<T>* node);//get height from any starting node
    int max(int a, int b);//get max of two integers

//    void insert(T& val);
    bool contains(T& val) { return contains(root, val); }
    void clear();//delete entire tree

    Node<T>* balanceTree(Node<T>* node);//balance the tree using right/left rotate
    Node<T>* rightRotate(Node<T>* node);
    Node<T>* leftRotate(Node<T>* node);

    void preOrder(Node<T>* n);//print functions
    void postOrder(Node<T>* n);
    void inOrder(Node<T>* n);
};

template <typename T>
DSAVLTree<T>::DSAVLTree()
{
    root = nullptr;
    left = nullptr;
    right = nullptr;
    height = 0;
    count = 0;
}

template <typename T>
DSAVLTree<T>::~DSAVLTree()
{
    deleteTree(root);
}

template <typename T>
void DSAVLTree<T>::deleteTree(Node<T>* node)
{
    Node<T>* curr = root;
    if (curr != nullptr){//postOrder
        deleteTree(curr->getLeft());
        deleteTree(curr->getRight());
        delete curr;
    }

    root = nullptr;
    left = nullptr;
    right = nullptr;
    height = 0;
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
int DSAVLTree<T>::getHeight(Node<T>* node)
{
    //go all the way down left and right of given node
    //return the max between those two heights
    int left = 0;
    Node<T>* curr = node;
    while (curr->getLeft() != nullptr){
        curr = curr->getLeft();
    }
    left = curr->getHeight();

    int right = 0;
    curr = node;//reset curr
    while (curr->getRight() != nullptr){
        curr = curr->getRight();
    }
    right = curr->getHeight();

    return max(left, right);
}

template <typename T>
int DSAVLTree<T>::max(int a, int b)
{
    if (a > b)
        return a;
    return b;
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
void DSAVLTree<T>::clear()
{
    deleteTree(root);
    height = 0;
}

template <typename T>
void DSAVLTree<T>::insert(Node<T>*& n, T& val)
{
    if (n == nullptr){//tree is empty or at the end of a leaf
        n = new Node<T>(val);//make new node to insert
        height++;
    }
    else if (val < n->getData())//go to the left for smaller
        insert(n->getLeft(), val);
    else if (n->getData() < val)//go to right for larger
        insert(n->getRight(), val);
    else
        ;//ignore duplicates
}

template <typename T>
Node<T>* DSAVLTree<T>::balanceTree(Node<T>* node)
{

}

template <typename T>
Node<T>* DSAVLTree<T>::rightRotate(Node<T>* node)
{

}

template <typename T>
Node<T>* DSAVLTree<T>::leftRotate(Node<T>* node)
{

}

template <typename T>
void DSAVLTree<T>::preOrder(Node<T>* n)//create copy
{
    if (n != nullptr){
        std::cout << n->getData();
        preOrder(n->getLeft());
        preOrder(n->getRight());
    }
}

template <typename T>
void DSAVLTree<T>::postOrder(Node<T>* n)//delete/clear a tree
{
    if (n != nullptr){
        postOrder(n->getLeft());
        postOrder(n->getRight());
        std::cout << n->getData();
    }
}

template <typename T>
void DSAVLTree<T>::inOrder(Node<T>* n)//visit nodes in ascending/descending order
{
    if (n != nullptr){
        postOrder(n->getLeft());
        std::cout << n->getData();
        postOrder(n->getRight());
    }
}


#endif //INC_22S_FINAL_PROJ_DSAVLTREE_H
