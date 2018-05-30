/*
 * File:    A2B4Tree
 * Author:  Spiros
 *
 * Created on May 30, 2018, 5:11 PM
 */

#ifndef COMPARISONOFTREEIMPLEMENTATIONS_A2B4TREE_HPP
#define COMPARISONOFTREEIMPLEMENTATIONS_A2B4TREE_HPP

#include <iostream>

class A2B4Tree {
public:
    A2B4Tree();

    virtual ~A2B4Tree();

    void insertElement(int x);

    void removeElement(int x);

    bool containsElement(int x);

    void displayElements();

private:
    struct Node {
        // A, B and C are the actual data values in the node
        int *A;
        int *B;
        int *C;

        // Child pointers
        Node *L, *M1, *M2, *R;

        // Constructor to initialize the node with one value. The other two value
        // pointers will be set to null and all child pointers will be set to null.
        // The pointer given as the parameter is directly copied to A.
        explicit Node(int *valueForA);

        // Constructor to initialize the node with one value and two child pointers.
        Node(int *valueForA, Node *leftChildOfA, Node *rightChildOfA);

        bool ContainsKey(int key);

        int *FindsKey(int key);

        void DeleteData();

        // Returns true if all three data-value pointers, A, B, and C, are non-null,
        // false otherwise.
        bool IsFull();

        // Returns true if all 4 child pointers are null,
        // implying that the node is a leaf
        bool IsLeaf();

        int ValueCount();
    };

    Node *m_root;

    void deleteTree(Node *root);

    void display(Node *n);

    int *find(int key);

    int *find(int const &key, Node *&n_ptr);
};


#endif // COMPARISONOFTREEIMPLEMENTATIONS_A2B4TREE_HPP