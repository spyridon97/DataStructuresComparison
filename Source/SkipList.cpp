/*
 * File:    SkipList.hpp
 * Author:  Spiros
 *
 * Created on May 29, 2018, 4:13 PM
 */

#include <SkipList.hpp>
#include <iostream>
#include <iomanip>
#include <experimental/random>

// initialise empty list with head Element's next pointing to tail Element
// on all list levels
SkipList::SkipList() : head(0, max_height), tail(INF, 0), height(0) {
    for (auto &i : head.next) {
        i = &tail;
    }
}

SkipList::~SkipList() = default;

// inserts Element with key x into list
void SkipList::insertElement(int x) {
    std::vector<Element *> update((unsigned long long) (max_height + 1));
    Element *p = &head;

    for (int i = height; i >= 0; --i) {
        while (p->next[i]->key < x) {
            p = p->next[i];
        }
        update[i] = p;
    }
    p = p->next[0];

    if (p->key == x) return;    // key x exists already in list

    int new_height = random_height();
    if (new_height > height) {  // link new Element to head, adjust list height
        for (int i = height + 1; i <= new_height; ++i) {
            update[i] = &head;
        }
        height = new_height;
    }

    // create new Element with height new_height and key x
    p = new Element(x, new_height);

    // insert p into level i lists immediately after Element update[i]
    for (int i = 0; i <= new_height; ++i) {
        p->next[i] = update[i]->next[i];
        update[i]->next[i] = p;
    }
}

// removes Element with key x from list
void SkipList::removeElement(int x) {
    std::vector<Element *> update((unsigned long long) (max_height + 1));
    Element *p = &head;
    for (int i = height; i >= 0; --i) {
        while (p->next[i]->key < x)
            p = p->next[i];
        update[i] = p;
    }
    p = p->next[0];

    // if found, remove and potentially reduce list height
    if (p->key == x) {
        for (unsigned int i = 0; i < p->next.size(); ++i) {
            // remove p from level i list
            update[i]->next[i] = p->next[i];
        }
        while (height >= 1 && head.next[height]->key == INF) {
            --height;
        }
        delete p;
    }
}

// returns pointer to Element with key x if x exists in list, 0 otherwise
bool SkipList::containsElement(int x) {
    Element *p = &head;
    for (int i = height; i >= 0; --i) {
        while (p->next[i]->key < x) {
            p = p->next[i];
        }
    }

    // now either p == &head and x <= p->next[0]->key
    // or p != &head and p->key < x <= p->next[0]->key
    p = p->next[0];
    return p->key == x;  // x is at position p in list or in list
}

void SkipList::displayElements() {
    Element *p = head.next[0];
    while (p->key != INF) {
        std::cout << std::setw(2) << p->key << "\n";
        p = p->next[0];
    }
}

int SkipList::random_height() {
    int rand_height = 0;
    std::srand(10000);
    while (std::experimental::randint(0, 10000) < 5000 && rand_height < max_height) {
        ++rand_height;
    }
    return rand_height;
}