#include "heap.h"
#include<iostream>
using namespace std;

int main(){
	minHeap<int> H;
	for(int i=0; i<10;i++){
		int el;
		cin >> el;
		H.insertNode(el);
	}
	while(!H.isEmpty()){
		cout << H.findMin() << " ";
		H.deleteNode();
	}
	return 0;
}
