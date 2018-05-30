/*
 * File:    RedBlackTree.hpp
 * Author:  Spiros
 *
 * Created on May 29, 2018, 5:35 PM
 */

#include <RedBlackTree.hpp>
#include <iostream>

RedBlackTree::Node::Node(int data) {
    this->data = data;
    color = RED;
    left = right = parent = nullptr;
}

RedBlackTree::RedBlackTree() {
    root = nullptr;
}

RedBlackTree::~RedBlackTree() = default;

void RedBlackTree::insertElement(int x) {
    auto *node = new Node(x);
    root = insertBST(root, node);
    fixInsertRedBlackTree(node);
}

void RedBlackTree::removeElement(int x) {
    Node *node = deleteBST(root, x);
    fixDeleteRedBlackBTree(node);
}

bool RedBlackTree::containsElement(int x) {
    Node *node = deleteBST(root, x);
    return node != nullptr;
}

void RedBlackTree::displayElements() {
    inOrderBST(root);
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

RedBlackTree::Node *RedBlackTree::insertBST(Node *&root, Node *&ptr) {
    if (root == nullptr) {
        return ptr;
    }

    if (ptr->data < root->data) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->data > root->data) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}

void RedBlackTree::rotateLeft(Node *&ptr) {
    Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr) {
        ptr->right->parent = ptr;
    }

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr) {
        root = right_child;
    } else if (ptr == ptr->parent->left) {
        ptr->parent->left = right_child;
    } else {
        ptr->parent->right = right_child;
    }

    right_child->left = ptr;
    ptr->parent = right_child;
}

void RedBlackTree::rotateRight(Node *&ptr) {
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr) {
        ptr->left->parent = ptr;
    }

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr) {
        root = left_child;
    } else if (ptr == ptr->parent->left) {
        ptr->parent->left = left_child;
    } else {
        ptr->parent->right = left_child;
    }

    left_child->right = ptr;
    ptr->parent = left_child;
}

void RedBlackTree::fixInsertRedBlackTree(Node *&ptr) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                // swap colours of parent and grandparent
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                ptr = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                // swap colours of parent and grandparent
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                ptr = parent;
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

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr) {
                child->parent = node->parent;
            }
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
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
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED) {
                            setColor(parent, BLACK);
                        } else {
                            setColor(parent, DOUBLE_BLACK);
                        }
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED) {
                            setColor(parent, BLACK);
                        } else {
                            setColor(parent, DOUBLE_BLACK);
                        }
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
        delete (node);
        setColor(root, BLACK);
    }
}

RedBlackTree::Node *RedBlackTree::deleteBST(Node *&root, int data) {
    if (root == nullptr) {
        return root;
    }
    if (data < root->data) {
        return deleteBST(root->left, data);
    }
    if (data > root->data) {
        return deleteBST(root->right, data);
    }
    if (root->left == nullptr || root->right == nullptr) {
        return root;
    }
    Node *temp = minValueNode(root->right);
    root->data = temp->data;
    return deleteBST(root->right, temp->data);
}


void RedBlackTree::inOrderBST(Node *&ptr) {
    if (ptr == nullptr) {
        return;
    }

    inOrderBST(ptr->left);
    // cout << ptr->data << " " << ptr->color << endl;
    std::cout << ptr->data << std::endl;
    inOrderBST(ptr->right);
}

RedBlackTree::Node *RedBlackTree::minValueNode(Node *&node) {
    Node *ptr = node;

    while (ptr->left != nullptr) {
        ptr = ptr->left;
    }
    return ptr;
}