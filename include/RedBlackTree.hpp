/*
 * File:    RedBlackTree.hpp
 * Author:  Thanasis1101, tasosxak
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

    int containsElement(int value);

    int getMinElement();

    int getMaxElement();

    bool isEmpty();

    void displayElements();

private:
    enum Color {
        RED, BLACK, DOUBLE_BLACK
    };

    struct Node {
        int value;
        int color;
        Node *left, *right, *parent;

        explicit Node(int value);
    };

    Node *root;

    void leftRotate(Node *&);

    void rotateRight(Node *&);

    Node *insert(Node *&, Node *&);

    Node *deleteBST(Node *&, int);

    void fixInsert(Node *&);

    void fixDelete(Node *&);

    void inOrder(Node *&);

    int getColor(Node *&);

    void setColor(Node *&, int);

    int find(Node *&root, int value);

    Node *findMin(Node *&);

    Node *findMax(Node *&);

    int getBlackHeight(Node *);

    void merge(RedBlackTree);
};

#endif // COMPARISONOFTREEIMPLEMENTATIONS_REDBLACKTREE_HPP