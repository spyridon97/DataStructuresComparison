/*
 * File:    SplayTree.hpp
 * Author:  Spiros
 *
 * Created on May 30, 2018, 2:59 PM
 */

#ifndef COMPARISONOFTREEIMPLEMENTATIONS_SPLAYTREE_HPP
#define COMPARISONOFTREEIMPLEMENTATIONS_SPLAYTREE_HPP

class SplayTree {
public:
    SplayTree();

    ~SplayTree();

    void insertElement(int value);

    void removeElement(int value);

    bool containsElement(int value);

    int getMinElement();

    int getMaxElement();

    void displayElements();

private:
    typedef struct Node {
        int value;
        struct Node *leftChild;
        struct Node *rightChild;
    } Node;

    Node *root;

    Node *newNode(int value);

    inline Node *rightRotate(Node *node);

    inline Node *leftRotate(Node *node);

    Node *splay(int value, Node *root);

    Node *insert(int value, Node *root);

    Node *remove(int value, Node *root);

    Node *find(int value, Node *root);

    Node *findMin(Node *node);

    Node *findMax(Node *node);

    void inOrder(Node *root);
};

#endif // COMPARISONOFTREEIMPLEMENTATIONS_SPLAYTREE_HPP