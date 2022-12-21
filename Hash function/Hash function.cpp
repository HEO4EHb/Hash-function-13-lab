#include <iostream>
#include <string>
#include <fstream>
#include <wchar.h>
#include <Windows.h>

#define PRIME_SIZE 4 // Использовано просто число

using namespace std;

class HashTable
{
    wstring table[PRIME_SIZE];

    // Считает сумму ASCII кодов, делит на константу и
    // получает остаток от деления.
    static int hash(wstring str)
    {
        int SumASCII = 0;
        for (int i = 0; i < str.length(); i++)
        {
            SumASCII += str[i];
        }
        return SumASCII % PRIME_SIZE;
    }

public:

    HashTable()
    {
        for (int i = 0; i < PRIME_SIZE; i++)
        {
            table[i] = L"";
        }
    }

    // Вставляет элемент в таблицу
    void add(wstring newStr)
    {
        int hashNumber = hash(newStr);

        while (table[hashNumber] != L"")
        {
            hashNumber++;
            if (hashNumber >= PRIME_SIZE)
            {
                wcout << '"' << newStr << '"' << L":  out of space in table (end) " << endl;
                return;
            }
        }
        table[hashNumber] = newStr;
    }

    // Считываем string
    wstring getString(int i)
    {
        return table[i];
    }
};

int main()
{
    setlocale(LC_ALL, "rus");

    HashTable NewTab;

    wifstream input("input.txt");

    if (!input.is_open())
    {
        cout << " input.txt is missing" << endl << "Closing application" << endl;
        return 1;
    }

    wofstream output("output.txt");

    wstring newString = L"";

    wchar_t newChar = ' ';

    // Посимвольно считываем из файла string и вставляем в таблицу
    while (!input.eof())
    {
        input.get(newChar);
        if ((newChar == L' ' && newString != L"") || (newChar == L'\n' && newString != L""))
        {
            NewTab.add(newString);
            newString = L"";
        }
        else
        {
            newString += newChar;
        }
    }
    if (newChar != ' ')
    {
        newString.erase(newString.size() - 1, 1);
        NewTab.add(newString);
    }
    input.close();

    //Выводим таблицу
    for (int i = 0; i < PRIME_SIZE; i++)
    {
        output << i << " -- " << NewTab.getString(i) << endl;
    }
    output.close();

    cout << "Table size = " << PRIME_SIZE << endl;
    cout << "Recorded in output.txt" << endl;

    return 0;
}
