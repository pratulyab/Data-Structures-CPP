#include "stackAsArray.h"

int main(){
	Stack<int> S(10);
	cout << S.getTop() << endl;;
	cout << S.empty() << endl;
	for(int i=0;i<30;i++)
		S.push(i);
	cout << S;
	cout << S.empty() << endl;
	cout << "Top = " << S.getTop() << endl;
	for(int i=2;i>=0;i--)
		S.pop();
	cout << S;
	cout << S.empty() << endl;
	cout << "Top = " << S.getTop() << endl;

return 0;
}
