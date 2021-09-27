#ifndef HASHTABLE
#define HASHTABLE

#include<iostream>
#include<cstdlib>
#include<string>
#define N 9973

using namespace std;
class item{
    friend class HashTable;
    friend class Link_list;
private:
    string key, Gender;
	int Height, Weight;
public:
	string getGender();
	int getHeight();
	int getWeight();
	item *next;
};

class Link_list{
public:
	item *head=NULL;
	void insert(string key, string Gender, int Height, int Weight);
};

class HashTable{
public:
	Link_list list[N];
	void addItem(string key, string Gender, int Height, int Weight);
	item operator [] (string key);
};

#endif
