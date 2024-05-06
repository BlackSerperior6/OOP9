#pragma once

#include "NegativeIndexError.h"
#include "IndexOutOfRangeError.h"
#include "EmptyColletionError.h"
#include "OverflowError.h"

#include <iostream>

using namespace std;

//Искуствено заданое максимальное кол-во элементов.
//Необходим для демонстрации работы ошибки IndexOutOfRang.
const int MAX_SIZE = 30; 


struct Node //Структура элемента списка
{
	Node* next = nullptr; //Указатель на следующий элемент
	Node* prev = nullptr; //Указатель на предыдущий
	int Data; //Данные элемента
};

class Iterator //Класс итератора списка
{
public:

    friend class List; //Список дружествен к итератору

    Iterator() { Element = nullptr; } //Конструктор без параметров

    Iterator& operator=(Iterator& anotherIterator) //Перегруженный оператор присваивания
    {
        Element = anotherIterator.Element;
        return *this;
    }
    
    bool operator==(Iterator& anotherIterator)//Оператор сравнения ит
    {
        return Element == anotherIterator.Element;
    }

    bool operator!=(Iterator& anotherIterator)
    {
        return Element != anotherIterator.Element;
    }

    Iterator& operator+=(int number)
    {
        if (number < 0) //Генерация ошибка о негативном индексе
            throw NegativeIndexError();

        for (int i = 0; i < number && Element != nullptr; i++)
            Element = Element->next;

        if (Element == nullptr) //Генерация ошибки о выходе за границы
            throw IndexOutOfRangeError();

        return *this;
    }

    //Операцтор разыменовывания
    int& operator*() { return Element->Data; }

private:
    Node* Element; //Итератор содержит указатель на элемент списка
};

class List
{
public:

    //Конструктор без параметров
    List() { head = nullptr, tail = nullptr, Lenght = 0, 
        beg.Element = head, end.Element = tail; }

    //Конструктор чистит список
    ~List() { Clear(); }

    Iterator first() { return beg; } //Получае итератор начала списка

    Iterator last() { return end; } //Получает итератор конца списка

    void Push_Back(int element) //Метод добавления элемента в конец списка
    {
        if (Lenght + 1 > MAX_SIZE) //Генерация ошибка о попытке выйти за предел
            throw OverflowError();

        Node* new_node = new Node;
        new_node->Data = element;

        if (head == nullptr)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }

        beg.Element = head;
        end.Element = tail;

        Lenght++;
    }

    void Push_Front(int element) //Метод добавления элемента в начало списка
    {
        if (Lenght + 1 > MAX_SIZE) //Генерация ошибка о попытке выйти за предел
            throw OverflowError();

        Node* new_node = new Node;
        new_node->Data = element;

        if (head == nullptr)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }

        beg.Element = head;
        end.Element = tail;

        Lenght++;
    }

    void Pop_Back() 
    {
        if (head == nullptr)
            throw EmptyColletionError();

        Node* tmp;

        if (head == tail)
        {
            tmp = head;

            head = nullptr;
            tail = nullptr;
        }
        else
        {
            tmp = tail;
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete tmp;

        beg.Element = head;
        end.Element = tail;

        Lenght--;
    }

    void Pop_Front() //Метода удаления элемента из начала списка
    {
        if (head == nullptr) //Генерация ошибки о попытке удаления элемента из пустого списка
            throw EmptyColletionError();

        if (head == tail)
        {
            Node* tmp = head;

            head = nullptr;
            tail = nullptr;
            delete tmp;
        }
        else
        {
            Node* tmp = head;
            head = head->next;
            head->prev = nullptr;
            delete tmp;
        }

        beg.Element = head;
        end.Element = tail;

        Lenght--;
    }

    int& operator[](int index) //Прямой доступ по индексу
    {
        if (index >= Lenght) //Генерация ошибки о слишком большом индексе
            throw IndexOutOfRangeError();
        
        if (index < 0) //Генерация ошибки о негативном индексе
            throw NegativeIndexError();

        Node* current = head;

        for (int i = 0; i < index; i++)
            current = current->next;

        return current->Data;
    }

    List& operator=(List& anotherList)
    {
        if (this != &anotherList)
        {
            Clear();

            Node* current = anotherList.head;

            while (current != nullptr)
            {
                Push_Back(current->Data);
                current = current->next;
            }
        }

        return *this;
    }

    int operator()() { return Lenght; }

    List& operator*=(List& anotherList)
    {
        int SmallerLenght = (anotherList.Lenght > Lenght) ? Lenght : anotherList.Lenght;

        for (int i = 0; i < SmallerLenght; i++)
            (*this)[i] *= anotherList[i];

        return *this;
    }

    int& operator+(int& n)
    {
        if (n >= Lenght)
            throw IndexOutOfRangeError();

        if (n < 0)
            throw IndexOutOfRangeError();

        Node* current = head;

        for (int i = 0; i < n; i++)
            current = current->next;

        return current->Data;
    }

    void Clear()
    {
        while (head != nullptr)
        {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }

        tail = nullptr;

        beg.Element = nullptr;
        end.Element = nullptr;

        Lenght = 0;
    }

    friend istream& operator>>(istream& stream, List& list);

    friend ostream& operator<<(ostream& stream, List& list);

private:

	Node* head;
	Node* tail;

    Iterator beg;
    Iterator end;

	int Lenght;
};

istream& operator>>(istream& stream, List& list) 
{
    list.Clear();

    int Lenght;

    cout << "Введите длину списка: "; stream >> Lenght;

    if (Lenght > MAX_SIZE)
        throw OverflowError();

    if (Lenght <= 0)
        throw EmptyColletionError();

    for (int i = 0; i < Lenght; i++)
    {
        int data;
        cout << "Введите данные: "; stream >> data;
        list.Push_Back(data);
    }

    return stream;
}

ostream& operator<<(ostream& stream, List& list)
{
    if (list.Lenght == 0)
        throw EmptyColletionError();

    Node* current = list.head;

    stream << current->Data;

    current = current->next;

    while (current != nullptr)
    {
        stream << " " << current->Data;
        current = current->next;
    }

    return stream;
}

