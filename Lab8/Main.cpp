#include <string>
#include <unordered_map>
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

const int MAX_SYM = 256;

map<string, int> encoding(string source) { //lzw

    map<string, int> table;
    int index = 0;
    for (int i = 0; i < source.length(); i++) {
        if (table.find((string)source.substr(i, 1)) == table.end()) {
            table.insert(make_pair(source.substr(i, 1), index));
            index++;
            table.begin();
        }
        else {
            for (int k = 1, start = i; k < source.length(); k++) {
                string subs = source.substr(start, k);
                if (table.find(subs) == table.end()) {
                    table.insert(make_pair(subs, index));
                    index++;
                    i = start + k;
                    table.begin();
                    break;
                }
            }
        }
    }

    return table;
}

class Huffman
{
public:
    int count;
    char symbol;
    Huffman* left;
    Huffman* right;

    Huffman() { }

    Huffman(char __symbol, int __count)
    {
        symbol = __symbol;
        count = __count;
    }

    Huffman(Huffman* l, Huffman* r)
    {
        symbol = 0;
        left = l;
        right = r;
        count = l->count + r->count;
    }
};

void print_Tree(Huffman* p, int level = 0)
{
    if (p)
    {
        print_Tree(p->right, level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << p->symbol << endl;
        print_Tree(p->left, level + 1);
    }
}

void BuildTable(Huffman* root, vector<bool>& code, map<char, vector<bool>>& table)
{
    if (root->left)
    {
        code.push_back(0);
        BuildTable(root->left, code, table);
    }
    if (root->right)
    {
        code.push_back(1);
        BuildTable(root->right, code, table);
    }
    if (root->symbol)
        table[root->symbol] = code;
    if (code.size())
        code.pop_back();
}

bool SortHuf(const Huffman* a, const Huffman* b)
{
    return a->count < b->count;
}

string readFile(string path)
{
    fstream fin(path, ios::in);
    if (!fin.is_open())
    {
        cout << "Error, file not open.\n";
        exit(1);
    }
    string data = "";
    while (fin)
    {
        getline(fin, data);
    }
    cout << endl;
    fin.close();
    return data;
}

void writeFile(string path, string str)
{
    fstream fout(path, ios::out | ios::trunc);
    if (!fout.is_open())
    {
        cout << "Error, file not open.";
        exit(1);
    }
    fout << str;
    fout.close();
}

int main()
{
    string sourceFile = "source.txt";

    string source = readFile(sourceFile);
    cout << "Source text: " << source << endl;
    map<char, int> symbols;
    cout << "Huffman" << endl;
    for (int i = 0; i < source.length(); i++)
    {
        symbols[source[i]]++;
    }

    list<Huffman*> trees;
    map<char, int>::iterator itr;
    for (itr = symbols.begin(); itr != symbols.end(); itr++)
    {
        Huffman* p = new Huffman(itr->first, itr->second);
        trees.push_back(p);
    }

    while (trees.size() != 1)
    {
        trees.sort(SortHuf);

        Huffman* l = trees.front();
        trees.pop_front();
        Huffman* r = trees.front();
        trees.pop_front();

        Huffman* parent = new Huffman(l, r);
        trees.push_back(parent);
    }

    Huffman* root = trees.front();
    print_Tree(root);

    vector<bool> code;
    map<char, vector<bool>> table;
    BuildTable(root, code, table);

    for (itr = symbols.begin(); itr != symbols.end(); itr++)
    {
        cout << itr->first << " - ";
        for (int j = 0; j < table[itr->first].size(); j++)
        {
            cout << table[itr->first][j];
        }
        cout << endl;
    }

    string firstResult = "";
    for (int i = 0; i < source.length(); i++)
    {
        for (int j = 0; j < table[source[i]].size(); j++)
        {
            firstResult += table[source[i]][j] + '0';
        }
    }
    string outPath1 = "huffman.txt";

    map<vector<bool>, char> ftable;
    for (auto i = table.begin(); i != table.end(); i++)
    {
        ftable[i->second] = i->first;
    }

    writeFile(outPath1, firstResult);

    cout << "LZW" << endl;
    setlocale(LC_ALL, 0);
    string s = readFile(sourceFile);
    map<string, int> output_code = encoding(s);

    cout << "LZW Dictionary: " << endl;

    string secondResult = "";

    for (auto it = output_code.begin(); it != output_code.end(); ++it) {
        cout << it->first << " : " << it->second << endl;
        secondResult += to_string(it->second) + " ";
    }

    string outPath2 = "lzw.txt";
    writeFile(outPath2, secondResult);
    cout << endl;
}