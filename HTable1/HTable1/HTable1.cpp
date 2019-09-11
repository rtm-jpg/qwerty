
#include "Hash.h"
#include <iostream>
#include <conio.h>
#include <ctime>

using namespace std;

struct Table
{
	 int key; const char* mas; Table(const int k, const char* z)
	{
		key = k; mas = z;
	}
	Table() {}
};

//Сам ключ

int key(void* d)
{
	Table* f = (Table*)d; return f->key;
}

//Вывод элементов

void Table_print(void* d)
{
	cout << "Ключ " << ((Table*)d)->key << " - " << ((Table*)d)->mas << endl;
}

//Главная функция

int main()
{
	setlocale(LC_ALL, "rus");
	int size = 0, choise, k; float a, b;
	Table a1(1, "one"), a2(2, "two"), a3(4, "three"), a4(2, "fo");
	cout << "Введите размер хэш-таблицы: "; cin >> size;
	Object H = Create(size, key); //создать
	do
	{
		_getch();
		system("cls");
		cout << "----------Меню-----------" << endl;
		cout << "1 - Добавление элемента" << endl;
		cout << "2 - Вывод хэш-таблицы" << endl;
		cout << "3 - Удаление элемента" << endl;
		cout << "4 - Поиск элемента" << endl;
		cout << "5 - Проверка заполнения" << endl;
		cout << "0 - Выход" << endl;
		cout << "Выберите действие: "; cin >> choise;
		cout << "-------------------------" << endl;
		switch (choise)
		{
		case 1:
		{
			Table* a = new Table; char* str = new char[20];
			cout << "Введите ключ: "; cin >> k;
			a->key = k;
			cout << "Введите строку: "; cin >> str;
			a->mas = str;
			clock_t time = clock();
			H.Insert(a);
			cout << "Время выполнения: " << clock() - time << endl;
		} break;
		case 2: {H.Scan(Table_print); } break;
		case 3: {cout << "Введите ключ для удаления: "; cin >> k; H.Delete(k); } break;
		case 4:{
			cout << "Введите ключ для поиска: "; cin >> k;
			if (H.Search(k) == NULL) cout << "Элемент не найден!" << endl;
			else Table_print(H.Search(k));
		} break;
		case 5: {a = H.N; b = size; cout << "Заполненность таблицы: " << a / b << endl; } break;
		}
	} while (choise != 0);

	return 0;

}