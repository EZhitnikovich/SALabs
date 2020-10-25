#include <iostream>
#include <ctime>

using namespace std;

int* BubleSort(int* arr, int len)
{
    int temp;
    int answer[2];
    int comparisons = 0;
    int permutations = 0;

    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                permutations++;
            }
            comparisons++;
        }
    }

    answer[0] = comparisons;
    answer[1] = permutations;

    return answer;
}

int* ShellSort(int* arr, int len)
{
    int answer[2];
    int comparisons = 0;
    int permutations = 0;

    int j, k;
    for (int gap = len / 2; gap > 0; gap = gap / 2) {
        for (j = gap; j < len; j++) {
            for (k = j - gap; k >= 0; k -= gap) {
                comparisons++;
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

    answer[0] = comparisons;
    answer[1] = permutations;

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

    int* arr1 = new int[len];
    int* arr2 = new int[len];

    for (int i = 0; i < len; i++)
    {
        arr1[i] = rand() % 100 + 1;
        arr2[i] = rand() % 100 + 1;
    }

    cout << "Исходный массив: \n";
    PrintArray(arr1, len);

    int* bubleResult = BubleSort(arr1, len);

    cout << "Сравнений: " << bubleResult[0] << ", перестановок: " << bubleResult[1] << endl;
    PrintArray(arr1, len);

    int* shellResult = ShellSort(arr2, len);

    cout << "Сравнений: " << shellResult[0] << ", перестановок: " << shellResult[1] << endl;
    PrintArray(arr2, len);

}