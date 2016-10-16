#include "vector.h"

int main(){
	Vector<int> ar;
	cout << "Capacity = " << ar.getCapacity() << endl;
	cout << "Size = " << ar.getSize() << endl;
	for(int i=0;i<10;i++)
		ar.push_back(i);
	cout << ar;
	cout << "Capacity = " << ar.getCapacity() << endl;
	cout << "Size = " << ar.getSize() << endl;
	cout << "Front = " << ar.front() << endl;
	ar.pop_back();
	ar.pop_back();
	cout << "Size = " << ar.getSize() << endl;
	cout << ar;
	ar.push_back(77);
	cout << "Size = " << ar.getSize() << endl;
	cout << ar;
	cout << "Size = " << ar.getSize() << endl;
	cout << "Back = " << ar.back() << endl;
	ar.shrink_to_fit();
	cout << "Capacity = " << ar.getCapacity() << endl;
	cout << "Size = " << ar.getSize() << endl;
	ar.insert(3,23);
	cout << ar;
	cout << "Capacity = " << ar.getCapacity() << endl;
	cout << "Size = " << ar.getSize() << endl;
	ar.insert(1,-11);
	cout << ar;
	ar.insert(ar.getSize(),123);
	cout << ar;
	cout << ar << "\n\n\n\n";
	int el[3] = {12,13,14};
	ar.insert(3,el,3);
	cout << ar;
	int size = ar.getSize();
	ar.insert(size,el,3);
	cout << ar;
	size = ar.getSize();
	ar.insert(size+1,el,3);
	cout << ar;
	cout << ar << "\n\n\n\n";
	ar.insert(1,el,3);
	cout << ar;
	cout << ar.getCapacity() << endl;
	size = ar.getSize();
	cout << ar << "\n\n\n\n";
	el[0] = 99;
	el[1] = 100;
	el[2] = 101;
	ar.insert(size+1,el,0,2);
	cout << ar;
	ar.insert(1,el,1,1);
	cout << ar;
	cout << "********\n";
	ar.erase(2);
	cout << ar;
	ar.erase(7);
	cout << ar;
	ar.erase(1,5);
	cout << ar;
	ar.erase(1,ar.getSize());
	cout << ar;
return 0;
}
