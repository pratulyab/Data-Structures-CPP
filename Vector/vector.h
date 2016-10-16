#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
using namespace std;

template <typename T>
class Vector{
	T * ar;
	int size;
	int capacity;
	
	void expand(){
		capacity = capacity*2;

		T *temp = new T[capacity];

		for(int i=0;i<size;i++){
			temp[i] = ar[i];
		}

		delete [] ar;
		ar = temp;
		temp = 0; // Dangling Pointer
	}

	void expand(int n){
		capacity = n;
		T *temp = new T[capacity];
		
		for(int i=0;i<size;i++){
			temp[i] = ar[i];
		}

		delete [] ar;
		ar = temp;
		temp = 0; // Dangling Pointer
	}

	void createVector(const Vector &DA){
		size = DA.size;
		capacity = DA.capacity;
		ar = new T[capacity];

		for(int i=0;i<size;i++){
			ar[i] = DA.ar[i];
		}
		return;
	}

	public:
	Vector() : ar(0) , size(0) , capacity(8) {
		ar = new T[8];
	}
	Vector(int cap) : ar(0) , size(0) , capacity(cap) {
		ar = new T[capacity];
	}

	Vector(const Vector &DA) { // : capacity(DA.capacity) , size(DA.size) {
		createVector();
	}

	~Vector() {
		delete [] ar;
	}

	const Vector & operator= (const Vector &DA){
		delete [] ar;
		createVector(DA);
		return (*this);
	}
	
	void push_back(const T &el) {
		if(size == capacity){
			expand();
		}
		ar[size++] = el;
	}

	void pop_back() {
		if(size == 0)
			return;
		size--;
	}

	T & operator[](int i){
		return ar[i];
	}

	T & front() {
		return ar[0];
	}

	T & back() {
		return ar[size-1];
	}

	bool isEmpty(){
		return size==0;
	}

	int getSize(){
		return size;
	}

	int getCapacity(){
		return capacity;
	}
	
	void reserve(int n){
		if(n<=capacity)
			return;
		expand(n);
	}

	void shrink_to_fit(){
		expand(size);
	}

	void clear(){
		delete [] ar;
		size = 0;
		ar = new T[capacity];
	}

	void insert(unsigned int pos, const T &el){
		if(pos > size+1 || pos==0)//pos<=0) < not reqd because unsigned
			return;

		if(size == capacity || pos >= capacity) //incase pos==size+1
			expand();

		int index = pos==size+1 ? pos : size;
		for(int i=index-1; i>=pos-1 && i>=0; i--){ //WTF!!? //Handles 0+1 case
			ar[i+1] = ar[i];
		}
		ar[pos-1] = el;
		size += 1;
	}

	void insert(unsigned int pos, T * el,int count){
		if(pos > size+1 || pos == 0 || !el || !count)
			return;

		if(size == capacity || pos>=capacity || pos+count>=capacity)
			expand();

		int index = pos==size+1 ? pos : size;

		for(int i=index-1; i>=pos-1 && i>=0; i--){ //WTF!!!?
			ar[i+count] = ar[i];
		}

		for(int i=0;i<count;i++){
			ar[pos+i-1] = el[i];
		}
		size += count;
	}

	void insert(unsigned int pos, T * el, int start, int last){
		if(pos>size+1 || pos == 0 || !el || start<0 || last<0 || start>last)
			return;
		int count = last-start+1;
		insert(pos,el,count);
	}

	void erase(unsigned int pos){
		if(pos>size)
			return;
		for(int i=pos-1;i<size;i++)
			ar[i] = ar[i+1];
		size -= 1;
	}

	void erase(unsigned int start, unsigned int end){
		if(start>end || start>size || end>size)
			return;
		int count = end - start + 1;

		for(int i=0;i<count;i++){
			for(int j=start-1;j<size;j++){
				ar[j] = ar[j+1];
			}
			size--;
		}
	}

template<typename V>
	friend ostream & operator<<(ostream &out,const Vector<V> &obj);
};

template <typename T>
ostream & operator<<(ostream &out,const Vector<T> &DA){
	if(DA.size==0){
		out << "Empty\n";
		return out;
	}
	for(int i=0;i<DA.size;i++)
		out << DA.ar[i] << " ";
	out << endl;
	return out;
}

#endif
