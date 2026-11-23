## Московский государственный технический университет имени Н.Э. Баумана

# Отчёт по лабораторной работе № 5

**Тема:** Изучение использования объектов своих классов в упорядоченных и неупорядоченных контейнерах библиотеки STL (`set`, `unordered_set`)

**Выполнила:** Смирнова Полина Игоревна  
**Проверил:** Барыкин Дмиртий Ваильевич  
**Группа:** ИУ8-14  
**Вариант:** 22

**Москва, 2026**

---


## 1. Цель работы

Изучить использование объектов своих классов в упорядоченных (`set`) и неупорядоченных (`unordered_set`) контейнерах STL и выяснить, какие операции должен поддерживать класс для работы с ними.

## 2. Задание

Для класса, разработанного в ЛР4, обеспечить возможность добавления объектов в контейнер `set` (сортировка по сумме кредита, как в ЛР4) и в контейнер `unordered_set`. Исходные данные, как в ЛР4, читать из файла, вывести на печать для контроля объекты контейнеров.

Вариант 22: объект — банковский кредит (поля: название, сумма кредита, тип валюты, ставка в % годовых), сортировка по сумме кредита.

## 3. Описание программы

### 3.1. Класс `Credit`

Класс взят из ЛР4 и дополнен операциями для `unordered_set`.

| Поле | Тип | Назначение |
|---|---|---|
| `name` | `string` | название кредита |
| `amount` | `double` | сумма кредита |
| `currency` | `string` | тип валюты (RUB, USD, EUR) |
| `rate` | `double` | ставка в % годовых |

Методы класса:

- **конструктор без параметров** и **конструктор с параметрами** (инициализация всех полей);
- **`operator <`** — сравнение по сумме кредита (из ЛР4), определяет порядок и уникальность в `set`;
- **`operator ==`** — равенство по всем полям, нужно для `unordered_set`;
- **`hash_value()`** и специализация **`std::hash<Credit>`** — хеш по всем полям, нужен для `unordered_set`;
- **дружественная `operator <<`** — вставка объекта в поток вывода.

### 3.2. Что потребовалось добавить в класс

| Контейнер | Что нужно классу | Как реализовано |
|---|---|---|
| `set` | строгое слабое упорядочение (`operator <`) | уже есть из ЛР4, сравнение по сумме кредита |
| `unordered_set` | операция `==` и хеш-функция `std::hash<Credit>` | добавлены `operator ==`, метод `hash_value()` и специализация `std::hash<Credit>` |

Для хеш-функции значения хешей полей (`name`, `amount`, `currency`, `rate`) объединяются по формуле `h = h * 31 + hash(поле)`. Хеш согласован с `operator ==`: равные объекты (совпадают все поля) имеют равные хеши.

### 3.3. Обоснование отсутствия конструкторов копирования и перемещения и операций присваивания

В классе нет указателей и динамической памяти, которой управлял бы сам класс. Поля `string` и `double` корректно копируются и перемещаются стандартными средствами, поэтому конструкторы копирования и перемещения и операции присваивания, создаваемые компилятором, подходят и писать их вручную не нужно (правило нуля). При вставке в `set` и `unordered_set` объекты копируются именно этими методами.

### 3.4. Ход работы программы

1. Открываются файлы; при отсутствии входного файла выводится сообщение об ошибке.
2. Данные читаются из `input.txt` в вектор и выводятся для контроля.
3. Каждый объект добавляется в `set` и в `unordered_set` методом `insert`; по значению `.second` результата определяется, добавлен ли объект.
4. Выводятся содержимое `set` (упорядочено по сумме) и содержимое `unordered_set` (порядок не определён).
5. Выполняется поиск пробного объекта, у которого совпадает только сумма: `set::find` и `unordered_set::find`, а также `count`.

### 3.5. Формат входного файла

В первой строке — число кредитов. Далее для каждого кредита две строки: название; сумма, тип валюты и ставка через пробел. Названия и подписи в выводе написаны латиницей, чтобы не было проблем с кодировкой в файлах.

Во входном файле намеренно есть точный дубликат (`Student Credit`) и два кредита с одинаковой суммой, но разными остальными полями (`Consumer Credit` и `Express Credit`), чтобы показать разницу в поведении контейнеров.

## 4. Входные данные (`input.txt`)

```text
8
Mortgage Standard
4500000.00 RUB 11.5
Auto Loan Fast
1200000.50 RUB 14.9
Student Credit
350000 RUB 5.5
Business Start
25000.75 USD 9.2
Consumer Credit
80000 EUR 12
Student Credit
350000 RUB 5.5
Home Repair
150000.00 RUB 10.8
Express Credit
80000 EUR 13.5
```

## 5. Результаты работы (`output.txt`)

```text
Source data (as read from file):
Mortgage Standard, amount 4500000.00 RUB, rate 11.50% per year
Auto Loan Fast, amount 1200000.50 RUB, rate 14.90% per year
Student Credit, amount 350000.00 RUB, rate 5.50% per year
Business Start, amount 25000.75 USD, rate 9.20% per year
Consumer Credit, amount 80000.00 EUR, rate 12.00% per year
Student Credit, amount 350000.00 RUB, rate 5.50% per year
Home Repair, amount 150000.00 RUB, rate 10.80% per year
Express Credit, amount 80000.00 EUR, rate 13.50% per year

Inserting objects:
Mortgage Standard, amount 4500000.00 RUB, rate 11.50% per year
    set: inserted; unordered_set: inserted
Auto Loan Fast, amount 1200000.50 RUB, rate 14.90% per year
    set: inserted; unordered_set: inserted
Student Credit, amount 350000.00 RUB, rate 5.50% per year
    set: inserted; unordered_set: inserted
Business Start, amount 25000.75 USD, rate 9.20% per year
    set: inserted; unordered_set: inserted
Consumer Credit, amount 80000.00 EUR, rate 12.00% per year
    set: inserted; unordered_set: inserted
Student Credit, amount 350000.00 RUB, rate 5.50% per year
    set: rejected (same amount already exists); unordered_set: rejected (equal object already exists)
Home Repair, amount 150000.00 RUB, rate 10.80% per year
    set: inserted; unordered_set: inserted
Express Credit, amount 80000.00 EUR, rate 13.50% per year
    set: rejected (same amount already exists); unordered_set: inserted

Container set (sorted by amount), size 6:
Business Start, amount 25000.75 USD, rate 9.20% per year
Consumer Credit, amount 80000.00 EUR, rate 12.00% per year
Home Repair, amount 150000.00 RUB, rate 10.80% per year
Student Credit, amount 350000.00 RUB, rate 5.50% per year
Auto Loan Fast, amount 1200000.50 RUB, rate 14.90% per year
Mortgage Standard, amount 4500000.00 RUB, rate 11.50% per year

Container unordered_set (order not defined), size 7:
Consumer Credit, amount 80000.00 EUR, rate 12.00% per year
Express Credit, amount 80000.00 EUR, rate 13.50% per year
Business Start, amount 25000.75 USD, rate 9.20% per year
Student Credit, amount 350000.00 RUB, rate 5.50% per year
Home Repair, amount 150000.00 RUB, rate 10.80% per year
Auto Loan Fast, amount 1200000.50 RUB, rate 14.90% per year
Mortgage Standard, amount 4500000.00 RUB, rate 11.50% per year

Search for object with amount 350000.00 and other fields different:
    set::find: found (comparison by amount only)
    unordered_set::find: not found (comparison by all fields)
    set::count of first source object: 1, unordered_set::count: 1
```

Порядок вывода элементов `unordered_set` зависит от реализации библиотеки и может отличаться на других компиляторах.

## 6. Анализ результатов

- В `set` попало 6 элементов из 8. Точный дубликат `Student Credit` отклонён, и `Express Credit` тоже отклонён: у него та же сумма, что у `Consumer Credit`, а `set` считает объекты эквивалентными, если ни один не меньше другого по `operator <`, то есть по сумме.
- В `unordered_set` попало 7 элементов из 8. Отклонён только точный дубликат, так как уникальность определяют `operator ==` и хеш по всем полям, а `Express Credit` отличается от `Consumer Credit` ставкой и названием.
- `set::find` нашёл пробный объект, у которого совпадает только сумма (сравнение по сумме), а `unordered_set::find` — нет (сравнение по всем полям).

## 7. Листинг программы (`main.cpp`)

```cpp
// Лабораторная работа №5. Вариант 22.
// Объект - банковский кредит (поля: название, сумма кредита, тип валюты, ставка в % годовых).
// Класс из ЛР4: добавляем объекты в контейнер set (сортировка по сумме кредита)
// и в контейнер unordered_set. Исходные данные читаются из input.txt,
// объекты контейнеров выводятся в output.txt.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <functional> // hash
using namespace std;

class Credit // Класс - банковский кредит (из ЛР4, добавлены operator == и хеш)
{
    string name;     // Название кредита
    double amount;   // Сумма кредита
    string currency; // Тип валюты
    double rate;     // Ставка в % годовых
public:
    Credit() // Конструктор без параметров
    {
        name = "";
        amount = 0;
        currency = "";
        rate = 0;
    }
    Credit(string name, double amount, string currency, double rate) // Конструктор для инициализации полей
    {
        this->name = name;
        this->amount = amount;
        this->currency = currency;
        this->rate = rate;
    }
    // Конструктор копирования, конструктор перемещения и операции присваивания (с копированием и
    // с перемещением) писать не нужно: в классе нет указателей и динамической памяти, которой
    // владел бы сам класс. Поля string, double копируются и перемещаются корректно стандартными
    // средствами, поэтому подходят методы, которые автоматически создает компилятор.
    bool operator <(const Credit & c) const // Сравнение по сумме кредита (для set)
    {
        return amount < c.amount;
    }
    bool operator ==(const Credit & c) const // Равенство по всем полям (нужно для unordered_set)
    {
        return name == c.name && amount == c.amount && currency == c.currency && rate == c.rate;
    }
    size_t hash_value() const // Хеш-значение объекта по всем полям (согласовано с операцией ==)
    {
        size_t h = hash<string>()(name);
        h = h * 31 + hash<double>()(amount);
        h = h * 31 + hash<string>()(currency);
        h = h * 31 + hash<double>()(rate);
        return h;
    }
    friend ostream & operator <<(ostream & out, const Credit & c); // Дружественная функция вставки в поток
};
ostream & operator <<(ostream & out, const Credit & c) // Вставка объекта в поток
{
    out << c.name << ", amount " << fixed << setprecision(2) << c.amount << " " << c.currency
        << ", rate " << c.rate << "% per year";
    return out;
}
namespace std // Специализация hash для класса Credit (нужна для unordered_set)
{
    template <> struct hash<Credit>
    {
        size_t operator ()(const Credit & c) const
        {
            return c.hash_value();
        }
    };
}

int main()
{
    ifstream fin("input.txt");   // Входной файл
    ofstream fout("output.txt"); // Выходной файл
    if (!fin) // Ошибка файл не открыт
    {
        cerr << "Error, input.txt not found" << endl;
        return 1;
    }
    int n; // Число кредитов
    fin >> n;
    fin.ignore(256, '\n'); // Пропускаем символы перехода на новую строку
    vector<Credit> data; // Прочитанные из файла данные
    for (int i = 0; i < n; i++) // Читаем кредиты из файла
    {
        string name, currency;
        double amount, rate;
        getline(fin, name); // Название - строка, может содержать пробелы
        if (!name.empty() && name.back() == '\r') name.pop_back(); // Файл с Windows переводами строк
        fin >> amount >> currency >> rate; // Остальные поля в одной строке
        fin.ignore(256, '\n');
        data.push_back(Credit(name, amount, currency, rate));
    }

    fout << "Source data (as read from file):" << endl;
    for (const Credit & c : data) fout << c << endl;

    set<Credit> s;            // Упорядоченный контейнер: порядок и уникальность определяет operator <
    unordered_set<Credit> us; // Неупорядоченный контейнер: уникальность определяют hash и operator ==
    fout << endl << "Inserting objects:" << endl;
    for (const Credit & c : data)
    {
        bool inSet = s.insert(c).second;   // insert возвращает пару, second - признак вставки
        bool inUnset = us.insert(c).second;
        fout << c << endl << "    set: " << (inSet ? "inserted" : "rejected (same amount already exists)")
             << "; unordered_set: " << (inUnset ? "inserted" : "rejected (equal object already exists)") << endl;
    }

    fout << endl << "Container set (sorted by amount), size " << s.size() << ":" << endl;
    for (const Credit & c : s) fout << c << endl;

    fout << endl << "Container unordered_set (order not defined), size " << us.size() << ":" << endl;
    for (const Credit & c : us) fout << c << endl;

    if (n > 0) // Поиск в контейнерах: пробный объект совпадает с одним из кредитов только суммой
    {
        Credit probe("Probe", 350000, "XXX", 0);
        fout << endl << "Search for object with amount 350000.00 and other fields different:" << endl;
        fout << "    set::find: " << (s.find(probe) != s.end() ? "found" : "not found")
             << " (comparison by amount only)" << endl;
        fout << "    unordered_set::find: " << (us.find(probe) != us.end() ? "found" : "not found")
             << " (comparison by all fields)" << endl;
        fout << "    set::count of first source object: " << s.count(data[0])
             << ", unordered_set::count: " << us.count(data[0]) << endl;
    }
    return 0;
}
```

## 8. Вывод

Объекты класса `Credit` из ЛР4 добавлены в контейнеры `set` и `unordered_set`. Для `set` достаточно перегруженной операции `<` (по сумме кредита): контейнер хранит элементы упорядоченно, а уникальность определяет именно это сравнение, поэтому разные кредиты с одинаковой суммой считаются одинаковыми и второй не добавляется. Для `unordered_set` в класс добавлены операция `==` и хеш-функция (специализация `std::hash<Credit>`), согласованные между собой; порядок элементов при этом не определён, а уникальность определяется равенством всех полей. Таким образом, выбор контейнера и операций класса влияет на то, какие объекты считаются одинаковыми, что показано на тестовых данных с дубликатом и с одинаковой суммой.
