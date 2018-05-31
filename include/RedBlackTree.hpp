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

        explicit Node(int value);
    };

    Node *root;

    void rotateLeft(Node *&node);

    void rotateRight(Node *&node);

    Node *insert(Node *&root, Node *&node);

    Node *remove(Node *&root, int value);

    void fixInsert(Node *&node);

    void fixDelete(Node *&node);

    int getColor(Node *&node);

    void setColor(Node *&node, int color);

    Node *findMin(Node *&node);

    Node *findMax(Node *&node);

    void inOrder(Node *&node);
};

#endif // COMPARISONOFTREEIMPLEMENTATIONS_REDBLACKTREE_HPP