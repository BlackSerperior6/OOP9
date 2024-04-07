#include "List.h"

int main()
{
	try
	{
		system("chcp 1251");

		List list;

		cin >> list;

		cout << endl;

		cout << list << endl;

		cout << "На какое число вы хотите увеличить все элементы списка?" << endl;

		int number;

		cin >> number;

		for (int i = 0; i < list(); i++)
			list[i] += number;

		cout << endl << list << endl;

		list.Pop_Front();
		list.Pop_Back();

		cout << endl << "Список после удаления первого и последнего элементов:" << endl << list << endl;

		cout << "Введите число, которое хотите добавить в начало списка: "; cin >> number;

		list.Push_Front(number);

		cout << endl << list << endl << endl;

		cout << "Возводим список в квадрат:";
		list *= list;
		cout << endl << list << endl << endl;

		cout << "Введите номер элемента, который вы хотите получить из списка: "; cin >> number;

		number--;

		Iterator it = list.first();
		it += number;

		cout << *it << endl;

		cout << list[number] << endl;
	}
	catch (BasicError& err)
	{
		err.PrintError();
	}	
}
