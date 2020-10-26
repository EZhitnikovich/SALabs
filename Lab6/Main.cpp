#include <iostream>
#include <ctime>

using namespace std;

int ShellSort(int* arr, int len)
{
    int permutations = 0;

    for (int gap = len / 2; gap > 0; gap = gap / 2) {
        for (int j = gap; j < len; j++) {
            for (int k = j - gap; k >= 0; k -= gap) {
                if (arr[k + gap] >= arr[k])
                    break;
                else
                {
                    int temp;
                    temp = arr[k + gap];
                    arr[k + gap] = arr[k];
                    arr[k] = temp;
                    permutations++;
                }
            }
        }
    }

    return permutations;
}

int* LineSearch(int* arr, int len, int elem)
{
    int answer[2];
    int operations = 0;

    answer[1] = -1;

    for (int i = 0; i < len; i++)
    {
        if (arr[i] == elem)
        {
            answer[1] = i;
            break;
        }
        operations++;
    }

    answer[0] = operations++;

    return answer;
}

int* BinarSearch(int* arr, int len, int elem)
{
    int answer[2];
    int operations = 0;

    answer[1] = -1;

    int left = 0;
    int right = len;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (elem == arr[mid])
        {
            answer[1] = mid;
            break;
        }
        if (elem < arr[mid])
            right = mid - 1;
        else
            left = mid + 1;
        operations++;
    }

    answer[0] = operations++;

    return answer;
}

void PrintArray(int* arr, int len)
{
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));

    cout << "Введите кол-во элементов массива: ";

    int len;
    cin >> len;

    int* arr = new int[len];

    for (int i = 0; i < len; i++)
    {
        arr[i] = -100 + rand() / (200);
    }

    cout << "Исходный массив: \n";
    PrintArray(arr, len);

    int shellResult = ShellSort(arr, len);

    cout << "Перестановок: " << shellResult << endl;
    PrintArray(arr, len);

    int elem;

    cout << "Введите элемент поиска: ";
    cin >> elem;

    cout << "Линейный поиск\n";
    int* lineResult = LineSearch(arr, len, elem);
    cout << "Кол-во операций: " << lineResult[0] << ", позиция в массиве: " << lineResult[1] << endl;

    cout << "Бинарный поиск\n";
    int* BinarResult = BinarSearch(arr, len, elem);
    cout << "Кол-во операций: " << BinarResult[0] << ", позиция в массиве: " << BinarResult[1] << endl;
}