#include "string.h"

int main(){
	String S("Pratulya");
	cout << S << "Length = " << S.getLength() << " Capacity = " << S.getCapacity() << endl;
	S += " Bubna";
	cout << S << "Length = " << S.getLength() << " Capacity = " << S.getCapacity() << endl;
	S += '!';
	cout << S << "Length = " << S.getLength() << " Capacity = " << S.getCapacity() << endl;
	for(int a=0;a<20;a++){
		S += '!';
	cout << S << "Length = " << S.getLength() << " Capacity = " << S.getCapacity() << endl;
	}

	String T;
	cout << T << "Length = " << T.getLength() << " Capacity = " << T.getCapacity() << endl;
	T = S;
	cout << T << "Length = " << T.getLength() << " Capacity = " << T.getCapacity() << endl;

	String U;
	U = S + T;
	cout << "S\n" << S << "Length = " << S.getLength() << " Capacity = " << S.getCapacity() << endl;
	cout << "T\n" << T << "Length = " << T.getLength() << " Capacity = " << T.getCapacity() << endl;
	cout << "U\n" << U << "Length = " << U.getLength() << "Capacity = " << U.getCapacity() << endl;	
	cout << U + "------";
	cout << "U\n" << U << "Length = " << U.getLength() << "Capacity = " << U.getCapacity() << endl;
	cout << U + '\\';

	cout << "U\n" << U << "Length = " << U.getLength() << "Capacity = " << U.getCapacity() << endl;	
	cout << U[0]<< U[69] << U[70] << U[71] << endl;
return 0;
}
