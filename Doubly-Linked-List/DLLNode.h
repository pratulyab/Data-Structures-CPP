#ifndef DLL_NODE_H
#define DLL_NODE_H
#include<iostream>
using namespace std;

template <typename T>
class DLLNode{
	T el;
	DLLNode<T> *next;
	DLLNode<T> *prev;

	public:
	DLLNode() : next(0) , prev(0) {}
	DLLNode(T el) : next(0) , prev(0) , data(el) {}
	DLLNode(const DLNodeL &n) : next(0) , prev(0) , data(n.data) {}
	
	template <typename V>
		friend class DoubleLinkedList<V>;
	template <typename V>
		friend ostream operator<<(ostream &, const DoubleLinkedList &);
};
#endif
