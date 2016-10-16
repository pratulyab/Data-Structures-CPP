#include "GenericTree.h"

int main(){
	GenericTree<char> T;
	T.createTreeRecursively();
	//T.createTreeIteratively();
	cout << "Iteratively: ";
	T.printIteratively();
	cout << endl;
	cout << "Recursively: ";
	cout << endl;
	T.printRecursively();
	cout << "\n\n";
	cout << "Level Order\n";
	T.printLevelOrder();
	cout << "\n\n Post Order: ";
	T.printPostOrderRecursively();
	cout << endl;
	T.printPostOrderIteratively();
	cout << endl;
	T.printZigZagLevelOrder();

	cout << "Just Greater = " << T.getData(T.findJustLargerThanK('E')) << endl;
	cout << "LCA = " << T.getData(T.findLeastCommonAncestor('E','K')) << endl;
	cout << "Height = " << T.getHeight();

	cout << endl << "At Depth 3: ";
	T.printAllElementsAtDepthK(3);
	
	cout << endl << "Largest Node = " << T.getData(T.findNodeWithLargestData());

	cout << endl << "Second Largest Node = " << T.getData(T.nodeWithSecondLargestData());

	cout << endl << "Nodes Greater Than Root = " << T.countNodesWithDataGreaterThanRoot();

	cout << endl << "Leaf Nodes = " << T.countLeafNodes();

	cout << endl << "Special Node = " << T.getData(T.findSomeSpecialNode());

	GenericTree<char> T1(T);
	cout << endl << (T==T1);

	cout << "\nLevel Order\n";
	T1.printLevelOrder();

	cout << T.isThereARootToLeafPathWithSumK(char('A'+'B'+'X'+'P'));

/*	
	GenericTree<char> T2;
	T2.createTreeIteratively();
	cout << "Level Order\n";
	T2.printLevelOrder();
	
	cout << (T2 == T1);

	T2 = T1;

	cout << (T2 == T1);*/
return 0;
}
