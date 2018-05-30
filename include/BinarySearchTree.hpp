/*
 * File:    BinarySearchTree
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

    void insertElement(int x);

    void removeElement(int x);

    bool containsElement(int x);

    void displayElements();

private:
    struct Node {
        int info;
        struct Node *left;
        struct Node *right;
    };

    Node *root;

    void find(int, Node **, Node **);

    void insert(Node *, Node *);

    void caseA(Node *, Node *);

    void caseB(Node *, Node *);

    void caseC(Node *, Node *);

    void inOrder(Node *);

};


#endif // COMPARISONOFTREEIMPLEMENTATIONS_BINARYTREE_HPP