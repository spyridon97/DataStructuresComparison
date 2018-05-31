/*
 * File:    RedBlackTree.cpp
 * Author:  Spiros
 *
 * Created on May 29, 2018, 5:35 PM
 */

#include <RedBlackTree.hpp>
#include <iostream>

RedBlackTree::Node::Node(int data) {
    this->value = data;
    color = RED;
    leftChild = rightChild = parent = nullptr;
}

RedBlackTree::RedBlackTree() {
    root = nullptr;
    sizeOfTree = 0;
}

RedBlackTree::~RedBlackTree() {
    root = nullptr;
    sizeOfTree = 0;
}

void RedBlackTree::insertElement(int value) {
    auto *node = new Node(value);
    root = insert(root, node);
    fixInsertRedBlackTree(node);
}

void RedBlackTree::removeElement(int value) {
    Node *node = remove(root, value);
    fixDeleteRedBlackBTree(node);
}

bool RedBlackTree::containsElement(int value) {
    Node *node = remove(root, value);
    return node != nullptr;
}

int RedBlackTree::getMinElement() {
    Node *minNode = findMin(root);
    if (minNode != nullptr) {
        return minNode->value;
    }
    return INT_MIN;
}

int RedBlackTree::getMaxElement() {
    Node *maxNode = findMax(root);
    if (maxNode != nullptr) {
        return maxNode->value;
    }
    return INT_MAX;
}

int RedBlackTree::size() {
    return sizeOfTree;
}

void RedBlackTree::displayElements() {
    inOrder(root);
}

int RedBlackTree::getColor(Node *&node) {
    if (node == nullptr) {
        return BLACK;
    }

    return node->color;
}

void RedBlackTree::setColor(Node *&node, int color) {
    if (node == nullptr) {
        return;
    }

    node->color = color;
}

RedBlackTree::Node *RedBlackTree::insert(Node *&root, Node *&node) {
    if (root == nullptr) {
        return node;
    }

    if (node->value < root->value) {
        root->leftChild = insert(root->leftChild, node);
        root->leftChild->parent = root;
    } else if (node->value > root->value) {
        root->rightChild = insert(root->rightChild, node);
        root->rightChild->parent = root;
    }
    return root;
}

void RedBlackTree::rotateLeft(Node *&node) {
    Node *right_child = node->rightChild;
    node->rightChild = right_child->leftChild;

    if (node->rightChild != nullptr) {
        node->rightChild->parent = node;
    }

    right_child->parent = node->parent;

    if (node->parent == nullptr) {
        root = right_child;
    } else if (node == node->parent->leftChild) {
        node->parent->leftChild = right_child;
    } else {
        node->parent->rightChild = right_child;
    }

    right_child->leftChild = node;
    node->parent = right_child;
}

void RedBlackTree::rotateRight(Node *&node) {
    Node *left_child = node->leftChild;
    node->leftChild = left_child->rightChild;

    if (node->leftChild != nullptr) {
        node->leftChild->parent = node;
    }

    left_child->parent = node->parent;

    if (node->parent == nullptr) {
        root = left_child;
    } else if (node == node->parent->leftChild) {
        node->parent->leftChild = left_child;
    } else {
        node->parent->rightChild = left_child;
    }

    left_child->rightChild = node;
    node->parent = left_child;
}

void RedBlackTree::fixInsertRedBlackTree(Node *&node) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (node != root && getColor(node) == RED && getColor(node->parent) == RED) {
        parent = node->parent;
        grandparent = parent->parent;
        if (parent == grandparent->leftChild) {
            Node *uncle = grandparent->rightChild;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                node = grandparent;
            } else {
                if (node == parent->rightChild) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(grandparent);
                // swap colours of parent and grandparent
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                node = parent;
            }
        } else {
            Node *uncle = grandparent->leftChild;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                node = grandparent;
            } else {
                if (node == parent->leftChild) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(grandparent);
                // swap colours of parent and grandparent
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                node = parent;
            }
        }
    }
    setColor(root, BLACK);
}

void RedBlackTree::fixDeleteRedBlackBTree(Node *&node) {
    if (node == nullptr) {
        return;
    }

    if (node == root) {
        root = nullptr;
        return;
    }

    if (getColor(node) == RED || getColor(node->leftChild) == RED || getColor(node->rightChild) == RED) {
        Node *child = node->leftChild != nullptr ? node->leftChild : node->rightChild;

        if (node == node->parent->leftChild) {
            node->parent->leftChild = child;
            if (child != nullptr) {
                child->parent = node->parent;
            }
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->rightChild = child;
            if (child != nullptr) {
                child->parent = node->parent;
            }
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->leftChild) {
                sibling = parent->rightChild;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->leftChild) == BLACK && getColor(sibling->rightChild) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED) {
                            setColor(parent, BLACK);
                        } else {
                            setColor(parent, DOUBLE_BLACK);
                        }
                        ptr = parent;
                    } else {
                        if (getColor(sibling->rightChild) == BLACK) {
                            setColor(sibling->leftChild, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->rightChild;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->rightChild, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->leftChild;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->leftChild) == BLACK && getColor(sibling->rightChild) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED) {
                            setColor(parent, BLACK);
                        } else {
                            setColor(parent, DOUBLE_BLACK);
                        }
                        ptr = parent;
                    } else {
                        if (getColor(sibling->leftChild) == BLACK) {
                            setColor(sibling->rightChild, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->leftChild;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->leftChild, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->leftChild) {
            node->parent->leftChild = nullptr;
        } else {
            node->parent->rightChild = nullptr;
        }
        sizeOfTree--;
        delete node;
        setColor(root, BLACK);
    }
}

RedBlackTree::Node *RedBlackTree::remove(Node *&root, int value) {
    if (root == nullptr) {
        return root;
    }
    if (value < root->value) {
        return remove(root->leftChild, value);
    }
    if (value > root->value) {
        return remove(root->rightChild, value);
    }
    if (root->leftChild == nullptr || root->rightChild == nullptr) {
        return root;
    }
    Node *temp = findMin(root->rightChild);
    root->value = temp->value;
    return remove(root->rightChild, temp->value);
}

RedBlackTree::Node *RedBlackTree::findMin(Node *&node) {
    Node *ptr = node;

    while (ptr->leftChild != nullptr) {
        ptr = ptr->leftChild;
    }
    return ptr;
}

RedBlackTree::Node *RedBlackTree::findMax(Node *&node) {
    Node *ptr = node;

    while (ptr->rightChild != nullptr) {
        ptr = ptr->rightChild;
    }
    return ptr;
}

void RedBlackTree::inOrder(Node *&ptr) {
    if (root == nullptr) {
        return;
    }
    if (ptr != nullptr) {
        inOrder(ptr->leftChild);
        // std::cout << ptr->value << " " << ptr->color << std::endl;
        std::cout << ptr->value << "\n";
        inOrder(ptr->rightChild);
    }
}