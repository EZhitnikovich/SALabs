#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Aeroflot {
    char destination[20]{};
    char number[5]{};
    char type[6]{};
};

void PutInFile(string fileName, Aeroflot* arr, int len);

void SortArray(Aeroflot* arr, int size);

void FindInfo(Aeroflot* arr, int size);

void ReadFile(string fileName, Aeroflot* arr, int size);

void ShowArray(Aeroflot* arr, int size);

void FillArray(Aeroflot* arr, int size);

void MainInfo();

int InputIntNumber();

int main()
{
    setlocale(LC_ALL, "RUS");
    system("chcp 1251");

    int size = 3;

    Aeroflot* arr = new Aeroflot[size];

    bool loop = true;

    while (loop)
    {
        cin.clear();
        MainInfo();

        int i;
        cout << "Введите номер пункта: ";
        i = InputIntNumber();

        switch (i)
        {
        
        case 1:
            FillArray(arr, size);
            break;

        case 2:
        {
            cout << "Введите название файла: ";

            string filename;

			cin >> filename;
            cin.clear();

            PutInFile(filename, arr, size);
            break;
        }
        case 3:
            ShowArray(arr, size);
            break;

        case 4:
        {
            cout << "Введите название файла: ";

            string filename;

            cin >> filename;
            cin.clear();

            ReadFile(filename, arr, size);
            break;
        }
        case 5:
            SortArray(arr, size);
            break;
        
        case 6:
            FindInfo(arr, size);
            break;
        
        case 7:
            loop = false;
            cout << "Работа прекращена\n";
            break;

        default:
            cout << "Неизвестное значение\n";
            break;
        }
        system("pause");
        system("cls");
    }

    delete[] arr;
    system("pause");
}

void MainInfo()
{
    cout << "Возможности консольного приложения Aeroflot:\n";
    cout << "1 - Ручное заполнение структуры\n";
    cout << "2 - Запись структуры в файл\n";
    cout << "3 - Вывод структуры на экран\n";
    cout << "4 - Чтение структуры из файла\n";
    cout << "5 - Сортировка структуры\n";
    cout << "6 - Поиск элемента\n";
    cout << "7 - Выход их приложения\n";

}

int InputIntNumber() {

    const int buff_size = 255;
    char buff[buff_size];
    cin.getline(buff, buff_size);

    return atoi(buff);
}

void CheckFail()
{
    if (cin.fail()) {
        cin.clear();
        cin.ignore(32756, '\n');
    }
}

void FillArray(Aeroflot* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "Введите название пункта назначения: ";
        cin.getline(arr[i].destination, 20, '\n');
        CheckFail();
        cout << "Введите номер рейса: ";
        cin.getline(arr[i].number, 5, '\n');
        CheckFail();
        cout << "Введите тип самолёта: ";
        cin.getline(arr[i].type, 6, '\n');
        CheckFail();
    }
}

void ShowArray(Aeroflot* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "Пункт назначения: " << arr[i].destination << endl;
        cout << "Номер рейса: " << arr[i].number << endl;
        cout << "Тип самолёта: " << arr[i].type << endl;
    }
}

void PutInFile(string fileName, Aeroflot* arr, int len) {

    fstream fout(fileName, ios_base::out | ios_base::trunc);

    if (fout.is_open())
    {
        for (int i = 0; i < len; i++) {
            fout.write((char*)&arr[i].destination, sizeof(arr[i].destination));
            fout.write((char*)&arr[i].number, sizeof(arr[i].number));
            fout.write((char*)&arr[i].type, sizeof(arr[i].type));
            fout << "\n";
        }
        cout << "Структура будет записана в файл " << fileName << endl;
        fout.close();
    }
    else
    {
        cout << "Файл не открыт.\n";
        return;
    }
}

void ReadFile(string fileName, Aeroflot* arr, int size)
{
    fstream fin(fileName, ios::in);

    if (fin.is_open())
    {
        for (int i = 0; i < size; i++) {
            fin.read(arr[i].destination, sizeof arr[i].destination);
            fin.read(arr[i].number, sizeof arr[i].number);
            fin.read(arr[i].type, sizeof arr[i].type + 1);
            cin.clear();
        }
        cout << "Структура прочитана из файла " << fileName << endl;
        fin.close();
    }
    else
    {
        cout << "Файл не открыт.\n";
        return;
    }

    cin.ignore(32756, '\n');
}

void FindInfo(Aeroflot* arr, int size)
{
    char type[6]{};

    cout << "Введите тип самолёта: ";

    cin.getline(type, 6);

    bool exist = false;

    for (int i = 0; i < size; i++) {
        if (strcmp(arr[i].type, type) == 0) {
            exist = true;
            cout << "Пункт назначения: " << arr[i].destination << endl;
            cout << "Номер рейса: " << arr[i].number << endl;
            cout << "Тип самолёта: " << arr[i].type << endl << endl;
        }
    }

    if (!exist) {
        cout << "Тип не найден.\n";
    }
}

void SortArray(Aeroflot* arr, int size) // inserion sort
{
    int j = 0;
    Aeroflot tmp{};

    for (int i = 0; i < size; i++) {
        j = i;
        for (int k = i; k < size; k++) {
            if (atoi(arr[j].number) > atoi(arr[k].number)) {
                j = k;
            }
        }

        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    cout << "Для проверки выведите список(3)\n";
}