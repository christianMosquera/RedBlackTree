#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <cstddef>
#include <utility>
#include <iostream>


/*****************************************************
 **
 ** File:    red_black_tree.h
 ** Project: CSCE 221 Lab 5 Spring 2022
 ** Author:  Christian Mosquera
 ** Date:    03/30/22
 ** Section: 510
 ** Email:   cwbo.1701@tamu.edu
 ** 
 ** This file contains all the functions for the 
 ** red black tree data structure. It has public 
 ** functions that a user can call and it utilizes
 ** internal private functions to help with recursion.
 **
 *****************************************************/

template <typename Comparable>
class RedBlackTree {

private:
	

	struct Node {
        Comparable value;
        Node* left;
        Node* right;
        int color;
        Node* parent;
        
        Node(const Comparable& value, Node* parent) : value(value), left(nullptr), right(nullptr), color(RED), parent(parent) {}
    };

    Node* root;

    // recursive functions

    //---------------------------------------
    // Name: recurse_find_min
    // PreCondition:  Binary tree exists
    // PostCondition: Returns the minimum value
    //---------------------------------------
    Node* recurse_find_min(Node* node) const { 
        if (!node) {
            throw std::invalid_argument("Tree is empty, no minimum value.");
        }

        else if (node->left == nullptr) {
            return node;
        }

        return recurse_find_min(node->left);
    }


    //---------------------------------------
    // Name: recurse_find_max
    // PreCondition:  Binary tree exists
    // PostCondition: Returns maximum value
    //---------------------------------------
    Node* recurse_find_max(Node* node) const { 
        if (!node) {
            throw std::invalid_argument("Tree is empty, no maximun value.");
        }   

        else if (node->right == nullptr) {
            return node;
        }   

        return recurse_find_max(node->right);
    }

    void printRecurse(Node* node, int count, std::ostream& os) const;
    void recurseInsert(const Comparable& value, Node* &node, Node* &parent);
    void balance(Node* &node);
    void singleRotateRight(Node* node);
    void singleRotateLeft(Node* node);
    void preorderInsert(Node* current);
    bool containRecurse(Node* node, const Comparable& value) const;
    void emptyRecurse(Node* &node);
    void removeRecurse(const Comparable& value, Node* &current);
    void removeBalance(Node* &node);
    void fixBlack(Node* node, Node* sibling);

public:
	enum Color {RED, BLACK};
	RedBlackTree();
	RedBlackTree(const RedBlackTree& other);
	~RedBlackTree();
	RedBlackTree& operator=(const RedBlackTree& other);
	bool contains(const Comparable& value) const;
	void insert(const Comparable& value);
	void remove(const Comparable& value);
	const Comparable& find_min() const;
	const Comparable& find_max() const;
	void print_tree(std::ostream& os=std::cout);
	bool is_empty() const;
	void make_empty();

	// FOR TESTING ONLY - do not use these in your implementation
	int color(const Node* node) const;
	const Node* get_root() const {return this->root;}

	// Optional
	// RedBlackTree(RedBlackTree&& other);
	// RedBlackTree& operator=(RedBlackTree&& other);
	// void insert(Comparable&& value);
};



//---------------------------------------
// Name: Defalut Constructor
//---------------------------------------
template<typename Comparable>
RedBlackTree<Comparable>::RedBlackTree() : root(nullptr) {}


//---------------------------------------
// Name: Copy Constructor
// PreCondition:  other tree is given
// PostCondition: A deep copied second tree
//---------------------------------------
template <typename Comparable>
RedBlackTree<Comparable>::RedBlackTree(const RedBlackTree& other) : root(nullptr) {

    // preorder traversal to copy
    if (other.root != nullptr) {
        this->preorderInsert(other.root);
    }

}


//---------------------------------------
// Name: Destructor
//---------------------------------------
template<typename Comparable>
RedBlackTree<Comparable>::~RedBlackTree() {
    make_empty();
}


//---------------------------------------
// Name: Copy assignment
// PreCondition:  other is given
// PostCondition: A deep copied tree
//---------------------------------------
template <typename Comparable>
RedBlackTree<Comparable>& RedBlackTree<Comparable>::operator=(const RedBlackTree& other) {

    // If this is the same as other
    if (this == &other) {
        return *this;
    }

    // make this empty first
    this->make_empty();

    // if other is empty
    if (other.root == nullptr) {
        this->root = nullptr;
        return *this;
    }

    // if other is non empty
    this->preorderInsert(other.root);
    return *this;

}


//---------------------------------------
// Name: insert
// PreCondition:  Value is comparable
// PostCondition: Node inserted into the binary tree
//---------------------------------------
template<typename Comparable>
void RedBlackTree<Comparable>::insert(const Comparable& value) {
    
    recurseInsert(value, root, root);
}


//---------------------------------------
// Name: insertRecurse
// PreCondition:  Value is comparable
// PostCondition: Node inserted into the binary tree
//---------------------------------------
template<typename Comparable>
void RedBlackTree<Comparable>::recurseInsert(const Comparable& value, Node* &node, Node* &parent) {

    if (!node) {
        node = new Node(value, parent);
    }

    else if (value < node->value) {
        recurseInsert(value, node->left, node);
    }

    else if (value > node->value) {
        recurseInsert(value, node->right, node);
    }

    balance(node);

}


//---------------------------------------
// Name: balance
// PreCondition:  node is not nullptr
// PostCondition: Balances the tree accordingly
//---------------------------------------
template <typename Comparable>
void RedBlackTree<Comparable>::balance(Node* &node) {

    // if null dont do anything
    if (!node) {
        return;
    }

    Node* Grandparent;
    Node* Parent = node->parent;

    if (Parent) {
       Grandparent = node->parent->parent; 
    }

    // root was just inserted
    if (!Parent) {
        node->color = BLACK;
        return;
    }

    // if no grandparent can not do rotation
    if (!Grandparent) {
        return;
    }
    
    // check if parent is black
    else if (Parent->color == BLACK) {
        return;
    }  

    // check if parent is red and sibling is black
    else if (Parent->color == RED && node->color == RED) {

        // zig zig rotation
        if (node == Parent->left && Parent == Grandparent->left) {

            // check uncle
            Node* Uncle = Grandparent->right;
            int uncleColor = BLACK;
            if (Uncle) {
                uncleColor = Uncle->color;
            }

            // left line black uncle
            if (uncleColor == BLACK) {
                // single rotate right and recolor
                singleRotateRight(node->parent->parent);
            }

            // left line red uncle
            else if (uncleColor == RED) {
                // swap colors
                Grandparent->color = RED;
                Uncle->color = BLACK;
                Parent->color = BLACK;
            }
            
        }

        else if (node == Parent->right && Parent == Grandparent->right) {

            // check uncle
            Node* Uncle = Grandparent->left;
            int uncleColor = BLACK;
            if (Uncle) {
                uncleColor = Uncle->color;
            }

            // right line black uncle
            if (uncleColor == BLACK) {
                // single rotate left and recolor
                singleRotateLeft(Grandparent);
            }

            // right line red uncle
            else if (uncleColor == RED) {
                // swap colors
                Grandparent->color = RED;
                Uncle->color = BLACK;
                Parent->color = BLACK;
            }

        }

        // zig zag rotation
        else if (node == Parent->right && Parent == Grandparent->left) {

            // check uncle
            Node* Uncle = Grandparent->right;
            int uncleColor = BLACK;
            if (Uncle) {
                uncleColor = Uncle->color;
            }

            if (uncleColor == BLACK) {
                singleRotateLeft(Parent);
                singleRotateRight(Grandparent);
            }

            else {
                Grandparent->color = RED;
                Uncle->color = BLACK;
                Parent->color = BLACK;
            }
        }

        else if (node == Parent->left && Parent == Grandparent->right) {

            // check uncle
            Node* Uncle = Grandparent->left;
            int uncleColor = BLACK;
            if (Uncle) {
                uncleColor = Uncle->color;
            }

            if (uncleColor == BLACK) {
                singleRotateRight(Parent);
                singleRotateLeft(Grandparent);
            }

            else {
                Grandparent->color = RED;
                Uncle->color = BLACK;
                Parent->color = BLACK;
            }
        }

        
    }
    
}


//---------------------------------------
// Name: singleRotateRight
// PreCondition:  node is not nullptr
// PostCondition: Rotates the tree right
//---------------------------------------
template <typename Comparable>
void RedBlackTree<Comparable>::singleRotateRight(Node* node) {

    // varibles to keep track of
    Node* nodeLeft = node->left;

    // change the node left to the nodeLeft's right
    node->left = nodeLeft->right;
    
    // update parent if there exists a subtree
    if (nodeLeft->right) {
        nodeLeft->right->parent = node;
    }

    // update nodeLeft's parent to be node's parent
    nodeLeft->parent = node->parent;

    // the right of nodeLeft is the node
    nodeLeft->right = node;

    // change the root if the node's parent is nullptr
    if (nodeParent == nullptr) {
        this->root = nodeLeft;
    }

    // change the node parent's right if node is on the right
    else if (nodeParent->right == node) {
        node->parent->right = nodeLeft;
    }

    // change the node parent's left if the node is on the left
    else if (nodeParent->left == node) {
        node->parent->left = nodeLeft;
    }

    // change node's parent to be nodeLeft
    node->parent = nodeLeft;

    // change colors
    nodeLeft->color = BLACK;
    nodeLeft->right->color = RED;

}


//---------------------------------------
// Name: singleRotateLeft
// PreCondition:  node is not nullptr
// PostCondition: Rotates the tree left
//---------------------------------------
template <typename Comparable>
void RedBlackTree<Comparable>::singleRotateLeft(Node* node) {

    // varibles to keep track of
    Node* nodeRight = node->right;

    // change the node right to the nodeRight's left
    node->right = nodeRight->left;

    // update parent if there exists a subtree
    if (nodeRight->left) {
        nodeRight->left->parent = node;
    }

    // update nodeRight's parent to be node's parent
    nodeRight->parent = node->parent;

    // the left of nodeRight is the node
    nodeRight->left = node;

    // change the root if the node's parent is nullptr
    if (node->parent == nullptr) {
        this->root = nodeRight;
    }

    // change the node parent's right if node is on the right
    else if (node->parent->right == node) {
        node->parent->right = nodeRight;
    }

    // change the node parent's left if the node is on the left
    else {
        node->parent->left = nodeRight;
    }

    // change node's parent to be nodeLeft
    node->parent = nodeRight;

    // change colors
    nodeRight->color = BLACK;
    nodeRight->left->color = RED;
} 



//---------------------------------------
// Name: remove
// PreCondition:  Value is comparable
// PostCondition: Removes the value from the tree
//---------------------------------------
template <typename Comparable>
void RedBlackTree<Comparable>::remove(const Comparable& value) {

    removeRecurse(value, this->root);

}



//---------------------------------------
// Name: removeRecurse
// PreCondition:  Value is comparable
// PostCondition: Removes the value from the tree
//---------------------------------------
template <typename Comparable>
void RedBlackTree<Comparable>::removeRecurse(const Comparable& value, Node* &current) {
    Node* sibling;
    int colorDelete = BLACK;

    // find value
    if (!current) {
        return;
    }

    if (value == current->value) {
        if (current) {
            colorDelete = current->color;
        }
        // case 1: leaf node
        if (current->left == nullptr && current->right == nullptr) {
            // if (current->color == BLACK) {
            //     if (current == current->parent->left) {
            //         sibling = current->parent->right;
            //     }
            //     else {
            //         sibling = current->parent->left;
            //     }
            //     fixBlack(current, sibling);
            // }
            delete current;
            current = nullptr;
            return;
        }

        // case 2: right sub tree and left sub tree
        else if (current->left && current->right) {

            // Find max in left sub tree
            Node* minRight = recurse_find_min(current->right);
            current->value = minRight->value;
            removeRecurse(minRight->value, current->right);
            
        }

        // case 3: right sub tree or left sub tree
        else if (current->right || current->left) {

            Node* temp = current;
            if (current->right) {
                current = current->right;
                delete temp;
                // if (current->color == BLACK && current->right->color == BLACK) {
                //     fixBlack(current, current->right);
                // }
                // else {
                //     if (current->right){
                //         current->right->color = BLACK;
                //     }
                    
                // }
                
            }
            else {
                current = current->left;
                delete temp;
                // if (current->color == BLACK && current->left->color == BLACK) {
                //     fixBlack(current, current->left);
                // }
                // else {
                //     if (current->left) {
                //         current->left->color = BLACK;
                //     }
                    
                // }

                
            }
        }
    }

    else if (value < current->value) {
        removeRecurse(value, current->left);
    }

    else {
        removeRecurse(value, current->right);
    }
    
    // At the end of inserting, make sure tree balanced
    // if (blackBlack) {
    //     fixBlack(current, sibling);
    // }
    // else if (current == root) {
    //     current->color = BLACK;
    // }
    // else {
    //     current->color = BLACK;
    // }
    
}


//---------------------------------------
// Name: fixBlack
// PreCondition:  node is not nullptr
// PostCondition: Fixes red black property
//---------------------------------------
template <typename Comparable>
void RedBlackTree<Comparable>::fixBlack(Node* node, Node* sibling) {

    if (node == root) {
        return;
    }

    Node* siblingRight = sibling->right;
    Node* siblingLeft = sibling->left;
    int colorRight = BLACK;
    int colorLeft = BLACK;
    int siblingColor = BLACK;

    if (sibling) {
        siblingColor = sibling->color;
    }
    if (siblingRight) {
        colorRight = siblingRight->color;
    }
    if (siblingLeft) {
        colorLeft = siblingLeft->color;
    }

    if (!sibling) {
        if (node->parent = node->parent->parent->left) {
            fixBlack(node->parent, node->parent->parent->right);
        }
        else {
            fixBlack(node->parent, node->parent->parent->left);
        }
        
    }
    

    if (siblingColor == BLACK && (colorLeft == RED || colorRight == RED)) {

        if (sibling == node->left && (colorLeft == RED || colorRight == RED)) {
            singleRotateRight(node);
        }
        else if (sibling == node->left && (colorRight == RED && colorLeft == BLACK)) {
            singleRotateLeft(sibling);
            singleRotateRight(node);
        }
        else if (sibling == node->right && (colorRight == RED || colorLeft == BLACK)) {
            singleRotateLeft(node);
        }
        else if (sibling == node->right && (colorLeft == RED && colorRight == BLACK)) {
            singleRotateRight(sibling);
            singleRotateLeft(node);
        }
    }

    else if (siblingColor == BLACK && (colorLeft == BLACK && colorRight == BLACK)) {
        if (sibling) {
            sibling->color = RED;
        }
        if (node->parent->color == BLACK) {
            if (node->parent = node->parent->parent->left) {
                fixBlack(node->parent, node->parent->parent->right);
            }
            else {
                fixBlack(node->parent, node->parent->parent->left);
            }
        }
        else {
            node->parent->color = BLACK;
        }
        
    }

    else if (siblingColor == RED) {

    }

}


//---------------------------------------
// Name: find_min
// PreCondition:  Binary tree exists
// PostCondition: Returns the minimum value
//---------------------------------------
template <typename Comparable>
const Comparable& RedBlackTree<Comparable>::find_min() const {

    Node* node = recurse_find_min(this->root);
    return node->value;

}


//---------------------------------------
// Name: find_max
// PreCondition:  Binary tree exists
// PostCondition: Returns maximum value
//---------------------------------------
template <typename Comparable>
const Comparable& RedBlackTree<Comparable>::find_max() const {

    Node* node = recurse_find_max(root);
    return node->value;

}


//---------------------------------------
// Name: print_tree
// PreCondition:  Tree exists
// PostCondition: Outputs to the os stream that is specified
//---------------------------------------
template <typename Comparable>
void RedBlackTree<Comparable>::print_tree(std::ostream& os) {

    // If tree is empty
    if (this->root == nullptr) {
        os << "<empty>" << std::endl;
    }

    // non empty tree
    int count = -1;
    printRecurse(root, count, os);
}


//---------------------------------------
// Name: printRecurse
// PreCondition:  Tree exists
// PostCondition: Outputs to the os stream
//---------------------------------------
template <typename Comparable>
void RedBlackTree<Comparable>::printRecurse(Node* node, int count, std::ostream& os) const {

    // check for nullptr
    if (node) {

        // Keep track of depth
        count++;

        printRecurse(node->right, count, os);

        // Determine amount of spacing
        if (node != root) {
            for (int i = 0; i < count*2; i++) {
                os << " ";
            }
        }

        // if color is red then print with R:
        if (node->color == RED) {
            os << "R:";
        }

        // else print normal
        os << node->value << std::endl;

        printRecurse(node->left, count, os);

    }
}


//---------------------------------------
// Name: is_empty
// PreCondition:  N/A
// PostCondition: Returns true if root is nullptr
//---------------------------------------
template <typename Comparable>
bool RedBlackTree<Comparable>::is_empty() const {

    return root == nullptr;

}


//---------------------------------------
// Name: preorderInsert
// PreCondition:  Current is not nullptr
// PostCondition: A fully inserted binary search tree
//---------------------------------------
template <typename Comparable>
void RedBlackTree<Comparable>::preorderInsert(Node* current) {

    // base case if null
    if (current) {
        this->insert(current->value);
        this->preorderInsert(current->left);
        this->preorderInsert(current->right);
    }

    return;

}


//---------------------------------------
// Name: contains
// PreCondition: Value is comparable
// PostCondition: Returns if value is in binary tree
//---------------------------------------
template <typename Comparable>
bool RedBlackTree<Comparable>::contains(const Comparable& value) const {

    return containRecurse(root, value);

}


//---------------------------------------
// Name: containRecurse
// PreCondition:  Node is not nullptr and value is comparable
// PostCondition: Returns if value is in binary tree
//---------------------------------------
template <typename Comparable>
bool RedBlackTree<Comparable>::containRecurse(Node* node, const Comparable& value) const {

    // Base case for nullptr
    if (node) {

        // Found value
        if (node->value == value) {
            return true;
        }

        // Traverse left
        else if (value < node->value) {
            return containRecurse(node->left, value);
        }
        
        // Traverse right
        else if (value > node->value) {
            return containRecurse(node->right, value);
        }

    }
    
    // Once it traverses to a null
    return false;

}


//---------------------------------------
// Name: make_empty
// PreCondition:  Tree exists
// PostCondition: All nodes from tree are removed
//---------------------------------------
template <typename Comparable>
void RedBlackTree<Comparable>::make_empty() {

    emptyRecurse(root);

}


//---------------------------------------
// Name: emptyRecurse
// PreCondition:  Tree exists
// PostCondition: All nodes from tree are removed
//---------------------------------------
template <typename Comparable>
void RedBlackTree<Comparable>::emptyRecurse(Node* &node) {

    // Base case for nullptr
    if (node) {
        
        emptyRecurse(node->left);
        emptyRecurse(node->right);
        delete node;

    }

    // make node nullptr
    node = nullptr;
}



template <typename Comparable>
int RedBlackTree<Comparable>::color(const Node* node) const {
    if (!node) {
        return BLACK;
    }
    return node->color;
}

#endif  // RED_BLACK_TREE_H