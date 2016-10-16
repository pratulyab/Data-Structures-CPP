#include "DLLNode.h"

template <typename T>
class DoubleLinkedList{
	DLLNode<T> *head;
	DLLNode<T> *tail;
	
	void createDoubleList(const DoubleLinkedList &DLL){
		const DLLNode<T> *it = DLL.head;
		while(it){
			DLLNode<T> *temp = new DLLNode<T>(*it);
			if(!head) { //!tail
				head = tail = temp;
			}
			else{
				temp->prev = tail;
				tail->next = temp;
				tail = temp;
			}
			it = it->next;
		}
	return;
	}

	void deleteDoubleList(){
		while(head){
			DLLNode<T> *temp = head;
			head = head->next;
			delete(head);
		}
		tail = 0; //Dangling Pointer
	return;
	}

	static void  printDoubleListHelper(DLLNode<T> *head){
		while(head){
			cout << head->data << "-->";
			head = head->next;
		}
		cout << "NULL" << endl;
	return;
	}

	public:
	DoubleLinkedList() : head(0) , tail(0) {}
	DoubleLinkedList(const DoubleLinkedList &DLL) {
		deleteDoubleList();
		createDoubleList(DLL);
	}
	~DoubleLinkedList() { deleteDoubleList(); }
	
	DoubleLinkedList & operator=(const DoubleLinkedList &DLL){
		deleteDoubleList();
		createDoubleList(DLL);
		return *this;
	}

	const DLLNode<T> * begin() const{
		return head;
	}

	const DLLNode<T> *end() const{
		return tail;
	}

	bool isEmpty() const{
		return head == 0;
	}

	unsigned int size() const{
		DLLNode<T> *it = head;
		unsigned int count = 0;
		while(it){
			++count;
			it = it->next;
		}
		return count;
	}

	T & front(){
		return head->data;
	}

	const T & front() const{
		return head->data;
	}

	T & back(){
		return tail->data;
	}

	const T & back() const{
		return tail->data;
	}

	void push_front(const T &el){
		DLLNode<T> *temp = new Node<T>(el);
		if(!head){
			head = tail = temp;
		}
		else{
			temp->next = head;
			head->prev = temp;
			head = temp;
		}
		return;
	}

	void push_back(const T &el){
		DLLNode<T> *temp = new Node<T>(el);
		if(!head){
			head = tail = temp;
		}
		else{
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
		return;
	}

	void pop_front(){
		if(head == tail){
			delete(head);
			head = tail = 0;
			return;
		}
		DLLNode<T> *temp = head;
		head = head->next;
		head->prev = 0;
		delete(temp);
		return;
	}

	void pop_back(){
		if(head == tail){
			delete(tail);
			head = tail = 0;
			return;
		}
		DLLNode<T> *temp = tail;
		tail = tail->prev;
		tail->next = 0;
		delete(temp);
		return;
	}

	DLLNode<T> * insert(DLLNode<T> *previous,const T &el){
		
		if(!head)
			return 0;

		if(!previous){
			push_back(el);
			return tail;
		}

		
		DLLNode<T> *temp = new DLLNode<T>(el);

		DLLNode<T> *prevNode = previous->prev;
		prevNode->next = temp;
		temp->prev = prevNode;
		temp->next = previous;
		previous->prev = temp;
		return temp;
	}

	DLLNode<T> * erase(DLLNode<T> * e){
		if(!head)
			return 0;
		if(head==e && tail==e){
			delete(e);
			head = tail = 0;
			return 0;
		}
		if(head==e){
			head = head->next;
			head->prev = 0;
			delete(e);
			return head;
		}
		if(tail==e){
			tail = tail->prev;
			tail->next = 0;
			delete(e);
			return 0;
		}

		DLLNode *prevNode = e->prev;
		DLLNode* nextNode = e->next;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		delete(e);
		return nextNode;
	}

	void clear(){
		deleteDoubleList();
	}

	void sort(){
		//merge sort
	}

	void reverse(){
		//recursively + iteratively
	}

	void merge(DLLNode<T> &DLL){

	}

	void printDoubleList() const{
		printDoubleListHelper(head);
	}

template <typename V>
	friend ostream &(ostream &, const DoubleLinkedList<V> &);

};

template<typename V>
	ostream &(ostream &out, const DoubleLinkedList<V> &DLL){
		DLL.printDoubleList();
		return out;
	}
