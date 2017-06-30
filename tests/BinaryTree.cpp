#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/include/catch.hpp>

#include "BinaryTree.hpp"

using namespace std;

SCENARIO( "Testing BinaryTree Class To Ensure Proper Output", "[btree]" ) {

    GIVEN("An empty binary tree") {
        BinaryTree* btree      = new BinaryTree();
        int arbInt1  = 14;
        int arbInt2  = 28;
        int arbInt3  = 8;
        int arbInt4  = 10;
        int arbInt5  = 11;

        REQUIRE(btree->depth(btree->root) == 0);    // depth function returns 0
        REQUIRE(btree->size(btree->root) == 0);     // size function returns 0
        
        WHEN("An arbitrary node is added" ) {
            REQUIRE(btree->add(arbInt1) == true);       // adding an arbitrary integer returns true
            
            THEN("the size and depth should be 1") {
                REQUIRE(btree->root->x == arbInt1);         // the arbitrary integer is now the root
                REQUIRE(btree->size(btree->root) == 1);     // the size of the tree is now 1
                REQUIRE(btree->depth(btree->root) == 0);    // the depth of the tree from the root is 0
            }

            AND_WHEN("Adding the same arbitrary node") {
                REQUIRE(btree->add(arbInt1) == false);       // adding the same arbitrary integer returns false

                THEN("the size and depth should still be 1") {
                    REQUIRE(btree->root->x == arbInt1);         // root node remains unchanged
                    REQUIRE(btree->size(btree->root) == 1);     // the size of the tree is still 1
                    REQUIRE(btree->depth(btree->root) == 0);    // the depth of the tree from the root is still 0
                }
            }
        }

        WHEN("Adding two different arbitrary nodes") {
            REQUIRE(btree->add(arbInt1) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(arbInt2) == true);       // adding a unique arbitrary integer returns true

            THEN("the size = 2 and depth = 0") {
                REQUIRE(btree->root->x == arbInt1);                 // root node remains unchanged
                REQUIRE(btree->size(btree->root) == 2);             // the size of the tree is now 2
                REQUIRE(btree->depth(btree->root) == 0);            // the depth of the tree from the root is still 0
                REQUIRE(btree->depth(btree->root->right) == 1);     // the depth of the tree from the root->right is 1
                REQUIRE(btree->root->right->x == arbInt2);          // since arbInt2 was larger than arbInt1, it should appear on the right to the root
            }
        }

        WHEN("Adding nodes in a way to create a balanced Binary Tree") {
            REQUIRE(btree->add(25) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(15) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(50) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(10) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(22) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(35) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(70) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(4) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(12) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(18) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(24) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(31) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(44) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(66) == true);       // adding a unique arbitrary integer returns true
            REQUIRE(btree->add(90) == true);       // adding a unique arbitrary integer returns true
            
            cout << "Assignment 2 Question 1" << endl;
            cout << "---------------------------------" << endl;
            // print out this binary tree horizontally
            btree->prettyPrintBT(btree->root);
            
            // ensure that we are traversing the BT correctly
            cout << "Preorder: " << endl;
            btree->printPreorder(btree->root);
            cout << endl;

            cout << "Postorder: " << endl;
            btree->printPostorder(btree->root);
            cout << endl;

            cout << "Inorder: " << endl;
            btree->printInorder(btree->root);
            cout << endl;
            
            // answer assignment 2 question 1 
            BTNode* preorderNext = btree->preorderNext(btree->root);
            cout << "PreorderNext(25): return the node visited after node x in a pre-order traversal of BT: " << preorderNext->x << endl;
            REQUIRE(preorderNext->x == 15);

            BTNode* postorderNext = btree->postorderNext(btree->root);
            cout << "PostorderNext(25): return the node visited after node x in a post-order traversal of BT: " << "NULL" << endl;
            REQUIRE(postorderNext == NULL);

            BTNode* inorderNext = btree->inorderNext(btree->root);
            cout << "InorderNext(25): return the node visited after node x in a in-order traversal of BT: " << inorderNext->x << endl;
            REQUIRE(inorderNext->x == 31);
        }

        WHEN("Determining if a Binary Tree does not satisfy the Search property") {
            THEN("an empty tree should be searchable") {
                REQUIRE(btree->isBinarySearchTree(btree->root) == true);
            }

            cout << "Assignment 2 Question 2" << endl;
            cout << "---------------------------------" << endl;

            // creating an unbalanced binary tree
            // http://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/
            btree->root                 = new BTNode(3);
            btree->root->left           = new BTNode(2, btree->root);
            btree->root->right          = new BTNode(5, btree->root);
            btree->root->left->left     = new BTNode(1, btree->root->left);
            btree->root->left->right    = new BTNode(4, btree->root->left);
            
            THEN("this tree should not be a binary search tree") {
                // print out this binary tree horizontally
                cout << "A Binary Tree that does not satisify the search property." << endl;
                btree->prettyPrintBT(btree->root);
                REQUIRE(btree->isBinarySearchTree(btree->root) == false);
            }
        }

        WHEN("Determining if a Binary Tree does satisfy the Search property") {
            THEN("an empty tree should be searchable") {
                REQUIRE(btree->isBinarySearchTree(btree->root) == true);
            }

            // creating an unbalanced binary tree
            // http://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/
            btree->root                 = new BTNode(4);
            btree->root->left           = new BTNode(2);
            btree->root->right          = new BTNode(5);
            btree->root->left->left     = new BTNode(1);
            btree->root->left->right    = new BTNode(3);
            
            THEN("this tree should be a binary search tree") {
                cout << "A Binary Tree that does satisify the search property." << endl;
                // print out this binary tree horizontally
                btree->prettyPrintBT(btree->root);
                REQUIRE(btree->isBinarySearchTree(btree->root) == true);
            }
        }
    }
}