//Nikhil Krishna
//niekrish
//CMPS-12B/M
//BST.h
//Functions to create a BST tree, traverse the tree, find nodes, and delete the tree

//-----------------------------------------------------------------------------
// BST.h
// Header file for the BST ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#ifndef _BST_H_INCLUDE_
#define _BST_H_INCLUDE_
#define TRUE 1
#define FALSE 0

// Exported reference type
// Tree node to store strings, space must be allocated for the strings
typedef struct BSTObj {
    char               *term;           /* string data in each block */
    struct BSTObj      *leftChild;      /* ptr to left child */
    struct BSTObj      *rightChild;     /* ptr to right child */
} BSTObj;

typedef struct BSTObjPair {
	BSTObj* parent;
	BSTObj* child;
} BSTObjPair;

// add a new node to the BST with the new_data values, space must be allocated in the BST node
int insert(char *new_data,  BSTObj **pBST);

// print to OUT the inorder traversal
void inorderTraverse(FILE *out, BSTObj *T);

// print to OUT the preorder traversal
void preorderTraverse(FILE *out, BSTObj *T);

// print to OUT the postorder traversal
void postorderTraverse(FILE *out, BSTObj *T);

// print the leaves of the tree in inorder to OUT
void inorderLeaves(FILE *out, BSTObj *T);


// return the node with the term case insensitive matching item_to_find, NULL if not found
BSTObj *find(char *term_to_find, BSTObj *T);
  
// compute the height of the tree
// call with height = 0 and root of tree
int treeHeight(BSTObj *T, int height);

// create and return a complete memory independent copy of the tree 
BSTObj * copyTree(BSTObj *T);

// remove all the nodes from the tree, deallocate space and reset Tree pointer
void makeEmpty(BSTObj **pT);

//delete a specified node
int deleteItem(char *term_to_delete, BSTObj **pT);

//helper functions
void deleteNode(BSTObj *T);
BSTObjPair* retrieveNode(char *term_to_find, BSTObjPair *pT);
BSTObjPair* findLeftMost(BSTObjPair *T);


#endif
