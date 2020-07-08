#include <iostream>
#include <cstdlib>
#include <string.h>

#include "ExtHashTable.h"

ExtHashTable::ExtHashTable( double upper_bound_ratio, double lower_bound_ratio, int size) :
	HashTable::HashTable(size),
	upper_bound_ratio(upper_bound_ratio),
	lower_bound_ratio(lower_bound_ratio){}

  
ExtHashTable::ExtHashTable(const ExtHashTable &t) : 
	HashTable(t),	
	upper_bound_ratio (t.upper_bound_ratio),
	lower_bound_ratio (t.lower_bound_ratio){}

void ExtHashTable::rehash() {
	if(size==0){return;}
	if(((double)size/capacity)>upper_bound_ratio){
		rehashing(capacity*2);
	}
	else if(((double)size/capacity)<lower_bound_ratio){
		rehashing(capacity/2);
	}
}

void ExtHashTable::rehashing(int newcapacity){
	HashTable newHashTable =  HashTable(newcapacity);

	for(int i=0; i<this->capacity; i++){
		if(!this->isAvailable(i)){
			newHashTable.add(this->table[i]);
		}
	}

	this->size = newHashTable.getSize();
	this->capacity = newHashTable.getCapacity();
	delete []this->table;
	this->table = new string[this->capacity];
	for(int i =0; i<newHashTable.getCapacity(); i++){
		this->table[i].assign(newHashTable.table[i]);
	}
	cout<<"--> Size: "<<newHashTable.getSize()<<", New capacity: "<<newcapacity<<"\n";
}

bool ExtHashTable::add(const string &str) {
	return add(str.c_str());
}

bool ExtHashTable::add(const char *s) {
	if(this->HashTable::add(s)){
		rehash();
		return true;
	}
	return false;
}

bool ExtHashTable::remove(const string &str) {
	return remove(str.c_str());
}

bool ExtHashTable::remove(const char *s) {
	if(this->HashTable::remove(s)){
		rehash();
		return true;
	}
	return false;
}

ExtHashTable ExtHashTable::operator+(const string &str) const{
	ExtHashTable newHashTable =  *this;
	newHashTable.add(str);
	return newHashTable;
}

ExtHashTable ExtHashTable::operator+(const char* s) const{
	ExtHashTable newHashTable =  *this;
	newHashTable.add(s);
	return newHashTable;
}

ExtHashTable ExtHashTable::operator-(const string &str) const{
	ExtHashTable newHashTable =  *this;
	newHashTable.remove(str);
	return newHashTable;
}

ExtHashTable ExtHashTable::operator-(const char *s) const{
	ExtHashTable newHashTable =  *this;
	newHashTable.remove(s);
	return newHashTable;
}

bool ExtHashTable::operator += (const string &str) { 
	return this->add(str);
}

bool ExtHashTable::operator += (const char* s) { 
	return this->add(s);
}

bool ExtHashTable::operator -= (const string &str) {
	return this->remove(str);
}

bool ExtHashTable::operator -= (const char *s) {
	return this->add(s);
}

ExtHashTable ExtHashTable::operator+(const ExtHashTable &table) const {
	ExtHashTable newHashTable =  ExtHashTable(*this);
	for(int i=0; i<table.capacity; i++){
		if(!table.isAvailable(i)){
			newHashTable.add(table.table[i]);
		}
	}
	return newHashTable;
}

ExtHashTable & ExtHashTable::operator+=(const ExtHashTable &table) {
	for(int i=0; i<table.capacity; i++){
		if(!table.isAvailable(i)){
			this->add(table.table[i]);
		}
	}
	return *this;
}

ExtHashTable & ExtHashTable::operator=(const ExtHashTable &t) {
	this->size = t.size;
	this->capacity = t.capacity;
	this->upper_bound_ratio = t.upper_bound_ratio;
	this->lower_bound_ratio = t.lower_bound_ratio;

	delete []this->table;
	this->table = new string[t.capacity];
	for(int i =0; i<t.getCapacity(); i++){
		this->table[i].assign(t.table[i]);
	}

	return *this;
}