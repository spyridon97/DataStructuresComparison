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

    void displayElements();

private:
    struct Node {
        int value;
        Node *leftChild;
        Node *rightChild;
        int height;
    };

    Node *root;

    void makeEmpty(Node *t);

    Node *insert(int value, Node *node);

    Node *singleRightRotate(Node *&node);

    Node *singleLeftRotate(Node *&node);

    Node *doubleLeftRotate(Node *&node);

    Node *doubleRightRotate(Node *&node);

    Node *containsElement(int value, Node *node);

    Node *findMin(Node *node);

    Node *findMax(Node *node);

    Node *remove(int value, Node *node);

    int height(Node *node);

    void inOrder(Node *node);
};

#endif // COMPARISONOFTREEIMPLEMENTATIONS_AVLTREE_HPP