#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch/include/catch.hpp>

#include "SubBinaryTree.hpp"

using namespace std;

SCENARIO( "Testing SubBinaryTree Class To Ensure Proper Output", "[subbtree]" ) {
    SubBinaryTree* subbtree = new SubBinaryTree();

    GIVEN("An empty binary tree") {

        WHEN ("Adding elements") {
            REQUIRE(subbtree->add(5) == true);
            REQUIRE(subbtree->root->x == 5);
            REQUIRE(subbtree->root->preorderX == 5);
            REQUIRE(subbtree->root->inorderX == 5);
            REQUIRE(subbtree->root->postorderX == 5);
            REQUIRE(subbtree->add(1) == true);
            REQUIRE(subbtree->add(8) == true);
            REQUIRE(subbtree->add(0) == true);
            REQUIRE(subbtree->add(3) == true);
            REQUIRE(subbtree->add(7) == true);
            REQUIRE(subbtree->add(10) == true);
            REQUIRE(subbtree->add(2) == true);
            REQUIRE(subbtree->add(4) == true);
            REQUIRE(subbtree->add(6) == true);
            REQUIRE(subbtree->add(9) == true);
            REQUIRE(subbtree->add(11) == true);

            THEN( "printing the tree to reveal its initial state" ) {
                cout << "-------------- original -------------- " << endl;
                subbtree->prettyPrint(subbtree->root);
                cout << "-------------- end original -------------- " << endl;
            }

            THEN( "init preorder" ) {
                cout << "-------------- preorder init -------------- " << endl;
                subbtree->prettyPrintPreOrder(subbtree->root);
                cout << "-------------- end preorder init -------------- " << endl;
            }

            THEN( "after preorder" ) {
                cout << "-------------- preorder after -------------- " << endl;
                subbtree->preOrderNumber(subbtree->root);
                subbtree->prettyPrintPreOrder(subbtree->root);
                cout << "-------------- end preorder after -------------- " << endl;
            }

            THEN( "init postorder" ) {
                cout << "-------------- postorder init -------------- " << endl;
                subbtree->prettyPrintPostOrder(subbtree->root);
                cout << "-------------- end postorder init -------------- " << endl;
            }

            THEN( "after postorder" ) {
                cout << "-------------- postorder after -------------- " << endl;
                subbtree->postOrderNumber(subbtree->root);
                subbtree->prettyPrintPostOrder(subbtree->root);
                cout << "-------------- end postorder after -------------- " << endl;
            }

            THEN( "init inorder" ) {
                cout << "-------------- inorder init -------------- " << endl;
                subbtree->prettyPrintInOrder(subbtree->root);
                cout << "-------------- end inorder init -------------- " << endl;
            }

            THEN( "after inorder" ) {
                cout << "-------------- inorder after -------------- " << endl;
                subbtree->inOrderNumber(subbtree->root);
                subbtree->prettyPrintInOrder(subbtree->root);
                cout << "-------------- end inorder after -------------- " << endl;
            }
        }
    }
}