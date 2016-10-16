#ifndef STACK_AS_ARRAY_H
#define STACK_AS_ARRAY_H

#define SIZE 20

#include<iostream>
using namespace std;

template <typename T>
class Stack{
	T * ar;
	int top;
	int capacity;
	
	void expand(){
		capacity *= 2;
		T * temp = new T[capacity];

		for(int i=0;i<=top;i++)
			temp[i] = ar[i];
		
		delete [] ar;
		ar = temp;
		temp = 0;
		
		return;
	}

	void createStack(const Stack &S){
		capacity = S.capacity;
		top = S.top;
		ar = new T[capacity];
		
		for(int i=0;i<=top;i++){
			ar[i] = S[i];
		}
		
		return;
	}

	public:
	Stack() : ar(0) , top(-1) , capacity(SIZE) {
		ar = new T[capacity];
	}
	Stack(int cap) : ar(0) , top(-1) , capacity(cap) {
		ar = new T[capacity];
	}
	Stack(const Stack &S) : ar(0) {
		createStack(S);
	}
	~Stack() {
		delete [] ar;
	}

	void push(const T &el){
		if(top+1 == capacity){
			expand();
		}
		ar[++top] = el;
		return;
	}

	void pop(){
		if(top == -1){
			cout << "UNDERFLOW\n";
			return;
		}
		top = top-1;
	}

	T & getTop(){
		return ar[top];
	}

	const T & getTop() const{
		return ar[top];
	}

	bool empty() const{
		return top==-1;
	}
	
	const Stack<T> & operator+=(const Stack<T> &S){
		int length = top + 1 + S.top + 1;
		while(length > capacity)
			expand();
	
		for(int i=0;i<=S.top;i++){
			ar[++top] = S.ar[i];
		}

		return (*this);
	}

	const Stack<T> & operator+=(const T &el){
		push(el);
		return (*this);
	}

	const Stack<T> & operator=(const Stack<T> &S){
		delete [] ar;
		createStack(S);
		return (*this);
	}
	
	template <typename V>
	friend ostream & operator<<(ostream &, const Stack<V> &);
};

template<typename T>
ostream & operator<< (ostream &out, const Stack<T> &S){
	if(S.top==-1){
		out << "EMPTY" << endl;
		return out;
	}
	for(int i=0;i<=S.top;i++)
		out << S.ar[i] << " ";
	out << endl;

	return out;
}
#endif
