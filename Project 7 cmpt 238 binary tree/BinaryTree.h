#pragma once
#include "stdafx.h"
#include "iostream"
using namespace std;

class BinaryTree {
private:
	struct node { //the decleration of a node structure.
		int value;
		node* left;
		node* right;
	};
	node* root;							
	int counter;
	void recursiveClearTool(node* ptr);		//i did not want to use a root pointer in the main function, as an argument to these display functions
	void recursivePreorderTool(node* ptr);  //so i made these private, and i use public no argument functions to get them started up.
	void recursiveInOrderTool(node* ptr);
	void recursivePostOrderTool(node* ptr);
	void reInsertBranch(node* branchHead);  //this function is used to insert an entire branch into the tree. Used only for dealing with leftover branches
public:										//from node deletion.
	BinaryTree() { //default constructor
		root = NULL;
		counter = 0;
	}

	int getMinimum();    //function I used to test if the max and min values of my tree were in the far corners, as intentended.
	int getMaximum();
	void insertNode(int value);  //This is the function for inserting a new node into the tree.
	bool searchNode(int value);  //this function returns true if a given value is found within the tree.
	bool deleteNode(int value);  //this function is used to delete a node, with a given value, from the tree.
	void displayPreorder();
	void displayInOrder();
	void displayPostOrder();
	void clearTree();    //this function starts up the tree deletion process.
};

void BinaryTree::insertNode(int value) {
	node* temp = new node;
	temp->value = value;
	temp->left = temp->right = NULL;
	if (root == NULL) { //if the tree is empty, then make this new node the root, and increment the counter by 1.
		root = temp;
		counter += 1;
	}
	else {
		node* traverser = root; //the traverser pointer scouts ahead of the follower pointer, to check if their is space available down the tree
		node* follower;			//if space is available, the follower node is used to set up the link with the new node.
		bool nodeSet = false;
		while (nodeSet == false) {  //this loop continues until it is determined what should be done with the new node.
			
			if (traverser->value > temp->value) { //go left if new node is less than parent
				follower = traverser;
				traverser = traverser->left;
				if (traverser == NULL) {  // IMPORTANT: if the traverser became NULL after going left, and the follower is always one node right behind it.
					follower->left = temp;  // the the follower node is on the perfect parent node, and the new node should link to its left.
					counter += 1;  //and the node counter is incremented.
					nodeSet = true;
				}
			}
			else if (traverser->value < temp->value) {  //go right if new node is greater than parent
				follower = traverser;
				traverser = traverser->right;
				if (traverser == NULL) {      //if the travers turned right and became NULL, then the new node must be linked to the right link field
					follower->right = temp;	  // of the node pointed at by the follower.
					counter += 1;
					nodeSet = true;
				}
			}
			else {  //it must be an edit command. overwrite data of a more complex structure, then delete the new node
				traverser->value = temp->value; // overwriting it doesn't really matter in this case.
				delete temp; 
				cout << "The node was already in the tree. It has been overwritten." << endl;
				nodeSet = true;
			}
		}
	}
	
}

bool BinaryTree::searchNode(int value) { //this function simply searches for the given value, and returns true or false depending
	node* traverser = root;					//on whether it found it or not.
	bool found = false;

	while (traverser != NULL) {  // the traverser pointer would be null if the tree is empty, or if it did not find the value and hit the end of the tree.
		if (traverser->value == value) {
			found = true;
			traverser = NULL;
		}
		else if ( value > traverser->value) {  //travels down the right or left link depending on how the current node value compares to the value it
			traverser = traverser->right;		// is searching for.
		}
		else {
			traverser = traverser->left;
		}
	}
	return found;
}

void BinaryTree:: clearTree() {//this function starts up the recursive clearing function.
	node* inspector = root;
	if (inspector == NULL) {
		cout << "The binary tree is already empty." << endl;
	}
	else {
		recursiveClearTool(inspector->left);
		recursiveClearTool(inspector->right);
		delete inspector; // delete the root node last.
		root = NULL;  // the root must be set to NULL to properly indicate an empty tree.
		counter = 0;
	}
}

void BinaryTree::recursiveClearTool(node* ptr) {  //this is a private function
	node* inspector = ptr;
	if (inspector != NULL) {  //if the pointer passed into this function exists
		recursiveClearTool(inspector->left); //send and inspector down its two link fields
		recursiveClearTool(inspector->right);
		delete inspector; //and when control returns to this instance of the function, delete the parent node.
	}
}

void BinaryTree::displayPreorder() {  //these are the two PRE ORDER displaying functions. This displays automatically in the main function
	node* traverser = root;			  //because i found it useful that it displays the root first, which helped me observe how the tree changed, when
	if (traverser == NULL) {		  // i had to test the deleting functions.
		cout << "The binary tree is empty, nothing to print." << endl;
	}
	else {
		cout << "Total node in the tree: " << counter << endl;
		cout << "ROOT: " << traverser->value << endl;
		cout << "Here is the data on the left subtree from the root:------- " << endl;
		recursivePreorderTool(traverser->left);
		cout << "Here is the data on the right subtree from the root:---------" << endl;
		recursivePreorderTool(traverser->right);
	}
}

void BinaryTree::recursivePreorderTool(node* ptr) {
	node *traverser = ptr;
	if (traverser != NULL) {
		cout << traverser->value << endl;		//In PRE ORDER, you must display the current node data, before arguing foward the left and right branches
		recursivePreorderTool(traverser->left);
		recursivePreorderTool(traverser->right);
	}
}

void BinaryTree::displayInOrder() {  //the In-Order displaying functions
	if (root == NULL) {
		cout << "The tree is empty, so there is nothing to display." << endl;
	}
	else {
		node* ptr = root;
		cout << "Here is the tree In Order, from least to greatest:" << endl;
		recursiveInOrderTool(ptr->left);
		cout <<"root:"<< ptr->value << endl;  //the print statement must be done after the left branch arguement, for 'IN ORDER' displaying
		recursiveInOrderTool(ptr->right);
	}
}

void BinaryTree::recursiveInOrderTool(node* ptr) { // here is the truly recursive part of the IN ORDER display
	if (ptr != NULL) {
		recursiveInOrderTool(ptr->left);
		cout << ptr->value << endl;
		recursiveInOrderTool(ptr->right);
	}
}

void BinaryTree::displayPostOrder() { //The POST ORDER display, prints out the nodes from the 'bottom' to the root of the structure.
	if (root == NULL) {					// so the root node will be printed last.
		cout << "The tree is empty, so there is nothing to display." << endl;
	}
	else {
		node* ptr = root;
		cout << "Here is the tree in Post Order:" << endl;
		recursivePostOrderTool(ptr->left);
		recursivePostOrderTool(ptr->right);
		cout <<"root: "<< ptr->value << endl;
	}
}

void BinaryTree::recursivePostOrderTool(node* ptr) {
	if (ptr != NULL) {
		recursivePostOrderTool(ptr->left);
		recursivePostOrderTool(ptr->right);
		cout << ptr->value << endl; // When display in POST ORDER form, you must display the data AFTER arguing the left, then the right branches.
	}
}

int BinaryTree::getMaximum() { //this simply goes to the farthest right node, which would be the one with  the greatest value
	if (root == NULL) {			// and then it returns that value.
		cout << "The tree is empty, there is no maximum value. -1 being returned." << endl;
		return -1;
	}
	else {
		node* traverser=root;
		while (traverser->right != NULL) {
			traverser = traverser->right;
		}
		return traverser->value;
	}
}

int BinaryTree::getMinimum() {  //Much like the max function, this min function sends a pointer to the farthest left node in the tree structure,
	if (root == NULL) {			// to get the lowest value present.
		cout << "The tree is empty, there is no minimum value. -1 being returned." << endl;
		return -1;
	}
	else {
		node* traverser = root;
		while (traverser->left != NULL) {
			traverser = traverser->left;
		}
		return traverser->value;
	}
}

bool BinaryTree::deleteNode(int value) { //this function takes an integer value, and deletes the node with that value if it is present in the tree.
	node* seeker = root;
	node* follower = seeker;;
	bool found = false;    // This boolean value, is turned true if the integer value that was argued, was found in the tree.
							// because if it wasnt, then the function does need to do anything.

	if (seeker == NULL) {
		cout << "The binary tree is empty, so there are no nodes to delete." << endl;
		return found;
	}
	else {
		while (seeker != NULL) {  // This loop continues until the seeker pointer has found the value, 
			if (seeker->value == value) {  //or it has reached the end of the tree(without finding it)
				found = true;
				break;
			}
			else if(value > seeker->value) {
				follower = seeker;
				seeker = seeker->right;
			}
			else {
				follower = seeker;
				seeker = seeker->left;
			}
		}

		if (found == false) {  //if the flag is still false, then the value was not in the tree.
			cout << "The node value you searched for was not in the tree." << endl;
			return found;  // i was going to use the returned boolean values in main, but decided not to.
		}
		else {		//this path is taken, if the value was found.
			
			node* leftBranch = seeker->left;  // Two pointers are made at the two links from the node which is about to be deleted.
			node* rightBranch = seeker->right;
			
			if (follower != seeker) {   // This statement checks if the follower pointer points at the same thing as seeker. 
				if (follower->left == seeker) {  //That would mean they are at the root, since the seeker pointer did not have to move from its starting spot
					follower->left = NULL;   //If the deleted node was not the root, then its parent node's link must be set to null
				}							// This is very important for my method of reconnecting the branches of the deleted node.
				else {
					follower->right = NULL;  //If the parent node above the deleted node had unexpected values for links, then i could not easily
				}								// implement my insertion approach.
			}
			else { //if the deleted node was the root, then the root pointer must be set to null, for the same reason.
				root = NULL;
			}

			delete seeker; //the node is deleted and the counter of nodes in the tree is decremented.
			counter -= 1;

			if (rightBranch != NULL) {  //if there is was no branch on the deleted nodes links, then there is not reason to use the reinsert function
				reInsertBranch(rightBranch);  //if these pointers are not null, then these branch roots exist and must be reinseted to the tree,
			}									// by using these functions.
			if (leftBranch != NULL) {
				reInsertBranch(leftBranch);
			}
			
			return found;
		}
	}
}

void BinaryTree::reInsertBranch(node* branchHead) {//this function is used to re-establish the position of a branch from a deleted node
	if (branchHead != NULL) { //this if statement checks just in case.
	
		if (root == NULL) { //this means the root node was deleted, and that the top of this branch should become the new root.
			root = branchHead;   //the root pointer now points to the top of this head.
		}
		else {  //if it was NOT the root pointer that was deleted:
			node* traverser = root;
			node* follower;
			bool branchSet=false;
			
			while (branchSet==false) {
				follower = traverser; //follower pointer will be one node behind the traverser pointer, so long as the traverser moves at least once
				
				if (branchHead->value > traverser->value) {					
					traverser = traverser->right;
					if (traverser == NULL) { //this means the follower is on the correct parent node, since the traverser hit NULL,
						follower->right = branchHead; //so the new node is assigned onto 
						branchSet = true;			  //the parents right link field(since the traverser had just turned right)
					}
				}
				else {
					traverser = traverser->left; 
					if (traverser == NULL) {		//the same logic is applied if the traverser pointer turns left and becomes NULL.
						follower->left = branchHead;
						branchSet = true;
					}
				}
				// There is no case of a second node with the exact same value as the branch head, because my regular insert function will not allow that.
			}	// Also the node counter stays the same, since this function only works with nodes that where already in the tree.

		}
	}
}


	