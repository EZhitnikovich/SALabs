#include <iostream>

using namespace std;

struct node
{
    int key;
    struct node* left, * right;
};

node* newNode(int item)
{
    node* temp = (node*)malloc(sizeof(node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void print_Tree(node* p, int level = 0)
{
    if (p)
    {
        print_Tree(p->right, level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << p->key << endl;
        print_Tree(p->left, level + 1);
    }
}

node* insert(node* node, int key)
{
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    return node;
}

void delMax(node* root)
{
    while (root->right->right)
    {
        root = root->right;
    }

    root->right = NULL;
}

int main()
{
    setlocale(LC_ALL, "rus");

    node* root = NULL;

    int arr[] = { 50,30,20,40,70,60,80 };

    for (int i = 0; i < 7; i++)
    {
        root = insert(root, arr[i]);
    }

    cout << "Дерево до удаления элемента:\n";

    print_Tree(root);

    cout << "Дерево после удаления элемента:\n";

    delMax(root->left);
    print_Tree(root);

    system("pause");
}