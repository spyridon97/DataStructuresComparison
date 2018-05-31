/*
 * File:    A2B4Tree.cpp
 * Author:  Spiros
 *
 * Created on May 30, 2018, 5:11 PM
 */

#include <A2B4Tree.hpp>
#include <iostream>
#include <string>
#include <queue>

A2B4Tree::A2B4Tree() {
    root = nullptr;
}

A2B4Tree::~A2B4Tree() {
    deleteTree(root);
    root = nullptr;
}

bool A2B4Tree::insertElement(int value) {
    // Create root node if 2-3-4 tree is empty
    if (!root) {
        root = new Node(new int(value));
        return true;
    }

    int key = value;

    Node *n_ptr = root;  // traversing pointer
    Node *parent = n_ptr;  // previous pointer

    while (n_ptr) {
        // Check for duplicates
        if (n_ptr->containsValue(key)) {
            return false;
        }

        /*** CASE 1: If it's 3 nodes split it ***/
        if (n_ptr->isFull()) {
            // Case 1a: If parent of node has 1 key
            if (1 == parent->valueCount()) {
                if (*(parent->valueA) < *(n_ptr->valueB)) {
                    parent->valueB = n_ptr->valueB;
                    parent->mid1Child = new Node(n_ptr->valueA, n_ptr->leftChild, n_ptr->mid1Child);
                    parent->mid2Child = new Node(n_ptr->valueC, n_ptr->mid2Child, n_ptr->rightChild);
                } else {
                    parent->valueB = parent->valueA;
                    parent->mid2Child = parent->mid1Child;
                    parent->valueA = n_ptr->valueB;
                    parent->leftChild = new Node(n_ptr->valueA, n_ptr->leftChild, n_ptr->mid1Child);
                    parent->mid1Child = new Node(n_ptr->valueC, n_ptr->mid2Child, n_ptr->rightChild);
                }

                delete n_ptr;

                if (key < *(parent->valueA)) {
                    n_ptr = parent->leftChild;
                } else if (key < *(parent->valueB)) {
                    n_ptr = parent->mid1Child;
                } else if (key > *(parent->valueB)) {
                    n_ptr = parent->mid2Child;
                } else {
                    return false; // duplicate
                }

            } // end Case 1a

                // Case 1b: If parent of node has 2 keys
            else if (2 == parent->valueCount()) {
                if (*(parent->valueB) < *(n_ptr->valueB)) {
                    parent->valueC = n_ptr->valueB;
                    parent->mid2Child = new Node(n_ptr->valueA, n_ptr->leftChild, n_ptr->mid1Child);
                    parent->rightChild = new Node(n_ptr->valueC, n_ptr->mid2Child, n_ptr->rightChild);
                } else if (*(parent->valueA) < *(n_ptr->valueB)) {
                    parent->valueC = parent->valueB;
                    parent->rightChild = parent->mid2Child;
                    parent->valueB = n_ptr->valueB;
                    parent->mid1Child = new Node(n_ptr->valueA, n_ptr->leftChild, n_ptr->mid1Child);
                    parent->mid2Child = new Node(n_ptr->valueC, n_ptr->mid2Child, n_ptr->rightChild);
                } else {
                    parent->valueC = parent->valueB;
                    parent->rightChild = parent->mid2Child;
                    parent->valueB = parent->valueA;
                    parent->mid2Child = parent->mid1Child;
                    parent->valueA = n_ptr->valueB;
                    parent->leftChild = new Node(n_ptr->valueA, n_ptr->leftChild, n_ptr->mid1Child);
                    parent->mid1Child = new Node(n_ptr->valueC, n_ptr->mid2Child, n_ptr->rightChild);
                }

                delete n_ptr;

                if (key < *(parent->valueA)) {
                    n_ptr = parent->leftChild;
                } else if (key < *(parent->valueB)) {
                    n_ptr = parent->mid1Child;
                } else if (key < *(parent->valueC)) {
                    n_ptr = parent->mid2Child;
                } else if (key > *(parent->valueC)) {
                    n_ptr = parent->rightChild;
                } else {
                    return false; // duplicate
                }
            } // end of Case 1b

                // Case 1c: If parent of node has 3 keys
            else {
                root = new Node(n_ptr->valueB);
                root->leftChild = new Node(n_ptr->valueA, n_ptr->leftChild, n_ptr->mid1Child);
                root->mid1Child = new Node(n_ptr->valueC, n_ptr->mid2Child, n_ptr->rightChild);
                delete n_ptr;
                parent = root;
                if (key < *(root->valueA)) {
                    n_ptr = root->leftChild;
                } else if (key > *(root->valueA)) {
                    n_ptr = root->mid1Child;
                } else {
                    return false; // duplicate
                }
            } // end Case 1c

        } // end Case 1


        /*** CASE 2: Is it a leaf node ***/
        if (n_ptr->isLeaf()) {
            // Case 2a: Has 1 key
            if (1 == n_ptr->valueCount()) {
                if (key > *(n_ptr->valueA)) {
                    n_ptr->valueB = new int(value);
                    return true;
                } else if (key < *(n_ptr->valueA)) {
                    auto *temp = new int(value);
                    n_ptr->valueB = n_ptr->valueA;
                    n_ptr->valueA = temp;
                    return true;
                }
            } // end Case 2a

                // Case 2b: Has 2 keys
            else if (2 == n_ptr->valueCount()) {
                if (key > *(n_ptr->valueB)) {
                    n_ptr->valueC = new int(value);
                    return true;
                } else if (key > *(n_ptr->valueA)) {
                    auto *temp = new int(value);
                    n_ptr->valueC = n_ptr->valueB;
                    n_ptr->valueB = temp;
                    return true;
                } else if (key < *(n_ptr->valueA)) {
                    auto *temp = new int(value);
                    n_ptr->valueC = n_ptr->valueB;
                    n_ptr->valueB = n_ptr->valueA;
                    n_ptr->valueA = temp;
                    return true;
                }
            } // end Case 2b
        } // end Case 2


            /*** CASE 3: Not a leaf node ***/
        else {
            // Assigns previous pointer
            parent = n_ptr;

            // Case 3a: Has 1 key
            if (1 == n_ptr->valueCount()) {
                if (key < *(n_ptr->valueA)) {
                    n_ptr = n_ptr->leftChild;
                } else {
                    n_ptr = n_ptr->mid1Child;
                }
            }

                // Case 3b: Has 2 keys
            else if (2 == n_ptr->valueCount()) {
                if (key < *(n_ptr->valueA)) {
                    n_ptr = n_ptr->leftChild;
                } else if (key < *(n_ptr->valueB)) {
                    n_ptr = n_ptr->mid1Child;
                } else {
                    n_ptr = n_ptr->mid2Child;
                }
            }
        } // end Case 3

    } // end while

    // Should never get here!
    return false;
}

bool A2B4Tree::removeElement(int value) {
    if (!root) {
        return false;
    }

    // Implement the rest of this function for extra credit
    // Return false if the value is not present in the tree
    // Don't forget the rules for fusing nodes

    Node *n_ptr = root;
    Node *parent = root;

    int *the_item = nullptr;
    Node *n_item = nullptr;

    while (n_ptr) {
        // Case 1: If root and root has single key
        // and both descendents has single keys
        if (n_ptr == root && n_ptr->valueCount() == 1 &&
                n_ptr->leftChild->valueCount() == 1 &&
                n_ptr->mid1Child->valueCount() == 1) {
            // Set value for C and R & M2 pointers
            Node *right = n_ptr->mid1Child;
            n_ptr->valueC = right->valueA;
            n_ptr->mid2Child = right->leftChild;
            n_ptr->rightChild = right->mid1Child;
            delete right;

            // Set value for B
            n_ptr->valueB = n_ptr->valueA;

            // Set value for A and L & M1 pointers
            Node *left = n_ptr->leftChild;
            n_ptr->valueA = left->valueA;
            n_ptr->leftChild = left->leftChild;
            n_ptr->mid1Child = left->mid1Child;
            delete left;

            parent = root;
            n_ptr = root;
        } // end Case 1

        // Cases 2: Transformations (Ensure the_item does not occur in a 2-node)
        // a) Transform each node encountered into a 3 node or a 4 node
        if (n_ptr->valueCount() == 1) {
            // single key on L pointer
            if (parent->leftChild == n_ptr) {
                // Parent has more than 1 key and M1 has 1 key, FUSE IT
                if (parent->mid1Child->valueCount() == 1) {
                    // set C and pointers R & M2
                    parent->mid1Child->valueC = parent->mid1Child->valueA;
                    parent->mid1Child->rightChild = parent->mid1Child->mid1Child;
                    parent->mid1Child->mid2Child = parent->mid1Child->leftChild;
                    // set B
                    parent->mid1Child->valueB = parent->valueA;
                    // set A and pointer L & M1
                    parent->mid1Child->valueA = n_ptr->valueA;
                    parent->mid1Child->leftChild = n_ptr->leftChild;
                    parent->mid1Child->mid1Child = n_ptr->mid1Child;

                    delete parent->leftChild;
                    parent->valueA = parent->valueB;
                    parent->valueB = parent->valueC;
                    parent->valueC = nullptr;
                    parent->leftChild = parent->mid1Child;
                    parent->mid1Child = parent->mid2Child;
                    parent->mid2Child = parent->rightChild;
                    parent->rightChild = nullptr;

                    n_ptr = parent->leftChild;
                }

                    // Sibling has more than 1 key. Borrow
                else if (parent->mid1Child->valueCount() >= 2) {
                    // set B and pointer M2
                    n_ptr->valueB = parent->valueA;
                    n_ptr->mid2Child = parent->mid1Child->leftChild;

                    // set parent A
                    parent->valueA = parent->mid1Child->valueA;

                    // set A, B, C of pointer M1 and its pointers
                    parent->mid1Child->valueA = parent->mid1Child->valueB;
                    parent->mid1Child->valueB = parent->mid1Child->valueC;
                    parent->mid1Child->valueC = nullptr;
                    parent->mid1Child->leftChild = parent->mid1Child->mid1Child;
                    parent->mid1Child->mid1Child = parent->mid1Child->mid2Child;
                    parent->mid1Child->mid2Child = parent->mid1Child->rightChild;
                    parent->mid1Child->rightChild = nullptr;
                }
            } // end single key on L pointer

                // single key on M1 pointer
            else if (parent->mid1Child == n_ptr) {
                // L & M2 have single key, FUSE L & M1
                if (parent->leftChild->valueCount() == 1 && parent->mid2Child->valueCount() == 1) {
                    // set C and pointers R & M2
                    n_ptr->valueC = n_ptr->valueA;
                    n_ptr->rightChild = n_ptr->mid1Child;
                    n_ptr->mid2Child = n_ptr->leftChild;
                    // set B
                    n_ptr->valueB = parent->valueA;
                    // set A and pointers L & M1
                    n_ptr->valueA = parent->leftChild->valueA;
                    n_ptr->mid1Child = parent->leftChild->mid1Child;
                    n_ptr->leftChild = parent->leftChild->leftChild;

                    delete parent->leftChild;
                    parent->valueA = parent->valueB;
                    parent->valueB = parent->valueC;
                    parent->valueC = nullptr;
                    parent->leftChild = parent->mid1Child;
                    parent->mid1Child = parent->mid2Child;
                    parent->mid2Child = parent->rightChild;
                    parent->rightChild = nullptr;

                    // n_ptr already good
                }

                    // borrow from M2
                else if (parent->leftChild->valueCount() < parent->mid2Child->valueCount()) {
                    // set B and pointer M2
                    n_ptr->valueB = parent->valueB;
                    n_ptr->mid2Child = parent->mid2Child->leftChild;

                    // set parent B
                    parent->valueB = parent->mid2Child->valueA;

                    // set M2 values and pointers
                    parent->mid2Child->valueA = parent->mid2Child->valueB;
                    parent->mid2Child->valueB = parent->mid2Child->valueC;
                    parent->mid2Child->valueC = nullptr;
                    parent->mid2Child->leftChild = parent->mid2Child->mid1Child;
                    parent->mid2Child->mid1Child = parent->mid2Child->mid2Child;
                    parent->mid2Child->mid2Child = parent->mid2Child->rightChild;
                    parent->mid2Child->rightChild = nullptr;
                }

                    // borrow from L
                else {
                    // set B and pointer M1 & M2
                    n_ptr->valueB = n_ptr->valueA;
                    n_ptr->mid2Child = n_ptr->mid1Child;
                    n_ptr->mid1Child = n_ptr->leftChild;

                    // set A, parent A and pointer L
                    n_ptr->valueA = parent->valueA;
                    if (parent->leftChild->valueC) {
                        n_ptr->leftChild = parent->leftChild->rightChild;
                        parent->valueA = parent->leftChild->valueC;
                        parent->leftChild->valueC = nullptr;
                        parent->leftChild->rightChild = nullptr;
                    } else {
                        n_ptr->leftChild = parent->leftChild->mid2Child;
                        parent->valueA = parent->leftChild->valueB;
                        parent->leftChild->valueB = nullptr;
                        parent->leftChild->mid2Child = nullptr;
                    }
                }

            } // end single key on M1 pointer

                // single key on M2 pointer
            else if (parent->mid2Child == n_ptr) {
                // M1 & R have single key, FUSE M2 & R
                if (parent->rightChild && parent->mid1Child->valueCount() == 1 &&
                        parent->rightChild->valueCount() == 1) {
                    // set B
                    n_ptr->valueB = parent->valueC;
                    parent->valueC = nullptr;

                    // set C and pointer M2 & R
                    n_ptr->valueC = parent->rightChild->valueA;
                    n_ptr->mid2Child = parent->rightChild->leftChild;
                    n_ptr->rightChild = parent->rightChild->mid1Child;

                    delete parent->rightChild;
                    parent->rightChild = nullptr;

                    // n_ptr is good
                }

                    // borrow from R
                else if (parent->rightChild &&
                        parent->rightChild->valueCount() >= parent->mid1Child->valueCount()) {
                    // set B and pointer M2
                    n_ptr->valueB = parent->valueC;
                    n_ptr->mid2Child = parent->rightChild->leftChild;

                    // set parent C
                    parent->valueC = parent->rightChild->valueA;

                    // set R values and pointers
                    parent->rightChild->valueA = parent->rightChild->valueB;
                    parent->rightChild->valueB = parent->rightChild->valueC;
                    parent->rightChild->valueC = nullptr;
                    parent->rightChild->leftChild = parent->rightChild->mid1Child;
                    parent->rightChild->mid1Child = parent->rightChild->mid2Child;
                    parent->rightChild->mid2Child = parent->rightChild->rightChild;
                    parent->rightChild->rightChild = nullptr;

                    // n_ptr is good
                }

                    // borrow from M1
                else {
                    // set B and pointer M1 & M2
                    n_ptr->valueB = n_ptr->valueA;
                    n_ptr->mid2Child = n_ptr->mid1Child;
                    n_ptr->mid1Child = n_ptr->leftChild;

                    // set A, parent B and pointer L
                    n_ptr->valueA = parent->valueB;
                    if (parent->mid1Child->valueC) {
                        n_ptr->leftChild = parent->mid1Child->rightChild;
                        parent->valueB = parent->mid1Child->valueC;
                        parent->mid1Child->rightChild = nullptr;
                        parent->mid1Child->valueC = nullptr;
                    } else {
                        n_ptr->leftChild = parent->mid1Child->mid2Child;
                        parent->valueB = parent->mid1Child->valueB;
                        parent->mid1Child->mid2Child = nullptr;
                        parent->mid1Child->valueB = nullptr;
                    }
                }

            } // end single key on M2 pointer

                // single key on R pointer
            else if (parent->rightChild == n_ptr) {
                // M2 has a single key, FUSE M2 & R
                if (parent->mid2Child->valueCount() == 1) {
                    // set B
                    parent->mid2Child->valueB = parent->valueC;
                    parent->valueC = nullptr;

                    // set C and pointer M2 & R
                    parent->mid2Child->valueC = n_ptr->valueA;
                    parent->mid2Child->mid2Child = n_ptr->leftChild;
                    parent->mid2Child->rightChild = n_ptr->mid1Child;

                    n_ptr->valueA = nullptr;
                    n_ptr->leftChild = nullptr;
                    n_ptr->mid1Child = nullptr;
                    delete parent->rightChild;

                    n_ptr = parent->mid2Child;
                }

                    // borrow from M2
                else if (parent->mid2Child->valueCount() >= 2) {
                    // set B and pointer M1 & M2
                    n_ptr->valueB = n_ptr->valueA;
                    n_ptr->mid2Child = n_ptr->mid1Child;
                    n_ptr->mid1Child = n_ptr->leftChild;

                    // set A, parent C and pointer L
                    n_ptr->valueA = parent->valueC;
                    if (parent->mid2Child->valueC) {
                        n_ptr->leftChild = parent->mid2Child->rightChild;
                        parent->valueC = parent->mid2Child->valueC;
                        parent->mid2Child->rightChild = nullptr;
                        parent->mid2Child->valueC = nullptr;
                    } else {
                        n_ptr->leftChild = parent->mid2Child->mid2Child;
                        parent->valueC = parent->mid2Child->valueB;
                        parent->mid2Child->mid2Child = nullptr;
                        parent->mid2Child->valueC = nullptr;
                    }
                }

            } // end single key on R pointer
        }

        // Case 3: Item hasn't been found
        // but this node contains key
        if (!the_item && n_ptr->containsValue(value) && !n_ptr->isLeaf()) {
            parent = n_ptr;
            n_item = n_ptr;      // points to the node where the key is found
            if (n_ptr->valueC && value == *(n_ptr->valueC)) {
                the_item = n_ptr->valueC;
                n_ptr = n_ptr->rightChild;  // go to right of key
            } else if (n_ptr->valueB && value == *(n_ptr->valueB)) {
                the_item = n_ptr->valueB;
                n_ptr = n_ptr->mid2Child; // go to right of key
            } else {
                the_item = n_ptr->valueA;
                n_ptr = n_ptr->mid1Child; // go to right of key
            }
        } // Case 3

            // Case 4: Item already found
            // and node contains key (assume its a leaf)
            // The key here is the inOrder successor key
        else if ((the_item && n_ptr->containsValue(value)) ||
                 (n_ptr->containsValue(value) && n_ptr->isLeaf())) {
            while (true) {
                // # of keys greater than or equal to 2 keys
                // delete the key
                if (n_ptr->valueCount() >= 2) {
                    // key is C
                    if (n_ptr->valueC && value == *(n_ptr->valueC)) {
                        delete n_ptr->valueC;
                        n_ptr->valueC = nullptr;
                    }
                        // key is B
                    else if (n_ptr->valueB && value == *(n_ptr->valueB)) {
                        delete n_ptr->valueB;
                        n_ptr->valueB = n_ptr->valueC;
                        n_ptr->valueC = nullptr;
                    }
                        // key is A
                    else // <----- PROBLEM MIGHT BE HERE
                    {
                        delete n_ptr->valueA;
                        n_ptr->valueA = n_ptr->valueB;
                        n_ptr->valueB = n_ptr->valueC;
                        n_ptr->valueC = nullptr;
                    }
                    return true;
                }

                    // key on R pointer
                else if (parent->rightChild && parent->rightChild == n_ptr) {
                    // M2 & R has single keys. FUSE IT
                    if (parent->mid2Child->valueCount() == 1 && parent->rightChild->valueCount() == 1) {
                        parent->mid2Child->valueB = parent->valueC;
                        parent->mid2Child->valueC = n_ptr->valueA;
                        n_ptr->valueA = nullptr;
                        delete parent->rightChild;
                        parent->rightChild = nullptr;
                        parent->valueC = nullptr;
                        n_ptr = parent->mid2Child;
                    }
                        // R has one key and M2 has more than one key
                    else {
                        // borrow from parent C
                        n_ptr->valueB = n_ptr->valueA;
                        n_ptr->valueA = parent->valueC;
                        // parent C borrow C from M2
                        if (parent->mid2Child->valueC) {
                            parent->valueC = parent->mid2Child->valueC;
                            parent->mid2Child->valueC = nullptr;
                        }
                            // parent C borrow B from M2
                        else {
                            parent->valueC = parent->mid2Child->valueB;
                            parent->mid2Child->valueB = nullptr;
                        }
                    }
                }

                    // key on M2 pointer
                else if (parent->mid2Child && parent->mid2Child == n_ptr) {
                    // M1, M2 & R has single keys. FUSE M2 & R
                    if ((parent->mid1Child->valueCount() == 1 &&
                            parent->mid2Child->valueCount() == 1 && !parent->valueC) ||
                        (parent->rightChild && parent->mid1Child->valueCount() == 1 &&
                                parent->mid2Child->valueCount() == 1 && parent->rightChild->valueCount() == 1)) {
                        n_ptr->valueB = parent->valueC;
                        n_ptr->valueC = parent->rightChild->valueA;
                        parent->rightChild->valueA = nullptr;
                        delete parent->rightChild;
                        parent->rightChild = nullptr;
                        parent->valueC = nullptr;
                    }
                        // M2 has one key and R has more keys than M1
                    else if (parent->rightChild &&
                            parent->rightChild->valueCount() >= parent->mid1Child->valueCount()) {
                        // borrow from parent C
                        n_ptr->valueB = parent->valueC;
                        // parent C borrow A from R
                        parent->valueC = parent->rightChild->valueA;
                        parent->rightChild->valueA = parent->rightChild->valueB;
                        parent->rightChild->valueB = parent->rightChild->valueC;
                        parent->rightChild->valueC = nullptr;
                    }
                        // M2 has one key and M1 has more keys than R
                    else {
                        // borrow from parent B
                        n_ptr->valueB = n_ptr->valueA;
                        n_ptr->valueA = parent->valueB;
                        // parent B borrow C from M1
                        if (parent->mid1Child->valueC) {
                            parent->valueB = parent->mid1Child->valueC;
                            parent->mid1Child->valueC = nullptr;
                        }
                            // parent B borrow B from M1
                        else {
                            parent->valueB = parent->mid1Child->valueB;
                            parent->mid1Child->valueB = nullptr;
                        }
                    }
                }

                    // key on M1 pointer
                else if (parent->mid1Child && parent->mid1Child == n_ptr) {
                    // L, M1, & M2 has single keys. FUSE L & M1
                    if (parent->leftChild->valueCount() == 1 &&
                            parent->mid1Child->valueCount() == 1 &&
                            parent->mid2Child->valueCount() == 1) {
                        n_ptr->valueC = n_ptr->valueA;
                        n_ptr->valueB = parent->valueA;
                        n_ptr->valueA = parent->leftChild->valueA;
                        parent->leftChild->valueA = nullptr;
                        delete parent->leftChild;
                        parent->valueA = parent->valueB;
                        parent->valueB = parent->valueC;
                        parent->leftChild = parent->mid1Child;
                        parent->mid1Child = parent->mid2Child;
                        parent->mid2Child = parent->rightChild;
                        parent->rightChild = nullptr;
                    }
                        // M1 has one key and M2 has more keys than L
                    else if (parent->leftChild->valueCount() < parent->mid2Child->valueCount()) {
                        // borrow from parent B
                        n_ptr->valueB = parent->valueB;
                        // parent B borrow A from M2
                        parent->valueB = parent->mid2Child->valueA;
                        parent->mid2Child->valueA = parent->mid2Child->valueB;
                        parent->mid2Child->valueB = parent->mid2Child->valueC;
                        parent->mid2Child->valueC = nullptr;
                    }
                        // M1 has one key and L has more keys than M2
                    else {
                        // borrow from parent A
                        n_ptr->valueB = n_ptr->valueA;
                        n_ptr->valueA = parent->valueA;
                        // parent A borrow C from L
                        if (parent->leftChild->valueC) {
                            parent->valueA = parent->leftChild->valueC;
                            parent->leftChild->valueC = nullptr;
                        }
                            // parent A borrow B from L
                        else {
                            parent->valueA = parent->leftChild->valueB;
                            parent->leftChild->valueB = nullptr;
                        }
                    }
                }

                    // key on L pointer
                else {
                    // L, M1 has single keys. FUSE IT!
                    if (parent->leftChild->valueCount() == 1 && parent->mid1Child->valueCount() == 1) {
                        parent->mid1Child->valueC = parent->mid1Child->valueA;
                        parent->mid1Child->valueB = parent->valueA;
                        parent->mid1Child->valueA = parent->leftChild->valueA;
                        parent->leftChild->valueA = nullptr;
                        delete parent->leftChild;
                        parent->valueA = parent->valueB;
                        parent->valueB = parent->valueC;
                        parent->leftChild = parent->mid1Child;
                        parent->mid1Child = parent->mid2Child;
                        parent->mid2Child = parent->rightChild;
                        parent->rightChild = nullptr;

                        n_ptr = parent->mid1Child;
                    }
                        // L has one key, borrow from M1
                    else {
                        // borrow from parent A
                        n_ptr->valueB = parent->valueA;
                        // parent A borrow A from M1
                        parent->valueA = parent->mid1Child->valueA;
                        parent->mid1Child->valueA = parent->mid1Child->valueB;
                        parent->mid1Child->valueB = parent->mid1Child->valueC;
                        parent->mid1Child->valueC = nullptr;
                    }
                }
            } // end while (1)
        } // end Case 4

        // Case: Item not found yet so continue looking
        if (!the_item) {
            parent = n_ptr;
            if (n_ptr->valueC && value > *(n_ptr->valueC)) {
                n_ptr = n_ptr->rightChild;
            } else if (n_ptr->valueB && value > *(n_ptr->valueB)) {
                n_ptr = n_ptr->mid2Child;
            } else if (value > *(n_ptr->valueA)) {
                n_ptr = n_ptr->mid1Child;
            } else {
                n_ptr = n_ptr->leftChild;
            }
        }
            // Case: Item found. Look for inOrder successor
        else {
            if (n_ptr->leftChild == nullptr) // n_ptr key A is the inOrder successor
            {
                if (n_item->valueA == the_item) {
                    delete n_item->valueA;
                    n_item->valueA = new int(*(n_ptr->valueA));
                } else if (n_item->valueB == the_item) {
                    delete n_item->valueB;
                    n_item->valueB = new int(*(n_ptr->valueA));
                } else {
                    delete n_item->valueC;
                    n_item->valueC = new int(*(n_ptr->valueA));
                }

                value = *(n_ptr->valueA);
            } else {
                parent = n_ptr;
                n_ptr = n_ptr->leftChild;   // go to left of key
            }
        }
    }
    return false;
}

int A2B4Tree::getMinElement() {
    Node *minNode = findMin(root);
    if (minNode != nullptr) {
        std::vector<int> nodeValues;
        if (minNode->valueA != nullptr) {
            nodeValues.push_back(*(minNode->valueA));
        }
        if (minNode->valueB != nullptr) {
            nodeValues.push_back(*(minNode->valueB));
        }
        if (minNode->valueC != nullptr) {
            nodeValues.push_back(*(minNode->valueC));
        }
        int smallest_element = nodeValues[0];
        for (int &nodeValue : nodeValues) {
            if (nodeValue < smallest_element) //used *it (with asterisk), because it's an iterator
            {
                smallest_element = nodeValue;
            }
        }
        return smallest_element;
    }
    return INT_MIN;
}

int A2B4Tree::getMaxElement() {
    Node *maxNode = findMax(root);
    if (maxNode != nullptr) {
        std::vector<int> nodeValues;
        if (maxNode->valueA != nullptr) {
            nodeValues.push_back(*(maxNode->valueA));
        }
        if (maxNode->valueB != nullptr) {
            nodeValues.push_back(*(maxNode->valueB));
        }
        if (maxNode->valueC != nullptr) {
            nodeValues.push_back(*(maxNode->valueC));
        }
        int largest_element = nodeValues[0];
        for (int &nodeValue : nodeValues) {
            if (nodeValue > largest_element) //used *it (with asterisk), because it's an iterator
            {
                largest_element = nodeValue;
            }
        }
        return largest_element;
    }
    return INT_MAX;
}

bool A2B4Tree::containsElement(int value) {
    return find(value) != nullptr;
}

void A2B4Tree::displayElements() {
    if (!root) {
        std::cout << "(tree is empty)";
    }
    display(root);
}

// Constructor to initialize the node with one value. The other two value
// pointers will be set to null and all child pointers will be set to null.
// The pointer given as the parameter is directly copied to A.
A2B4Tree::Node::Node(int *valueForA) {
    valueA = valueForA;
    valueB = valueC = nullptr;
    leftChild = mid1Child = mid2Child = rightChild = nullptr;
}

// Constructor to initialize the node with one value and two child pointers.
A2B4Tree::Node::Node(int *valueA, Node *leftChildOfA, Node *rightChildOfA) {
    this->valueA = valueA;
    leftChild = leftChildOfA;
    mid1Child = rightChildOfA;

    // Everything else is NULL
    valueB = valueC = nullptr;
    mid2Child = rightChild = nullptr;
}

bool A2B4Tree::Node::containsValue(int value) {
    if (valueC && *valueC == value) {
        return true;
    }
    if (valueB && *valueB == value) {
        return true;
    }
    return *valueA == value;
}

int *A2B4Tree::Node::findValue(int value) {
    if (valueC && *valueC == value) {
        return valueC;
    }
    if (valueB && *valueB == value) {
        return valueB;
    }
    if (*valueA == value) {
        return valueA;
    }
    return nullptr;
}

void A2B4Tree::Node::deleteData() {
    if (valueA) {
        delete valueA;
        valueA = nullptr;
    }
    if (valueB) {
        delete valueB;
        valueB = nullptr;
    }
    if (valueC) {
        delete valueC;
        valueC = nullptr;
    }
}

// Returns true if all three data-value pointers, A, B, and C, are non-null,
// false otherwise.
bool A2B4Tree::Node::isFull() {
    return (valueA != nullptr && valueB != nullptr && valueC != nullptr);
}

// Returns true if all 4 child pointers are null,
// implying that the node is a leaf
bool A2B4Tree::Node::isLeaf() {
    return (nullptr == leftChild && nullptr == mid1Child && nullptr == mid2Child && nullptr == rightChild);
}

int A2B4Tree::Node::valueCount() {
    if (valueC) {
        return 3;
    } else if (valueB) {
        return 2;
    } else if (valueA) {
        return 1;
    }
    // Should never come here
    return 0;
}

void A2B4Tree::deleteTree(A2B4Tree::Node *root) {
    if (root) {
        root->deleteData();
        deleteTree(root->leftChild);
        deleteTree(root->mid1Child);
        deleteTree(root->mid2Child);
        deleteTree(root->rightChild);
        delete root;
    }
}

void A2B4Tree::display(A2B4Tree::Node *node) {
    if (!node) {
        return;
    }
    // There will always be an A value with a subtree to left and right of it
    display(node->leftChild);
    int nodeValue = *(node->valueA);
    std::cout << nodeValue << std::endl;
    display(node->mid1Child);

    // There may or may not be a B and C value
    if (node->valueB) {
        nodeValue = *(node->valueB);
        std::cout << nodeValue << std::endl;
        display(node->mid2Child);

        if (node->valueC) {
            nodeValue = *(node->valueC);
            std::cout << nodeValue << std::endl;
            display(node->rightChild);
        }
    }
}

int *A2B4Tree::find(int value) {
    Node *n_ptr = root;

    int *result = n_ptr->findValue(value);

    if (result) {
        return result;
    } else {
        if (n_ptr->valueC && *(n_ptr->valueC) < value) {
            return find(value, n_ptr->rightChild);
        } else if (n_ptr->valueB && *(n_ptr->valueB) < value) {
            return find(value, n_ptr->mid2Child);
        } else if (*(n_ptr->valueA) < value) {
            return find(value, n_ptr->mid1Child);
        } else {
            return find(value, n_ptr->leftChild);
        }
    }
}

int *A2B4Tree::find(int const &value, Node *&node) {
    if (!node) {
        return nullptr;
    }

    int *result = node->findValue(value);
    if (result) { return result; }
    else {
        if (node->valueC && *(node->valueC) < value) {
            return find(value, node->rightChild);
        } else if (node->valueB && *(node->valueB) < value) {
            return find(value, node->mid2Child);
        } else if (*(node->valueA) < value) {
            return find(value, node->mid1Child);
        } else {
            return find(value, node->leftChild);
        }
    }
}

// Finds and returns the node containing the minimum value in the subtree.
A2B4Tree::Node *A2B4Tree::findMin(Node *root) {
    if (root->isLeaf()) {
        return root;
    }

    Node *n = root->leftChild;
    while (n->leftChild) {
        n = n->leftChild;
    }
    return n;
}

A2B4Tree::Node *A2B4Tree::findMax(A2B4Tree::Node *root) {
    if (root->isLeaf()) {
        return root;
    }

    Node *n = root->rightChild;
    while (n->rightChild) {
        n = n->rightChild;
    }
    return n;
}