// Project 7 cmpt ;238 binary tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "BinaryTree.h"
using namespace std;


int main()		// Here is created the same simple interface that I used for my other data structure projects.
{
	BinaryTree tree1 = BinaryTree();
	int choice;
	bool looper = true;
	while (looper) {
		cout << endl;
		tree1.displayPreorder();  // I like to display the tree in PREORDER form usually.
		cout << "Enter 1 to insert an integer value into the tree" << endl;
		cout << "Enter 2 to find out if a value is already in the tree" << endl;  //I display the options
		cout << "Enter 3 to get the maximum value in the tree presently " << endl;
		cout << "Enter 4 to get the minimum value in the tree presently " << endl;
		cout << "Enter 5 to delete a node with a specifice value, from the tree" << endl;
		cout << "Enter 6 to clear the tree" << endl;
		cout << "Enter 7 to display In-Order" << endl;
		cout << "Enter 8 to display Post-Order" << endl;
		cout << "Enter 9 to exit the program properly" << endl;
		cout << "Enter you choice: ";
		cin >> choice;  // the choice is determined by an integer value.

		switch (choice) { // This switch statements determines which action should be taken based on the choice value.
		case 1:
			cout << "Enter the integer, that you want to store: ";
			cin >> choice;
			tree1.insertNode(choice);
			break;
		case 2:
			cout << "What value would you like to search for ? ";
			cin >> choice;
			cout << choice << " is in the tree? " << tree1.searchNode(choice);
			break;
		case 3:
			cout << "The max in the tree is : " << tree1.getMaximum() << endl;
			break;
		case 4:
			cout << "The min in the tree is : " << tree1.getMinimum() << endl;
			break;
		case 5:
			cout << "Enter the value (integer) of the node you would like to delete: ";
			cin >> choice;
			tree1.deleteNode(choice);
			break;
		case 6:
			tree1.clearTree();
			break;
		case 7:
			tree1.displayInOrder();
			break;
		case 8:
			tree1.displayPostOrder();
			break;
		case 9:
			tree1.clearTree();
			looper = false;
			break;
		default:
			cout << "Error invalid choice"<<endl;
			break;
		}
	}
    return 0;
}

