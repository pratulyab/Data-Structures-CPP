#include "BinaryTree.h"
int main(){
	BinaryTree<char> T;
//	T.createTreeIteratively();
	T.createTreeRecursively();
	cout << "\nPost Order: ";
	T.printPostOrderIteratively();
	T.printPostOrder();
	cout << "\nPre Order: ";
	T.printPreOrder();
	cout << "\nIn Order: ";
	T.printInOrder();
	cout << endl;
	T.printTreeIteratively();
/*	T.deleteAllHalfNodes();
	cout << "\nAfter Deleting All Half Nodes: ";
	T.printTreeIteratively();
	cout << "\nAfter Deleting All Leaf Nodes: ";
	T.deleteAllLeafNodes();
*/
//	T.convertMirror();
	T.printTreeIteratively();
	cout << "\nHeight Of Tree = " << T.getHeight() << endl;
	cout << "\nDiameter = " << T.diameter() << endl;
	cout << "Balanced = " << T.isBalanced() << endl;
	cout << "Nodes Without Siblings: ";
	T.printAllNodesWithoutSiblings();
	cout << T.isThereAPathSum(char('M'+'S'+'F'));
	cout << T.checkIfAllLeafNodesAreAtSameLevel();
	cout << endl << endl;
	T.prettyPrint();
	cout << endl << T.checkIfTwoNodesWithSum('F' + 'W') << endl;;
	
	cout << "\n\n**";
	vector<char> temp = T.maxRootToLeafPath();
	for(int i=0;i<temp.size();i++)
		cout << temp[i] << " ";
	cout << endl;
	return 0;
}
