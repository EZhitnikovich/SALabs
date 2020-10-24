#include <iostream>
using namespace std;

struct List {
    char letter = NULL;
    List* next = NULL;
};

void AddElement(List *head, char letter) {
    
    if (head->next == NULL && head->letter == NULL) {
        head->letter = letter;
    }
    else {
        while (head->next) {
            head = head->next;
        }

        List* tmp = new List;
        tmp->letter = letter;
        tmp->next = NULL;

        head->next = tmp;
    }

}

void CopySN(List* head, List* head2) {

    int words = 2;

    while (words) {

        if (head2->next == NULL && head2->letter == NULL) {
            head2->letter = head->letter;
        }
        else {

            while (head2->next) {
                head2 = head2->next;
            }

            List* tmp = new List;
            tmp->letter = head->letter;
            tmp->next = NULL;

            head2->next = tmp;
        }

        head = head->next;

        if (head->letter == ' ') {
            words--;
        }
    }

}

void ShowList(List* head) {

    while (head) {

        cout << "Адрес элемента: " << head << " Информационная часть: " << head->letter << endl;
        //printf("%с\tАдрес элемента: %p, Адрес информационной части: %p\n", head->letter, head, &head->letter);

        head = head->next;
    }

    return;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    system("chcp 1251");

    List *head = new List;

    cout << "Для окончания ввода ФИО введите 0\n";

    char letter;

    while (true) {
        cin.get(letter);

        if (letter == '0')
            break;

        AddElement(head, letter);
    }

    ShowList(head);

    cout << "Создание нового листа:\n";

    List* head2 = new List;
    CopySN(head, head2);
    ShowList(head2);

    system("pause");
}