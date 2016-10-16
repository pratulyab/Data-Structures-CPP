#ifndef QUEUE_LL_H
#define QUEUE_LL_H
#include<iostream>
using namespace std;

template <typename V>
class Queue;

template <typename T>
class Node{
	T data;
	Node<T> *next;

	public:
	Node() : next(0) {
		cout << "Node Default Constructor";
	}
	Node(T d) : next(0) , data(d) {}
	Node(const Node<T> &n) : next(0) , data(n.data) {}

	template <typename V>
		friend class Queue;
	template <typename V>
		friend ostream & operator<<(ostream &,const Queue<V> &);
};

template <typename V>
class Queue{
	Node<V> *top;
	Node<V> *rear;

	void createQueue(const Queue &Q){
		const Node<V> *it = Q.top;
		while(it){
			Node<V> *temp = new Node<V>(*it);
			if(!top && !rear){
				top = rear = temp;
			}
			else{
				rear->next = temp;
				rear = temp;
			}
			it = it->next;
		}
	return;
	}

	void deleteQueue(){
		while(top){
			const Node<V> *temp = top;
			top = top->next;
			delete(temp);
		}
		rear = 0;
		return;
	}

	static void printQueueHelper(const Node<V> *it){
		while(it){
			cout << it->data << "-->";
			it = it->next;
		}
		cout << "NULL" << endl;
	}

	Node<V> * reverseQueueHelper(Node<V> *it){
		if(!it){
			return it;
		}
		Node<V> *temp = reverseQueueHelper(it->next);
		if(!temp){
			top = rear = it;
		}
		else{
			rear->next = it;
			rear = it;
		}
		return it;
	}

	public:
	Queue() : top(0) , rear(0) {};
	Queue(const Queue &Q) : top(0) , rear(0) {
		createQueue(Q);
	}
	~Queue() {
		deleteQueue();
	}

	Queue & operator=(const Queue &Q){
		deleteQueue();
		createQueue(Q);
		return *this;
	}
	
	Queue & operator+=(const Queue &Q){
		Queue Q2(Q);
		if(!top){
			top = Q2.top;
			rear = Q2.rear;
		}
		else{
			rear->next = Q2.top;
			rear = Q2.rear;
		}
		Q2.top = Q2.rear = 0; //Dangling Pointers
		return *this;
	}

	Queue & operator+=(V el){
		Node<V> *temp = new Node<V>(el);
		if(!top){
			top = rear = temp;
			return *this;
		}
		rear->next = temp;
		rear = temp;
		
		return *this;
	}

	Queue & operator++(){ //Pre-increment
		Node<V> *it = top;
		while(it){
			++it->data;
			it = it->next;
		}
		return *this;
	}

	Queue operator++(int dummy){ //Post-increment
		Queue temp(*this);
		++(*this);
		return temp;
	}

	bool operator==(const Queue &Q) const{
		const Node<V> *it1 = top;
		const Node<V> *it2 = Q.top;
		
		while(it1 && it2){
			if(it1->data != it2->data)
				return false;

			it1 = it1->next;
			it2 = it2->next;
		}

		const Node<V> *temp = it1 ? it1 : it2;

		if(temp)
			return false;
		else
			return true;
	}

	void push(V el) {
		*this += el;
	}

	void pop() {
		if(!top && !rear){
			cout << "UNDERFLOW" << endl;
			return;
		}
		if(top == rear){
			delete(top);
			top = 0;
			rear = 0;
			return;
		}
		Node<V> *temp = top;
		top = top->next;
		delete(temp);
		return;
	}
	
	V & front() {
		return top->data;
	}

	const V & front() const{ //What to return when top is NULL?
		return top->data;
	}

	V & back() {
		return rear->data;
	}

	const V & back() const{
		return rear->data;
	}

	bool empty() const{
		return (top==0 || rear==0);
	}

	int size() const{
		const Node<V> *it = top;
		int count = 0;
		while(it){
			++count;
			it = it->next;
		}
		return count;
	}
	
	void printQueue() const{
		printQueueHelper(top);
	}

	void reverseQueue() {
		Node<V> *temp = reverseQueueHelper(top);
		temp->next = 0;
	}

	template <typename T>
		friend ostream & operator<<(ostream &, const Queue<T> &);
};

template <typename T>
	ostream & operator<<(ostream &out, const Queue<T> &Q){
		Q.printQueue();
		return out;
	}
#endif
