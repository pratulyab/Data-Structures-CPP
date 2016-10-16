#ifndef STACK_LL_H
#define STACK_LL_H
#include<iostream>
using namespace std;

template <typename V>
class Stack;

template <typename T>
class Node{
	T data;
	Node<T> *next;

	public:
	Node() : next(0) {}
	Node(T d) : next(0) , data(d) {}
	Node(const Node<T> &n) : next(0) , data(n.data) {}

	template <typename V>
		friend class Stack;
	template <typename V>
		friend ostream & operator<<(ostream &,const Stack<V> &);
	template <typename V>
		friend istream & operator>>(istream &,Stack<V> &);
};

template <typename V>
class Stack{
	Node<V> *top;
	//static int stacks; //Static can only be mentioned inside the class def

	void createStack(const Stack &s){
		const Node<V> *it = s.top;
		Node<V> *prevNode = 0;
		while(it){
			Node<V> *temp = new Node<V>(*it);

			if(!top){
				top = temp;
			}
			else{
				prevNode->next = temp;
			}
			prevNode = temp;
			it = it->next;
		}
	return;
	}

	void deleteStack() {
		while(top){
			Node<V> *temp = top;
			top = top->next;
			delete(temp);
		}
		return;
	}

	static void printStackHelper(const Node<V> *temp){
		while(temp){
			cout << temp->data << "-->";
			temp = temp->next;
		}
		cout << "NULL\n";
	}

	public:
	Stack() : top(0) {}
	Stack(const Stack &s) : top(0) {
		createStack(s);
	}
	~Stack() {
		deleteStack();
	}

	Stack & operator+=(const Stack &S){
		Stack S2(S);
		if(!top){
			top = S2.top;
		}
		else{
			Node<V> *it = top;
			while(it->next)
				it = it->next;
			
			it->next = S2.top;
		}

		S2.top = 0; //Removing Dangling Pointers
		return *this;
	}

	Stack & operator+=(V el){
		Node<V> *temp = new Node<V>(el);
		if(!top){
			top = temp;
		}
		else{
			Node<V> *it = top;
			while(it->next)
				it = it->next;

			it->next = temp;
		}

		return *this;
	}

	Stack & operator=(const Stack &S){
		deleteStack();
		createStack(S);
		return *this;
	}

	Stack & operator++(){ //Pre-Increment
		Node<V> *it = top;
		while(it){
			++it->data;
			it = it->next;
		}
		return *this;
	}

	Stack operator++(int dummy){ //Post-Increment //Why dummy??
		Stack temp(*this);
		++(*this);
		return temp;
	}

	bool operator==(const Stack &S) const{
		const Node<V> *it1 = top;
		const Node<V> *it2 = S.top;
		
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
	
	void push(V el){
		Node<V> *temp = new Node<V>(el);
		temp->next = top;
		top = temp;
	}

	void pop(){
		if(!top){
			cout << "UNDERFLOW\n";
			return;
		}
		Node<V> *temp = top;
		top = top->next;
		delete(temp);
	}

	int size() const{ //const or not?
		Node<V> *it = top;
		int count = 0;
		while(it){
			++count;
			it = it->next;
		}
		return count;
	}

	bool empty() const{ //const or not?
		return top==0;
	}

	V & getTop(){
		return top->data;
	}

	const V & getTop() const{
		return top->data;
	}

	void printStack() const{
		printStackHelper(top);
		return;
	}
	template<typename P>	//WHY new template??
		friend ostream & operator<<(ostream &,const Stack<P> &);
};

template <typename V>
	ostream & operator<<(ostream &out,const Stack<V> &s){
		s.printStack();
		return out;
	}
template <typename V>
	istream & operator>>(istream &in, Stack<V> &s){
	//Appends Each Node To End
		V el = cin.get();
		cout << el;
		s += el;
		return in;
	}

/*template <typename V>
int Stack<V>::stacks = 0;*/
#endif
