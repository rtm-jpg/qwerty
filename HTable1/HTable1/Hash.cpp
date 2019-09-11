
#include "Hash.h"
#include <iostream>
using namespace std;

//Хэш функция
int HashFunction(int key, int size, int p)
{
	int A;
	double buf;
	A = (sqrt(5) - 1) / 2;
	int key2 = size * (modf(key * A, &buf));
	return (key2 + p) % size;
}

//Следующий элемент

int Next_hash(int hash, int size, int p)
{
	return (hash + 5 * p + 3 * p * p) % size;
}

//Передаем параметров для создания элемента

Object Create(int size, int(*getkey)(void*))
{
	return *(new Object(size, getkey));
}

//Создание нового элемента

Object::Object(int size, int(*getkey)(void*))
{
	N = 0; this->Size = size;
	this->GetKey = getkey;
	this->Data = new void* [size];
	for (int i = 0; i < size; ++i)
		Data[i] = NULL;
}

//Вставка чего то

bool Object::Insert(void* d)
{
	bool b = false;
	if (N != Size)
		for (int i = 0, t = GetKey(d), j = HashFunction(t, Size, 0);
			i != Size && !b;
			j = HashFunction(t, Size, ++i))
			//j = Next_hash(j, Size, ++i))
			if (Data[j] == NULL || Data[j] == DEL)
			{
				Data[j] = d; N++; b = true;
			}
	return b;
}

//Поиск элемента по ключу

int Object::SearchInd(int key)
{
	int t = -1; bool b = false;
	if (N != 0)
		for (int i = 0, j = HashFunction(key, Size, 0);
			Data[j] != NULL && i != Size && !b; j = HashFunction(key, Size, ++i))
			if (Data[j] != DEL)
				if (GetKey(Data[j]) == key)
				{
					t = j; b = true;
				}
	return t;
}

//Передаем в ф-цию поиска

void* Object::Search(int key)
{
	int t = SearchInd(key);
	return(t >= 0) ? (Data[t]) : (NULL);
}

//Удаление элемента

void* Object::Delete(int key)
{
	int i = SearchInd(key);
	void* t = Data[i];
	if (t != NULL)
	{
		Data[i] = DEL; N--;
	}
	return t;
}

//Передаем в ф-цию удаления

bool Object::Delete(void* d)
{
	return(Delete(GetKey(d)) != NULL);
}

//Проверка элементов в хэше

void Object::Scan(void(*f)(void*))
{
	for (int i = 0; i < this->Size; i++)
	{
		cout << "Элемент " << i << ": ";
		if ((this->Data)[i] == NULL) cout << "Пуст" << endl;
		else if ((this->Data)[i] == DEL) cout << "Удален" << endl;
		else f((this->Data)[i]);
	}
}