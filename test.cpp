/*
 * File:    main.cpp
 * Author:  Spiros
 *
 * Created on May 27, 2018, 7:28 PM
 */

#include <iostream>
#include <fstream>
#include <ctime>
#include <AvlTree.hpp>
#include <BinarySearchTree.hpp>
#include <RedBlackTree.hpp>
#include <SkipList.hpp>
#include <SplayTree.hpp>
#include <ScapeGoatTree.hpp>
#include <VanEmdeBoasTree.hpp>

using namespace std;

vector<int> readDate() {
    ifstream inFile;
    vector<int> inputNumbers(7481964);

    inFile.open("numbers.txt");
    if (inFile) {
        for (int i = 0; i < 7481965; i++) {
            inFile >> inputNumbers[i];
        }
    } else {
        cerr << "Error accessing the file numbers.txt\n";
    }
    return inputNumbers;
}

int main(int argc, char *argv[]) {
    vector<int> inputNumbers = readDate();
    RedBlackTree tree;

    clock_t start = clock();
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";
    for (int i = 0; i < 7481965; i++) {
        tree.insertElement(inputNumbers[i]);
    }
    cout << "Insert-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";

    start = clock();
    for (int i = 0; i < 1000000; i++) {
        //  cout << tree.containsElement(3740982) << "\n";
        tree.containsElement(3740982);
        tree.containsElement(198765);
        tree.containsElement(765);
    }
    cout << "Contains-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";

    start = clock();
    for (int i = 0; i < 1000000; i++) {
        //  cout << "MinValue = " << tree.getMinElement() << "\n";
        tree.getMinElement();
    }
    cout << "MinValue-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";

    start = clock();
    for (int i = 0; i < 1000000; i++) {
        //  cout << "MaxValue = " << tree.getMaxElement() << "\n";
        tree.getMaxElement();
    }
    cout << "MaxValue-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";

    start = clock();
    for (int i = 0; i < 7481965; i++) {
        //tree.removeElement(inputNumbers[i]);
    }
    cout << "Delete-Duration: " << ((clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";
    cout << "Tree is Empty: " << (tree.isEmpty() ? "true" : "false") << " \n";

    //tree.displayElements();
    return 0;
}