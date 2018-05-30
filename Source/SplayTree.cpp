/*
 * File:    SplayTree.cpp
 * Author:  Spiros
 *
 * Created on May 30, 2018, 2:59 PM
 */

#include <SplayTree.hpp>
#include <iostream>

SplayTree::SplayTree() {
    root = nullptr;
}

SplayTree::~SplayTree() {
    root = nullptr;
}

void SplayTree::insertElement(int x) {
    root = insert(x, root);
}

void SplayTree::removeElement(int x) {
    root = remove(x, root);
}

bool SplayTree::containsElement(int x) {
    root = search(x, root);
    return root->key == x;
}

void SplayTree::displayElements() {
    inOrder(root);
}

SplayTree::Node *SplayTree::newNode(int key) {
    auto *p_node = new Node;
    p_node->key = key;
    p_node->lChild = p_node->rChild = nullptr;
    return p_node;
}

/* RR(Y rotates to the right):
        k2                   k1
       /  \                 /  \
      k1   Z     ==>       X   k2
     / \                      /  \
    X   Y                    Y    Z
*/
inline SplayTree::Node *SplayTree::rrRotate(Node *k2) {
    Node *k1 = k2->lChild;
    k2->lChild = k1->rChild;
    k1->rChild = k2;
    return k1;
}

/* LL(Y rotates to the left):
        k2                       k1
       /  \                     /  \
      X    k1         ==>      k2   Z
          /  \                /  \
         Y    Z              X    Y
 */
inline SplayTree::Node *SplayTree::llRotate(Node *k2) {
    Node *k1 = k2->rChild;
    k2->rChild = k1->lChild;
    k1->lChild = k2;
    return k1;
}

/* An implementation of top-down splay tree
 If key is in the tree, then the node containing the key will be rotated to root,
 else the last non-NULL node (on the search path) will be rotated to root.
 */
SplayTree::Node *SplayTree::splay(int key, Node *root) {
    if (!root) {
        return nullptr;
    }
    Node header;
    /* header.rChild points to L tree; header.lChild points to R Tree */
    header.lChild = header.rChild= nullptr;
    Node *LeftTreeMax = &header;
    Node *RightTreeMin = &header;

    /* loop until root->lChild == NULL || root->rChild == NULL; then break!
       (or when find the key, break too.)
     The zig/zag mode would only happen when cannot find key and will reach
     null on one side after RR or LL Rotation.
     */
    while (true) {
        if (key < root->key) {
            if (!root->lChild) {
                break;
            }
            if (key < root->lChild->key) {
                root = rrRotate(root); /* only zig-zig mode need to rotate once,
										   because zig-zag mode is handled as zig
										   mode, which doesn't require rotate,
										   just linking it to R Tree */
                if (!root->lChild) {
                    break;
                }
            }
            /* Link to R Tree */
            RightTreeMin->lChild = root;
            RightTreeMin = RightTreeMin->lChild;
            root = root->lChild;
            RightTreeMin->lChild = nullptr;
        } else if (key > root->key) {
            if (!root->rChild) {
                break;
            }
            if (key > root->rChild->key) {
                root = llRotate(root);/* only zag-zag mode need to rotate once,
										  because zag-zig mode is handled as zag
										  mode, which doesn't require rotate,
										  just linking it to L Tree */
                if (!root->rChild) {
                    break;
                }
            }
            /* Link to L Tree */
            LeftTreeMax->rChild = root;
            LeftTreeMax = LeftTreeMax->rChild;
            root = root->rChild;
            LeftTreeMax->rChild = nullptr;
        } else {
            break;
        }
    }
    /* assemble L Tree, Middle Tree and R tree together */
    LeftTreeMax->rChild = root->lChild;
    RightTreeMin->lChild = root->rChild;
    root->lChild = header.rChild;
    root->rChild = header.lChild;

    return root;
}

/* Implementation 1:
   First Splay(key, root)(and assume the tree we get is called *), so root node and
   its left child tree will contain nodes with keys <= key, so we could rebuild
   the tree, using the newly allocated node as a root, the children of original tree
   *(including root node of *) as this new node's children.
NOTE: This implementation is much better! Reasons are as follows in implementation 2.
NOTE: This implementation of splay tree doesn't allow nodes of duplicate keys!
 */
SplayTree::Node *SplayTree::insert(int key, Node *root) {
    static Node *p_node = nullptr;
    if (!p_node) {
        p_node = newNode(key);
    } else {// could take advantage of the node remains because of there was duplicate key before.
        p_node->key = key;
    }
    if (!root) {
        root = p_node;
        p_node = nullptr;
        return root;
    }
    root = splay(key, root);
    /* This is BST that, all keys <= root->key is in root->lChild, all keys >
       root->key is in root->rChild. (This BST doesn't allow duplicate keys.) */
    if (key < root->key) {
        p_node->lChild = root->lChild;
        p_node->rChild = root;
        root->lChild = nullptr;
        root = p_node;
    } else if (key > root->key) {
        p_node->rChild = root->rChild;
        p_node->lChild = root;
        root->rChild = nullptr;
        root = p_node;
    } else {
        return root;
    }
    p_node = nullptr;
    return root;
}

/*
Implementation: just Splay(key, root), if key doesn't exist in the tree(key !=
root->key), return root directly; else join the root->lChild and root->rChild
and then free(old_root).
To join T1 and T2 (where all elements in T1 < any element in T2) is easy if we
have the largest element in T1 as T1's root, and here's a trick to simplify code,
see "Note" below.
 */
SplayTree::Node *SplayTree::remove(int key, Node *root) {
    Node *temp;
    if (!root) {
        return nullptr;
    }
    root = splay(key, root);
    if (key != root->key) { // No such node in splay tree
        return root;
    } else {
        if (!root->lChild) {
            temp = root;
            root = root->rChild;
        } else {
            temp = root;
            /*Note: Since key == root->key, so after Splay(key, root->lChild),
              the tree we get will have no right child tree. (key > any key in
              root->lChild)*/
            root = splay(key, root->lChild);
            root->rChild = temp->rChild;
        }
        free(temp);
        return root;
    }
}

SplayTree::Node *SplayTree::search(int key, Node *root) {
    return splay(key, root);
}

void SplayTree::inOrder(Node *root) {
    if (root) {
        inOrder(root->lChild);
        std::cout << root->key << "\n";
        inOrder(root->rChild);
    }
}