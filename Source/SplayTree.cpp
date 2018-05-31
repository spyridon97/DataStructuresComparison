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

void SplayTree::insertElement(int value) {
    root = insert(value, root);
}

void SplayTree::removeElement(int value) {
    root = remove(value, root);
}

bool SplayTree::containsElement(int value) {
    root = find(value, root);
    return root->value == value;
}

int SplayTree::getMinElement() {
    Node *minNode = findMin(root);
    if (minNode != nullptr) {
        return minNode->value;
    }
    return INT_MIN;
}

int SplayTree::getMaxElement() {
    Node *maxNode = findMax(root);
    if (maxNode != nullptr) {
        return maxNode->value;
    }
    return INT_MAX;
}

void SplayTree::displayElements() {
    inOrder(root);
}

SplayTree::Node *SplayTree::newNode(int value) {
    auto *p_node = new Node;
    p_node->value = value;
    p_node->leftChild = p_node->rightChild = nullptr;
    return p_node;
}

/* RR(Y rotates to the right):
        k2                   k1
       /  \                 /  \
      k1   Z     ==>       X   k2
     / \                      /  \
    X   Y                    Y    Z
*/
inline SplayTree::Node *SplayTree::rightRotate(Node *node) {
    Node *k1 = node->leftChild;
    node->leftChild = k1->rightChild;
    k1->rightChild = node;
    return k1;
}

/* LL(Y rotates to the left):
        k2                       k1
       /  \                     /  \
      X    k1         ==>      k2   Z
          /  \                /  \
         Y    Z              X    Y
 */
inline SplayTree::Node *SplayTree::leftRotate(Node *node) {
    Node *k1 = node->rightChild;
    node->rightChild = k1->leftChild;
    k1->leftChild = node;
    return k1;
}

/* An implementation of top-down splay tree
 If key is in the tree, then the node containing the key will be rotated to root,
 else the last non-NULL node (on the search path) will be rotated to root.
 */
SplayTree::Node *SplayTree::splay(int value, Node *root) {
    if (!root) {
        return nullptr;
    }
    Node header;
    /* header.rChild points to L tree; header.lChild points to R Tree */
    header.leftChild = header.rightChild = nullptr;
    Node *LeftTreeMax = &header;
    Node *RightTreeMin = &header;

    /* loop until root->lChild == NULL || root->rChild == NULL; then break!
       (or when find the key, break too.)
     The zig/zag mode would only happen when cannot find key and will reach
     null on one side after RR or LL Rotation.
     */
    while (true) {
        if (value < root->value) {
            if (!root->leftChild) {
                break;
            }
            if (value < root->leftChild->value) {
                root = rightRotate(root); /* only zig-zig mode need to rotate once,
										   because zig-zag mode is handled as zig
										   mode, which doesn't require rotate,
										   just linking it to R Tree */
                if (!root->leftChild) {
                    break;
                }
            }
            /* Link to R Tree */
            RightTreeMin->leftChild = root;
            RightTreeMin = RightTreeMin->leftChild;
            root = root->leftChild;
            RightTreeMin->leftChild = nullptr;
        } else if (value > root->value) {
            if (!root->rightChild) {
                break;
            }
            if (value > root->rightChild->value) {
                root = leftRotate(root);/* only zag-zag mode need to rotate once,
										  because zag-zig mode is handled as zag
										  mode, which doesn't require rotate,
										  just linking it to L Tree */
                if (!root->rightChild) {
                    break;
                }
            }
            /* Link to L Tree */
            LeftTreeMax->rightChild = root;
            LeftTreeMax = LeftTreeMax->rightChild;
            root = root->rightChild;
            LeftTreeMax->rightChild = nullptr;
        } else {
            break;
        }
    }
    /* assemble L Tree, Middle Tree and R tree together */
    LeftTreeMax->rightChild = root->leftChild;
    RightTreeMin->leftChild = root->rightChild;
    root->leftChild = header.rightChild;
    root->rightChild = header.leftChild;

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
SplayTree::Node *SplayTree::insert(int value, Node *root) {
    static Node *p_node = nullptr;
    if (!p_node) {
        p_node = newNode(value);
    } else {// could take advantage of the node remains because of there was duplicate key before.
        p_node->value = value;
    }
    if (!root) {
        root = p_node;
        p_node = nullptr;
        return root;
    }
    root = splay(value, root);
    /* This is BST that, all keys <= root->key is in root->lChild, all keys >
       root->key is in root->rChild. (This BST doesn't allow duplicate keys.) */
    if (value < root->value) {
        p_node->leftChild = root->leftChild;
        p_node->rightChild = root;
        root->leftChild = nullptr;
        root = p_node;
    } else if (value > root->value) {
        p_node->rightChild = root->rightChild;
        p_node->leftChild = root;
        root->rightChild = nullptr;
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
SplayTree::Node *SplayTree::remove(int value, Node *root) {
    Node *temp;
    if (!root) {
        return nullptr;
    }
    root = splay(value, root);
    if (value != root->value) { // No such node in splay tree
        return root;
    } else {
        if (!root->leftChild) {
            temp = root;
            root = root->rightChild;
        } else {
            temp = root;
            /*Note: Since key == root->key, so after Splay(key, root->lChild),
              the tree we get will have no right child tree. (key > any key in
              root->lChild)*/
            root = splay(value, root->leftChild);
            root->rightChild = temp->rightChild;
        }
        free(temp);
        return root;
    }
}

SplayTree::Node *SplayTree::find(int value, Node *root) {
    return splay(value, root);
}

SplayTree::Node *SplayTree::findMin(Node *node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->leftChild == nullptr) {
        return node;
    } else {
        return findMin(node->leftChild);
    }
}

SplayTree::Node *SplayTree::findMax(Node *node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->rightChild == nullptr) {
        return node;
    } else {
        return findMax(node->rightChild);
    }
}

void SplayTree::inOrder(Node *root) {
    if (root) {
        inOrder(root->leftChild);
        std::cout << root->value << "\n";
        inOrder(root->rightChild);
    }
}