/*
 * File:    ScapeGoatTree.cpp
 * Author:  Spiros
 *
 * Created on May 30, 2018, 10:05 PM
 */

#include <ScapeGoatTree.hpp>
#include <iostream>
#include <cmath>
#include <climits>

ScapeGoatTree::ScapeGoatTree() {
    root = nullptr;
    n = 0;
}

ScapeGoatTree::~ScapeGoatTree() {
    makeEmpty();
}

/* Function to insert an element */
bool ScapeGoatTree::insertElement(int value) {
    /* first do basic insertion keeping track of depth */
    auto *u = new Node(value);
    int d = addWithDepth(u);
    if (d > log32(q)) {
        /* depth exceeded, find scapegoat */
        Node *w = u->parent;
        while (3 * size(w) <= 2 * size(w->parent)) {
            w = w->parent;
        }
        rebuild(w->parent);
    }
    return d >= 0;
}

bool ScapeGoatTree::removeElement(int value) {
    if (removeBST(value)) {
        if (2 * n < q) {
            rebuild(root);
            q = n;
        }
        return true;
    }
    return false;
}

/* Functions to search for an element */
bool ScapeGoatTree::containsElement(int value) {
    return find(root, value);
}

int ScapeGoatTree::getMinElement() {
    Node *minNode = findMin(root);
    if (minNode != nullptr) {
        return minNode->value;
    }
    return INT_MIN;
}

int ScapeGoatTree::getMaxElement() {
    Node *maxNode = findMax(root);
    if (maxNode != nullptr) {
        return maxNode->value;
    }
    return INT_MAX;
}

bool ScapeGoatTree::isEmpty() {
    return !root;
}

/* Function for inorder traversal */
void ScapeGoatTree::displayElements() {
    inOrder(root);
}

ScapeGoatTree::Node::Node() {
    value = 0;
    rightChild = nullptr;
    leftChild = nullptr;
    parent = nullptr;
}

ScapeGoatTree::Node::Node(int value) {
    this->value = value;
    rightChild = nullptr;
    leftChild = nullptr;
    parent = nullptr;
}


/* Function to clear  tree */
void ScapeGoatTree::makeEmpty() {
    root = nullptr;
    n = 0;
}

/* Function to count number of nodes recursively */
int ScapeGoatTree::size(Node *root) {
    if (root == nullptr) {
        return 0;
    } else {
        int l = 1;
        l += size(root->leftChild);
        l += size(root->rightChild);
        return l;
    }
}

int ScapeGoatTree::log32(int q) {
    double const log23 = 2.4663034623764317;
    return (int) ceil(log23 * log(q));
}

/* Function to rebuild tree from node u */
void ScapeGoatTree::rebuild(Node *node) {
    int ns = size(node);
    Node *p = node->parent;
    auto **a = new Node *[ns];
    packIntoArray(node, a, 0);
    if (p == nullptr) {
        root = buildBalanced(a, 0, ns);
        root->parent = nullptr;
    } else if (p->rightChild == node) {
        p->rightChild = buildBalanced(a, 0, ns);
        p->rightChild->parent = p;
    } else {
        p->leftChild = buildBalanced(a, 0, ns);
        p->leftChild->parent = p;
    }
}

/* Function to packIntoArray */
int ScapeGoatTree::packIntoArray(Node *u, Node *a[], int i) {
    if (u == nullptr) {
        return i;
    }
    i = packIntoArray(u->leftChild, a, i);
    a[i++] = u;
    return packIntoArray(u->rightChild, a, i);
}

/* Function to build balanced nodes */
ScapeGoatTree::Node *ScapeGoatTree::buildBalanced(Node **a, int i, int ns) {
    if (ns == 0) {
        return nullptr;
    }
    int m = ns / 2;
    a[i + m]->leftChild = buildBalanced(a, i, m);
    if (a[i + m]->leftChild != nullptr) {
        a[i + m]->leftChild->parent = a[i + m];
    }
    a[i + m]->rightChild = buildBalanced(a, i + m + 1, ns - m - 1);
    if (a[i + m]->rightChild != nullptr) {
        a[i + m]->rightChild->parent = a[i + m];
    }
    return a[i + m];
}

/* Function add with depth */
int ScapeGoatTree::addWithDepth(Node *node) {
    Node *w = root;
    if (w == nullptr) {
        root = node;
        n++;
        q++;
        return 0;
    }
    bool done = false;
    int d = 0;
    do {
        if (node->value < w->value) {
            if (w->leftChild == nullptr) {
                w->leftChild = node;
                node->parent = w;
                done = true;
            } else {
                w = w->leftChild;
            }
        } else if (node->value > w->value) {
            if (w->rightChild == nullptr) {
                w->rightChild = node;
                node->parent = w;
                done = true;
            } else {
                w = w->rightChild;
            }
        } else {
            return -1;
        }
        d++;
    } while (!done);

    n++;
    q++;
    return d;
}

// Delete Element from the tree
bool ScapeGoatTree::removeBST(int value) {
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

// * Case A
void ScapeGoatTree::caseA(Node *par, Node *loc) {
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
void ScapeGoatTree::caseB(Node *par, Node *loc) {
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
void ScapeGoatTree::caseC(Node *par, Node *loc) {
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

// Find Element in the Tree
void ScapeGoatTree::find(int value, Node **par, Node **loc) {
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

/* Function to search for an element recursively */

bool ScapeGoatTree::find(Node *root, int value) {
    bool found = false;
    while ((root != nullptr) && !found) {
        int rVal = root->value;
        if (value < rVal) {
            root = root->leftChild;
        } else if (value > rVal) {
            root = root->rightChild;
        } else {
            found = true;
            break;
        }
        found = find(root, value);
    }
    return found;
}

ScapeGoatTree::Node *ScapeGoatTree::findMin(Node *node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->leftChild == nullptr) {
        return node;
    } else {
        return findMin(node->leftChild);
    }
}

ScapeGoatTree::Node *ScapeGoatTree::findMax(Node *node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->rightChild == nullptr) {
        return node;
    } else {
        return findMax(node->rightChild);
    }
}

void ScapeGoatTree::inOrder(Node *node) {
    if (node != nullptr) {
        inOrder(node->leftChild);
        std::cout << node->value << "\n";
        inOrder(node->rightChild);
    }
}