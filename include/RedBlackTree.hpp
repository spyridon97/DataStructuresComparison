/*
 * File:    RedBlackTree.hpp
 * Author:  Spiros
 *
 * Created on May 29, 2018, 5:35 PM
 */

#ifndef COMPARISONOFTREEIMPLEMENTATIONS_REDBLACKTREE_HPP
#define COMPARISONOFTREEIMPLEMENTATIONS_REDBLACKTREE_HPP

class RedBlackTree {
public:
    RedBlackTree();

    ~RedBlackTree();

    void insertElement(int value);

    void removeElement(int value);

    bool containsElement(int value);

    int getMinElement();

    int getMaxElement();

    void displayElements();

private:
    enum Color {
        RED, BLACK, DOUBLE_BLACK
    };

    struct Node {
        int value;
        int color;
        Node *leftChild, *rightChild, *parent;

        explicit Node(int);
    };

    Node *root;

    void rotateLeft(Node *&node);

    void rotateRight(Node *&node);

    Node *insert(Node *&root, Node *&node);

    Node *remove(Node *&root, int value);

    void fixInsertRedBlackTree(Node *&node);

    void fixDeleteRedBlackBTree(Node *&node);

    int getColor(Node *&);

    void setColor(Node *&, int);

    Node *findMin(Node *&);

    Node *findMax(Node *&);

    void inOrder(Node *&);
};

#endif // COMPARISONOFTREEIMPLEMENTATIONS_REDBLACKTREE_HPP