#ifndef HASH_MAP_H
#define HASH_MAP_H
#include<iostream>
#include<vector>
#include<list>
#include<string>
using namespace std;

unsigned int hashfunction(const string &key){
	unsigned int hashvalue = 0;

	for(int i=0; i<key.size(); i++){
		hashvalue = 37*hashvalue + key[i];
	}
	return hashvalue;
}

unsigned int hashfunction(unsigned int key){
	return key;
}

template<typename key,typename value>
class HashMap{
	vector<list<pair<key,value> > > table;
	int numofelements;
	
	unsigned int myhash(const key &k){
		return hashfunction(k) % table.size();
	}
    
    void rehash() {
        vector<list<pair<key,value> > > temp = table;
        clear();
        int size = table.size();
        table.resize(2*size);
        for(int i=0;i<temp.size();i++){
            typename list<pair<key,value> > :: iterator it = temp[i].begin();
            while(it != temp[i].end()){
                add(it->first,it->second);
                it++;
            }
        }
    }

	public:
	HashMap(int size = 101) {
		table.resize(size);
		numofelements = 0;
	}
	
	void clear() {
		for(int i=0; i<table.size(); i++){
			table[i].clear();
		}
		numofelements = 0;
	}

	bool isEmpty() const {
		return numofelements == 0;
	}

	bool contains(const key &k) const {
		list<pair<key,value> > &whichList = table[myhash(k)];
		return find(whichList.begin(),whichList.end(),k) != whichList.end();
	}

	bool add(const key &k,const value &v) {
		list<pair<key,value> > &whichList = table[myhash(k)];
		typename list<pair<key,value> >::iterator it = whichList.begin();
		for(;it!=whichList.end();it++){
			if(it->first == k)
				return false;
		}

		whichList.push_back(make_pair(k,v));
		numofelements++;

		if(numofelements == table.size()/2){
			rehash();
		}
		return true;
	}

	bool update(const key &k,const value &v) {
		list<pair<key,value> > &whichList = table[myhash(k)];
		typename list<pair<key,value> > :: iterator it = whichList.begin();

		while(it!=whichList.end()){
			if(it->first == k)
				break;
			it++;
		}

		if(it == whichList.end())
			return false;
		else{
			it->second = v;
			return true;
		}
	}

	bool remove(const key &k) {
		list<pair<key,value> > &whichList = table[myhash(k)];
		typename list<pair<key,value> > :: iterator it = whichList.begin();

		while(it!=whichList.end()){
			if(it->first == k){
				whichList.erase(it);
				numofelements--;
				return true;
			}
			it++;
		}
		return false;
	}
	
	value & get(const key &k) {
		list<pair<key,value> > &whichList = table[myhash(k)];
		typename list<pair<key,value> > :: iterator it = whichList.begin();

		while(it!=whichList.end()){
			if(it->first==k){
				return it->second;
			}
			it++;
		}

		throw "Key Doesn't Exist";
	}

	const value & get(const key &k) const{
		list<pair<key,value> > &whichList = table[myhash(k)];
		typename list<pair<key,value> > :: const_iterator it = whichList.begin();

		while(it!=whichList.end()){
			if(it->first==k){
				return it->second;
			}
			it++;
		}

		throw "Key Doesn't Exist";	
	}

	value & operator[](const key &k){
		list<pair<key,value> > &whichList = table[myhash(k)];
		typename list<pair<key,value> >::iterator it = whichList.begin();

		while(it!=whichList.end()){
			if(it->first == k)
				return it->second;

			it++;
		}

		pair<key,value> P;
		value v;
		P.first = k;
		P.second = v;
		whichList.push_back(P);
		numofelements++;

		if(numofelements == table.size()/2)
			rehash();

		return get(k);
	}

	const value & operator[](const key &k) const{
		list<pair<key,value> > &whichList = table[myhash(k)];
		typename list<pair<key,value> >::const_iterator it = whichList.begin();

		while(it!=whichList.end()){
			if(it->first == k)
				return it->second;
			it++;
		}

		throw "Key Doesn't Exist";
	}
};
#endif
