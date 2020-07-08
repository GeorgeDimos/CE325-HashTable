
#include "HashTable.h"
#include "HashTableException.h"
#include <stdio.h>

using namespace std;

int HashTable::getHashCode(const char *str) {
	int code = 0;
	while(*str != 0) {
		code += *(str++);
	}
	return code;
}

int HashTable::getSize() const { return size; }

int HashTable::getCapacity() const {return capacity; }

bool HashTable::isEmpty(int pos) const { 
	if(table[pos]=="") 
		return true;
	return false;
}

bool HashTable::isTomb(int pos) const { 
	if(table[pos].compare("##tomb##")==0)
		return true; 
	return false;
}

bool HashTable::isAvailable(int pos) const {
	return table[pos].compare("")==0 || table[pos].compare("##tomb##")==0;
}

/*Should be called only if contains() returned true*/
int HashTable::findPos(const string &s){
	int i = getHashCode(s.c_str())%capacity;
	while(table[i].compare(s)){i=(i+1)%capacity;}
	return i;
}

HashTable::HashTable(int capacity) {
	table = new string[capacity];
	if( capacity<=0 || table == NULL){
		throw new std::bad_alloc;
	}

	for(int i=0;i<capacity; i++){
		table[i].assign("");
	}
	size = 0;
	this->capacity = capacity;
}

HashTable::HashTable(const HashTable &ht) {
	size = ht.size;
	capacity = ht.capacity;

	table = new string[capacity];
	if(table == NULL){
		throw new std::bad_alloc;
	}

	for(int i=0;i<capacity; i++){
		table[i].assign(ht.table[i]);
	}
}

bool HashTable::contains(const string &s) const {
	return contains(s.c_str());
}

bool HashTable::contains(const char *s) const {
	int orig_pos = getHashCode(s)%capacity;
	int i = orig_pos;
	while(1){

		if(!table[i].compare(s)){
			return true;
		}

		if(isEmpty(i)){
			return false;
		}

		i = (i+1)%capacity;

		if(i==orig_pos){
			return false;
		}

	}
}

string HashTable::print() const {
  string str;
  char buf[128];
/* Remove the following comment if you want 
 * to try the iterator version.
 */
// #define __USE_ITERATOR__
#ifdef  __USE_ITERATOR__
	int j=0;
	for(HashTable::Iterator it = begin(); it!=end(); it++) {
		sprintf(buf, "%2d. -%s-\n", j++, (*it).c_str());
		str.append(buf);
	}
#else
	for(int i=0, j=0; i<capacity; i++){
		if(!isAvailable(i)) {
			sprintf(buf, "%2d. -%s-\n", j++, table[i].c_str());
			str.append(buf);
		}
	}
#endif
	sprintf(buf, " --- CAPACITY: %d, SIZE: %d ---\n", capacity, size);
	str.append(buf);
	return str;
}

bool HashTable::add(const string &str) {
	return add(str.c_str());
}

bool HashTable::add(const char *s) {
	
	int orig_pos = getHashCode(s)%capacity;
	int i = orig_pos;
	while(1){

		if(table[i]==s){
			return false;
		}

		if(isAvailable(i)){
			table[i].assign(s);
			size++;
			return true;
		}

		i = (i+1)%capacity;
		
		if(i==orig_pos){
			cout<<"THROW Exception!\n";
			throw HashTableException();
		}

	}
}

bool HashTable::remove(const string &str) {
	return remove(str.c_str());
}

bool HashTable::remove(const char *s) {
	if(!contains(s)){
		return false;
	}

	int pos = findPos(s);
	table[pos].assign("##tomb##");
	size--;
	return true;
}

HashTable& HashTable::operator=(const HashTable &ht) {
	size = ht.size;
	capacity = ht.capacity;
	
	table = new string[capacity];
	if(table == NULL){
		throw new std::bad_alloc;
	}

	for(int i=0;i<capacity; i++){
		table[i].assign(ht.table[i]);
	}
	return *this;
}

bool HashTable::operator += (const string &str) { 
	return add(str);
}

bool HashTable::operator += (const char* s) { 
	return add(s);
}

bool HashTable::operator -= (const string &str) {
	return remove(str);
}

bool HashTable::operator -= (const char *s) { 
	return remove(s);
}

HashTable HashTable::operator + (const string &str) const {
	HashTable n = HashTable(*this);
	try{
		n.add(str);
	}
	catch(HashTableException &ex) {
		throw HashTableException();
	}
	return n;
}

HashTable HashTable::operator + (const char* s) const {
	HashTable n = HashTable(*this);
	try{
		n.add(s);
	}
	catch(HashTableException &ex) {
		throw HashTableException();
	}
	return n;
}

HashTable HashTable::operator - (const string &str) const {
	HashTable n = HashTable(*this);
	n.remove(str);
	return n;
}

HashTable HashTable::operator - (const char *s) const {
	HashTable n = HashTable(*this);
	n.remove(s);
	return n;
}

HashTable HashTable::operator + (const HashTable &t) const {
	HashTable n = HashTable(this->capacity + t.capacity);
	for(int i=0; i<this->capacity; i++){
		if(!this->isAvailable(i)){
			n.add(this->table[i]);
		}
	}
	for(int i=0; i<t.capacity; i++){
		if(!t.isAvailable(i)){
			n.add(t.table[i]);
		}
	}
	return n;
}

HashTable& HashTable::operator += (const HashTable &t) {

	HashTable n = HashTable(*this);

	this->table = new (nothrow) string[this->capacity + t.capacity];
	if(this->table==NULL){
		throw std::bad_alloc();
	}

	this->capacity += t.capacity;

	for(int i=0; i<n.capacity; i++){
		if(!n.isAvailable(i)){
			this->add(n.table[i]);
		}
	}

	for(int i=0; i<t.capacity; i++){
		if(!t.isAvailable(i)){
			this->add(t.table[i]);
		}
	}
	
	return *this;
}

std::ostream& operator<<(std::ostream &os, HashTable &t) {
	return os.write(t.print().c_str(), t.print().length());
}

HashTable::Iterator HashTable::begin() const {
	return Iterator(this);
}

HashTable::Iterator HashTable::end() const {
	return Iterator(this, false);
}
