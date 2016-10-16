#include "queueAsLL.h"

int main(){
	Queue<int> Q;
	
	if(Q.empty()){
		cout << "Queue Is Empty" << endl;
	}
	else{
		cout << "Queue Is Not Empty" << endl;
	}

	for(int i=0;i<10;i++)
		Q.push(i);
	cout << Q;
	Q++;
	cout << Q;
	++Q;
	cout << Q;

	if(Q.empty()){
		cout << "Queue Is Empty" << endl;
	}
	else{
		cout << "Queue Is Not Empty" << endl;
	}
	
	Queue<int> Q2;
	Q2.push(99);
	Q2.push(88);
	Q2.push(77);
	Q += Q2;
	cout << Q;
	
	Q += 123;
	cout << Q;
	cout << "Size = " << Q.size() << endl;
	cout << "Front = " << Q.front() << endl;
	cout << "Back = " << Q.back() << endl;
	
	for(int i=0;i<3;i++){
		Q.pop();
		cout << Q;
	}
	Q++;
	cout << Q;
	Q = Q2;
	if(Q==Q2)
		cout << "Identical" << endl;
	else
		cout << "Different" << endl;

	cout << Q << Q2;
	
	Q.reverseQueue();
	cout << Q;
	cout << "Front = " << Q.front() << endl;
	cout << "Back = " << Q.back() << endl;
	cout << "Size = " << Q.size() << endl;
	return 0;
}
