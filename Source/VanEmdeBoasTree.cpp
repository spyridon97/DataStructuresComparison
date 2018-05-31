/*
 * File:    VanEmdeBoasTree
 * Author:  Spiros
 *
 * Created on May 31, 2018, 7:38 PM
 */

#include "VanEmdeBoasTree.hpp"

VanEmdeBoasTree::VanEmdeBoasTree() {
    root = new Node((int) pow(2, 30));
}

VanEmdeBoasTree::~VanEmdeBoasTree() {
    delete root;
}

bool VanEmdeBoasTree::insertElement(int value) {
    return insert(root, value);
}

bool VanEmdeBoasTree::removeElement(int value) {
    return remove(root, value);

}

bool VanEmdeBoasTree::containsElement(int value) {
    return find(root, value);
}

int VanEmdeBoasTree::getMinElement() {
    int min;
    bool found = findMin(root, min);
    if (found) {
        return min;
    } else {
        return INT_MIN;
    }
}

int VanEmdeBoasTree::getMaxElement() {
    int max;
    bool found = findMax(root, max);
    if (found) {
        return max;
    } else {
        return INT_MAX;
    }
}

bool VanEmdeBoasTree::isEmpty() {
    return root->min == INT_MIN;
}

void VanEmdeBoasTree::displayElements() {
    inOrder(root);
}

VanEmdeBoasTree::Node::Node(int uniSize) : uni(powTwoRoundUp(uniSize)), uniSqrt(static_cast<const int>(sqrt(uni))),
                                           lowerUniSqrt(static_cast<const int>(lowerSqrt(uni))),
                                           higherUniSqrt(static_cast<const int>(higherSqrt(uni))),
                                           min(INT_MIN), max(INT_MIN), summary(nullptr) {
    if (uniSize <= 0) {
        std::cerr << "universe size of TvEB must be bigger than 0" << std::endl;
        return;
    }

    if (uni > 2) {
        cluster = new Node *[higherUniSqrt];
        for (int i = 0; i < higherUniSqrt; ++i) {
            cluster[i] = nullptr;
        }
    } else {
        cluster = nullptr;
    }
}

VanEmdeBoasTree::Node::~Node() {
    delete summary;
    if (cluster) {
        for (int i = 0; i < higherUniSqrt; ++i) {
            if (cluster[i]) {
                delete cluster[i];
            }
        }
        delete[] cluster;
    }
}

int VanEmdeBoasTree::powTwoRoundUp(int value) {
    if (value < 0) return 0;
    --value;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return value + 1;
}

float VanEmdeBoasTree::higherSqrt(int value) {
    return static_cast<float>(pow(2, ceil(log2(value) / 2)));
}

float VanEmdeBoasTree::lowerSqrt(int value) {
    return static_cast<float>(pow(2, floor(log2(value) / 2)));
}

int VanEmdeBoasTree::low(Node *root, int value) {
    return value % (int) lowerSqrt(root->uni);
}

int VanEmdeBoasTree::high(Node *root, int value) {
    return static_cast<int>(value / lowerSqrt(root->uni));
}

int VanEmdeBoasTree::index(Node *root, int high, int low) {
    return static_cast<int>(high * lowerSqrt(root->uni) + low);
}

bool VanEmdeBoasTree::findMin(Node *root, int &result) {
    if (root) {
        result = root->min;
        return true;
    }
    return false;
}

bool VanEmdeBoasTree::findMax(Node *root, int &result) {
    if (root) {
        result = root->max;
        return true;
    }
    return false;
}

bool VanEmdeBoasTree::insert(Node *&root, int value, int parentUniSqrt) {
    if (!root) {
        root = new Node(parentUniSqrt);
    }
    if (value < 0 || value >= root->uni) {
        return false;
    }
    if (root->min == value || root->max == value) {
        return false;
    }
    if (root->min == INT_MIN) {
        root->min = root->max = value;
        return true;
    }
    if (value < root->min) {
        int tmp = value;
        value = root->min;
        root->min = tmp;
    }
    if (value > root->max) {
        root->max = value;
    }
    if (root->uni > 2) {
        int lowVal = low(root, value);
        int highVal = high(root, value);
        if (!root->cluster[highVal]) {
            if (!insert(root->summary, highVal, root->higherUniSqrt)) {
                return false;
            }
        }
        if (!insert(root->cluster[highVal], lowVal, root->lowerUniSqrt)) {
            return false;
        }
    }
    return true;
}

bool VanEmdeBoasTree::remove(Node *&root, int value) {
    if (!root) {
        return false;
    }

    if (value < 0 || value >= root->uni) {
        return false;
    }
    if (root->min > value || root->max < value) {
        return false;
    }

    if (root->min == value) {
        int i;
        if (!findMin(root->summary, i) || i == INT_MIN) {
            if (root->min != root->max) {
                root->min = root->max;
                return true;
            }

            root->min = root->max = INT_MIN;
            delete root;
            root = nullptr;
            return true;
        }
        value = root->min = index(root, i, root->cluster[i]->min);
    }

    if (root->uni > 2) {
        int highVal = high(root, value);
        if (!remove(root->cluster[highVal], low(root, value))) {
            return false;
        }

        int tmp;
        if (!findMin(root->cluster[highVal], tmp) || tmp == INT_MIN) {
            if (!remove(root->summary, highVal)) {
                return false;
            }
        }
    }

    if (root->max == value) {
        int tmp;
        if (!findMax(root->summary, tmp) || tmp == INT_MIN) {
            root->max = root->min;
        } else {
            int i;
            if (!findMax(root->summary, i)) {
                return false;
            }
            root->max = index(root, i, root->cluster[i]->max);
        }
    }
    return true;
}

bool VanEmdeBoasTree::find(Node *root, int value) {
    if (!root) {
        return false;
    }

    if (value < 0 || value >= root->uni) {
        return false;
    }
    if (root->min > value || root->max < value) {
        return false;
    }
    if (root->min == value) {
        return true;
    }
    if (!root->summary) {
        return root->max == value;
    }
    return find(root->cluster[high(root, value)], low(root, value));
}

bool VanEmdeBoasTree::successor(Node *root, int value, int &result) {
    if (!root) {
        return false;
    }

    if (value < -1 || value >= root->uni) {
        return false;
    }

    if (root->min > value) {
        result = root->min;
        return true;
    }

    if (!root->summary) {
        if (root->max > value) {
            result = root->max;
            return true;
        }
        return false;
    }

    int lowVal = low(root, value);
    int highVal = high(root, value);
    int i = highVal;
    int j = INT_MIN;
    int tmp;
    if (findMax(root->cluster[i], tmp) && lowVal < tmp) {
        if (!successor(root->cluster[i], lowVal, j)) {
            return false;
        }
    } else {
        if (!successor(root->summary, highVal, i)) {
            if (root->max > value) {
                result = root->max;
                return true;
            }
            return false;
        }
        if (!findMin(root->cluster[i], j)) {
            return false;
        }
    }

    result = index(root, i, j);
    return true;
}

bool VanEmdeBoasTree::predecessor(Node *root, int value, int &result) {
    if (!root) {
        return false;
    }

    if (value < 0 || value > root->uni) {
        return false;
    }

    if (root->max < value) {
        result = root->max;
        return true;
    }

    if (!root->summary) {
        if (root->min < value) {
            result = root->min;
            return true;
        }
        return false;
    }

    int lowVal = low(root, value);
    int highVal = high(root, value);
    int i = highVal;
    int j = INT_MIN;
    int tmp;
    if (findMin(root->cluster[i], tmp) && lowVal > tmp) {
        if (!predecessor(root->cluster[i], lowVal, j)) {
            return false;
        }
    } else {
        if (!predecessor(root->summary, highVal, i)) {
            if (root->min < value) {
                result = root->min;
                return true;
            }
            return false;
        }
        if (!findMax(root->cluster[i], j)) return false;
    }

    result = index(root, i, j);
    return true;
}

//  needs to be implemented
void VanEmdeBoasTree::inOrder(Node *root) {
    if (!root) {
        return;
    }
    /*std::cout << "tree: " << root << std::endl;
    std::cout << "min: " << root->min << ", max: " << root->max << std::endl;
    std::cout << "uni: " << root->uni << ", uniSqrt: " << root->uniSqrt << std::endl;
    std::cout << "lowerUniSqrt: " << root->lowerUniSqrt;
    std::cout << ", higherUniSqrt: " << root->higherUniSqrt << std::endl;
    std::cout << "summary: " << root->summary << std::endl;
    if (root->uni > 2) {
        for (int i = 0; i < root->higherUniSqrt; ++i) {
            std::cout << "cluster " << i << ": " << root->cluster[i] << std::endl;
        }
    } else {
        std::cout << "cluster " << root->cluster << std::endl;
    }*/
}