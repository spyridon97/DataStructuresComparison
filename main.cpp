/*
 * File:    main.cpp
 * Author:  Spiros
 *
 * Created on May 27, 2018, 7:28 PM
 */

#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <AvlTree.hpp>
#include <BinarySearchTree.hpp>
#include <RedBlackTree.hpp>
#include <SkipList.hpp>
#include <SplayTree.hpp>
#include <ScapeGoatTree.hpp>
#include <VanEmdeBoasTree.hpp>

using namespace std;

vector<int> getRandomNumbersForFind(int inputSize) {
    srand(unsigned(time(nullptr)));
    vector<int> randomNumbersForInput;

    int number = 1;
    for (int i = 0; i < inputSize; i++) {
        randomNumbersForInput.push_back(number);

        if (number == inputSize - 1) {
            number *= 2;
        } else if (number != inputSize) {
            number = 1;
        } else if (number == inputSize) {
            number = inputSize - 1;
        }
    }
    return randomNumbersForInput;
}

vector<int> getRandomNumbers(int inputSize) {
    srand(unsigned(time(nullptr)));
    vector<int> randomNumbers;

    for (int i = 0; i < inputSize; i++) {
        randomNumbers.push_back(i);
    }
    std::shuffle(randomNumbers.begin(), randomNumbers.end(), std::mt19937(std::random_device()()));
    return randomNumbers;
}

vector<int> getAscendingNumbers(int inputSize) {
    vector<int> ascendingNumbers;

    for (int i = 0; i < inputSize; i++) {
        ascendingNumbers.push_back(i);
    }
    return ascendingNumbers;
}

vector<int> getDescendingNumbers(int inputSize) {
    vector<int> descendingNumbers;

    for (int i = inputSize - 1; i >= 0; i--) {
        descendingNumbers.push_back(i);
    }
    return descendingNumbers;
}

int main(int argc, char *argv[]) {
    auto inputSize = (int) pow(2, 24);

    //  vector<int> randomNumbers = getRandomNumbers(inputSize);
    //  vector<int> ascendingNumbers = getAscendingNumbers(inputSize);
    vector<int> descendingNumbers = getDescendingNumbers(inputSize);

    //  vector<int> randomNumbersForFind = getRandomNumbersForFind(inputSize);

    //  use the tree that you want
    RedBlackTree tree;

    /*//  random insertion Test
    clock_t start = clock();
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";
    for (int number: randomNumbers) {
        tree.insertElement(number);
    }
    cout << "Random-Insert-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";*/

    /*//  ascending insertion Test
    clock_t start = clock();
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";
    for (int number: ascendingNumbers) {
        tree.insertElement(number);
    }
    cout << "Ascending-Insert-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";*/

    //  descending insertion Test
    clock_t start = clock();
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";
    for (int number: descendingNumbers) {
        tree.insertElement(number);
    }
    cout << "Descending-Insert-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";

    /*//  contains Test with random non repetitive numbers
    start = clock();
    for (int number: randomNumbers) {
        //  cout << tree.containsElement(number) << "\n";
        tree.containsElement(number);
    }
    cout << "Non Repetitive-Random-Contains-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000
         << " millisecond\n";

    //  contains Test with random repetitive numbers
    start = clock();
    for (int number: randomNumbersForFind) {
        //  cout << tree.containsElement(number) << "\n";
        tree.containsElement(number);
    }
    cout << "Repetitive-Random-Contains-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";

    //  getMin Test
    start = clock();
    for (int i = 0; i < 1000000; i++) {
        //  cout << "MinValue = " << tree.getMinElement() << "\n";
        tree.getMinElement();
    }
    cout << "MinValue-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";

    //  getMax Test
    start = clock();
    for (int i = 0; i < 1000000; i++) {
        //  cout << "MaxValue = " << tree.getMaxElement() << "\n";
        tree.getMaxElement();
    }
    cout << "MaxValue-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";*/

    /*//  random removal Test
    start = clock();
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";
    for (int number: randomNumbers) {
        tree.removeElement(number);
    }
    cout << "Random-removal-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";*/

    /*//  ascending removal Test
    start = clock();
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";
    for (int number: ascendingNumbers) {
        tree.removeElement(number);
    }
    cout << "Ascending-removal-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";*/

    //  descending removal Test
    start = clock();
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";
    for (int number: descendingNumbers) {
        tree.removeElement(number);
    }
    cout << "Descending-removal-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";

    //tree.displayElements();
    return 0;
}