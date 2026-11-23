// Лабораторная работа №5. Вариант 22.
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
