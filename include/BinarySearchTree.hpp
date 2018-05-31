/*
 * File:    BinarySearchTree.hpp
 * Author:  Spiros
 *
 * Created on May 30, 2018, 7:36 PM
 */

#ifndef COMPARISONOFTREEIMPLEMENTATIONS_BINARYTREE_HPP
#define COMPARISONOFTREEIMPLEMENTATIONS_BINARYTREE_HPP

class BinarySearchTree {
public:
    BinarySearchTree();

    ~BinarySearchTree();

    bool insertElement(int value);

    bool removeElement(int value);

    bool containsElement(int value);

    int getMinElement();

    int getMaxElement();

    bool isEmpty();

    void displayElements();

private:
    struct Node {
        int value;
        struct Node *leftChild;
        struct Node *rightChild;
    };

    Node *root;

    bool insert(Node *node, Node *newNode);

    void find(int value, Node **par, Node **loc);

    void caseA(Node *par, Node *loc);

    void caseB(Node *par, Node *loc);

    void caseC(Node *par, Node *loc);

    Node *findMin(Node *node);

    Node *findMax(Node *node);

    void inOrder(Node *node);

};

#endif // COMPARISONOFTREEIMPLEMENTATIONS_BINARYTREE_HPP