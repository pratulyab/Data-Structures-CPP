#include "BinarySearchTree.h"

int main(){
	BST<int> T;
	
	/*
	int ar[10] = {3,4,5,7,8,9,10,12,14,16};
	BST<int> T(ar,10);
	*/

	T.insertRecursively(9);
	T.insertRecursively(5);
	T.insertRecursively(14);
	T.insertRecursively(3);
	T.insertRecursively(4);
	T.insertRecursively(10);
	T.insertRecursively(12);
	T.insertRecursively(16);
	T.insertRecursively(7);
	T.insertRecursively(8);
	T.printTreeIteratively();
	T.findElement(7);
	T.deleteNodeRecursively(7);
	T.printTreeIteratively();
	T.findElement(16);
	T.findElement(7);
	T.deleteNodeRecursively(9);
	T.printTreeIteratively();
	cout << endl << "Elements Between 5 and 14: ";
	T.printInRange(5,14);
	cout << endl;
	//T.insertDuplicate();
	T.printTreeIteratively();
	T.findInorderSuccessor(8);
	T.updateNodeWithSumOfAllGreaterNodes();
	T.printTreeIteratively();
return 0;
}
