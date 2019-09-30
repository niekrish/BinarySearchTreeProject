//Nikhil Krishna
//niekrish
//CMPS-12B/M
//BST.c
//Functions to create a BST tree, traverse the tree, find nodes, and delete the tree


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "BST.h"

BSTObj* create_new_node(char* term){
	BSTObj* temp = (BSTObj *) malloc(sizeof(BSTObj));
	temp->leftChild = NULL;
	temp->rightChild = NULL;
	temp->term = (char *) malloc(strlen(term) + 1);
	strcpy(temp->term, term);
	return temp;
}

int isLeafNode(BSTObj* T){
	if(T == NULL) return -1;
	else if(T->leftChild == NULL && T->rightChild == NULL) return 0;
	return 1;
}

// add a new node to the BST with the new_data values, space must be allocated in the BST node
int insert(char *new_data,  BSTObj **pBST){
	BSTObj * root = *pBST;
	BSTObj * node = root;
	int compare;
	if(root == NULL){
		root = create_new_node(new_data);
		*pBST = root;
		return 0;
	}
	while(node != NULL){
		compare = strcasecmp(node->term, new_data);
		if(compare == 0) return -1;
		if(compare > 0){
			//printf("igo left\n");
			if(node->leftChild == NULL){
				node->leftChild = create_new_node(new_data);
				return 0;
			}else{
				return insert(new_data, &node->leftChild);
			}

		}else{
			//printf("igo right\n");
			 if(node->rightChild == NULL){
                                node->rightChild = create_new_node(new_data);
                                return 0;
                        }else{
                                return insert(new_data,  &node->rightChild);
                        }
		}	
	}
	return -1;
}

// print to OUT the inorder traversal
void inorderTraverse(FILE *out, BSTObj *T){
	if(T == NULL){
		return;
	}
	if(T->leftChild != NULL){
		inorderTraverse(out, T->leftChild);
	}
	fprintf(out, "%s\n", T->term);
	if(T->rightChild != NULL){
		inorderTraverse(out, T->rightChild);
	}
}

// print to OUT the preorder traversal
void preorderTraverse(FILE *out, BSTObj *T){
	if(T == NULL){
                return;
        }
	fprintf(out,"%s\n", T->term);
	if(T->leftChild != NULL){
		preorderTraverse(out, T->leftChild);
	}
	if(T->rightChild != NULL){
		preorderTraverse(out, T->rightChild);
	}
}


// print to OUT the postorder traversal
void postorderTraverse(FILE *out, BSTObj *T){
	if(T == NULL){
		return;
	}
	if(T->leftChild != NULL){
		postorderTraverse(out, T->leftChild);
	}
	if(T->rightChild != NULL){
		postorderTraverse(out, T->rightChild);
	}
	fprintf(out,"%s\n", T->term);
}

// print the leaves of the tree in inorder to OUT
void inorderLeaves(FILE *out, BSTObj *T){
	if(T == NULL){
                return;
        }
        if(T->leftChild != NULL){
                inorderLeaves(out, T->leftChild);
        }
        if(T->rightChild != NULL){
                inorderLeaves(out, T->rightChild);
        }
	if(T->leftChild == NULL && T->rightChild == NULL){
		fprintf(out, "%s\n", T->term);
	}
}


// return the node with the term case insensitive matching item_to_find, NULL if not found
BSTObj *find(char *term_to_find, BSTObj *T){
	int compare = strcasecmp(T->term, term_to_find);
	if(compare == 0) return T;
	if(compare > 0){
		if(T->leftChild == NULL) return NULL;
		else{
			return find(term_to_find, T->leftChild);
		}
	}else{
		if(T->rightChild == NULL) return NULL;
		else{
			return find(term_to_find, T->rightChild);
		}
	}
}
  
// compute the height of the tree
// call with height = 0 and root of tree
int treeHeight(BSTObj *T, int height){
	int countLeft = 0;
	int countRight = 0;
	if(T == NULL) return 0;
	//printf("Current height = %d at node %s\n", height, T->term);
	if(T->leftChild != NULL){
		countLeft = treeHeight(T->leftChild, height);
	}
	if(T->rightChild != NULL){
                countRight = treeHeight(T->rightChild, height);
        }
	if(height > countLeft && height > countRight) return height + 1;
	else if(countLeft > countRight) return countLeft + 1;
	else return countRight + 1;
	
	
}

// create and return a complete memory independent copy of the tree 
BSTObj * copyTree(BSTObj *T){
	BSTObj *temp;
	if(T == NULL){
		return NULL;
	}
	temp = create_new_node(T->term);
	if(T->leftChild != NULL){
		temp->leftChild = copyTree(T->leftChild);
	}
	if(T->rightChild != NULL){
		temp->rightChild = copyTree(T->rightChild);
	}
	return temp;

}

// remove all the nodes from the tree, deallocate space and reset Tree pointer
void makeEmpty(BSTObj **pT){
	BSTObj *temp = *pT;
	if(temp == NULL){
		return;
	}
	if(temp->leftChild != NULL){
		makeEmpty(&temp->leftChild);
	}
	if(temp->rightChild != NULL){
		makeEmpty(&temp->leftChild);
	}
	deleteNode(temp);
	*pT = NULL;

}
//delete a specified node
int deleteItem(char *term_to_delete, BSTObj **pT){
	BSTObjPair P;
	BSTObjPair replace;
	if(*pT == NULL) return -1; //if tree is empty return -1
	P.parent = *pT;
	P.child = *pT;
	if (retrieveNode(term_to_delete, &P) == NULL) return -1; //if node was not found return -1
	//printf("Parent and child after retrieve: %s %s\n", P.parent->term, P.child->term);
	if(P.child->leftChild == NULL && P.child->rightChild == NULL){ //if node is a leaf node
		deleteNode(P.child);
		if(P.parent->leftChild == P.child) P.parent->leftChild = NULL; 
		else P.parent->rightChild = NULL;
		if(P.child == *pT) *pT = NULL;
		return 0;
	}
	else if(P.child->rightChild != NULL){ //if right node exists
		replace.parent = P.child;
		replace.child = P.child->rightChild;
		findLeftMost(&replace); //look for the leftmost successor in the right subtree
		free(P.child->term); //free existing term
		P.child->term = (char *)malloc(strlen(replace.child->term) + 1);
		strcpy(P.child->term, replace.child->term); //copy new term
		//replace the parent link to the deleted node with the right child of the deleted node
		if(replace.parent->leftChild == replace.child) replace.parent->leftChild = replace.child->rightChild;
		else replace.parent->rightChild = replace.child->rightChild;
		deleteNode(replace.child); //delete the dropped node
		return 0;
	}
	else { //going left if no right available
		replace.parent = P.child;
                replace.child = P.child->leftChild;
                findLeftMost(&replace); 
                free(P.child->term); //delete the old term
                P.child->term = (char *)malloc(strlen(replace.child->term) + 1); //replace with the new term
                strcpy(P.child->term, replace.child->term);
		//replace the parent link to the deleted node with the right child of the deleted node
                if(replace.parent->leftChild == replace.child) replace.parent->leftChild = replace.child->rightChild;
                else replace.parent->rightChild = replace.child->rightChild;
                deleteNode(replace.child);
                return 0;
	}
	
	
}
//helper functions
void deleteNode(BSTObj *node){
        free(node->term);
        node->term = NULL;
        node->leftChild = NULL;
        node->rightChild = NULL;
        free(node);
}
BSTObjPair* retrieveNode(char *term_to_find, BSTObjPair *T){
	int compare = strcasecmp(T->child->term, term_to_find);
	if(compare == 0) return T;
	if(compare > 0){
		//if you cannot move left the search ends
		if((T->child == NULL) || (T->child->leftChild == NULL)) return NULL;
		else{ //search to the left
			T->parent = T->child;
			T->child = T->child->leftChild;
			return retrieveNode(term_to_find, T);
		}
	}else{
		//if you cannot move right the search ends
		if((T->child == NULL) || (T->child->rightChild == NULL)) return NULL;
		else{ //search to the right
			 T->parent = T->child;
                         T->child = T->child->rightChild;
			return retrieveNode(term_to_find, T);
		}
	}
}
BSTObjPair* findLeftMost(BSTObjPair *P){
	if(P->child == NULL) return P;
	else {
	//	printf("find leftmost: %s %s\n", P->parent->term, P->child->term);
		if (P->child->leftChild == NULL) { //when there is no left child -done
			return P;
		}
		else{ //search to the left
			P->parent = P->child;
			P->child = P->parent->leftChild;
			return findLeftMost(P);
		}
	}		
}

