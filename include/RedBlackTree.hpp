/*
 * File:    RedBlackTree.hpp
 * Author:  Spiros
 *
 * Created on May 29, 2018, 5:35 PM
 */

#ifndef TREECOMPARISON_REDBLACKTREE_HPP
#define TREECOMPARISON_REDBLACKTREE_HPP

enum Color {
    RED, BLACK, DOUBLE_BLACK
};

struct Node {
    int data;
    int color;
    Node *left, *right, *parent;

    explicit Node(int);
};

class RedBlackTree {
private:
    Node *root;
protected:
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

public:
    RedBlackTree();

    ~RedBlackTree();

    void insertElement(int data);

    void removeElement(int data);

    bool containsElement(int data);

    void displayElements();
};


#endif // TREECOMPARISON_REDBLACKTREE_HPP