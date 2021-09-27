#include<iostream>
#include<cstdlib>
#include<string>
#include"HashTable.h"
void Link_list::insert(string key, string Gender, int Height, int Weight){
	item *current=new item;
	if(head==NULL){
        current->next=NULL;
        head=current;
        current->key=key;
        current->Gender=Gender;
        current->Height=Height;
        current->Weight=Weight;
	}
	else{
        current->next=head;
        head=current;
        current->key=key;
        current->Gender=Gender;
        current->Height=Height;
        current->Weight=Weight;
	}
}
void HashTable::addItem(string key, string Gender, int Height, int Weight){
	int temp=atoi(key.c_str());
	temp=temp%N;
	list[temp].insert(key, Gender, Height, Weight);
}
item HashTable::operator[](string key){
	int temp=atoi(key.c_str());
	temp=temp%N;
	item *current=list[temp].head;
	while(current!=NULL){
        if(current->key!=key){
            current=current->next;
        }
        else if(current->key==key){
            return *current;
        }
	}
}

string item::getGender(){
	return Gender;
}
int item::getHeight(){
	return Height;
}
int item::getWeight(){
	return Weight;
}
