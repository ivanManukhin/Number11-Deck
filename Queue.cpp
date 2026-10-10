// Queue.cpp
#include "Queue.h"
#include <stdexcept>
#include <utility>

Queue::Queue(unsigned int capacity)
    : cap(capacity ? capacity : 1), head(0), count(0), data(new int[cap])
{
}

Queue::Queue(const Queue& other)
    : cap(other.cap), head(0), count(other.count), data(new int[other.cap])
{
    for (unsigned int i = 0; i < count; i++)
        data[i] = other.data[other.idx(i)];
}

const Queue& Queue::operator=(const Queue& other)
{
    Queue tmp(other);   // копия (если new бросит исключение, *this не пострадает)
    swap(tmp);          // меняем содержимое
    return *this;       // старые данные удалит деструктор tmp
}

void Queue::swap(Queue& other)
{
    std::swap(cap, other.cap);
    std::swap(head, other.head);
    std::swap(count, other.count);
    std::swap(data, other.data);
}

int Queue::front() const
{
    if (count == 0) throw std::out_of_range("Queue::front: queue is empty");
    return data[head];
}

int Queue::back() const
{
    if (count == 0) throw std::out_of_range("Queue::back: queue is empty");
    return data[idx(count - 1)];
}

int Queue::at(unsigned int i) const
{
    if (i >= count) throw std::out_of_range("Queue::at: index out of range");
    return data[idx(i)];
}

void Queue::clear()
{
    head = 0;
    count = 0;
}

void Queue::grow()
{
    unsigned int new_cap = cap * 2;
    int *new_data = new int[new_cap];
    for (unsigned int i = 0; i < count; i++)
        new_data[i] = data[idx(i)];     // «распрямляем» кольцо
    delete [] data;
    data = new_data;
    cap = new_cap;
    head = 0;
}

void Queue::push_back(int x)
{
    if (count == cap) grow();
    data[idx(count)] = x;
    count++;
}

void Queue::push_front(int x)
{
    if (count == cap) grow();
    head = (head + cap - 1) % cap;
    data[head] = x;
    count++;
}

int Queue::pop_front()
{
    if (count == 0) throw std::out_of_range("Queue::pop_front: queue is empty");
    int x = data[head];
    head = (head + 1) % cap;
    count--;
    return x;
}

int Queue::pop_back()
{
    if (count == 0) throw std::out_of_range("Queue::pop_back: queue is empty");
    count--;
    return data[idx(count)];
}

const Queue& Queue::operator+=(const Queue& other)
{
    unsigned int n = other.count;       // запоминаем: при q += q размер растёт
    for (unsigned int i = 0; i < n; i++)
        push_back(other.data[other.idx(i)]);
    return *this;
}

Queue Queue::operator+(const Queue& other) const
{
    Queue res(*this);
    res += other;
    return res;
}

int Queue::compare(const Queue& other) const
{
    unsigned int n = (count < other.count) ? count : other.count;
    for (unsigned int i = 0; i < n; i++) {
        int a = data[idx(i)];
        int b = other.data[other.idx(i)];
        if (a < b) return -1;
        if (a > b) return 1;
    }
    if (count < other.count) return -1;     // префикс меньше
    if (count > other.count) return 1;
    return 0;
}

Queue& Queue::operator<<(int x)
{
    push_back(x);
    return *this;
}

Queue& Queue::operator>>(int& x)
{
    x = pop_front();
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Queue& q)
{
    out << '[';
    for (unsigned int i = 0; i < q.size(); i++) {
        if (i > 0) out << ' ';
        out << q.at(i);
    }
    out << ']';
    return out;
}

std::istream& operator>>(std::istream& in, Queue& q)
{
    long long n;
    if (!(in >> n) || n < 0) {
        in.setstate(std::ios::failbit);
        return in;
    }
    Queue tmp;
    for (long long i = 0; i < n; i++) {
        int x;
        if (!(in >> x)) return in;      // q остаётся без изменений
        tmp.push_back(x);
    }
    q = tmp;
    return in;
}
