// Queue.h
// Очередь целых чисел, реализованная как дэк (двусторонняя очередь)
// на кольцевом буфере (обычный динамический массив, без контейнеров STL).
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

class Queue {
    unsigned int cap;    // размер выделенного массива
    unsigned int head;   // индекс первого элемента в массиве
    unsigned int count;  // число элементов в очереди
    int *data;           // кольцевой буфер

public:
    // ---- Конструкторы, деструктор, присваивание ----
    // Пустая очередь с заданной начальной ёмкостью (explicit: чтобы
    // число не превращалось в очередь неявно, например в q + 5)
    explicit Queue(unsigned int capacity = 8);
    Queue(const Queue& other);                  // конструктор копирования
    ~Queue() { delete [] data; }
    const Queue& operator=(const Queue& other); // copy-and-swap

    // ---- Информация об очереди ----
    unsigned int size() const { return count; }
    bool empty() const { return count == 0; }
    int front() const;                  // первый элемент (исключение, если пусто)
    int back() const;                   // последний элемент (исключение, если пусто)
    int at(unsigned int i) const;       // i-й элемент от начала (0 <= i < size)
    void clear();

    // ---- Операции дэка ----
    void push_back(int x);              // в конец
    void push_front(int x);             // в начало
    int pop_front();                    // вытащить из начала
    int pop_back();                     // вытащить из конца

    // ---- Объединение очередей ----
    Queue operator+(const Queue& other) const;
    const Queue& operator+=(const Queue& other);

    // ---- Сравнение: == и != поэлементно, остальные лексикографически ----
    bool operator==(const Queue& o) const { return compare(o) == 0; }
    bool operator!=(const Queue& o) const { return compare(o) != 0; }
    bool operator<(const Queue& o) const  { return compare(o) < 0; }
    bool operator<=(const Queue& o) const { return compare(o) <= 0; }
    bool operator>(const Queue& o) const  { return compare(o) > 0; }
    bool operator>=(const Queue& o) const { return compare(o) >= 0; }

    // ---- q << x кладёт x в конец, q >> x вытаскивает первый элемент в x ----
    Queue& operator<<(int x);
    Queue& operator>>(int& x);

private:
    unsigned int idx(unsigned int i) const { return (head + i) % cap; }
    int compare(const Queue& other) const;  // -1, 0, 1 (лексикографически)
    void grow();                            // удвоение ёмкости
    void swap(Queue& other);
};

// Вывод вида [1 2 3]. Ввод: сначала количество n, затем n чисел.
// Если ввод некорректен, очередь не меняется, у потока ставится failbit.
std::ostream& operator<<(std::ostream& out, const Queue& q);
std::istream& operator>>(std::istream& in, Queue& q);

#endif
