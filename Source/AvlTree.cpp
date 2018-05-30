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

void AvlTree::insertElement(int x) {
    root = insert(x, root);
}

void AvlTree::removeElement(int x) {
    root = remove(x, root);
}

bool AvlTree::containsElement(int x) {
    return containsElement(x, root) != nullptr;
}

void AvlTree::displayElements() {
    inOrder(root);
}

void AvlTree::makeEmpty(AvlTree::Node *t) {
    if (t == nullptr) {
        return;
    }
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

AvlTree::Node *AvlTree::insert(int x, AvlTree::Node *t) {
    if (t == nullptr) {
        t = new Node;
        t->data = x;
        t->height = 0;
        t->left = t->right = nullptr;
    } else if (x < t->data) {
        t->left = insert(x, t->left);
        if (height(t->left) - height(t->right) == 2) {
            if (x < t->left->data) {
                t = singleRightRotate(t);
            } else {
                t = doubleRightRotate(t);
            }
        }
    } else if (x > t->data) {
        t->right = insert(x, t->right);
        if (height(t->right) - height(t->left) == 2) {
            if (x > t->right->data) {
                t = singleLeftRotate(t);
            } else {
                t = doubleLeftRotate(t);
            }
        }
    }

    t->height = __max(height(t->left), height(t->right)) + 1;
    return t;
}

AvlTree::Node *AvlTree::singleRightRotate(AvlTree::Node *&t) {
    Node *u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = __max(height(t->left), height(t->right)) + 1;
    u->height = __max(height(u->left), t->height) + 1;
    return u;
}

AvlTree::Node *AvlTree::singleLeftRotate(AvlTree::Node *&t) {
    Node *u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = __max(height(t->left), height(t->right)) + 1;
    u->height = __max(height(t->right), t->height) + 1;
    return u;
}

AvlTree::Node *AvlTree::doubleRightRotate(AvlTree::Node *&t) {
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
}

AvlTree::Node *AvlTree::doubleLeftRotate(AvlTree::Node *&t) {
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
}


AvlTree::Node *AvlTree::containsElement(int x, AvlTree::Node *t) {
    if (t == nullptr) { // Element not found
        return nullptr;
    } else if (x < t->data) { // Searching for element
        return containsElement(x, t->left);
    } else if (x > t->data) {
        return containsElement(x, t->right);
    } else { // Element found
        return t;
    }
}

AvlTree::Node *AvlTree::findMin(AvlTree::Node *t) {
    if (t == nullptr) {
        return nullptr;
    } else if (t->right == nullptr) {
        return t;
    } else {
        return findMax(t->right);
    }
}

AvlTree::Node *AvlTree::findMax(Node *t) {
    if (t == nullptr) {
        return nullptr;
    } else if (t->right == nullptr) {
        return t;
    } else {
        return findMax(t->right);
    }
}

AvlTree::Node *AvlTree::remove(int x, AvlTree::Node *t) {
    Node *temp;

    if (t == nullptr) { // Element not found
        return nullptr;
    } else if (x < t->data) { // Searching for element
        t->left = remove(x, t->left);
    } else if (x > t->data) {
        t->right = remove(x, t->right);
    } else if (t->left && t->right) { // Element found With 2 children
        temp = findMin(t->right);
        t->data = temp->data;
        t->right = remove(t->data, t->right);
    } else { // With one or zero child
        temp = t;
        if (t->left == nullptr) {
            t = t->right;
        } else if (t->right == nullptr) {
            t = t->left;
        }
        delete temp;
    }

    if (t == nullptr)
        return t;

    t->height = __max(height(t->left), height(t->right)) + 1;

    // If Node is unbalanced
    // If left Node is deleted, right case
    if (height(t->left) - height(t->right) == 2) {
        if (height(t->left->left) - height(t->left->right) == 1) { // right right case
            return singleLeftRotate(t);
        } else { // right left case
            return doubleLeftRotate(t);
        }
    } else if (height(t->right) - height(t->left) == 2) { // If right Node is deleted, left case
        // left left case
        if (height(t->right->right) - height(t->right->left) == 1) {
            return singleRightRotate(t);
        } else { // left right case
            return doubleRightRotate(t);
        }
    }
    return t;
}

int AvlTree::height(AvlTree::Node *t) {
    return (t == nullptr ? -1 : t->height);
}

void AvlTree::inOrder(AvlTree::Node *t) {
    if (t == nullptr) {
        return;
    }
    inOrder(t->left);
    std::cout << t->data << "\n";
    inOrder(t->right);
}