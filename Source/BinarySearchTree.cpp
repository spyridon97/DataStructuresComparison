/*
 * File:    BinarySearchTree.cpp
 * Author:  Spiros
 *
 * Created on May 30, 2018, 7:36 PM
 */

#include <BinarySearchTree.hpp>
#include <iostream>

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    root = nullptr;
}

bool BinarySearchTree::insertElement(int value) {
    auto *temp = new Node;
    temp->value = value;
    return insert(root, temp);
}

// Delete Element from the tree
bool BinarySearchTree::removeElement(int value) {
    Node *parent, *location;
    if (root == nullptr) {
        return false;
    }
    find(value, &parent, &location);
    if (location == nullptr) {
        return false;
    }
    if (location->leftChild == nullptr && location->rightChild == nullptr) {
        caseA(parent, location);
    }
    if (location->leftChild != nullptr && location->rightChild == nullptr) {
        caseB(parent, location);
    }
    if (location->leftChild == nullptr && location->rightChild != nullptr) {
        caseB(parent, location);
    }
    if (location->leftChild != nullptr && location->rightChild != nullptr) {
        caseC(parent, location);
    }
    delete location;
    return true;
}

bool BinarySearchTree::containsElement(int value) {
    if (root->value == value) {
        return true;
    }
    Node *parent, *location;
    find(value, &parent, &location);
    return location != nullptr;
}

int BinarySearchTree::getMinElement() {
    Node *minNode = findMin(root);
    if (minNode != nullptr) {
        return minNode->value;
    }
    return INT_MIN;
}

int BinarySearchTree::getMaxElement() {
    Node *maxNode = findMax(root);
    if (maxNode != nullptr) {
        return maxNode->value;
    }
    return INT_MAX;
}

// In Order Traversal
void BinarySearchTree::displayElements() {
    inOrder(root);
}

// Find Element in the Tree
void BinarySearchTree::find(int value, Node **par, Node **loc) {
    Node *ptr, *ptrSave;
    if (root == nullptr) {
        *loc = nullptr;
        *par = nullptr;
        return;
    }
    if (value == root->value) {
        *loc = root;
        *par = nullptr;
        return;
    }
    if (value < root->value) {
        ptr = root->leftChild;
    } else {
        ptr = root->rightChild;
    }
    ptrSave = root;
    while (ptr != nullptr) {
        if (value == ptr->value) {
            *loc = ptr;
            *par = ptrSave;
            return;
        }
        ptrSave = ptr;
        if (value < ptr->value) {
            ptr = ptr->leftChild;
        } else {
            ptr = ptr->rightChild;
        }
    }
    *loc = nullptr;
    *par = ptrSave;
}

// Inserting Element into the Tree
bool BinarySearchTree::insert(Node *node, Node *newNode) {
    if (root == nullptr) {
        root = new Node;
        root->value = newNode->value;
        root->leftChild = nullptr;
        root->rightChild = nullptr;
        //  std::cout << "Root Node is Added" << std::endl;
        return true;
    }
    if (node->value == newNode->value) {
        //  std::cout << "Element already in the tree" << std::endl;
        return false;
    }
    if (node->value > newNode->value) {
        if (node->leftChild != nullptr) {
            insert(node->leftChild, newNode);
        } else {
            node->leftChild = newNode;
            (node->leftChild)->leftChild = nullptr;
            (node->leftChild)->rightChild = nullptr;
            //  std::cout << "Node Added To Left" << std::endl;
            return true;
        }
    } else {
        if (node->rightChild != nullptr) {
            insert(node->rightChild, newNode);
        } else {
            node->rightChild = newNode;
            (node->rightChild)->leftChild = nullptr;
            (node->rightChild)->rightChild = nullptr;
            //  std::cout << "Node Added To Right" << std::endl;
            return true;
        }
    }
    return false;
}

// * Case A
void BinarySearchTree::caseA(Node *par, Node *loc) {
    if (par == nullptr) {
        root = nullptr;
    } else {
        if (loc == par->leftChild) {
            par->leftChild = nullptr;
        } else {
            par->rightChild = nullptr;
        }
    }
}

// * Case B
void BinarySearchTree::caseB(Node *par, Node *loc) {
    Node *child;
    if (loc->leftChild != nullptr) {
        child = loc->leftChild;
    } else {
        child = loc->rightChild;
    }
    if (par == nullptr) {
        root = child;
    } else {
        if (loc == par->leftChild) {
            par->leftChild = child;
        } else {
            par->rightChild = child;
        }
    }
}

// * Case C
void BinarySearchTree::caseC(Node *par, Node *loc) {
    Node *ptr, *ptrSave, *suc, *parSuc;
    ptrSave = loc;
    ptr = loc->rightChild;
    while (ptr->leftChild != nullptr) {
        ptrSave = ptr;
        ptr = ptr->leftChild;
    }
    suc = ptr;
    parSuc = ptrSave;
    if (suc->leftChild == nullptr && suc->rightChild == nullptr) {
        caseA(parSuc, suc);
    } else {
        caseB(parSuc, suc);
    }
    if (par == nullptr) {
        root = suc;
    } else {
        if (loc == par->leftChild) {
            par->leftChild = suc;
        } else {
            par->rightChild = suc;
        }
    }
    suc->leftChild = loc->leftChild;
    suc->rightChild = loc->rightChild;
}

// In Order Traversal
void BinarySearchTree::inOrder(Node *ptr) {
    if (root == nullptr) {
        return;
    }
    if (ptr != nullptr) {
        inOrder(ptr->leftChild);
        std::cout << ptr->value << "\n";
        inOrder(ptr->rightChild);
    }
}

BinarySearchTree::Node *BinarySearchTree::findMin(Node *node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->leftChild == nullptr) {
        return node;
    } else {
        return findMin(node->leftChild);
    }
}

BinarySearchTree::Node *BinarySearchTree::findMax(Node *node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->rightChild == nullptr) {
        return node;
    } else {
        return findMax(node->rightChild);
    }
}