/*
 * File:    AvlTree.cpp
 * Author:  Spiros
 *
 * Created on May 27, 2018, 7:28 PM
 */

#include <AvlTree.hpp>
#include <iostream>

AvlTree::AvlTree() {
    root = nullptr;
}

AvlTree::~AvlTree() {
    delete root;
}

void AvlTree::insertElement(int value) {
    root = insert(root, value);
}

void AvlTree::removeElement(int value) {
    root = remove(root, value);
}

bool AvlTree::containsElement(int value) {
    return containsElement(value, root) != nullptr;
}

int AvlTree::getMinElement() {
    Node *minNode = findMin(root);
    if (minNode != nullptr) {
        return minNode->value;
    }
    return INT_MIN;
}

int AvlTree::getMaxElement() {
    Node *maxNode = findMax(root);
    if (maxNode != nullptr) {
        return maxNode->value;
    }
    return INT_MAX;
}

void AvlTree::displayElements() {
    inOrder(root);
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
AvlTree::Node *AvlTree::newNode(int key) {
    auto *node = new Node;
    node->value = key;
    node->leftChild = nullptr;
    node->rightChild = nullptr;
    node->height = 1;  // new node is initially added at leaf
    return node;
}

AvlTree::Node *AvlTree::rightRotate(Node *node) {
    Node *x = node->leftChild;
    Node *T2 = x->rightChild;

    // Perform rotation
    x->rightChild = node;
    node->leftChild = T2;

    // Update heights
    node->height = __max(height(node->leftChild), height(node->rightChild)) + 1;
    x->height = __max(height(x->leftChild), height(x->rightChild)) + 1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
AvlTree::Node *AvlTree::leftRotate(Node *node) {
    Node *y = node->rightChild;
    Node *T2 = y->leftChild;

    // Perform rotation
    y->leftChild = node;
    node->rightChild = T2;

    //  Update heights
    node->height = __max(height(node->leftChild), height(node->rightChild)) + 1;
    y->height = __max(height(y->leftChild), height(y->rightChild)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int AvlTree::getBalance(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->leftChild) - height(node->rightChild);
}

AvlTree::Node *AvlTree::containsElement(int value, Node *node) {
    if (node == nullptr) { // Element not found
        return nullptr;
    } else if (value < node->value) { // Searching for element
        return containsElement(value, node->leftChild);
    } else if (value > node->value) {
        return containsElement(value, node->rightChild);
    } else { // Element found
        return node;
    }
}

AvlTree::Node *AvlTree::findMin(Node *node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->leftChild == nullptr) {
        return node;
    } else {
        return findMin(node->leftChild);
    }
}

AvlTree::Node *AvlTree::findMax(Node *node) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->rightChild == nullptr) {
        return node;
    } else {
        return findMax(node->rightChild);
    }
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
AvlTree::Node *AvlTree::insert(Node *node, int value) {
    /* 1.  Perform the normal BST insertion */
    if (node == nullptr) {
        return (newNode(value));
    }

    if (value < node->value) {
        node->leftChild = insert(node->leftChild, value);
    } else if (value > node->value) {
        node->rightChild = insert(node->rightChild, value);
    } else {// Equal values are not allowed in BST
        return node;
    }

    /* 2. Update height of this ancestor node */
    node->height = 1 + __max(height(node->leftChild), height(node->rightChild));

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && value < node->leftChild->value) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && value > node->rightChild->value) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && value > node->leftChild->value) {
        node->leftChild = leftRotate(node->leftChild);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && value < node->rightChild->value) {
        node->rightChild = rightRotate(node->rightChild);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
AvlTree::Node *AvlTree::remove(Node *root, int value) {
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == nullptr) {
        return root;
    }

    // If the value to be deleted is smaller than the
    // root's value, then it lies in leftChild subtree
    if (value < root->value) {
        root->leftChild = remove(root->leftChild, value);
    }

        // If the value to be deleted is greater than the
        // root's value, then it lies in rightChild subtree
    else if (value > root->value) {
        root->rightChild = remove(root->rightChild, value);
    }

        // if value is same as root's value, then This is
        // the node to be deleted
    else {

        // node with only one child or no child
        if ((root->leftChild == nullptr) || (root->rightChild == nullptr)) {
            Node *temp = root->leftChild ? root->leftChild : root->rightChild;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else // One child case
                *root = *temp; // Copy the contents of
            // the non-empty child
            delete temp;
        } else {
            // node with two children: Get the inorder
            // successor (smallest in the rightChild subtree)
            Node *temp = findMin(root->rightChild);

            // Copy the inOrder successor's data to this node
            root->value = temp->value;

            // Delete the inOrder successor
            root->rightChild = remove(root->rightChild, temp->value);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr) {
        return root;
    }

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + __max(height(root->leftChild), height(root->rightChild));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // leftChild leftChild Case
    if (balance > 1 && getBalance(root->leftChild) >= 0) {
        return rightRotate(root);
    }

    // leftChild rightChild Case
    if (balance > 1 && getBalance(root->leftChild) < 0) {
        root->leftChild = leftRotate(root->leftChild);
        return rightRotate(root);
    }

    // rightChild rightChild Case
    if (balance < -1 && getBalance(root->rightChild) <= 0) {
        return leftRotate(root);
    }

    // rightChild leftChild Case
    if (balance < -1 && getBalance(root->rightChild) > 0) {
        root->rightChild = rightRotate(root->rightChild);
        return leftRotate(root);
    }

    return root;
}

int AvlTree::height(Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

void AvlTree::inOrder(AvlTree::Node *node) {
    if (node != nullptr) {
        inOrder(node->leftChild);
        std::cout << node->value << "\n";
        inOrder(node->rightChild);
    }
}