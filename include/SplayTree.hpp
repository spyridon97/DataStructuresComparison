/*
 * File:    SplayTree
 * Author:  Spiros
 *
 * Created on May 30, 2018, 2:59 PM
 */

#ifndef TREECOMPARISON_SPLAYTREE_HPP
#define TREECOMPARISON_SPLAYTREE_HPP


typedef int KEY_TYPE;

class SplayTree {
private:
    typedef struct Node {
        int key;
        struct Node *lChild;
        struct Node *rChild;
    } Node;

    Node *root;

    Node *newNode(int key);

    inline Node *rrRotate(Node *k2);

    inline Node *llRotate(Node *k2);

    Node *splay(int key, Node *root);

    Node *insert(int key, Node *root);

    Node *remove(int key, Node *root);

    Node *search(int key, Node *root);

    void inOrder(Node *root);

public:
    SplayTree();

    ~SplayTree();

    void insertElement(int x);

    void removeElement(int x);

    bool containsElement(int x);

    void displayElements();

};


#endif // TREECOMPARISON_SPLAYTREE_HPP