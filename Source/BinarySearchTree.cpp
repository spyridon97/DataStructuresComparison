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

void BinarySearchTree::insertElement(int x) {
    auto *temp = new Node;
    temp->info = x;
    insert(root, temp);
}

// Delete Element from the tree
void BinarySearchTree::removeElement(int item) {
    Node *parent, *location;
    if (root == nullptr) {
        return;
    }
    find(item, &parent, &location);
    if (location == nullptr) {
        return;
    }
    if (location->left == nullptr && location->right == nullptr) {
        caseA(parent, location);
    }
    if (location->left != nullptr && location->right == nullptr) {
        caseB(parent, location);
    }
    if (location->left == nullptr && location->right != nullptr) {
        caseB(parent, location);
    }
    if (location->left != nullptr && location->right != nullptr) {
        caseC(parent, location);
    }
    delete location;
}

bool BinarySearchTree::containsElement(int x) {
    if (root->info == x) {
        return true;
    }
    Node *parent, *location;
    find(x, &parent, &location);
    return location != nullptr;
}

// In Order Traversal
void BinarySearchTree::displayElements() {
    inOrder(root);
}

// Find Element in the Tree
void BinarySearchTree::find(int item, Node **par, Node **loc) {
    Node *ptr, *ptrSave;
    if (root == nullptr) {
        *loc = nullptr;
        *par = nullptr;
        return;
    }
    if (item == root->info) {
        *loc = root;
        *par = nullptr;
        return;
    }
    if (item < root->info) {
        ptr = root->left;
    } else {
        ptr = root->right;
    }
    ptrSave = root;
    while (ptr != nullptr) {
        if (item == ptr->info) {
            *loc = ptr;
            *par = ptrSave;
            return;
        }
        ptrSave = ptr;
        if (item < ptr->info) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }
    *loc = nullptr;
    *par = ptrSave;
}


// Inserting Element into the Tree
void BinarySearchTree::insert(Node *tree, Node *newNode) {
    if (root == nullptr) {
        root = new Node;
        root->info = newNode->info;
        root->left = nullptr;
        root->right = nullptr;
        //  std::cout << "Root Node is Added" << std::endl;
        return;
    }
    if (tree->info == newNode->info) {
        //  std::cout << "Element already in the tree" << std::endl;
        return;
    }
    if (tree->info > newNode->info) {
        if (tree->left != nullptr) {
            insert(tree->left, newNode);
        } else {
            tree->left = newNode;
            (tree->left)->left = nullptr;
            (tree->left)->right = nullptr;
            //  std::cout << "Node Added To Left" << std::endl;
            return;
        }
    } else {
        if (tree->right != nullptr) {
            insert(tree->right, newNode);
        } else {
            tree->right = newNode;
            (tree->right)->left = nullptr;
            (tree->right)->right = nullptr;
            //  std::cout << "Node Added To Right" << std::endl;
            return;
        }
    }
}


// * Case A
void BinarySearchTree::caseA(Node *par, Node *loc) {
    if (par == nullptr) {
        root = nullptr;
    } else {
        if (loc == par->left) {
            par->left = nullptr;
        } else {
            par->right = nullptr;
        }
    }
}


// * Case B
void BinarySearchTree::caseB(Node *par, Node *loc) {
    Node *child;
    if (loc->left != nullptr) {
        child = loc->left;
    } else {
        child = loc->right;
    }
    if (par == nullptr) {
        root = child;
    } else {
        if (loc == par->left) {
            par->left = child;
        } else {
            par->right = child;
        }
    }
}


// * Case C
void BinarySearchTree::caseC(Node *par, Node *loc) {
    Node *ptr, *ptrsave, *suc, *parsuc;
    ptrsave = loc;
    ptr = loc->right;
    while (ptr->left != nullptr) {
        ptrsave = ptr;
        ptr = ptr->left;
    }
    suc = ptr;
    parsuc = ptrsave;
    if (suc->left == nullptr && suc->right == nullptr) {
        caseA(parsuc, suc);
    } else {
        caseB(parsuc, suc);
    }
    if (par == nullptr) {
        root = suc;
    } else {
        if (loc == par->left) {
            par->left = suc;
        } else {
            par->right = suc;
        }
    }
    suc->left = loc->left;
    suc->right = loc->right;
}

// In Order Traversal
void BinarySearchTree::inOrder(Node *ptr) {
    if (root == nullptr) {
        return;
    }
    if (ptr != nullptr) {
        inOrder(ptr->left);
        std::cout << ptr->info << "\n";
        inOrder(ptr->right);
    }
}