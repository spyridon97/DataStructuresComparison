/*
 * File:    RedBlackTree.hpp
 * Author:  Spiros
 *
 * Created on May 29, 2018, 5:35 PM
 */

#ifndef COMPARISONOFTREEIMPLEMENTATIONS_REDBLACKTREE_HPP
#define COMPARISONOFTREEIMPLEMENTATIONS_REDBLACKTREE_HPP

#include <memory>
#include <utility>
#include <iostream>

//  this tree does not full work
class RedBlackTree {
public:
    RedBlackTree();

    ~RedBlackTree();

    void insertElement(int value);

    void removeElement(int value);

    bool containsElement(int x) const;

    int getMinElement();

    int getMaxElement();

    bool isEmpty() const;

    void displayElements();

private:
    enum Color {
        Red, Black, DoubleBlack
    };

    struct Node {
        Node(std::shared_ptr<Node const> lft, int val,
             std::shared_ptr<Node const> rgt) : leftChild(std::move(lft)), value(val), rightChild(std::move(rgt)) {
        }

        std::shared_ptr<Node const> leftChild;
        int value;
        std::shared_ptr<Node const> rightChild;
    };

    Color _rootColor;
    std::shared_ptr<const Node> _root;

    RedBlackTree(Color c, RedBlackTree const &lft, int val, RedBlackTree const &rgt)
            : _rootColor(c), _root(std::make_shared<Node>(lft._root, val, rgt._root)) {
    }

    RedBlackTree(Color c, std::shared_ptr<const Node> node) : _rootColor(c), _root(std::move(node)) {}

    RedBlackTree insert(int x) const;

    RedBlackTree remove(int x) const;

    int root() const;

    RedBlackTree left() const;

    RedBlackTree right() const;

    Color rootColor() const;

    RedBlackTree rem(int x) const;

    RedBlackTree remove() const;

    RedBlackTree predecessor() const;

    RedBlackTree ins(int x) const;

    static RedBlackTree removeDoubleBlack(Color c, RedBlackTree const &lft, int x, RedBlackTree const &rgt) {
        if (lft.rootColor() == DoubleBlack) {
            if (rgt.rootColor() == Black) {
                return RedBlackTree(Color(c + 1), lft.paint(Black), x, rgt.paint(Red));
            } else
                return RedBlackTree(Black, RedBlackTree(Black, lft.paint(Black), x, rgt.left()), rgt.root(),
                                    rgt.right());
        } else if (rgt.rootColor() == DoubleBlack) {
            if (lft.rootColor() == Black) {
                return RedBlackTree(Color(c + 1), lft.paint(Red), x, rgt.paint(Black));
            } else {
                return RedBlackTree(Black, lft.left(), lft.root(),
                                    RedBlackTree(Black, lft.right(), x, rgt.paint(Black)));
            }
        } else {
            return RedBlackTree(c, lft, x, rgt);
        }
    }

    static RedBlackTree balance(Color c, RedBlackTree const &lft, int x, RedBlackTree const &rgt) {
        if (c == Black && lft.doubledLeft()) {
            return RedBlackTree(Red, lft.left().paint(Black), lft.root(), RedBlackTree(Black, lft.right(), x, rgt));
        } else if (c == Black && lft.doubledRight()) {
            return RedBlackTree(Red, RedBlackTree(Black, lft.left(), lft.root(), lft.right().left()),
                                lft.right().root(), RedBlackTree(Black, lft.right().right(), x, rgt));
        } else if (c == Black && rgt.doubledLeft()) {
            return RedBlackTree(Red, RedBlackTree(Black, lft, x, rgt.left().left()), rgt.left().root(),
                                RedBlackTree(Black, rgt.left().right(), rgt.root(), rgt.right()));
        } else if (c == Black && rgt.doubledRight()) {
            return RedBlackTree(Red, RedBlackTree(Black, lft, x, rgt.left()), rgt.root(), rgt.right().paint(Black));
        } else {
            return RedBlackTree(c, lft, x, rgt);
        }
    }

    std::shared_ptr<const Node> findMin(std::shared_ptr<const RedBlackTree::Node> &node);

    std::shared_ptr<const Node> findMax(std::shared_ptr<const RedBlackTree::Node> &node);

    bool doubledLeft() const;

    bool doubledRight() const;

    RedBlackTree paint(Color c) const;

    void inOrder(const std::shared_ptr<const Node> &node);
};

#endif // COMPARISONOFTREEIMPLEMENTATIONS_REDBLACKTREE_HPP