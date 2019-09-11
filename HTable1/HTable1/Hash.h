#pragma once
#define HASHDEL (void*)-1
struct Object
{
	int N;
	int Size;
	void** Data;
	bool Insert(void*);
	bool Delete(void*);
	int(*GetKey)(void*);
	void* Delete(int key);
	void* Search(int key);
	int SearchInd(int key);
	void Scan(void(*f)(void*));
	Object(int, int(*)(void*));

};

static void* DEL = (void*)HASHDEL;

Object Create(int size, int(*getkey)(void*));

#undef HASHDEL