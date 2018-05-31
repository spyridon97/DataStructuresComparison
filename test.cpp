/*
 * File:    main.cpp
 * Author:  Spiros
 *
 * Created on May 27, 2018, 7:28 PM
 */

#include <iostream>
#include <fstream>
#include <ctime>
#include <A2B4Tree.hpp>
#include <AvlTree.hpp>
#include <BinarySearchTree.hpp>
#include <RedBlackTree.hpp>
#include <SkipList.hpp>
#include <SplayTree.hpp>
#include <ScapeGoatTree.hpp>
#include <VanEmdeBoasTree.hpp>

std::vector<int> readDate() {
    std::ifstream inFile;
    std::vector<int> inputNumbers(7481964);

    inFile.open("numbers.txt");
    if (inFile) {
        for (int i = 0; i < 7481965; i++) {
            inFile >> inputNumbers[i];
        }
    } else {
        std::cerr << "Error accessing the file numbers.txt\n";
    }
    return inputNumbers;
}

int main(int argc, char *argv[]) {
    std::vector<int> inputNumbers = readDate();

    RedBlackTree tree;

    std::clock_t start = std::clock();
    std::cout << "Tree is : " << tree.isEmpty() << " \n";
    for (int i = 0; i < 7481965; i++) {
        tree.insertElement(inputNumbers[i]);
    }
    std::cout << "Insert-Duration: " << ((std::clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";
    std::cout << "Tree is : " << tree.isEmpty() << " \n";

    start = std::clock();
    for (int i = 0; i < 7481965; i++) {
        tree.removeElement(inputNumbers[i]);
    }
    std::cout << "Delete-Duration: " << ((std::clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";
    std::cout << "Tree is : " << tree.isEmpty() << " \n";

    start = std::clock();
    std::cout << tree.containsElement(3740982) << "\n";
    std::cout << "Contains-Duration: " << ((std::clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";

    start = std::clock();
    std::cout << "MinValue = " << tree.getMinElement() << "\n";
    std::cout << "MinValue-Duration: " << ((std::clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";

    start = std::clock();
    std::cout << "MaxValue = " << tree.getMaxElement() << "\n";
    std::cout << "MaxValue-Duration: " << ((std::clock() - start) / (double) CLOCKS_PER_SEC) * 1000 << " millisecond\n";

    //tree.displayElements();
    return 0;
}