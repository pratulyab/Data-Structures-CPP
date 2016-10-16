#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include<iostream>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
template <typename T>
class Node{
	T data;
	Node *left , *right;

	public:
	Node(T d) : data(d) , left(0) , right(0) {}
	Node(const Node &N) : data(N.data) , left(0) , right(0) {}

	template<typename V>
		friend class BinaryTree;
};

template <typename T>
class BinaryTree{
	Node<T> *root;

	static Node<T> * copyAs(const Node<T> *node){
		if(!node)
			return NULL;
		Node<T> *newnode = new Node<T>(*node);
		
		newnode->left = copyAs(node->left);
		newnode->right = copyAs(node->right);

		return newnode;
	}

	static bool isSame(const Node<T> *node1, const Node<T> *node2){
		if(!node1 && !node2)
			return true;

		if( (!node1 && node2) || (node1 && !node2) ){
			return false;
		}

		if(node1->data != node2->data){
			return false;
		}

		bool verdictLeft = isSame(node1->left,node2->left);
		bool verdictRight = isSame(node1->right,node2->right);

		if(!(verdictLeft && verdictRight)){
			return false;
		}
		return true;
	}

	public:
	BinaryTree() : root(0) {}
	BinaryTree(const BinaryTree &BT) : root(0) {
		root = copyAs(BT.root);
	}
	~BinaryTree() {
		deleteTreeRecursively(root);
	}
	const BinaryTree & operator=(const BinaryTree &BT){
		deleteTreeRecursively(root);
		root = copyAs(BT.root);
	}

	bool isEmpty() const{
		return root==NULL;
	}

	bool operator==(const BinaryTree &BT) const{
		return isSame(root,BT.root);
	}

	const T & getData(const Node<T> *node) const{
		return node->data;
	}

	T getData(Node<T> *node){
		return node->data;
	}

	
	/*
		createTree --> Recursively + Iteratively
		deleteTree --> Recursively + Iteratively
		printTreeIteratively
	*/

	private:
	static Node<T> * createTreeRecursivelyHelper(){
		cout << "Enter Data: ";
		T el;
		cin >> el;

		Node<T> *root = new Node<T>(el);

		cout << "Add Left Node For " << el << " ?(y/n) ";
		char ch;
		cin >> ch;
		if(ch=='y' || ch=='Y'){
			root->left = createTreeRecursivelyHelper();
		}
		cout << "Add Right Node For " << el << " ?(y/n) ";
		cin >> ch;
		if(ch=='y' || ch=='Y'){
			root->right = createTreeRecursivelyHelper();
		}
		return root;
	}

	static Node<T> * deleteTreeRecursively(Node<T> *node){
		if(!node)
			return NULL;
		if(!node->left && !node->right){
			delete(node);
			return NULL;
		}
		node->left = deleteTreeRecursively(node->left);
		node->right = deleteTreeRecursively(node->right);
		return node;
	}

	public:
	void createTreeRecursively() {
		if(!isEmpty()){
			cout << "Tree Already Exists" << endl;
			return;
		}
		root = createTreeRecursivelyHelper();
	}

	void createTreeIteratively() {
		if(!isEmpty()){
			cout << "Tree Already Exists" << endl;
			return;
		}
		queue<Node<T> *> Q;
		T el;
		cout << "Enter Data For Root: ";
		cin >> el;
		root = new Node<T>(el);
		Q.push(root);

		while(!Q.empty()){
			Node<T> *temp = Q.front();
			Q.pop();
			
			char ch;
			cout << "Is There A Left Node Of " << temp->data << " ?(y/n)";
			cin >> ch;
			if(ch=='y' || ch=='Y'){
				cout << "Enter Data: ";
				T d;
				cin >> d;
				temp->left = new Node<T>(d);
				Q.push(temp->left);
			}

			cout << "Is There A Right Node Of " << temp->data << " ?(y/n)";
			cin >> ch;
			if(ch=='y' || ch=='Y'){
				cout << "Enter Data: ";
				T d;
				cin >> d;
				temp->right = new Node<T>(d);
				Q.push(temp->right);
			}
		}
	}

	void deleteTreeRecursively(){
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
		root = deleteTreeRecursivelyHelper(root);
	}

	void deleteTreeIteratively(){
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
		queue<Node<T> *> Q;
		Q.push(root);
		root = NULL;
		while(!Q.empty()){
			Node<T> *temp = Q.front();
			Q.pop();
			if(temp->left){
				Q.push(temp->left);
			}
			if(temp->right){
				Q.push(temp->right);
			}
			temp->left = temp->right = 0;
			delete(temp);
		}
		return;
	}

	void printTreeIteratively() const{
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
		cout << endl;
		queue<const Node<T> *> Q;
		Q.push(root);
		Q.push(NULL);

		while(!Q.empty()){
			const Node<T> *temp = Q.front();
			Q.pop();
			if(temp == NULL){
				if(!Q.empty()){
					cout << endl;
					Q.push(NULL);
				}
				continue;
			}

			cout << temp->data << " ";
			if(temp->left)
				Q.push(temp->left);
			if(temp->right)
				Q.push(temp->right);
		}
		cout << endl;
	}
	
	// print--> PostOrder,PreOrder,InOrder Recursively
	private:
	
	static void printPostOrderHelper(const Node<T> *node){
		if(!node)
			return;
		printPostOrderHelper(node->left);
		printPostOrderHelper(node->right);
		cout << node->data << " ";
	}
	static void printInOrderHelper(const Node<T> *node){
		if(!node)
			return;
		printInOrderHelper(node->left);
		cout << node->data << " ";
		printInOrderHelper(node->right);
	}
	static void printPreOrderHelper(const Node<T> *node){
		if(!node)
			return;
		cout << node->data << " ";
		printPreOrderHelper(node->left);
		printPreOrderHelper(node->right);
	}

	public:

	void printPostOrder() const{
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
		printPostOrderHelper(root);
	}

	void printInOrder() const{
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
		printInOrderHelper(root);
	}

	void printPreOrder() const{
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
		printPreOrderHelper(root);
	}
	
	//Iterative Post Order
	void printPostOrderIteratively() const{
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
		stack<const Node<T> *> S,Sprint;
		S.push(root);

		while(!S.empty()){
			const Node<T> *temp = S.top();
			S.pop();
			cout << temp->data;
			Sprint.push(temp);
			if(temp->left)
				S.push(temp->left);
			if(temp->right)
				S.push(temp->right);
		}
		cout << endl << endl << endl << endl;
		while(!Sprint.empty()){
			cout << Sprint.top()->data << " ";
			Sprint.pop();
		}
		cout << endl;
	}

	//Delete All Leaf Nodes
	private:
		static Node<T> * deleteAllLeafNodesHelper(Node<T> *node){
			if(!node)
				return NULL;
			if(!node->left && !node->right){
				delete(node);
				return NULL;
			}
			node->left = deleteAllLeafNodesHelper(node->left);
			node->right = deleteAllLeafNodesHelper(node->right);
			return node;
		}
	public:
		void deleteAllLeafNodes(){
			if(isEmpty()){
				cout << "NULL Tree" << endl;
				return;
			}
			root = deleteAllLeafNodesHelper(root);
		}

	//Delete All Half Nodes
	private:
		static Node<T> * deleteAllHalfNodes(Node<T> *node){
			if(!node)
				return NULL;
			if((!node->left && node->right) || (node->left && !node->right))
			{
				Node<T> *temp = NULL;
				if(node->left){
					temp = deleteAllHalfNodes(node->left);
				}
				if(node->right){
					temp = deleteAllHalfNodes(node->right);
				}
				delete(node);
				return temp;
			}
			node->left = deleteAllHalfNodes(node->left);
			node->right = deleteAllHalfNodes(node->right);
			return node;
		}
	
	public:
		void deleteAllHalfNodes() {
			if(isEmpty()){
				cout << "NULL Tree" << endl;
				return;
			}
			root = deleteAllHalfNodes(root);
		}

	// Diameter Of Tree

	private:
		static pair<int,int> diameterHelper(Node<T> *node){ //pair(height,Lsum)
			if(!node)
				return make_pair(0,-1);
			/*
				0
			   /
			  0
			 / \
			0	0
		   / \	 \
		  0	  0	  0
		   \	   \
			0	    0
		*/
			pair<int,int> l = diameterHelper(node->left);
			pair<int,int> r = diameterHelper(node->right);
			int height = (l.first>r.first?l.first:r.first) + 1;

			int dia = l.second > r.second ? l.second : r.second;
			
			int largest = dia > (l.first+r.first+1) ? dia : (l.first+r.first+1);

			return make_pair(height,largest);
			
		}

	public:

		int diameter() const{
			return diameterHelper(root).second;
		}

	//Mirror
	private:
		static Node<T> * convertMirrorHelper(Node<T> *node){
			if(!node){
				return NULL;
			}
			if(!node->left && !node->right){
				return node;
			}
			Node<T> *tempL = convertMirrorHelper(node->left);
			Node<T> *tempR = convertMirrorHelper(node->right);
			node->left = tempR;
			node->right = tempL;

			return node;
		}
	public:
		void convertMirror(){
			convertMirrorHelper(root);
		}

	//Height
	private:
		static int getHeightHelper(const Node<T> *node){
			if(!node)
				return 0;
			int l = getHeightHelper(node->left);
			int r = getHeightHelper(node->right);
			return ((l>r?l:r)+1);
		}

	public:
		int getHeight() const{
			return getHeightHelper(root);
		}

	//isBalanced
	private:
		static pair<int,bool> isBalancedHelper(Node<T> *node){
			if(!node)
				return make_pair(0,true);
			pair<int,bool> lverdict = isBalancedHelper(node->left);
			pair<int,bool> rverdict = isBalancedHelper(node->right);
			
			int height = (lverdict.first > rverdict.first ? lverdict.first : rverdict.first) + 1;
			
			if(!(lverdict.second && rverdict.second))
				return make_pair(height,false);

			int diff = lverdict.first - rverdict.first;
			return make_pair(height , (diff>=-1 && diff<=1));
		}

	public:
		bool isBalanced() const{
			
			pair<int,bool> temp = isBalancedHelper(root);
			cout << temp.first;
			return temp.second;
		}

	//Print Nodes W/O Siblings
	private:
		static void printAllNodesWithoutSiblingsHelper(const Node<T> *node){
			if(!node)
				return;
			bool siblings = true;;
			if( (!node->left && node->right) || (node->left && !node->right)){
				siblings = false;
			}
			if(!siblings){
				if(node->left)
					cout << node->left->data << " ";
				if(node->right)
					cout << node->right->data << " ";
			}
			printAllNodesWithoutSiblingsHelper(node->left);
			printAllNodesWithoutSiblingsHelper(node->right);
		}
		
	public:
		void printAllNodesWithoutSiblings() const{
			if(isEmpty()){
				cout << "NULL Tree" << endl;
				return;
			}
			printAllNodesWithoutSiblingsHelper(root);
			cout << endl;
		}

	//Is There A Path With Sum
	private:
		static bool isThereAPathSumHelper(const Node<T> *node,const T &sum,T add){
			if(!node){
				return false;
			}
			add += node->data;
			if(!node->left && !node->right){
				if(add==sum)
					return true;
				else
					return false;
			}
			bool l = isThereAPathSumHelper(node->left,sum,add);
			bool r = isThereAPathSumHelper(node->right,sum,add);
			if(l || r)
				return true;
			else
				return false;
		}

	public:
		bool isThereAPathSum(const T &sum) const{
			if(isEmpty()){
				cout << "NULL Tree" << endl;
				return false;
			}
			T add;
			return isThereAPathSumHelper(root,sum,add);
		}

	//Check If All Leaf Nodes Are At Same Level
	public:
		bool checkIfAllLeafNodesAreAtSameLevel() const{
			if(isEmpty()){
				cout << "NULL Tree" << endl;
				return false;
			}
			queue<const Node<T> *> Qit;
			Qit.push(root);
			Qit.push(NULL);

			int ar[100] = {0};
			int index = 0;
			int count = 0;

			while(!Qit.empty()){
				const Node<T> *temp = Qit.front();
				Qit.pop();

				if(!temp){
					if(!Qit.empty()){
						Qit.push(NULL);
					}
					ar[index] = count;
					count = 0;
					index++;
					continue;
				}

				if(!temp->left && !temp->right){
					count++;
				}
				if(temp->left)
					Qit.push(temp->left);
				if(temp->right)
					Qit.push(temp->right);
			}
			int leaf = 0;
			cout << "\n*";
			for(int i=0;i<index;i++){
				if(ar[i])
					leaf++;
			}
		
		return (leaf==1);
		}

	// Check Sum Of Two Nodes
	public:
		bool checkIfTwoNodesWithSum(const T &sum) const{
			if(isEmpty()){
				return false;
			}
			queue<const Node<T> *> Q;
			vector<T> V;
			Q.push(root);
			while(!Q.empty()){
				const Node<T> *temp = Q.front();
				Q.pop();
				V.push_back(temp->data);
				if(temp->left)
					Q.push(temp->left);
				if(temp->right)
					Q.push(temp->right);
			}
			bool found = false;
			for(int i=0;i<V.size();i++){
				
				for(int j=i;j<V.size();j++){
					T add = V[i]+ V[j];
					if(add == sum){
						found = true;
					}
				}
			}
			return found;
		}


	//Maximum Sum Path In Vector
	private:
		static pair<T,vector<T> > maxRootToLeafPathHelper(const Node<T> *node,T sum, vector<T> V){
			if(!node){
				vector<T> V;
				T el;
				return make_pair(el,V);
			}
			
			V.push_back(node->data);
			sum += node->data;

			if(!node->left && !node->right){
				return make_pair(sum,V);
			}

			pair<T,vector<T> > l = maxRootToLeafPathHelper(node->left,sum,V);
			pair<T,vector<T> > r = maxRootToLeafPathHelper(node->right,sum,V);

			pair<T,vector<T> > temp = l.first > r.first ? l : r;
			
			pair<T,vector<T> > final = sum > temp.first ? make_pair(sum,V) : temp;
			
			return final;
		}

	public:
		vector<T> maxRootToLeafPath() const{
			vector<T> V;
			T sum;
			V = maxRootToLeafPathHelper(root,sum,V).second;
			return V;
		}

	//Pretty Print
	/*
	void prettyPrint() const{
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
		int spacer = 1;
		int asd = spacer;
		int height = getHeightHelper(root);
		queue<const Node<T> *> Q;
		queue<char> Qslash;
		Q.push(root);
		Q.push(NULL);
		for(int i=spacer;i<2*height-1;i++){
			cout << " ";
		}
		while(!Q.empty()){
			const Node<T>* temp = Q.front();
			Q.pop();
			if(temp==NULL){
				if(!Q.empty()){
					cout << endl;
					spacer++;
					for(int i=spacer;i<2*height-1;i++)
						cout << " ";
					while(!Qslash.empty()){
						cout << Qslash.front() << " ";
						
						Qslash.pop();
					}
					cout << endl;
					Q.push(NULL);
					for(int i=spacer+1;i<2*height-1;i++)
						cout << " ";
					asd = spacer;
					spacer++;
				}
				continue;
			}

			cout << temp->data << " ";
			for(int i=asd;i<2*height-1;i++)
				cout << " ";
			if(temp->left){
				Qslash.push('/');
				Q.push(temp->left);
			}
			else
				Qslash.push(' ');

			if(temp->right){
				Qslash.push('\\');
				Q.push(temp->right);
			}
			else
				Qslash.push(' ');
		}
		return;
	}*/

	void prettyPrint() const{
		int height = getHeightHelper(root);
		int leftSpace = height;
		int middleSpace = 1;
		for(int i=leftSpace;i>0;i--)
			cout << " ";
		queue<Node<T> *>  Q;
		queue<char> Qslash;

		Q.push(root);
		Q.push(NULL);

		while(!Q.empty()){
			Node<T> *temp = Q.front();
			Q.pop();

			if(temp == NULL){
				if(!Q.empty()){
					cout << endl;
					Q.push(NULL);

					leftSpace--;
					for(int i=leftSpace;i>0;i--)
						cout << " ";
					leftSpace--;

					while(!Qslash.empty()){
						cout << Qslash.front();
						Qslash.pop();
					}

					cout << endl;

					for(int i=leftSpace;i>0;i--){
						cout << " ";
					}
				}
				middleSpace += 2;
				continue;
			}

			bool lprint = false;
			bool rprint = false;

			cout << temp->data;

			if(temp->left){
				Q.push(temp->left);
				Qslash.push('/');
				Qslash.push(' ');
				lprint = true;
			}
			else{
				Qslash.push(' ');
				Qslash.push(' ');
			}
			
			for(int i=middleSpace;i>0;i--)
				cout << " ";
			
			if(temp->right){
				Q.push(temp->right);
				Qslash.push('\\');
				for(int i=middleSpace;i>0;i--)
					Qslash.push(' ');
				rprint = true;
			}
			else{
				for(int i=middleSpace-1;i>0;i--)
					Qslash.push(' ');
			}
		}
	}

};

#endif
