//Implementing Weighted And Directed Graph Using Adjacency List
#ifndef WD_GRAPH
#define WD_GRAPH

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

template<typename T>
class List;

template<typename T>
class wdGraph;

template <typename T>
class ListNode{
	T value;
	int weight;
	ListNode *next;
	ListNode *prev;

	public:
	ListNode() : weight(INT_MAX) , next(0) , prev(0) {}
	ListNode(T el) : value(el) , weight(INT_MAX) , next(0) , prev(0) {}
	ListNode(T el,int w) : value(el) , weight(w) , next(0) , prev(0) {}
	ListNode(const ListNode &n) : value(n.value) , weight(n.weight) , next(0) , prev(0) {}
	
	template<typename V>
	friend class List;
	
	template<typename V>
	friend class wdGraph;
	
	template<typename V>
	friend ostream & operator<<(ostream &,const List<V> &L); //because in List class ostream method we're using cout << temp->value...
											  // Since ostream is a different class we've to mention it
											  // Also because friendship of List And ListNode is not shared(Mutual Friendship X) with ostream class..!!!
};

template <typename T>
class List{
	T source;
	ListNode<T> *head;
	ListNode<T> *tail;
	
	void addVertexHelper(T el,int w){
			ListNode<T> *temp = new ListNode<T>(el,w);
			if(!head) { //!tail
				head = tail = temp;
			}
			else{
				temp->prev = tail;
				tail->next = temp;
				tail = temp;
			}
			return;
	}
	void addVertexHelper(const ListNode<T> &n){
		ListNode<T> *temp = new ListNode<T>(n);
		if(!head) { //!tail
			head = tail = temp;
		}
		else{
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
		return;
	}

	bool vertexExists(T el) const{ //Comparing Only The Values
		const ListNode<T> *it = head;
		while(it){
			if(it->value == el){
				cout << "Exists\n";
				return true;
			}
			it = it->next;
		}
		return false;
	}

	bool vertexExists(const ListNode<T> &n) const{ //Comparing Only The Values
		const ListNode<T> *it = head;
		while(it){
			if(it->value == n.value){
				cout << "Exists\n";
				return true;
			}
			it = it->next;
		}
		return false;
	}

	ListNode<T> * createList(ListNode<T> *it){
		while(it){
			if(vertexExists(*it)){
				continue;
			}
			addVertexHelper(*it);
			it = it->next;
		}
	}

	void deleteList(){
		while(head){
			ListNode<T> *temp = head;
			head = head->next;
			delete(temp);
		}
	}

	public:
	List() : head(0) , tail(0) {}
	List(T el) : source(el) , head(0) , tail(0) {}
	List(const List &L) : source(L.source) , head(0) , tail(0) {
		createList(L.head);
	}
	~List() {
		deleteList();
		head = tail = 0;
	}

	void addVertex(T el,int w){
		if(vertexExists(el)){
			return;
		}
		addVertexHelper(el,w);
	}

	template<typename V>
	friend ostream & operator<<(ostream &,const List<V> &L);
	
	template<typename V>
	friend class wdGraph;
};

template<typename V>
ostream & operator<<(ostream &out,const List<V> &L){
//	cout << L.source << " :" << endl;
	ListNode<V> *temp = L.head;
	if (!temp){
		cout << L.source << " --> NULL" << endl;
	}
	else{
		while(temp){
			cout << L.source << " --(";
			if(temp->weight == INT_MAX)
				cout << "N)--> " << temp->value << endl;
			else
				cout << temp->weight << ")--> " << temp->value << endl;
			temp = temp->next;
		}
	}
	return out;
}


template<typename T>
class wdGraph{
	vector<List<T> *> G;
	
	int getListIndex(T src) const{ //Finds A ListNode Of T Type.. Returns vector[index] if found.. else -1
		
		typename vector<List<T> *>::const_iterator it = G.begin();
		while(it!=G.end()){
			if( (*it)->source == src){ //IMP: (*it) => List<T> *
				return (it-G.begin());
			}
			it++;
		}
		return -1;
	}

	public:

	~wdGraph(){
		for(int i=0;i<G.size();i++){
			delete(G[i]);
		}
	}
	
	void addEdge(T src,T dest,int w){
		int index = getListIndex(src);
		if(index == -1){ //Means List For The Vertex Doesn't Exist
			List<T> *L = new List<T>(src);
			L->addVertex(dest,w);
			G.push_back(L);
		}
		else{
			List<T> *L = G[index];
			L->addVertex(dest,w);
		}
		
		if(src ==  dest)
			return;

		if(getListIndex(dest) == -1)
			G.push_back(new List<T>(dest));
	}

	int noOfVertices() const{
		return G.size();
	}

	//Any class inheriting or using this class' object as a data member,  must define operator- to call this fxn and also type conversion to int
	vector<vector<int> > getAdjacencyMatrix() const{
		vector<vector<int> > M;
		M.resize(noOfVertices());
		for(int i=0;i<noOfVertices();i++){
			M[i].resize(noOfVertices(),INT_MAX);
		}
		typename vector<List<T> *>::const_iterator it = G.begin();
		T base = (*it)->source;
		it++;
		while(it != G.end()){
			T temp = (*it)->source;
			if(temp < base)
				base = temp;
			it++;
		}

		it = G.begin();
		while(it != G.end()){
			int src = (*it)->source - base;
			const ListNode<T> *temp = (*it)->head;
			while(temp){
				int dest = temp->value - base;
				M[src][dest] = temp->weight;
				temp = temp->next;
			}
			it++;
		}
		return M;
	}

	//Classes Should Define < operator for this fxn
	vector<T> getVerticesInAscendingOrder() const{
		vector<T> temp;
		typename vector<List<T> *>::const_iterator it = G.begin();
		while(it != G.end()){
			temp.push_back((*it)->source);
			it++;
		}
		temp.shrink_to_fit();
		sort(temp.begin(),temp.end());
		return temp;
	}

	template<typename V>
	friend ostream & operator<<(ostream &, const wdGraph<V> &Gr);
};

template<typename V>
ostream & operator<<(ostream &out, const wdGraph<V> &Gr){
	typename vector<List<V> *>::const_iterator it = Gr.G.begin();
	while(it != Gr.G.end()){
		cout << *(*it); //IMP: *it => List<V> *
		it++;
	}
	return out;
}

#endif
