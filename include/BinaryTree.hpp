#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

using namespace std;

// each node in the tree is a struct
struct BTNode {
    BTNode* parent;
    BTNode* left;
    BTNode* right;
    int x;

    BTNode(int x, BTNode* parent = NULL, BTNode* left = NULL, BTNode* right = NULL): x(x), parent(parent), left(left), right(right) {}
};

class BinaryTree {
    private:
    int totalSize;
    // add a child node u to a parent node p
    const bool addChild(BTNode* p, BTNode* u) {
        // handle tree is empty
        if (p == NULL) {
            this->root = u;          // inserting into empty tree
        } else {
            // handle tree is not empty
            int comp = compare(u->x, p->x);

            if (comp < 0 ) {
                u->parent   = p;
                p->left     = u;
            } else if (comp > 0) {
                u->parent   = p;
                p->right    = u;
            } else {
                return false;   // u-> x is already in the tree
            }
        }

        this->totalSize++;
        return true;
    }

    // returns a node if it exists in the tree, otherwise returns NULL
    BTNode* findNode(const int x) {
        BTNode* w       = this->root;
        BTNode* prev    = NULL;

        while (w != NULL) {
            prev    = w;
            int comp    = compare(x, w->x);

            if (comp < 0) {
                w   = w->left;
            } else if (comp > 0) {
                w   = w->right;
            } else {
                return w;   // node matching x was found
            }
        }

        return prev;
    }

    // compares two integers and returns -1, 1 or 0
    static const int compare(const int p, const int q) {
        if (p < q) {
            return -1;
        } else if (p > q) {
            return 1;
        } else {
            return 0;
        }
    }
    public:
    BTNode* root; // root node

    // constructor func
    BinaryTree() : root(NULL), totalSize(0) {

    }

    // IsBinarySearchTree: tests whether a binary tree satisifies the search tree order property at every node
    // http://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/
    bool isBinarySearchTree(struct BTNode* root, struct BTNode* l=NULL, struct BTNode* r=NULL)
    {
        // Base condition
        if (root == NULL)
            return true;
    
        // if left node exist that check it has
        // correct data or not
        if (l != NULL && root->x < l->x)
            return false;
    
        // if right node exist that check it has
        // correct data or not
        if (r != NULL && root->x > r->x)
            return false;
    
        // check recursively for every node.
        return isBinarySearchTree(root->left, l, root) &&
            isBinarySearchTree(root->right, root, r);
    }

    // preorderNext(x): return the node visited after node x in a pre-order traversal of BT
    BTNode* preorderNext(BTNode* x) {
        if (x == NULL) return NULL; // return NULL if given a NULL ptr

        // create a vector to store the nodes that we visit
        vector<BTNode*> nodesVisited = {};

        // perform a basic preorder traversal to track each node we visit
        preorderNextInner(x, nodesVisited);

        // returning the node visited after x (index 1 since x is always the first visited node with pre order)
        if (nodesVisited[1] != NULL) return nodesVisited[1];
        else return NULL;
    };

    void preorderNextInner(BTNode* x, vector<BTNode*>& nodesVisited) {
        if (x == NULL) return;
        // deal with x here for preorder traversal
        // we will use a vector to store nodes as we visit them 
        nodesVisited.push_back(x);

        // recur through left subtree
        preorderNextInner(x->left, nodesVisited);
        // recur through right subtree
        preorderNextInner(x->right, nodesVisited);
    };

    // postorderNext(x): return the node visited after node x in a post-order traversal of BT
    BTNode* postorderNext(BTNode* x) {
        if (x == NULL) return NULL; // return NULL if given a NULL ptr

        // create a vector to store the nodes that we visit
        vector<BTNode*> nodesVisited = {};

        // perform a basic postorder traversal to track each node we visit
        postorderNextInner(x, nodesVisited);

        // in a post-traversal, node X would be the last node visited, so there would be no "node visited after node x"?
        // returning NULL instead
        return NULL;
    };

    void postorderNextInner(BTNode* x, vector<BTNode*>& nodesVisited) {
        if (x == NULL) return;

        // recur through left subtree
        postorderNextInner(x->left, nodesVisited);

        // recur through right subtree
        postorderNextInner(x->right, nodesVisited);

        // deal with x here for postorder traversal
        // we will use a vector to store nodes as we visit them 
        nodesVisited.push_back(x);
    };

    // inorderNext(x): return the node visited after node x in a in-order traversal of BT
    BTNode* inorderNext(BTNode* x) {
        if (x == NULL) return NULL; // return NULL if given a NULL ptr

        // create a vector to store the nodes that we visit
        vector<BTNode*> nodesVisited = {};
        // i'll use an additional variable here that will be used to keep track of node x's index in our nodeVisited vector once it is reached
        unsigned int nodeXPos;
        // perform a basic inorder traversal to track each node we visit
        inorderNextInner(x, x, nodesVisited, nodeXPos);

        // we have stored node x's index in our vector when it was visited as nodeXPos
        // return the next node visited after
        return nodesVisited[nodeXPos+1];
    };

    void inorderNextInner(BTNode* x, BTNode* sudoRoot, vector<BTNode*>& nodesVisited, unsigned int& nodeXPos) {
        if (x == NULL) return;

        // recur through left subtree
        inorderNextInner(x->left, sudoRoot, nodesVisited, nodeXPos);

        // deal with x here for inorder traversal
        // we will use a vector to store nodes as we visit them 
        nodesVisited.push_back(x);

        // if x == sudoRoot, then we have visited our initial node, store it's index
        if (x == sudoRoot) {
            nodeXPos = nodesVisited.size() - 1;
        }

        // recur through right subtree
        inorderNextInner(x->right, sudoRoot, nodesVisited, nodeXPos);
    };

    // create a pretty vertical tree: https://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way
    void prettyPrintBT(BTNode* p, int indent = 0) {
        if(p != NULL) {
            if(p->right) {
                prettyPrintBT(p->right, indent+4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
            std::cout<< p->x << "\n ";
            if(p->left) {
                std::cout << std::setw(indent) << ' ' <<" \\\n";
                prettyPrintBT(p->left, indent+4);
            }
        }
    }

    // print postorder
    void printPostorder(BTNode* u) {
        if (u == NULL) return;

        // first recur on left subtree
        printPostorder(u->left);

        // then recur on right subtree
        printPostorder(u->right);

        // now deal with the node
        cout << " -> " << u->x;
    }

    // print postorder
    void printInorder(BTNode* u) {
        if (u == NULL) return;

        // first recur on left subtree
        printInorder(u->left);

        // now deal with the node
        cout << " -> " << u->x;

        // then recur on right subtree
        printInorder(u->right);
    }

    // print preorder
    void printPreorder(BTNode* u) {
        if (u == NULL) return;

        // now deal with the node
        cout << " -> " << u->x;

        // first recur on left subtree
        printPreorder(u->left);

        // then recur on right subtree
        printPreorder(u->right);
    }

    // get height of node
    int height(BTNode* u) {
        if (u == NULL) return -1;
        return 1 + max(height(u->left), height(u->right));
    }

    // returns the depth of the parameter 'u' from the root of the tree and 0 for the root
    int depth(const BTNode* u) const {
        int d   = 0;
        while(u != this->root) {
            u = u->parent;
            d++;
        }
        
        return d;
    }

    // returns the total number of nodes attached to a given node
    const int size(const BTNode* u) const {
        if (u == NULL) return 0;
        return 1 + (u->left == NULL ? 0 : size(u->left)) + (u->right == NULL ? 0 : size(u->right));
    }

    // returns the total number of nodes in the tree
    const int size() const {
        return totalSize;
    }

    // add a new node to the binary tree
    const bool add(const int x) {
        BTNode* p   = findNode(x);
        return addChild(p, new BTNode(x));
    }

    // find an integer in the tree, otherwise return 0
    const int find(const int x) const {
        BTNode* w       = this->root;
        BTNode* prev    = NULL;

        while (w != NULL) {
            prev    = w;
            int comp    = compare(x, w->x);

            if (comp < 0) {
                w   = w->left;
            } else if (comp > 0) {
                w   = w->right;
            } else {
                return w->x;   // node matching x was found
            }
        }

        return 0; // return 0 if the element is not found
    }

    // splice node from tree: useful when parent contains 1 or 0 nodes
    const bool splice (const BTNode* u) {
        BTNode* s   = NULL;
        BTNode* p   = NULL;

        // ensure this node is spliceable (only has 1 child)
        if (u->left != NULL && u->right != NULL) return false;

        // reference the child to splice
        if (u->left != NULL) {
            s   = u->left;
        } else {
            s   = u->right;
        }

        // splice the node
        if (u == this->root) { 
            // handle node being removed is root
            this->root  = s;        // update new root
            p           = NULL;     // new root's parent will be NULL
        } else {
            // handle node being removed is not root
            p           = u->parent; // reference new parent

            // update the new parents children
            if (p->left == u) {
                p->left     = s;
            } else {
                p->right    = s;
            }
        }

        // update the child's new parent
        if (s != NULL) {
            s->parent       = p;
        }

        // update the tree's size
        this->totalSize--;
        return true;
    }

    const bool remove (const int x) {
        BTNode* p   = findNode(x);  // find the node for the given X

        // test if this node is spliceable
        if (p->left == NULL || p->right == NULL) {
            return splice(p);
        } else {
            // node p has 2 children
            BTNode* w   = p->right; // reference the right child
            while (w->left != NULL) { // obtain the farthest child to the left
                w   = w->left; 
            }

            p->x    = w->x; // move this x to one of our parents

            return splice(w); // splice this deeply nested node now that is only has 1 child
        }
    }
};

#endif  // BINARYTREE_H