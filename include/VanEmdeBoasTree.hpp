/*
 * File:    VanEmdeBoasTree
 * Author:  Spiros
 *
 * Created on May 31, 2018, 7:38 PM
 */

#ifndef COMPARISONOFTREEIMPLEMENTATIONS_VANEMDEBOASTREE_HPP
#define COMPARISONOFTREEIMPLEMENTATIONS_VANEMDEBOASTREE_HPP

#include <cmath>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <iostream>

//  displayElements() needs to be implemented
class VanEmdeBoasTree {
public:
    VanEmdeBoasTree();

    ~VanEmdeBoasTree();

    bool insertElement(int value);

    bool removeElement(int value);

    bool containsElement(int value);

    int getMinElement();

    int getMaxElement();

    bool isEmpty();

    void displayElements();

private:
    struct Node {
        explicit Node(int uniSize);

        ~Node();

        //  The size of the universe.
        const int uni;

        //  The square root of the universe size.
        const int uniSqrt;

        //  The lower square root of the universe size.
        const int lowerUniSqrt;

        //  The higher square root of the universe size.
        const int higherUniSqrt;

        //  The minimal value in the tree.
        int min;

        //  The maximal value in the tree.
        int max;

        //  The pointer to the summary structure of the tree.
        Node *summary;

        //  The pointer to the array of clusters of the tree.
        Node **cluster;
    };

    Node *root;

    static int powTwoRoundUp(int value);

    static float lowerSqrt(int value);

    static float higherSqrt(int value);

    bool successor(Node *root, int value, int &result);

    bool predecessor(Node *root, int value, int &result);

    int low(Node *root, int value);

    int high(Node *root, int value);

    int index(Node *root, int high, int low);

    bool insert(Node *&root, int value, int parentUniSqrt = 65536);

    bool remove(Node *&root, int value);

    bool find(Node *root, int value);

    bool findMin(Node *root, int &result);

    bool findMax(Node *root, int &result);

    void inOrder(Node *root);
};


#endif // COMPARISONOFTREEIMPLEMENTATIONS_VANEMDEBOASTREE_HPP