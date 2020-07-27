
#include "HashTable.h"
#include "HashTableException.h"
#include <stdio.h>

using namespace std;

HashTable::Iterator::Iterator(const HashTable *t) {
	ht = t;

	int i=0;
	while(i<t->capacity && t->isAvailable(i)){
		i++;
	}

	curr = &t->table[i];
	
}

HashTable::Iterator::Iterator(const HashTable *t, bool start) {
	ht = t;
	if(start){
		int i=0;
		while(i<t->capacity && t->isAvailable(i)){
			i++;
		}
		curr = &t->table[i];
	}
	else{
		int i = t->capacity-1;
		while(i>0 && t->isAvailable(i)){
			i--;
		}
		curr = &t->table[++i];
	}
}

HashTable::Iterator::Iterator(const Iterator &it) {
	ht = it.ht;
	curr = it.curr;
}

HashTable::Iterator& HashTable::Iterator::operator=(const HashTable::Iterator &it) {
	ht = it.ht;
	curr = it.curr;
	return *this;
}

HashTable::Iterator HashTable::Iterator::operator++() {
	curr++;
	while(curr!=&ht->table[ht->capacity] && (!(*curr).compare("") || !(*curr).compare("##tomb##"))){
		curr++;
	}
	return *this;
}

HashTable::Iterator HashTable::Iterator::operator++(int a) {
	Iterator it (*this);
	curr++;
	while(curr!=&ht->table[ht->capacity] && (!(*curr).compare("") || !(*curr).compare("##tomb##"))){
		curr++;
	}
	return it;
}

bool HashTable::Iterator::operator==(const HashTable::Iterator &it) const {
	return it.curr==curr && it.ht==ht;
}

bool HashTable::Iterator::operator!=(const HashTable::Iterator &it) const {
	return it.curr!=curr || it.ht!=ht;
}

const string& HashTable::Iterator::operator*() {
	return *curr;
}

const string* HashTable::Iterator::operator->() {
	return curr;
}