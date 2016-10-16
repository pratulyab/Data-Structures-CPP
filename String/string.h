#ifndef STRING_H
#define STRING_H
#include<iostream>
#define SIZE 20
using namespace std;

class String{
	char * str;
	int length;
	int capacity;


	int strLength(const char *ptr) const{
		int len = 0;
		const char *temp = ptr;
		while(*temp){
			len++;
			temp++;
		}
	return len;
	}
	
	void strCopy(char * dest, const char *src){
		int len = strLength(src);
		for(int i=0;i<len;i++){
			dest[i] = src[i];
		}
		dest[len] = '\0';
	}
	
	void expand(){
		capacity *= 4;

		char *newstr = new char[capacity];

		strCopy(newstr,str);

		delete [] str;

		str = newstr;
		newstr = 0; //Dangling Pointer
	}

	public:
	String() : str(0) , length(0) , capacity(SIZE){
		str = new char[capacity];
		str[0] = '\0';
	}
	String(const char * ptr) : str(0) {
		int len = strLength(ptr);
		length = capacity = len;
		str = new char[capacity];
		strCopy(str,ptr);
	}
	String(const String &S) : length(S.length) ,capacity(S.capacity),str(0){
		str = new char[capacity];
		strCopy(str,S.str);
	}
	~String() {
		delete [] str;
	}

	const String & operator=(const String &S){
		length = S.length;
		capacity = S.capacity;
		delete [] str;
		str = new char[capacity];
		strCopy(str,S.str);
		return (*this);
	}

	const String & operator+=(const String &S){

		int len = strLength(S.str);
		length += len;
		
		while(length>=capacity){
			expand();
		}

		String temp = S;

		int i=0;
		for(;str[i];i++);

		for(int k=0;k<=len;k++){
			str[i++] = S.str[k];
		}
		
		return (*this);
	}

	const String & operator+=(const char *ptr){
		int len = strLength(ptr);
		
		length += len;

		while(length >= capacity)
			expand();
		
		int i=0;
		for(;str[i];i++);

		for(int k=0;k<=len;k++){
			str[i++] = ptr[k];
		}

		return (*this);
	}

	const String & operator+=(const char ch){
		if(length==capacity)
			expand();
		
		str[length++] = ch;
		str[length] = '\0';
		return (*this);
	}

	const String operator+(const char ch) const{
		String temp = *this;
		temp += ch;
		return temp;
	}

	const String operator+(const String &S) const{
		String temp1 = *this;
		String temp2(S);
		
		temp1 += temp2;
		return temp1;
	}

	const String operator+(const char *ptr) const{
		String temp = *this;
		temp += ptr;
		return temp;
	}

	char operator[](int index){
		if(index>length || index<0)
			return 0;
		return str[index];
	}

	int getCapacity() const;
	int getLength() const;

	friend ostream & operator<< (ostream &, const String &);

};

ostream & operator<<(ostream &out, const String &S) const{
	if(!S.length){
		out << "Empty\n";
		return out;
	}

	for(int i=0;S.str[i];i++){
		out << S.str[i];
	}
	out << endl;
	return out;
}

int String::getCapacity() const{
	return capacity;
}

int String::getLength() const{
	return length;
}
#endif
