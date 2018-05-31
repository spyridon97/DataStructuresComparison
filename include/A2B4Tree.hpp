/*
 * File:    A2B4Tree.hpp
 * Author:  Spiros
 *
 * Created on May 30, 2018, 5:11 PM
 */

#ifndef COMPARISONOFTREEIMPLEMENTATIONS_A2B4TREE_HPP
#define COMPARISONOFTREEIMPLEMENTATIONS_A2B4TREE_HPP

/*
 *  it has an error while you remove and element it duplicates another the preexisted
 */
class A2B4Tree {
public:
    A2B4Tree();

    virtual ~A2B4Tree();

    bool insertElement(int value);

    bool removeElement(int value);

    bool containsElement(int value);

    int getMinElement();

    int getMaxElement();

    bool isEmpty();

    void displayElements();

private:
    struct Node {
        // A, B and C are the actual data values in the node
        int *valueA;
        int *valueB;
        int *valueC;

        // Child pointers
        Node *leftChild, *mid1Child, *mid2Child, *rightChild;

        // Constructor to initialize the node with one value. The other two value
        // pointers will be set to null and all child pointers will be set to null.
        // The pointer given as the parameter is directly copied to A.
        explicit Node(int *valueForA);

        // Constructor to initialize the node with one value and two child pointers.
        Node(int *valueA, Node *leftChildOfA, Node *rightChildOfA);

        bool containsValue(int value);

        int *findValue(int value);

        void deleteData();

        // Returns true if all three data-value pointers, A, B, and C, are non-null,
        // false otherwise.
        bool isFull();

        // Returns true if all 4 child pointers are null,
        // implying that the node is a leaf
        bool isLeaf();

        int valueCount();
    };

    Node *root;

    void deleteTree(Node *root);

    void display(Node *node);

    int *find(int value);

    int *find(int const &value, Node *&node);

    Node *findMin(Node *root);

    Node *findMax(Node *root);
};

#endif // COMPARISONOFTREEIMPLEMENTATIONS_A2B4TREE_HPP