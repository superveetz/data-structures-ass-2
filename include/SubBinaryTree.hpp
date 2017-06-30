#ifndef SUBBINARYTREE_H
#define SUBBINARYTREE_H

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
    int preorderX;
    int inorderX;
    int postorderX;

    BTNode(int x): x(x), preorderX(x), inorderX(x), postorderX(x), parent(NULL), left(NULL), right(NULL )  {}
};

class SubBinaryTree {
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
    SubBinaryTree() : root(NULL), totalSize(0) {

    }

    // inOrderNumber
    void inOrderNumber(BTNode* x, bool IsLeftTree = true) {
        if (x == NULL) return;

        inOrderNumber(x->left, IsLeftTree);

        if (IsLeftTree) {
            // if parent is smaller than x, swap
            if (x->parent != NULL && x->parent->postorderX < x->postorderX) {
                int tmp1 = x->parent->postorderX;
                x->parent->postorderX = x->postorderX;
                x->postorderX = tmp1;
            }
            
            // if grandparent is smaller than x, swap
            if (x->parent != NULL && x->parent->parent != NULL && x->parent->parent->postorderX < x->postorderX) {
                int tmp2 = x->parent->parent->postorderX;
                x->parent->parent->postorderX = x->postorderX;
                x->postorderX = tmp2;
            }
            
        } else {
            // if parent is larger than x, swap
            if (x->parent != NULL && x->parent->postorderX < x->postorderX) {
                int tmp1 = x->parent->postorderX;
                x->parent->postorderX = x->postorderX;
                x->postorderX = tmp1;
            }
            
            // if grandparent is larger than x, swap
            if (x->parent != NULL && x->parent->parent != NULL && x->parent->parent->postorderX < x->postorderX) {
                int tmp2 = x->parent->parent->postorderX;
                x->parent->parent->postorderX = x->postorderX;
                x->postorderX = tmp2;
            }

        }

        // if parent->right is less than x, swap
        if (x->parent != NULL && x->parent->right != NULL && x->parent->right->postorderX < x->postorderX) {
            int tmp4 = x->parent->right->postorderX;
            x->parent->right->postorderX = x->postorderX;
            x->postorderX = tmp4;
        }

        // if parent->left is greater than x, swap
        if (x->parent != NULL && x->parent->left != NULL && x->parent->left->postorderX > x->postorderX) {
            int tmp3 = x->parent->left->postorderX;
            x->parent->left->postorderX = x->postorderX;
            x->postorderX = tmp3;
        }

        inOrderNumber(x->right, false);
    }

    // postOrderNumber
    void postOrderNumber(BTNode* x) {
        if (x == NULL) return;

        postOrderNumber(x->left);

        // if left is greater than x, swap
        if (x->left != NULL && x->left->postorderX > x->postorderX) {
            int tmp3 = x->left->postorderX;
            x->left->postorderX = x->postorderX;
            x->postorderX = tmp3;
        }

        // if right is less than x, swap
        if (x->right != NULL && x->right->postorderX < x->postorderX) {
            int tmp4 = x->right->postorderX;
            x->right->postorderX = x->postorderX;
            x->postorderX = tmp4;
        }

        postOrderNumber(x->right);

        // if parent is less than x, swap
        if (x->parent != NULL && x->parent->postorderX < x->postorderX) {
            int tmp1 = x->parent->postorderX;
            x->parent->postorderX = x->postorderX;
            x->postorderX = tmp1;
        }

        // if grandparent is less than x, swap
        if (x->parent != NULL && x->parent->parent != NULL && x->parent->parent->postorderX < x->postorderX) {
            int tmp2 = x->parent->parent->postorderX;
            x->parent->parent->postorderX = x->postorderX;
            x->postorderX = tmp2;
        }
    };

    // preOrderNumber
    void preOrderNumber(BTNode* x) {
        if (x == NULL) return;

        preOrderNumber(x->left);

        // perform a basic preorder traversal to track each node we visit
        preOrderNumber(x->right);

        // if parent is greater than x, swap
        if (x->parent != NULL && x->parent->preorderX > x->preorderX) {
            int tmp1 = x->parent->preorderX;
            x->parent->preorderX = x->preorderX;
            x->preorderX = tmp1;
        }

        // if grandparent is greater than x, swap
        if (x->parent != NULL && x->parent->parent != NULL && x->parent->parent->preorderX > x->preorderX) {
            int tmp2 = x->parent->parent->preorderX;
            x->parent->parent->preorderX = x->preorderX;
            x->preorderX = tmp2;
        }

        // if parent->left is greater than x, swap
        if (x->parent != NULL && x->parent->left != NULL && x->parent->left->preorderX > x->preorderX) {
            int tmp3 = x->parent->left->preorderX;
            x->parent->left->preorderX = x->preorderX;
            x->preorderX = tmp3;
        }

        // if parent->right is less than x, swap
        if (x->parent != NULL && x->parent->right != NULL && x->parent->right->preorderX < x->preorderX) {
            int tmp4 = x->parent->right->preorderX;
            x->parent->right->preorderX = x->preorderX;
            x->preorderX = tmp4;
        }
    };

    // create a pretty vertical tree: https://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way
    void prettyPrintInOrder(BTNode* p, int indent = 0) {
        if(p != NULL) {
            if(p->right) {
                prettyPrintInOrder(p->right, indent+4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
            std::cout<< p->inorderX << "\n ";
            if(p->left) {
                std::cout << std::setw(indent) << ' ' <<" \\\n";
                prettyPrintInOrder(p->left, indent+4);
            }
        }
    }

    // create a pretty vertical tree: https://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way
    void prettyPrintPreOrder(BTNode* p, int indent = 0) {
        if(p != NULL) {
            if(p->right) {
                prettyPrintPreOrder(p->right, indent+4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
            std::cout<< p->preorderX << "\n ";
            if(p->left) {
                std::cout << std::setw(indent) << ' ' <<" \\\n";
                prettyPrintPreOrder(p->left, indent+4);
            }
        }
    }

    // create a pretty vertical tree: https://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way
    void prettyPrintPostOrder(BTNode* p, int indent = 0) {
        if(p != NULL) {
            if(p->right) {
                prettyPrintPostOrder(p->right, indent+4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
            std::cout<< p->postorderX << "\n ";
            if(p->left) {
                std::cout << std::setw(indent) << ' ' <<" \\\n";
                prettyPrintPostOrder(p->left, indent+4);
            }
        }
    }

    // create a pretty vertical tree: https://stackoverflow.com/questions/13484943/print-a-binary-tree-in-a-pretty-way
    void prettyPrint(BTNode* p, int indent = 0) {
        if(p != NULL) {
            if(p->right) {
                prettyPrint(p->right, indent+4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
            std::cout<< p->x << "\n ";
            if(p->left) {
                std::cout << std::setw(indent) << ' ' <<" \\\n";
                prettyPrint(p->left, indent+4);
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

#endif  // SUBBINARYTREE_H