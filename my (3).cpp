// my.cpp — демонстрация всех операций класса Queue на очередях, введённых вручную
// Сборка: g++ -Wall -Wextra -g my.cpp Queue.cpp -o my
#include <iostream>
#include <stdexcept>
#include "Queue.h"

using std::cout;

int main()
{
    Queue a, b;
    int x;

    // 1. Ввод с клавиатуры (operator>> для istream)
    cout << "Введите очередь a (n и n чисел): ";
    std::cin >> a;
    cout << "Введите очередь b (n и n чисел): ";
    std::cin >> b;
    cout << "Введите число x: ";
    std::cin >> x;
    if (!std::cin) {
        cout << "Некорректный ввод\n";
        return 1;
    }
    cout << "\n1. Ввод/вывод (cout << q):  a = " << a << ", b = " << b
         << ", x = " << x << "\n\n";

    // Все дальнейшие операции идут над копиями, чтобы a и b не менялись
    // 2. q << x: положить в конец
    Queue t(a);
    t << x;
    cout << "2. t = a; t << x:            t = " << t << "\n\n";

    // 3. q >> y: вытащить первый
    cout << "3. t >> y:                   ";
    if (t.empty()) {
        cout << "t пуста, пропуск\n\n";
    } else {
        int y;
        t >> y;
        cout << "y = " << y << ", t = " << t << "\n\n";
    }

    // 4. Операции дэка
    Queue dq(a);
    dq.push_front(x);
    cout << "4. dq = a; dq.push_front(x): dq = " << dq << '\n';
    dq.push_back(x);
    cout << "   dq.push_back(x):          dq = " << dq << '\n';
    cout << "   dq.pop_back():            " << dq.pop_back() << ", dq = " << dq << '\n';
    cout << "   dq.pop_front():           " << dq.pop_front() << ", dq = " << dq << '\n';
    if (dq.empty())
        cout << "   front() / back():         dq пуста, пропуск\n";
    else
        cout << "   front() / back():         " << dq.front() << " / " << dq.back() << '\n';
    cout << "   size() / empty():         " << dq.size() << " / " << dq.empty() << "\n\n";

    // 5. Конструктор копирования и присваивание
    Queue c(a);
    c << x;
    cout << "5. Queue c(a); c << x:       c = " << c << ", a = " << a << '\n';
    Queue d;
    d = b;
    cout << "   d = b:                    d = " << d << "\n\n";

    // 6. Объединение
    Queue s = a + b;
    cout << "6. a + b:                    " << s << '\n';
    Queue u(a);
    u += b;
    cout << "   u = a; u += b:            u = " << u << "\n\n";

    // 7. Сравнения a и b
    cout << "7. Сравнение a = " << a << " и b = " << b << '\n';
    cout << "   a == b: " << (a == b) << "   a != b: " << (a != b) << '\n';
    cout << "   a <  b: " << (a < b)  << "   a <= b: " << (a <= b) << '\n';
    cout << "   a >  b: " << (a > b)  << "   a >= b: " << (a >= b) << "\n\n";

    // 8. Исключение на пустой очереди
    Queue e;
    cout << "8. Извлечение из пустой очереди: ";
    try {
        e.pop_front();
    } catch (const std::out_of_range& ex) {
        cout << "Ошибка: " << ex.what() << '\n';
    }
    return 0;
}
