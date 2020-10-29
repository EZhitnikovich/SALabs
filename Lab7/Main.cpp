#include <iostream>
#include <vector>
#include <string>

using namespace std;

int Find(string str, string templ)
{
    int  i, j, strlen, templlen;

    strlen = str.length();
    templlen = templ.length();
    int* d = new int[templlen];

    i = 0;
    j = -1;
    d[0] = -1;
    while (i < templlen - 1)
    {
        while ((j >= 0) && (templ[j] != templ[i]))
            j = d[j];
        ++i;
        ++j;
        d[i] = (templ[i] == templ[j]) ? d[j] : j;
    }

    for (i = 0, j = 0; (i <= strlen - 1) && (j <= templlen - 1); ++i, ++j)
        while ((j >= 0) && (templ[j] != str[i]))
            j = d[j];
    delete[] d;

    return (j == templlen) ? i - j : -1;
}

int main()
{
    setlocale(LC_ALL, "rus");

    string source, pattern;

    cout << "Введите ФИО: ";
    getline(cin, source);

    cout << "Введите шаблон: ";
    getline(cin, pattern);

    cout << Find(source, pattern);
}