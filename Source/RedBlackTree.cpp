/*
 * File:    RedBlackTree.cpp
 * Author:  Spiros
 *
 * Created on May 29, 2018, 5:35 PM
 */

#include <RedBlackTree.hpp>

RedBlackTree::RedBlackTree() = default;

RedBlackTree::~RedBlackTree() = default;

void RedBlackTree::insertElement(int value) {
    *this = this->insert(value);
}

void RedBlackTree::removeElement(int value) {
    *this = this->remove(value);
}

bool RedBlackTree::containsElement(int x) const {
    if (isEmpty()) {
        return false;
    }
    int y = root();
    if (x < y) {
        return left().containsElement(x);
    } else if (y < x) {
        return right().containsElement(x);
    } else {
        return true;
    }
}

int RedBlackTree::getMinElement() {
    std::shared_ptr<const Node> minNode = findMin(_root);
    if (minNode != nullptr) {
        return minNode->value;
    }
    return INT_MIN;
}

int RedBlackTree::getMaxElement() {
    std::shared_ptr<const Node> maxNode = findMax(_root);
    if (maxNode != nullptr) {
        return maxNode->value;
    }
    return INT_MAX;
}

void RedBlackTree::displayElements() {
    inOrder(_root);
}

bool RedBlackTree::isEmpty() const {
    return !_root;
}

RedBlackTree RedBlackTree::insert(int x) const {
    RedBlackTree t = ins(x);
    return RedBlackTree(Black, t.left(), t.root(), t.right());
}

RedBlackTree RedBlackTree::remove(int x) const {
    RedBlackTree t = rem(x);
    return RedBlackTree(Black, t.left(), t.root(), t.right());
}

int RedBlackTree::root() const {
    return _root->value;
}

RedBlackTree RedBlackTree::left() const {
    return RedBlackTree(_rootColor, _root->leftChild);
}

RedBlackTree RedBlackTree::right() const {
    return RedBlackTree(_rootColor, _root->rightChild);
}

RedBlackTree::Color RedBlackTree::rootColor() const {
    return _rootColor;
}

RedBlackTree RedBlackTree::rem(int x) const {
    if (isEmpty()) {
        return RedBlackTree();
    }
    int y = root();
    if (x < y) {
        return removeDoubleBlack(rootColor(), left().rem(x), y, right());
    } else if (y < x) {
        return removeDoubleBlack(rootColor(), left(), y, right().rem(x));
    } else {
        return remove();
    }
}

RedBlackTree RedBlackTree::remove() const {
    if (!left().isEmpty() && !right().isEmpty()) {
        RedBlackTree p = predecessor();
        int x = p.root();

        return removeDoubleBlack(rootColor(), left().rem(x), x, right());
    } else if (!left().isEmpty()) {
        return left().paint(Black);
    } else if (!right().isEmpty()) {
        return right().paint(Black);
    } else if (rootColor() == Black) {
        return RedBlackTree(DoubleBlack, nullptr);
    } else {
        return RedBlackTree();
    }
}

RedBlackTree RedBlackTree::predecessor() const {
    RedBlackTree t = left();
    while (!t.right().isEmpty()) {
        t = t.right();
    }

    return t;
}

RedBlackTree RedBlackTree::ins(int x) const {
    if (isEmpty()) {
        return RedBlackTree(Red, RedBlackTree(), x, RedBlackTree());
    }
    int y = root();
    if (x < y) {
        return balance(rootColor(), left().ins(x), y, right());
    } else if (y < x) {
        return balance(rootColor(), left(), y, right().ins(x));
    } else {
        return *this; // no duplicates
    }
}

std::shared_ptr<const RedBlackTree::Node> RedBlackTree::findMin(std::shared_ptr<const Node> &node) {
    std::shared_ptr<const Node> ptr = node;

    while (ptr->leftChild != nullptr) {
        ptr = ptr->leftChild;
    }
    return ptr;
}

std::shared_ptr<const RedBlackTree::Node> RedBlackTree::findMax(std::shared_ptr<const Node> &node) {
    std::shared_ptr<const Node> ptr = node;

    while (ptr->rightChild != nullptr) {
        ptr = ptr->rightChild;
    }
    return ptr;
}

bool RedBlackTree::doubledLeft() const {
    return !isEmpty()
           && rootColor() == Red
           && !left().isEmpty()
           && left().rootColor() == Red;
}

bool RedBlackTree::doubledRight() const {
    return !isEmpty()
           && rootColor() == Red
           && !right().isEmpty()
           && right().rootColor() == Red;
}

RedBlackTree RedBlackTree::paint(Color c) const {
    if (isEmpty()) {
        return RedBlackTree(c, nullptr);
    } else {
        return RedBlackTree(c, left(), root(), right());
    }
}

void RedBlackTree::inOrder(const std::shared_ptr<const Node> &node) {
    if (node != nullptr) {
        inOrder(node->leftChild);
        std::cout << node->value << "\n";
        inOrder(node->rightChild);
    }
}