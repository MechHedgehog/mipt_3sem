#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

class Hash
{
private:
  int len = 149;
  int in = 0;

  string* hash_table;
  bool* table_in;

  int prime1 = 61;
  int prime2 = 47;
  int prime3 = 19;
  int alpha = 42;

  int hash_f(string s, int prime)
  {
    int hash_val = 0;
    for (int i = 0; i < s.size(); i++)
      hash_val = (prime * hash_val + s[i]) % len;
    return (prime3 * hash_val + alpha) % len;
  }

  void resize()
  {
    Hash buf(len * 2);
    for (int i = 0; i < len; i++)
      if (table_in[i])
        buf.insert(hash_table[i]);
    *this = buf;
  }

public:

  Hash(int len) : len(len) // конструктор
  {
    hash_table = new string[len];
    table_in = new bool[len]; //нужен лишь для вохможности вставки в хэш симовла пустой строки
    for (int i = 0; i < len; i++) hash_table[i] = "";
    for (int i = 0; i < len; i++) table_in[i] = false;
  }
  Hash(): Hash(149) {}// конструктор дефолт

  ~Hash() // деструктор
  {
    delete[] hash_table;
    delete[] table_in;
  }

  Hash(const Hash& src) // конструктор копирования
  {
    len = src.len;
    in = src.in;
    hash_table = new string[len];
    for(int i = 0; i < len; i++) hash_table[i] = src.hash_table[i];
    table_in = new bool[len];
    for(int i = 0; i < len; i++) table_in[i] = src.table_in[i];
  }
  Hash& operator=(const Hash& src) // присваивание копированием
  {
    if(&src == this) return *this;

    delete[] hash_table;
    delete[] table_in;

    len = src.len;
    in = src.in;
    hash_table = new string[len];
    for(int i = 0; i < len; i++) hash_table[i] = src.hash_table[i];
    table_in = new bool[len];
    for(int i = 0; i < len; i++) table_in[i] = src.table_in[i];

    return *this;
  }

  Hash(Hash&& src) : len(src.len), in(src.in), // конструктор перемещения
                     hash_table(src.hash_table), table_in(src.table_in)
  {
    src.hash_table = nullptr;
    src.table_in = nullptr;
  }

  Hash& operator=(Hash&& src) // присваивание перемещением.
  {
    if(&src == this) return *this;

    delete[] hash_table;
    delete[] table_in;

    len = src.len;
    in = src.in;
    hash_table = src.hash_table;
    table_in = src.table_in;
    src.hash_table = nullptr;
    src.table_in = nullptr;

    return *this;
  }

  int insert(const string& s)
  {
    if(in > 0.6 * len) resize();

    int hash_buf1 = hash_f(s, prime1);
    int hash_buf2 = hash_f(s, prime2);

    for (int i = 0; i < (int)log(len) * 2; i++)
      if (!table_in[hash_buf1 + i * hash_buf2])
      {
        table_in[hash_buf1 + i * hash_buf2] = true;
        hash_table[hash_buf1 + i * hash_buf2] = s;
        in++;
        return hash_buf1 + i * hash_buf2;
      }

    resize();
    return insert(s);
  }

  bool erase(const string& s)
  {
    int hash_buf1 = hash_f(s, prime1);
    int hash_buf2 = hash_f(s, prime2);

    for(int i = 0; i < (int)log(len) * 2; i++)
      if(hash_table[hash_buf1 + i * hash_buf2] == s && table_in[hash_buf1 + i * hash_buf2])
      {
        in--;
        table_in[hash_buf1 + i * hash_buf2] = false;
        hash_table[hash_buf1 + i * hash_buf2] = "";
        return true;
      }

    return false;
  }

  bool find(const string& s)
  {
    int hash_buf1 = hash_f(s, prime1);
    int hash_buf2 = hash_f(s, prime2);

    for(int i = 0; i < (int)log(len) * 2; i++)
      if(hash_table[hash_buf1 + i * hash_buf2] == s && table_in[hash_buf1 + i * hash_buf2])
        return true;
    return false;
  }
};


class hash1
{
private:
  int len = 149;
  int in = 0;

  vector <vector <string>> hash_table;

  int prime = 61;

  int hash_f(string s)
  {
    int hash_val = 0;
    for (int i = 0; i < s.size(); i++)
      hash_val = (prime * hash_val + s[i]) % len;
    return hash_val;
  }

  void resize()
  {
    hash1 buf(len * 2);
    for (int i = 0; i < len; i++)
      for(int j = 0; j < hash_table[i].size(); j++) buf.insert(hash_table[i][j]);
    *this = buf;
  }

public:
  hash1(int len) : len(len) // конструктор
  {
    hash_table.assign(len, vector <string>(0));
  }
  hash1(): hash1(149) {}// конструктор дефолт

  ~hash1() {}// деструктор

  hash1(const hash1& src) : len(src.len), in(src.len), hash_table(src.hash_table) {}// конструктор копирования

  int insert(const string& s)
  {
    if(in > 0.6 * len) resize();
    int hash_buf = hash_f(s);
    hash_table[hash_buf].push_back(s);
    if(hash_table[hash_buf].size() > 2 * log(len))
      resize();
    return hash_buf;
  }

  bool erase(const string& s)
  {
    int hash_buf = hash_f(s);
    for(int i = 0; i < hash_table[hash_buf].size(); i++)
      if(hash_table[hash_buf][i] == s)
      {
        in--;
        hash_table[hash_buf].erase(hash_table[hash_buf].begin() + i);
        return true;
      }
    return false;
  }

  bool find(const string& s)
  {
    int hash_buf = hash_f(s);
    for(int i = 0; i < hash_table[hash_buf].size(); i++)
      if(hash_table[hash_buf][i] == s)
        return true;
    return false;
  }



};


int main()
{
  Hash h = Hash(5);
  for(char i = 48; i < 64; i++)
    h.insert(string(1, i));
  char buf = 50;
  cout << h.find(string(1, buf)) << " ";
  h.erase(string(1, buf));
  cout << h.find(string(1, buf)) << " ";
  cout << h.find(string(1, buf + 30)) << endl;

  hash1 h1 = hash1(5);
  for(char i = 48; i < 64; i++)
    h1.insert(string(1, i));
  char buf1 = 50;
  cout << h1.find(string(1, buf1)) << " ";
  h1.erase(string(1, buf1));
  cout << h1.find(string(1, buf1)) << " ";
  cout << h1.find(string(1, buf1 + 30)) << endl;
  return 0;
}
