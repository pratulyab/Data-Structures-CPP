#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include<iostream>
#include<queue>
#include<stack>
#include<vector>
using namespace std;

template<typename T>
class Node{
	T data;
	Node<T> *left,*right;
	
	public:
	Node(T d) : data(d) , left(0) , right(0) {}
	Node(const Node &N) : data(N.data) , left(0) , right(0) {}

	template<typename V>
		friend class BST;
};

template<typename T>
class BST{
	Node<T> *root;

	private:

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

	static Node<T> * clearTreeRecursively(Node<T> *node){
		if(!node)
			return NULL;
		if(!node->left && !node->right){
			delete(node);
			return NULL;
		}
		node->left = clearTreeRecursively(node->left);
		node->right = clearTreeRecursively(node->right);
		return node;
	}

	public:
	BST() : root(0) {}
	BST(const BST &BT) : root(0) {
		root = copyAs(BT.root);
	}

	//Construct BST using sorted array
	BST(const T (&ar)[10], int len) : root(0) {
		int mid=len/2;
		insertRecursively(ar[mid]);
		for(int i=mid-1;i>=0;i--){
			insertRecursively(ar[i]);
		}
		for(int i=mid+1;i<len;i++){
			insertRecursively(ar[i]);
		}
	}

	~BST() {
		root = clearTreeRecursively(root);
	}
	const BST & operator=(const BST &BT){
		root = clearTreeRecursively(root);
		root = copyAs(BT.root);
	}

	void clear(){
		if(isEmpty())
			return;
		root = clearTreeRecursively(root);
	}

	bool isEmpty() const{
		return root==NULL;
	}

	bool operator==(const BST &BT) const{
		return isSame(root,BT.root);
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

	void insertIteratively(T el){
		Node<T> *newnode = new Node<T>(el);

		Node<T> *it = root;
		Node<T> *prev = NULL;
		while(it){
			prev = it;
			if(it->data > el){
				it = it->left;
			}
			else{
				it = it->right;
			}
		}
		if(!prev){
			root = newnode;
		}
		else{
			if(prev->data > el){
				prev->left = newnode;
			}
			else{
				prev->right = newnode;
			}
		}
		return;
	}

	//Insert Iteratively
	private:
		static Node<T> * insertRecursivelyHelper(Node<T> *node,T el){
			if(!node){
				Node<T> *newnode = new Node<T>(el);
				return newnode;
			}
			if(node->data > el){
				node->left = insertRecursivelyHelper(node->left,el);
			}
			else{
				node->right = insertRecursivelyHelper(node->right,el);
			}
			return node;
		}

	public:
		void insertRecursively(T el){
			root = insertRecursivelyHelper(root,el);
			return;
		}
	
	//Find Min And Max
	private:
		static const Node<T> * findMinHelper(const Node<T> *node){
			if(!node)
				return NULL;
			
			if(!node->left){
				return node;
			}

			return findMinHelper(node->left);
		}

		static Node<T> * findMinHelper(Node<T> *node){
			if(!node)
				return NULL;
			
			if(!node->left){
				return node;
			}

			return findMinHelper(node->left);
		}

	public:
		const Node<T> * findMin() const{
			if(isEmpty())
				return NULL;
			return findMinHelper(root);
		}

		Node<T> * findMin(){
			if(isEmpty())
				return NULL;
			return findMinHelper(root);
		}

	private:
		static const Node<T> * findMaxHelper(const Node<T> *node){
			if(!node)
				return NULL;
			
			if(!node->right){
				return node;
			}

			return findMaxHelper(node->right);
		}

		static Node<T> * findMaxHelper(Node<T> *node){
			if(!node)
				return NULL;
			if(!node->right)
				return node;
			return findMaxHelper(node->right);
		}

	public:
		const Node<T> * findMax() const{
			if(isEmpty())
				return NULL;
			return findMaxHelper(root);
		}

		Node<T> * findMax() {
			if(isEmpty())
				return NULL;
			return findMaxHelper(root);
		}

	//Find Element
	private:
		static const Node<T> * findElementHelper(const Node<T> *node, const T &el){
			if(!node)
				return NULL;
			if(node->data == el){
				return node;
			}
			const Node<T> *temp;
			if(node->data > el){
				temp = findElementHelper(node->left,el);
			}
			else{
				temp = findElementHelper(node->right,el);
			}
			return temp;
		}

		static Node<T> * findElementHelper(Node<T> *node, T &el){
			if(!node)
				return NULL;
			if(node->data == el){
				return node;
			}
			Node<T> *temp;
			if(node->data > el){
				temp = findElementHelper(node->left,el);
			}
			else{
				temp = findElementHelper(node->right,el);
			}
			return temp;
		}

	public:
		const Node<T> * findElement (const T &el) const{
			if(isEmpty())
				return NULL;
			const Node<T> *temp =findElementHelper(root,el);
			if(!temp){
				cout << "\nElement Not Found" << endl;
				return NULL;
			}
			else
				cout << "Element Found" << endl;
			return temp;
		}

		Node<T> * findElement (T &el) {
			if(isEmpty())
				return NULL;
			Node<T> *temp =findElementHelper(root,el);
			if(!temp){
				cout << "\nElement Not Found" << endl;
				return NULL;
			}
			else
				cout << "Element Found" << endl;
			return temp;
		}

	//Delete Min Max
	private:
		static Node<T> * deleteMinRecursively(Node<T> *node){
			if(!node){
				return NULL;
			}
			if(!node->left){
				Node<T> *temp = node->right;
				delete(node);
				return temp;
			}
			node->left = deleteMinRecursively(node->left);
			return node;
		}
	
	public:
		void deleteMin(){
			if(isEmpty())
				return;
			root = deleteMinRecursively(root);
		}
	
	private:
		static Node<T> * deleteMaxRecursively(Node<T> *node){
			if(!node){
				return NULL;
			}
			if(!node->right){
				Node<T> *temp = node->left;
				delete(node);
				return temp;
			}
			node->right = deleteMaxRecursively(node->right);
			return node;
		}
	
	public:
		void deleteMax(){
			if(isEmpty())
				return;
			root = deleteMaxRecursively(root);
		}

	//Delete Node Iteratively

		void deleteMaxIteratively(){
			if(isEmpty())
				return;
			Node<T> *it = root;
			Node<T> *prev = NULL;

			while(it->right){
				prev = it;
				it = it->right;
			}
			delete(it);
			if(prev){
				prev->right = it->left;
			}
			else{
				root = 0;
			}
			return;
		}

		void deleteMinIteratively(){
			if(isEmpty())
				return;
			Node<T> *it = root;
			Node<T> *prev = NULL;

			while(it->left){
				prev = it;
				it = it->left;
			}
			delete(it);
			if(prev)
				prev->left = it->right;
			else
				root = 0;
			return;
		}


	//Remove Node Recursively
	private:
		static Node<T> * deleteNodeRecursivelyHelper(Node<T> *node,T el){
			if(!node)
				return NULL;
			if(node->data == el){
				if(!node->left && !node->right){
					delete node;
					return NULL;
				}
				else if(!node->left && node->right){
					Node<T> *temp = node->right;
					delete(node);
					return temp;
				}
				else if(node->left && !node->right){
					Node<T> *temp = node->left;
					delete(node);
					return temp;
				}
				else{
					Node<T> *temp = findMaxHelper(node->left);
					node->data = temp->data;
					node->left = deleteNodeRecursivelyHelper(node->left,temp->data);
				}
			}
			else if(node->data > el){
				node->left = deleteNodeRecursivelyHelper(node->left,el);
			}
			else{
				node->right = deleteNodeRecursivelyHelper(node->right,el);
			}
			return node;
		}


	public:
		void deleteNodeRecursively(T el){
			if(isEmpty())
				return;
			root = deleteNodeRecursivelyHelper(root,el);
		}

	//Size
	private:
		static int sizeHelper(const Node<T> *node){
			if(!node)
				return 0;
			return sizeHelper(node->left) + sizeHelper(node->right) + 1;
		}

	public:
		int size() const{
			return sizeHelper(root);
		}

	// Insert Duplicate
	private:
		static void insertDuplicateHelper(Node<T> *node){
			if(!node)
				return;
			Node<T> *newnode = new Node<T>(node->data);
			newnode->left = node->left;
			node->left = newnode;

			insertDuplicateHelper(newnode->left);
			insertDuplicateHelper(node->right);
		}

	public:
		void insertDuplicate(){
			if(isEmpty())
				return;
			insertDuplicateHelper(root);
		}

	// Print In Range
	private:
		static void printInRangeHelper(Node<T> *node, const T &K1, const T &K2){
			if(!node)
				return;
			if(node->data > K1 && node->data < K2){
				cout << node->data << " ";
				printInRangeHelper(node->left,K1,K2);
				printInRangeHelper(node->right,K1,K2);
			}
			else if(node->data <= K1)
				printInRangeHelper(node->right,K1,K2);
			else if(node->data >= K2)
				printInRangeHelper(node->left,K1,K2);
		}
		
	public:
		void printInRange(const T &K1, const T &K2) const{
			if(isEmpty())
				return;
			if(K1 > K2)
				printInRangeHelper(root,K2,K1);
			else
				printInRangeHelper(root,K1,K2);
		}
	
		//Inorder Successor Of A Node
	private:
		static void findInorderSuccessorHelper(const Node<T> *node, stack<const Node<T> *> &S){
			if(!node)
				return;
			if(node->right)
				findInorderSuccessorHelper(node->right,S);
			S.push(node);
			if(node->left)
				findInorderSuccessorHelper(node->left,S);
		}

	public:
		const Node<T> * findInorderSuccessor(const T &el){
			stack<const Node<T> *> S;
			findInorderSuccessorHelper(root,S);
			
			const Node<T> *ans = NULL;
			while(!S.empty()){
				const Node<T> *temp = S.top();
				S.pop();
				if(el == temp->data){
					ans = S.top();
				}
			}
			if(ans)
				cout << ans->data << endl;
			return ans;
		}

		//Update Noes With Sum Of All Nodes Above
	private:
		static void updateNodeWithSumOfAllGreaterNodesHelper(Node<T> *node,T sum){
			if(!node){
				return;
			}
			sum += node->data;
			node->data = sum;
			updateNodeWithSumOfAllGreaterNodesHelper(node->left,sum);
			updateNodeWithSumOfAllGreaterNodesHelper(node->right,sum);
		}

	public:
		void updateNodeWithSumOfAllGreaterNodes() {
			T el;
			updateNodeWithSumOfAllGreaterNodesHelper(root,0);
		}
};

#endif
