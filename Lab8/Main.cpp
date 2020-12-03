#include <string>
#include <unordered_map>
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

const int MAX_SYM = 256;

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

string Decode(string& str, map<vector<bool>, char>& table)
{
    string out = "";
    vector<bool> code;
    for (int i = 0; i < str.length(); i++)
    {
        code.push_back(str[i] == '0' ? false : true);
        if (table[code])
        {
            out += table[code];
            code.clear();
        }
    }
    return out;
}

vector<int> encoding(string s1)
{
    unordered_map<string, int> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    string p = "", c = "";
    p += s1[0];
    int code = 256;
    vector<int> output_code;
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {
            cout << p << "\t" << table[p] << "\t\t"
                << p + c << "\t" << code << endl;
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    cout << p << "\t" << table[p] << endl;
    output_code.push_back(table[p]);
    return output_code;
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
    string path_src = "source.txt";

    string raw = readFile(path_src);
    cout << "Source text: " << raw << endl;
    map<char, int> symbols;
    cout << "Huffman" << endl;
    for (int i = 0; i < raw.length(); i++)
    {
        symbols[raw[i]]++;
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

    string out = "";
    for (int i = 0; i < raw.length(); i++)
    {
        for (int j = 0; j < table[raw[i]].size(); j++)
        {
            out += table[raw[i]][j] + '0';
        }
    }
    string path1 = "huffman.txt";

    map<vector<bool>, char> ftable;
    for (auto i = table.begin(); i != table.end(); i++)
    {
        ftable[i->second] = i->first;
    }

    writeFile(path1, out);

    cout << "LZW" << endl;
    setlocale(LC_ALL, 0);
    string s = readFile(path_src);
    vector<int> output_code = encoding(s);

    cout << "Output Codes are: ";

    string out2 = "";

    for (int i = 0; i < output_code.size(); i++) {
        cout << output_code[i] << " ";
        out2 += to_string(output_code[i]);
    }
    string path2 = "lzw.txt";
    writeFile(path2, out2);
    cout << endl;
}