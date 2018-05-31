/*
 * File:    SkipList.hpp
 * Author:  Spiros
 *
 * Created on May 29, 2018, 4:13 PM
 */

#ifndef COMPARISONOFTREEIMPLEMENTATIONS_SKIPLIST_HPP
#define COMPARISONOFTREEIMPLEMENTATIONS_SKIPLIST_HPP

#include <vector>
#include <limits>

class SkipList {
public:
    SkipList();

    ~SkipList();

    bool insertElement(int value);

    bool removeElement(int value);

    bool containsElement(int value);

    int getMinElement();

    int getMaxElement();

    void displayElements();

private:
    struct Element {
        Element(int k, int new_height) : value(k), next((unsigned long long) new_height + 1) {}

        int value;
        std::vector<Element *> next;
    };

    const int MAX_HEIGHT = 16;

    const int INF = std::numeric_limits<int>::max();

    Element head;

    Element tail;

    int height;

    int randomHeight();
};

#endif // COMPARISONOFTREEIMPLEMENTATIONS_SKIPLIST_HPP