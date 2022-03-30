#include <iostream>
#include <sstream>
#include "red_black_tree.h"

using std::cout;
using std::endl;

/*****************************************************
 **
 ** File:    red_black_tree_tests.cpp
 ** Project: CSCE 221 Lab 4 Spring 2022
 ** Author:  Christian Mosquera
 ** Date:    03/30/22
 ** Section: 510
 ** Email:   cwbo.1701@tamu.edu
 ** 
 ** This file contains function calls to the red black
 ** tree data structure to test all the functions associated 
 ** with it.
 **
 *****************************************************/

int main() {
    // example test case given in lab assignment
    // make an empty tree
    RedBlackTree<int> tree;

    // insert 5 values into the tree
    std::cout << "insert 6, 4, 2, 8, 10 " << std::endl;
    tree.insert(6);
    tree.insert(4);
    tree.insert(2);
    tree.insert(1);
    tree.insert(0);
    tree.insert(3);

    // print the tree
    std::cout << "tree: " << std::endl;
    {
    std::ostringstream ss;
    tree.print_tree(ss);  
    std::cout << ss.str() << std::endl;
    }

    std::cout << "contains 4? " << std::boolalpha <<tree.contains(4) << std::endl;
    std::cout << "contains 7? " << std::boolalpha << tree.contains(7) << std::endl;

    // remove the root
    std::cout << "remove 4" << std::endl;
    tree.remove(4);

    tree.print_tree();

    // find the minimum element
    std::cout << "min: " << tree.find_min() << std::endl;

    // find the maximum element
    std::cout << "max: " << tree.find_max() << std::endl;

    // print the tree
    std::cout << "tree: " << std::endl;
    {
    std::ostringstream ss;
    tree.print_tree(ss);
    std::cout << ss.str() <<
    std::endl;
    }

    return 0;
}
