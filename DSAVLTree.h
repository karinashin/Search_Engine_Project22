//
// Created by Karina Shin on 4/5/2022.
//

#ifndef INC_22S_FINAL_PROJ_DSAVLTREE_H
#define INC_22S_FINAL_PROJ_DSAVLTREE_H

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
class DSAVLTree {
private:
    Node<T>* root;
    Node<T>* left;
    Node<T>* right;
    int height;//height of entire tree

public:
    DSAVLTree();//Rule of 3
    ~DSAVLTree();
    DSAVLTree& operator= (const DSAVLTree<T>& copy);

    int getHeight(Node<T>* node);//get height from any starting node
    int max(int a, int b);//get max of two integers
    void insert(Node<T>* data);

    Node<T>* balanceTree(Node<T>* node);//balance the tree using right/left rotate
    Node<T>* rightRotate(Node<T>* node);
    Node<T>* leftRotate(Node<T>* node);

    void preOrder();//print functions
    void postOrder();
};

template <typename T>
DSAVLTree<T>::DSAVLTree()
{
    root = nullptr;
    left = nullptr;
    right = nullptr;
    height = 0;
}

template <typename T>
DSAVLTree<T>::~DSAVLTree()
{

}

template <typename T>
DSAVLTree<T>& DSAVLTree<T>::operator= (const DSAVLTree<T>& copy)
{
    //delete everything first
    //then copy elements
}


template <typename T>
int DSAVLTree<T>::getHeight(Node<T>* node)
{
    //go all the way down left and right of given node
    //return the max between those two heights
}

template <typename T>
int DSAVLTree<T>::max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

template <typename T>
void DSAVLTree<T>::insert(Node<T>* data)
{

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
void DSAVLTree<T>::preOrder()
{

}

template <typename T>
void DSAVLTree<T>::postOrder()
{

}


#endif //INC_22S_FINAL_PROJ_DSAVLTREE_H
