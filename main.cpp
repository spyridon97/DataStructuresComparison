/*
 * File:    main.cpp
 * Author:  Spiros
 *
 * Created on May 27, 2018, 7:28 PM
 */

#include <iostream>
#include <A2B4Tree.hpp>
#include <AvlTree.hpp>
#include <BinarySearchTree.hpp>
#include <RedBlackTree.hpp>
#include <SkipList.hpp>
#include <SplayTree.hpp>
#include <ScapeGoatTree.hpp>

int main() {

    AvlTree tree;
    //*
    tree.insertElement(25);
    tree.insertElement(15);
    tree.insertElement(10);
    tree.insertElement(30);
    tree.insertElement(5);
    tree.insertElement(35);
    tree.insertElement(67);
    tree.insertElement(43);
    tree.insertElement(21);
    tree.insertElement(21);
    tree.insertElement(10);
    tree.insertElement(89);
    tree.insertElement(38);
    tree.insertElement(69);
    tree.insertElement(69);
    tree.insertElement(189);
    std::cout << "Contains the Element: " << tree.containsElement(65) << " \n";
    tree.displayElements();
    //*
    std::cout << "Rest " << "\n";
    tree.displayElements();
    //*
    std::cout << "Contains the Element: " << tree.containsElement(35) << " \n";
    tree.removeElement(35);
    std::cout << "Contains the Element: " << tree.containsElement(65) << " \n";
    tree.removeElement(65);
    std::cout << "Contains the Element: " << tree.containsElement(89) << " \n";
    tree.removeElement(89);
    std::cout << "Contains the Element: " << tree.containsElement(43) << " \n";
    tree.removeElement(43);
    std::cout << "Contains the Element: " << tree.containsElement(88) << " \n";
    tree.removeElement(88);
    std::cout << "Contains the Element: " << tree.containsElement(20) << " \n";
    tree.removeElement(20);
    std::cout << "Contains the Element: " << tree.containsElement(38) << " \n";
    tree.removeElement(38);
    tree.displayElements();
    //*/

    std::cout<<"MinValue = " << tree.getMinElement() <<"\n";
    std::cout<<"MinValue = " << tree.getMaxElement() <<"\n";

    return 0;
}