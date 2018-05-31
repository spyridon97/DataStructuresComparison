/*
 * File:    ScapeGoatTree.hpp
 * Author:  Spiros
 *
 * Created on May 30, 2018, 10:05 PM
 */

#ifndef COMPARISONOFTREEIMPLEMENTATIONS_SCAPEGOATTREE_HPP
#define COMPARISONOFTREEIMPLEMENTATIONS_SCAPEGOATTREE_HPP


class ScapeGoatTree {
public:
    ScapeGoatTree();

    ~ScapeGoatTree();

    bool insertElement(int value);

    bool removeElement(int value);

    bool containsElement(int value);

    int getMinElement();

    int getMaxElement();

    void displayElements();

private:
    struct Node {
        Node *rightChild, *leftChild, *parent;
        int value;

        Node();

        explicit Node(int value);
    };

    Node *root;

    int n, q;

    void makeEmpty();

    int size(Node *root);

    int log32(int q);

    void rebuild(Node *node);

    int packIntoArray(Node *u, Node *a[], int i);

    Node *buildBalanced(Node **a, int i, int ns);

    int addWithDepth(Node *node);

    bool removeBST(int value);

    void caseA(Node *par, Node *loc);

    void caseB(Node *par, Node *loc);

    void caseC(Node *par, Node *loc);

    void find(int value, Node **par, Node **loc);

    bool find(Node *root, int value);

    Node *findMin(Node *node);

    Node *findMax(Node *node);

    void inOrder(Node *node);
};

#endif // COMPARISONOFTREEIMPLEMENTATIONS_SCAPEGOATTREE_HPP