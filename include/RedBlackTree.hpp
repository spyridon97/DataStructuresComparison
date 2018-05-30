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

    void insertElement(int x);

    void removeElement(int x);

    bool containsElement(int x);

    void displayElements();

private:
    enum Color {
        RED, BLACK, DOUBLE_BLACK
    };

    struct Node {
        int data;
        int color;
        Node *left, *right, *parent;

        explicit Node(int);
    };

    Node *root;

    void rotateLeft(Node *&);

    void rotateRight(Node *&);

    void fixInsertRedBlackTree(Node *&);

    void fixDeleteRedBlackBTree(Node *&);

    void inOrderBST(Node *&);

    int getColor(Node *&);

    void setColor(Node *&, int);

    Node *minValueNode(Node *&);

    Node *insertBST(Node *&, Node *&);

    Node *deleteBST(Node *&, int);
};


#endif // COMPARISONOFTREEIMPLEMENTATIONS_REDBLACKTREE_HPP