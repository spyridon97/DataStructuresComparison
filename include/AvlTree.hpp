/*
 * File:    AvlTree.hpp
 * Author:  Spiros
 *
 * Created on May 27, 2018, 7:28 PM
 */

#ifndef TREECOMPARISON_AVLTREE_HPP
#define TREECOMPARISON_AVLTREE_HPP


class AvlTree {
private:
    struct Node {
        int data;
        Node *left;
        Node *right;
        int height;
    };
    Node *root;

    void makeEmpty(Node *t);

    Node *insert(int x, Node *t);

    Node *singleRightRotate(Node *&t);

    Node *singleLeftRotate(Node *&t);

    Node *doubleLeftRotate(Node *&t);

    Node *doubleRightRotate(Node *&t);

    Node *containsElement(int x, Node *t);

    Node *findMin(Node *t);

    Node *findMax(Node *t);

    Node *remove(int x, Node *t);

    int height(Node *t);

    void inOrder(Node *t);

public:
    AvlTree();

    ~AvlTree();

    void insertElement(int x);

    void removeElement(int x);

    bool containsElement(int x);

    void displayElements();
};


#endif // TREECOMPARISON_AVLTREE_HPP