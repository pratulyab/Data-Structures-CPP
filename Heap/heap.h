#ifndef HEAP_H
#define HEAP_H
#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class minHeap{
	vector<T> V;
	
	void swapIndices(int i,int j){
		T temp = V[i];
		V[i] = V[j];
		V[j] = temp;
	}
/*
	void swapData(T &a, T &b){
		T temp = a;
		a = b;
		b = temp;
	}*/

	void heapify(){
		for(int i=size()/2;i>=1;i--){
			percolateDown(i);
		}
	}

	void percolateDown(int index){
		while(2*index < size() && (V[index] > V[2*index] || V[index] > V[2*index + 1])){
			T smaller = V[2*index] > V[2*index+1] ? 2*index+1 : 2*index;
			
			//swapData(V[index],V[smaller]);
			T temp = V[index];
			V[index] = V[smaller];
			V[smaller] = temp;
			index = smaller;
		}
	}

	public:
	minHeap() {V.resize(1);}

	bool isEmpty() const{
		return V.size() == 1;
	}

	void clear(){
		V.clear();
		V.resize(1);
	}

	int size() const{
		return V.size() - 1;
	}

	T findMin() const{
		return V[1];
	}

	void insertNode(T el){
		V.push_back(el);
		int index = V.size() - 1;
		
		while(index>1){
			if(V[index/2] > V[index]){
				swapIndices(index,index/2);
				index /= 2;
			}
			else{
				break;
			}
		}
	}

	void deleteNode(){
		if(isEmpty())
			return;
		if(size() == 1){
			V.pop_back();
			return;
		}

		V[1] = V[V.size() - 1]; // V[1] = V.back();
		V.pop_back();
		percolateDown(1);
	}

};

#endif
