/*
* Лабораторная работа №4
* Реализация дека (шаблонный класс)
* с операциями вставки, удаления с обоих концов
* Конструкторы: копирования, по умолчанию, задания размерности
* Перегрузка операции
* Вывод дека
* 213 группа, Сергеев В.С.
*/

#include <iostream>

template <class T> class Deque;
template<typename T> double operator!(Deque<T>& ob) {
    return ob.middle();
}

template <class T>
class Deque {
private:
    template <class T>
    class Node {
    public:
        T data;
        Node<T>* next;
        Node(T data) {
            this->data = data;
            this->next = nullptr;
        }
    };
    void init();
    Node<T>* First;
    Node<T>* End;
public:    
    Deque(); // конструктор по умолчанию
    Deque(int size, T value); // n элементов заданного значения
    Deque(const Deque&); // конструктор копирования

    // вставка
    void push_back(T data);
    void push_end(T data);
    
    // удаление
    void pop_back();
    void pop_end();

    // вывод
    void print();

    // среднее арифметическое
    double middle(); 
    friend double operator !<T>(Deque& ob);
};

template<class T> void Deque<T>::init() {
    this->First = nullptr;
    this->End = nullptr;
}

template<typename T> Deque<T>::Deque() {
    this->init();
}

template<typename T> Deque<T>::Deque(int size, T value) {
    this->init();
    for (int i = 0; i < size; i++) {
        this->push_end(value);
    }
}

template<typename T> Deque<T>::Deque(const Deque& copy)
{
    this->init();
    Node<T>* element = copy.First;
    while (element) {
        this->push_end(element->data);
        element = element->next;
    }
}

template<typename T> void Deque<T>::push_back(T data)
{
    Node<T>* element = new Node<T>(data);
    element->next = this->First;
    this->First = element;
    if (this->End == nullptr) this->End = element;
}

template<typename T> void Deque<T>::push_end(T data)
{
    Node<T>* element = new Node<T>(data);
    element->next = nullptr;
    if (this->End == nullptr) {
        this->End = element;
        this->First = element;
    }
    this->End->next = element;
    this->End = element;
    if (this->First == nullptr) this->First = element;
}

template<typename T> void Deque<T>::pop_back()
{
    Node<T>* f = this->First;
    this->First = f->next;
    delete f;
}

template<typename T> void Deque<T>::pop_end()
{
    Node<T>* end = this->End;
    Node<T>* start = this->First;
    while (start) {
        if (start->next == end) {
            start->next = nullptr;
            delete end;
            return;
        }
        start = start->next;
    }
}

template<typename T> void Deque<T>::print()
{
    Node<T>* p = this->First;
    std::cout << std::endl;
    std::cout << "---------" << std::endl;
    while (p) {
        std::cout << p->data << std::endl;
        p = p->next;
    }
    std::cout << "---------" << std::endl;
}

template<typename T> double Deque<T>::middle() {
    double S = 0;
    int count = 0;
    Node<T>* p = this->First;
    while (p) {
        S = S + p->data;
        count++;
        p = p->next;
    }
    return S / count;
}

// Тестирование, управляющая конструкция
int main()
{
    Deque<int>* D = new Deque<int>();
    D->push_back(1);
    D->push_back(1);
    D->push_end(2);
    D->push_back(2);
    D->print();
    D->pop_back();
    D->pop_end();
    D->print();
    
    Deque<float> D2 = Deque<float>(5,15);
    
    double t = !D2;
    std::cout << t;
    Deque<float> D3(D2);
    D3.print();
}
