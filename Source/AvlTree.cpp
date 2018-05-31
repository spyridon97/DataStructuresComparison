/*
 * File:    AvlTree.cpp
 * Author:  Spiros
 *
 * Created on May 27, 2018, 7:28 PM
 */

#include <AvlTree.hpp>
#include <iostream>

AvlTree::AvlTree() {
    root = nullptr;
}

AvlTree::~AvlTree() {
    delete root;
}

void AvlTree::insertElement(int value) {
    root = insert(value, root);
}

void AvlTree::removeElement(int value) {
    root = remove(value, root);
}

bool AvlTree::containsElement(int value) {
    return containsElement(value, root) != nullptr;
}

void AvlTree::displayElements() {
    inOrder(root);
}

int AvlTree::getMinElement() {
    Node *minNode = findMin(root);
    if (minNode != nullptr) {
        return minNode->value;
    }
    return INT_MIN;
}

int AvlTree::getMaxElement() {
    Node *maxNode = findMax(root);
    if (maxNode != nullptr) {
        return maxNode->value;
    }
    return INT_MAX;
}

void AvlTree::makeEmpty(AvlTree::Node *t) {
    if (t == nullptr) {
        return;
    }
    makeEmpty(t->leftChild);
    makeEmpty(t->rightChild);
    delete t;
}

AvlTree::Node *AvlTree::insert(int value, Node *node) {
    if (node == nullptr) {
        node = new Node;
        node->value = value;
        node->height = 0;
        node->leftChild = node->rightChild = nullptr;
    } else if (value < node->value) {
        node->leftChild = insert(value, node->leftChild);
        if (height(node->leftChild) - height(node->rightChild) == 2) {
            if (value < node->leftChild->value) {
                node = singleRightRotate(node);
            } else {
                node = doubleRightRotate(node);
            }
        }
    } else if (value > node->value) {
        node->rightChild = insert(value, node->rightChild);
        if (height(node->rightChild) - height(node->leftChild) == 2) {
            if (value > node->rightChild->value) {
                node = singleLeftRotate(node);
            } else {
                node = doubleLeftRotate(node);
            }
        }
    }

    node->height = __max(height(node->leftChild), height(node->rightChild)) + 1;
    return node;
}

AvlTree::Node *AvlTree::singleRightRotate(Node *&node) {
    Node *u = node->leftChild;
    node->leftChild = u->rightChild;
    u->rightChild = node;
    node->height = __max(height(node->leftChild), height(node->rightChild)) + 1;
    u->height = __max(height(u->leftChild), node->height) + 1;
    return u;
}

AvlTree::Node *AvlTree::singleLeftRotate(Node *&node) {
    Node *u = node->rightChild;
    node->rightChild = u->leftChild;
    u->leftChild = node;
    node->height = __max(height(node->leftChild), height(node->rightChild)) + 1;
    u->height = __max(height(node->rightChild), node->height) + 1;
    return u;
}

AvlTree::Node *AvlTree::doubleRightRotate(Node *&node) {
    node->leftChild = singleLeftRotate(node->leftChild);
    return singleRightRotate(node);
}

AvlTree::Node *AvlTree::doubleLeftRotate(Node *&node) {
    node->rightChild = singleRightRotate(node->rightChild);
    return singleLeftRotate(node);
}


AvlTree::Node *AvlTree::containsElement(int value, Node *node) {
    if (node == nullptr) { // Element not found
        return nullptr;
    } else if (value < node->value) { // Searching for element
        return containsElement(value, node->leftChild);
    } else if (value > node->value) {
        return containsElement(value, node->rightChild);
    } else { // Element found
        return node;
    }
}

AvlTree::Node *AvlTree::findMin(Node *node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->leftChild == nullptr) {
        return node;
    } else {
        return findMin(node->leftChild);
    }
}

AvlTree::Node *AvlTree::findMax(Node *node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->rightChild == nullptr) {
        return node;
    } else {
        return findMax(node->rightChild);
    }
}

AvlTree::Node *AvlTree::remove(int value, Node *node) {
    Node *temp;

    if (node == nullptr) { // Element not found
        return nullptr;
    } else if (value < node->value) { // Searching for element
        node->leftChild = remove(value, node->leftChild);
    } else if (value > node->value) {
        node->rightChild = remove(value, node->rightChild);
    } else if (node->leftChild && node->rightChild) { // Element found With 2 children
        temp = findMin(node->rightChild);
        node->value = temp->value;
        node->rightChild = remove(node->value, node->rightChild);
    } else { // With one or zero child
        temp = node;
        if (node->leftChild == nullptr) {
            node = node->rightChild;
        } else if (node->rightChild == nullptr) {
            node = node->leftChild;
        }
        delete temp;
    }

    if (node == nullptr)
        return node;

    node->height = __max(height(node->leftChild), height(node->rightChild)) + 1;

    // If Node is unbalanced
    // If left Node is deleted, right case
    if (height(node->leftChild) - height(node->rightChild) == 2) {
        if (height(node->leftChild->leftChild) - height(node->leftChild->rightChild) == 1) { // right right case
            return singleLeftRotate(node);
        } else { // right left case
            return doubleLeftRotate(node);
        }
    } else if (height(node->rightChild) - height(node->leftChild) == 2) { // If right Node is deleted, left case
        // left left case
        if (height(node->rightChild->rightChild) - height(node->rightChild->leftChild) == 1) {
            return singleRightRotate(node);
        } else { // left right case
            return doubleRightRotate(node);
        }
    }
    return node;
}

int AvlTree::height(Node *node) {
    return (node == nullptr ? -1 : node->height);
}

void AvlTree::inOrder(AvlTree::Node *node) {
    if (node == nullptr) {
        return;
    }
    inOrder(node->leftChild);
    std::cout << node->value << "\n";
    inOrder(node->rightChild);
}