/*
 * File:    SkipList.hpp
 * Author:  Spiros
 *
 * Created on May 29, 2018, 4:13 PM
 */

#ifndef TREECOMPARISON_SKIPLIST_HPP
#define TREECOMPARISON_SKIPLIST_HPP

#include <iostream>
#include <vector>
#include <limits>


class SkipList {
private:
    struct Element {
        Element(int k, int new_height) : key(k), next((unsigned long long) new_height + 1) {}

        int key;
        std::vector<Element *> next;
    };

    const int max_height = 16;

    const int INF = std::numeric_limits<int>::max();

    Element head;

    Element tail;

    int height;

    int random_height();

public:
    SkipList();

    ~SkipList();

    void insertElement(int x);

    void removeElement(int x);

    bool containsElement(int x);

    void displayElements();

    int get_height();
};


#endif // TREECOMPARISON_SKIPLIST_HPP