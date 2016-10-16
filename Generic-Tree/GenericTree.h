#ifndef GENERIC_TREE_H
#define GENERIC_TREE_H
#include<iostream>
#include<queue>
#include<vector>
#include<stack>
using namespace std;

template <typename T>
class Node {
	T data;
	vector<Node<T> *> children; // Ensured That NULL Is Not Inserted

	public:
	Node(T el) : data(el) , children(0) {}
	Node(const Node &N) : data(N.data) , children(0) {
		
	}
	template<typename V>
		friend class GenericTree;
};



template <typename T>
class GenericTree {
	Node<T> *root;

	/*
	copyAs --> Recursively + Iteratively
	deleteTree --> Recursively + Iteratively
	isSame()
	*/
	private:
	Node<T> * copyAsRecursively(const Node<T> *node){
		if(!node)
			return NULL;
		
		Node<T> *temp = new Node<T>(node->data);

		for(int i=0;i<node->children.size();i++){
			Node<T> *child = copyAsRecursively(node->children[i]);
			if(child)
				temp->children.push_back(child);
		}
		return temp;
	}

	void copyAsIteratively(const GenericTree &GT){
		if(!GT.root)
			return;

		root = new Node<T>(GT.root->data);
		
		queue<const Node<T> *> Q_src;
		queue<Node<T> *> Q_dest;
		
		Q_src.push(GT.root);
		Q_dest.push(root);

		while(!Q_src.empty()){
			const Node<T> *temp_src = Q_src.front();
			Node<T> *temp_dest = Q_dest.front();
			Q_src.pop();
			Q_dest.pop();

			for(int i=0;i<temp_src->children.size();i++){
				Node<T> *newnode = new Node<T>(temp_src->children[i]->data);
				temp_dest->children.push_back(newnode);
				
				Q_src.push(temp_src->children[i]);
				Q_dest.push(newnode);
			}
		}
		return;
	}

	void deleteTreeRecursively(Node<T> *node){
		if(!node)
			return;
		if(node->children.empty()){
			delete(node);
			return;
		}
		for(int i=0;i<node->children.size();i++){
			deleteTreeRecursively(node->children[i]);
			if(i+1 == node->children.size()){
				node->children.clear();
			}
		}
		return;
	}

	void deleteTreeIteratively(){
		if(!root)
			return;
		
		stack<Node<T> *> S;
		queue<Node<T> *> Q;
		Q.push(root);
		while(!Q.empty()){
			Node<T> *temp = Q.front();
			S.push(temp);
			Q.pop();
			for(int i=0;i<temp->children.size();i++){
				Q.push(temp->children[i]);
				if(i+1 == temp->children.size()){
					temp->children.clear();
				}
			}
		}

		while(!S.empty){
			Node<T> *temp = S.top();
			S.pop();
			delete(temp);
		}
	}

	bool isSame(const Node<T> *node1,const Node<T> *node2) const{
		if(!node1 && !node2)
			return true;
		
		if((node1 && !node2) || (!node1 && node2))
			return false;
		
		if(node1->data != node2->data)
			return false;

		if(node1->children.size() != node2->children.size())
			return false;

		bool verdict = true;
		for(int i=0;i<node1->children.size();i++){
			verdict = isSame(node1->children[i],node2->children[i]);
			if(!verdict)
				return verdict;
		}
		return verdict;
	}
	

	public:
	GenericTree() : root(0) {}
	GenericTree(const GenericTree &GT) : root(0) {
		root = copyAsRecursively(GT.root);
		//copyAsIteratively(GT);
	}
	~GenericTree() {
		deleteTreeRecursively(root);
		//deleteTreeIteratively();
	}
	const GenericTree & operator=(const GenericTree & GT){
		//deleteTreeRecursively(root);
		deleteTreeIteratively();
		//root = copyAsRecursively(GT.root);
		copyAsIteratively(GT);
		return *this;
	}

	bool isEmpty() const{
		return root==NULL;
	}

	T getData(const Node<T> *node){
		return node->data;
	}

	const T & getData(const Node<T> *node) const{
		return node->data;
	}

	bool operator==(const GenericTree &GT) const{
		return isSame(root,GT.root);
	}
	
	/*
	createTree --> Recursive + Iterative
	Print Iteratively & Recursively
	PrintPostOrder--> Recursive + Iterative
	Level Order Printing
	ZigZag Printing
	*/
	private:
	static Node<T> *createTreeRecursivelyHelper(){
		cout << "Enter Data: ";
		T d;
		cin >> d;
		Node<T> *newnode = new Node<T>(d);
		
		char ch;
		cout << "Want To Add Child For " << d << " ?(y/n) ";
		cin >> ch;

		while(ch=='y' || ch=='Y'){
			Node<T> *child = createTreeRecursivelyHelper();
			newnode->children.push_back(child);
			cout << "Want To Add Child For " << d << " ?(y/n) ";
			cin >> ch;
		}
		return newnode;
	}

	static void printPostOrderRecursivelyHelper(const Node<T> *node){
		if(!node)
			return;
		for(int i=0;i<node->children.size();i++)
			printPostOrderRecursivelyHelper(node->children[i]);
		cout << node->data << " ";
	}

	static void printRecursivelyHelper(const Node<T> *node){
		if(!node)
			return;
		cout << node->data << " ";
		for(int i=0;i<node->children.size();i++)
			printRecursivelyHelper(node->children[i]);
	}

	public:
	void createTreeRecursively(){
		if(!isEmpty()){
			cout << "Tree Already Exists (Recursively)" << endl;
			return;
		}
		root = createTreeRecursivelyHelper();
	}

	void createTreeIteratively(){
		if(!isEmpty()){
			cout << "Tree Already Exists (Iteratively)" << endl;
			return;
		}
		cout << "Enter Data For Root: ";
		T d;
		cin >> d;
		root = new Node<T>(d);
		queue<Node<T> *> Q;
		Q.push(root);
		
		while(!Q.empty()){
			Node<T> *temp = Q.front();
			Q.pop();
			
			int child_count;
			cout << "Enter How Many Children Does " << temp->data << " Have: ";
			cin >> child_count;

			for(int i=0;i<child_count;i++){
				cout << "Enter Data For " << i+1 << " Child Of " << temp->data << ": ";
				T el;
				cin >> el;
				Node<T> *child = new Node<T>(el);
				temp->children.push_back(child);
				Q.push(child);
			}
		}
		cout << endl;
	}

	void printPostOrderRecursively() const{
		printPostOrderRecursivelyHelper(root);
		cout << endl;
	}

	void printPostOrderIteratively() const{
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
		stack<Node<T> *> S,Sprint;
		
		S.push(root);

		while(!S.empty()){
			Node<T> *temp = S.top();
			S.pop();
			Sprint.push(temp);

			for(int i=0;i<temp->children.size();i++){
				S.push(temp->children[i]);
			}
		}

		while(!Sprint.empty()){
			cout << Sprint.top()->data << " ";
			Sprint.pop();
		}
	return;
	}

	void printLevelOrder() const{
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
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

			for(int i=0;i<temp->children.size();i++){
				Q.push(temp->children[i]);
			}
		}
		cout << endl;
		
	}

	void printIteratively() const{
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
		queue<const Node<T> *> Q;
		Q.push(root);
		while(!Q.empty()){
			const Node<T> *temp = Q.front();
			Q.pop();
			cout << temp->data << " ";
			for(int i=0;i<temp->children.size();i++){
				Q.push(temp->children[i]);
			}
		}
	}

	void printRecursively() const{
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
		printRecursivelyHelper(root);
	}

	void printZigZagLevelOrder() const{
		if(isEmpty()){
			cout << "NULL Tree" << endl;
			return;
		}
		queue<const Node<T> *> Q;
		vector<const Node<T> *> Vprint;
		stack<const Node<T> *> S;
		Q.push(root);
		Q.push(NULL);
		Vprint.push_back(root);
		Vprint.push_back(NULL);
		int counter = 0;

		while(!Q.empty()){
			const Node<T> *temp = Q.front();
			Q.pop();
			bool move = (Q.front() == NULL);
			if(temp == NULL){
				if(!Q.empty()){
					Vprint.push_back(NULL);
					Q.push(NULL);
					counter++;
					continue;
				}
			}
			if(!temp){
				Vprint.push_back(NULL);
				continue;
			}
			for(int i=0;i<temp->children.size();i++){
				Q.push(temp->children[i]);

				if(counter % 2 == 0){
					S.push(temp->children[i]);
				}
				else{
					Vprint.push_back(temp->children[i]);
				}
			}
			while(!S.empty() && move){
				Vprint.push_back(S.top());
				S.pop();
			}
		}
		
		for(int i=0;i<Vprint.size();i++){
			if(Vprint[i] == NULL){
				cout << endl;
				continue;
			}
			cout << Vprint[i]->data << " ";
		}
	}

	//Height Of Tree
	private:
		static int heightOfTree(const Node<T> *node){
			if(!node)
				return 0;
			int height = 0;
			for(int i=0;i<node->children.size();i++){
				int temp = heightOfTree(node->children[i]) + 1;
				if(temp > height)
					height = temp;
			}
			return height;
		}
	public:
		int getHeight() const{
			return heightOfTree(root)+1;
		}

	//Node With Largest Data
	private:
		static const Node<T> * largestNodeHelper(const Node<T> *node){
			if(!node)
				return NULL;
			const Node<T> *largest = node;
			
			for(int i=0;i<node->children.size();i++){
				const Node<T> *temp = largestNodeHelper(node->children[i]);
				if(temp->data > largest->data)
					largest = temp;
			}
			return largest;
		}

	public:
		const Node<T> * findNodeWithLargestData() const{
			return largestNodeHelper(root);
		}

	//Print Elements At Depth K
	private:
		static void printAtDepthK(const Node<T> *node,int k){
			if(!node)
				return;
			else if(k==1){
				cout << node->data << " ";
				return;
			}
			for(int i=0;i<node->children.size();i++){
				printAtDepthK(node->children[i],k-1);
			}
		}

	public:
		void printAllElementsAtDepthK(int k) const{
			printAtDepthK(root,k);
			cout << endl;
		}

	//Number Of Nodes With Data Greater Than Root
	private:
		static int nodesGreaterThanRoot(const Node<T> *node,const Node<T> *root){
			if(!node)
				return 0;
			int count = 0;	
			for(int i=0;i<node->children.size();i++){
				count += nodesGreaterThanRoot(node->children[i],root);
				if(node->children[i]->data > root->data)
					count++;
			}
			return count;
		}

	public:
		int countNodesWithDataGreaterThanRoot() const{
			return nodesGreaterThanRoot(root,root);
		}

	//Number Of Leaf Nodes
	private:
		static int countLeafNodesHelper(const Node<T> *node){
			if(!node)
				return 0;

			if(node->children.empty()){
				return 1;
			}
			int count = 0;
			for(int i=0;i<node->children.size();i++){
				count += countLeafNodesHelper(node->children[i]);
			}
			return count;
		}

	public:
		int countLeafNodes() const{
			return countLeafNodesHelper(root);
		}

	//Second Largest Data
	private:
		pair<const Node<T> *, const Node<T> *> secondLargestNode(const Node<T> *node) const{
			const Node<T> *largest = node;
			const Node<T> *slargest = NULL;
			pair<const Node<T> *, const Node<T> *> final = make_pair(largest,slargest);

			if(!node || node->children.size()==0)
				return final;

			for(int i=0; i<node->children.size();i++){
				pair<const Node<T> *, const Node<T> *> semifinal = secondLargestNode(node->children[i]);
				if(semifinal.first->data > final.first->data){
					if(!semifinal.second){
						final.second = final.first;
						final.first = semifinal.first;
					}
					else if(semifinal.second->data < final.first->data){
						final.second = final.first;
						final.first = semifinal.first;
					}
					else
						final = semifinal;
				}
				else if(!final.second || semifinal.first->data > final.second->data){
						final.second = semifinal.first;
						continue;
					}
				
				if(semifinal.second && semifinal.second->data > final.second->data){
					final.second = semifinal.second;
				}
			}
		return final;
		}
		
	public:
		const Node<T> * nodeWithSecondLargestData() const{
			return secondLargestNode(root).second;
		}

	//Maximum Sum Of Node + Children
	private:
		pair<T, const Node<T> *> maxImmediateSum(const Node<T> *node) const{
			if(!node){
				pair<T, const Node<T> *> temp;
				temp.second = NULL;
				return temp;
			}
			
			T sum = node->data;	
			for(int i=0;i<node->children.size();i++){
				if(!node->children[i])
					continue;
				sum += node->children[i]->data;
			}
			
			pair<T, const Node<T> *> largest = make_pair(sum,node);

			for(int i=0;i<node->children.size();i++){
				pair<T, const Node<T> *> temp = maxImmediateSum(node->children[i]);
				if(temp.first > largest.first){
					largest = temp;
				}
			}
			return largest;
		}

	public:
		const Node<T> * findSomeSpecialNode() const{
			return maxImmediateSum(root).second;
		}

	//Node Just Greater Than K
	private:
		static const Node<T> *findJustLargerThanKHelper(const Node<T> *node,const T &el){
			if(!node)
				return NULL;
			const Node<T> *larger = node;

			for(int i=0;i<node->children.size();i++){
				const Node<T> *temp = findJustLargerThanKHelper(node->children[i],el);
				if(temp->data > el){
					if(larger->data > el){
						if(temp->data < larger->data)
							larger = temp;
					}
					else
						larger = temp;
				}
			}
			return larger;
		}

	public:
		const Node<T> *findJustLargerThanK(const T & K) const{
			if(isEmpty())
				return NULL;
			return findJustLargerThanKHelper(root,K);
		}

	//Least Common Ancestor
	private:
		static bool fillPathInStack(const Node<T> *root,const T &el,stack<const Node<T>* >&S){
			if(!root)
				return false;

			S.push(root);
			
			if(root->data == el)
				return true;

			for(int i=0;i<root->children.size();i++){
				bool verdict = fillPathInStack(root->children[i],el,S);
				if(verdict)
					return true;
			}

			S.pop();
			return false;
		}

		static const Node<T> * LCAHelper(const Node<T> *root, const T &el1, const T &el2){
			if(!root)
				return NULL;
			stack<const Node<T> *> S1,S2,S3,S4;

			fillPathInStack(root,el1,S1);
			fillPathInStack(root,el2,S2);

			while(!S1.empty()){
				S3.push(S1.top());
				S1.pop();
			}
			while(!S2.empty()){
				S4.push(S2.top());
				S2.pop();
			}

			const Node<T> *prev = NULL;

			while(!S3.empty() && !S4.empty()){
				if(S3.top() != S4.top()){
					break;
				}
				prev = S3.top();
				S3.pop();
				S4.pop();
			}
			return prev;
		}

	public:
		const Node<T> * findLeastCommonAncestor(const T &el1,const T &el2) const{
		if(isEmpty())
			return NULL;
		return LCAHelper(root,el1,el2);
		}

	//Root To Leaf Sum K Path
	private:
		static bool rootToLeafSumK(const Node<T> *root,const T &k,T sum){
			if(!root){
				return false;
			}
			sum += root->data;
			if(root->children.size() == 0 && sum == k){
				return true;
			}
			for(int i=0;i<root->children.size();i++){
				if(rootToLeafSumK(root->children[i],k,sum))
					return true;
			}
			return false;

		}

	public:
		bool isThereARootToLeafPathWithSumK(const T &k) const{
			if(isEmpty())
				return false;
			T sum = 0;
			return rootToLeafSumK(root,k,sum);
		}
};
#endif
