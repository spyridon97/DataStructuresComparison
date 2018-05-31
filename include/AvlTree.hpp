/*
 * File:    AvlTree.hpp
 * Author:  Spiros
 *
 * Created on May 27, 2018, 7:28 PM
 */

#ifndef COMPARISONOFTREEIMPLEMENTATIONS_AVLTREE_HPP
#define COMPARISONOFTREEIMPLEMENTATIONS_AVLTREE_HPP

class AvlTree {
public:
    AvlTree();

    ~AvlTree();

    void insertElement(int value);

    void removeElement(int value);

    bool containsElement(int value);

    int getMinElement();

    int getMaxElement();

    bool isEmpty();

    void displayElements();

private:
    struct Node {
        int value;
        Node *leftChild;
        Node *rightChild;
        int height;
    };

    Node *root;

    Node* newNode(int key);

    Node *insert(Node *node, int value);

    Node *rightRotate(Node *node);

    Node *leftRotate(Node *node);

    Node *containsElement(int value, Node *node);

    int getBalance(Node *node);

    Node *findMin(Node *node);

    Node *findMax(Node *node);

    Node *remove(Node *root, int value);

    int height(Node *node);

    void inOrder(Node *node);
};

#endif // COMPARISONOFTREEIMPLEMENTATIONS_AVLTREE_HPP