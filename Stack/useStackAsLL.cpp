#include<iostream>
#include "stackAsLL.h"

int main(){
	Stack<int> S;
	if(S.empty()){
		cout << "Stack Is Empty" << endl;
	}
	else{
		cout << "Stack Is Not Empty" << endl;
	}
	for(int i=0;i<10;i++)
		S.push(i);
	cout << S;
	S++;
	++S;
	cout << S;
	Stack<int> S2;
	S2.push(99);
	S2.push(88);
	S2.push(77);
	S += S2;
	cout << S;
	int a = 6;
	while(a--)
		S.pop();
	cout << S;
	S += 123;
	cout << S;
	cout << "Top = " << S.getTop() << endl;
	cout << "Size = " << S.size() << endl;
	if(S.empty()){
		cout << "Stack Is Empty" << endl;
	}
	else{
		cout << "Stack Is Not Empty" << endl;
	}

	S = S2;
	if(S==S2)
		cout << "Identical" << endl;
	else
		cout << "Different" << endl;
return 0;
}
