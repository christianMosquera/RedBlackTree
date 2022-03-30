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




    // Test 2: test insert negatives and positives
    // and test printing the tree

    cout << "TESTING REDBLACKTREE 3" << endl;
    RedBlackTree<int> tree2;
    cout << "Inserting elements into tree2:" << endl;
    // inserting
    tree2.insert(1);
    tree2.insert(5);
    tree2.insert(-1);
    tree2.insert(-5);
    tree2.insert(0);
    tree2.insert(20);

    // printing   
    tree2.print_tree();
    cout << endl;




    // Test 3: test copy constructor and copy assignment

    cout << "TEST REDBLACKTREE 3" << endl;

    // construct tree3
    RedBlackTree<int> tree3(tree2);
    tree3.insert(100);

    // construct tree4
    RedBlackTree<int> tree4;
    tree4.insert(1);
    tree4 = tree4;
    tree4 = tree3;
    tree4.insert(50);
    tree2.make_empty();
    tree4 = tree2;
    tree4.insert(100);

    cout << "Print tree3:" << endl;
    tree3.print_tree();
    cout << endl;

    cout << "Print tree4:" << endl;
    tree4.print_tree();
    cout << "Is empty: " << tree4.is_empty() << endl;
    cout << endl;


    // Test 4: print empty tree

    cout << "TEST REDBLACKTREE 4" << endl;

    RedBlackTree<int> tree5;

    tree5.print_tree();

    try {
        cout << "Min of tree5: " << tree5.find_min() << endl;
    }
    catch(std::invalid_argument& e) {
        cout << e.what() << endl;
    }

    try {
        cout << "Max of tree5: " << tree5.find_max() << endl;
    }
    catch(std::invalid_argument& e) {
        cout << e.what() << endl;
    }

    cout << "Is empty: " << tree5.is_empty() << endl;

    cout << endl;


    // Test 5: all possible rotations
    cout << "TEST REDBLACKTREE 5" << endl;

    RedBlackTree<int> tree6;

    tree6.insert(0);
    tree6.insert(5);
    tree6.insert(4);
    tree6.insert(-3);
    tree6.insert(-129);
    tree6.insert(-23);
    tree6.insert(51);
    tree6.insert(45);
    tree6.insert(-389);
    tree6.insert(-12);
    tree6.insert(100);
    tree6.insert(59);
    tree6.insert(12);
    tree6.insert(-10);
    tree6.insert(-1);
    tree6.insert(190);
    tree6.insert(500);
    tree6.insert(900);
    tree6.insert(921);
    tree6.insert(1000);
    tree6.insert(10);

    // remove root
    tree6.remove(-3);
    tree6.remove(500);

    // remove non existent node
    tree6.remove(200);


    tree6.print_tree();

    cout << endl;


    // Test 6: contains check
    cout << "TEST REDBLACKTREE 6" << endl;

    RedBlackTree<int> tree7(tree6);

    cout << "tree7 contains 45: " << tree7.contains(45) << endl;
    cout << "tree7 contains 54: " << tree7.contains(54) << endl;
    cout << "tree7 contains 10: " << tree7.contains(10) << endl;
    cout << "tree7 contains 14: " << tree7.contains(14) << endl;
    cout << "tree7 contains 879: " << tree7.contains(879) << endl;
    cout << "tree7 contains 33: " << tree7.contains(33) << endl;
    cout << "tree7 contains 122: " << tree7.contains(122) << endl;
    cout << "tree7 contains 140: " << tree7.contains(140) << endl;
    cout << endl;



    // Test 7: all possible rotations
    cout << "TEST REDBLACKTREE 7" << endl;

    RedBlackTree<int> tree8;

    tree8.insert(0);
    tree8.insert(5);
    tree8.insert(4);
    tree8.insert(-3);
    tree8.insert(-129);
    tree8.insert(-23);
    tree8.insert(51);
    tree8.insert(45);
    tree8.insert(-389);
    tree8.insert(-12);
    tree8.insert(100);
    tree8.insert(59);
    tree8.insert(12);
    tree8.insert(-10);
    tree8.insert(-1);
    tree8.insert(190);
    tree8.insert(500);
    tree8.insert(900);
    tree8.insert(921);
    tree8.insert(1000);
    tree8.insert(10);
    tree8.insert(0);
    tree8.insert(513);
    tree8.insert(462);
    tree8.insert(-367);
    tree8.insert(-1293);
    tree8.insert(-231);
    tree8.insert(519);
    tree8.insert(454);
    tree8.insert(-39);
    tree8.insert(-6762);
    tree8.insert(10055);
    tree8.insert(592);
    tree8.insert(1211);
    tree8.insert(-101);
    tree8.insert(-178);
    tree8.insert(1907);
    tree8.insert(55);
    tree8.insert(98);
    tree8.insert(93);
    tree8.insert(600);
    tree8.insert(170);

    tree8.print_tree();

    tree8.remove(1211);
    tree8.remove(592);
    tree8.remove(10055);
    tree8.remove(-39);
    tree8.remove(12);
    tree8.remove(5);
    tree8.remove(55);
    tree8.remove(-3);
    tree8.remove(-101);
    tree8.remove(-178);
    tree8.remove(1907);
    tree8.remove(55);
    tree8.remove(98);

    tree8.make_empty();

    tree8.print_tree();
    
    cout << "Is empty: " << tree8.is_empty() << endl;

    cout << endl;



    return 0;
}
