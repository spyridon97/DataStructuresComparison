/*
 * File:    RedBlackTree.cpp
 * Author:  Thanasis1101, tasosxak
 *
 * Created on May 29, 2018, 5:35 PM
 */

#include <RedBlackTree.hpp>
#include <bits/stdc++.h>

RedBlackTree::RedBlackTree() {
    root = nullptr;
}

RedBlackTree::~RedBlackTree() {
    root = nullptr;
}

int RedBlackTree::containsElement(int value) {
    return find(root, value);
}

void RedBlackTree::insertElement(int value) {
    auto *node = new Node(value);
    root = insert(root, node);
    fixInsert(node);
}

bool RedBlackTree::isEmpty() {
    return root == nullptr;
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

void RedBlackTree::displayElements() {
    inOrder(root);
}

RedBlackTree::Node::Node(int data) {
    this->value = data;
    color = RED;
    left = right = parent = nullptr;
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

RedBlackTree::Node *RedBlackTree::insert(Node *&root, Node *&ptr) {
    if (root == nullptr) {
        return ptr;
    }
    if (ptr->value < root->value) {
        root->left = insert(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->value > root->value) {
        root->right = insert(root->right, ptr);
        root->right->parent = root;
    }
    return root;
}


int RedBlackTree::find(Node *&root, int value) {
    if (root == nullptr) {
        return -1;
    }
    if (value == root->value) {
        return value;
    } else if (value < root->value) {
        find(root->left, value);
    } else if (value > root->value) {
        find(root->right, value);
    }
}


void RedBlackTree::leftRotate(Node *&ptr) {
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

void RedBlackTree::fixInsert(Node *&ptr) {
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
                    leftRotate(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                //  swap
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
                leftRotate(grandparent);
                //  swap
                int temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}

void RedBlackTree::fixDelete(Node *&node) {
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
                    leftRotate(parent);
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
                        leftRotate(parent);
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
                            leftRotate(sibling);
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

    if (data < root->value) {
        return deleteBST(root->left, data);
    }

    if (data > root->value) {
        return deleteBST(root->right, data);
    }

    if (root->left == nullptr || root->right == nullptr) {
        return root;
    }

    Node *temp = findMin(root->right);
    root->value = temp->value;
    return deleteBST(root->right, temp->value);
}

void RedBlackTree::deleteElement(int data) {
    Node *node = deleteBST(root, data);
    fixDelete(node);
}

void RedBlackTree::inOrder(Node *&ptr) {
    if (ptr == nullptr) {
        return;
    }

    inOrder(ptr->left);
    std::cout << ptr->value << "\n";
    inOrder(ptr->right);
}


RedBlackTree::Node *RedBlackTree::findMin(Node *&node) {
    Node *ptr = node;

    while (ptr->left != nullptr) {
        ptr = ptr->left;
    }

    return ptr;
}

RedBlackTree::Node *RedBlackTree::findMax(Node *&node) {
    Node *ptr = node;

    while (ptr->right != nullptr) {
        ptr = ptr->right;
    }

    return ptr;
}

int RedBlackTree::getBlackHeight(Node *node) {
    int blackheight = 0;
    while (node != nullptr) {
        if (getColor(node) == BLACK) {
            blackheight++;
        }
        node = node->left;
    }
    return blackheight;
}

void RedBlackTree::merge(RedBlackTree RedBlackTree2) {
    int temp;
    Node *c, *temp_ptr;
    Node *root1 = root;
    Node *root2 = RedBlackTree2.root;

    int initialblackheight1 = getBlackHeight(root1);
    int initialblackheight2 = getBlackHeight(root2);
    if (initialblackheight1 > initialblackheight2) {
        c = findMax(root1);
        temp = c->value;
        deleteElement(c->value);
        root1 = root;
    } else if (initialblackheight2 > initialblackheight1) {
        c = findMin(root2);
        temp = c->value;
        RedBlackTree2.deleteElement(c->value);
        root2 = RedBlackTree2.root;
    } else {
        c = findMin(root2);
        temp = c->value;
        RedBlackTree2.deleteElement(c->value);
        root2 = RedBlackTree2.root;
        if (initialblackheight1 != getBlackHeight(root2)) {
            RedBlackTree2.insertElement(c->value);
            root2 = RedBlackTree2.root;
            c = findMax(root1);
            temp = c->value;
            deleteElement(c->value);
            root1 = root;
        }
    }
    setColor(c, RED);

    int finalblackheight1 = getBlackHeight(root1);
    int finalblackheight2 = getBlackHeight(root2);
    if (finalblackheight1 == finalblackheight2) {
        c->left = root1;
        root1->parent = c;
        c->right = root2;
        root2->parent = c;
        setColor(c, BLACK);
        c->value = temp;
        root = c;
    } else if (finalblackheight2 > finalblackheight1) {
        Node *ptr = root2;
        while (finalblackheight1 != getBlackHeight(ptr)) {
            temp_ptr = ptr;
            ptr = ptr->left;
        }
        Node *ptr_parent;
        if (ptr == nullptr) {
            ptr_parent = temp_ptr;
        } else {
            ptr_parent = ptr->parent;
        }
        c->left = root1;
        if (root1 != nullptr) {
            root1->parent = c;
        }
        c->right = ptr;
        if (ptr != nullptr) {
            ptr->parent = c;
        }
        ptr_parent->left = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == RED) {
            {
                fixInsert(c);
            }
        } else if (getColor(ptr) == RED) {
            fixInsert(ptr);
        }
        c->value = temp;
        root = root2;
    } else {
        Node *ptr = root1;
        while (finalblackheight2 != getBlackHeight(ptr)) {
            ptr = ptr->right;
        }
        Node *ptr_parent = ptr->parent;
        c->right = root2;
        root2->parent = c;
        c->left = ptr;
        ptr->parent = c;
        ptr_parent->right = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == RED) {
            fixInsert(c);
        } else if (getColor(ptr) == RED) {
            fixInsert(ptr);
        }
        c->value = temp;
        root = root1;
    }
}