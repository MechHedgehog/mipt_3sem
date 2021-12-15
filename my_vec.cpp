#include <iostream>
#include <string>

template <class T>
class Vector
{
private:
  int size;
  int last;
  T* vec;
public:
  Vector() : size(0), vec(nullptr), last(0) { };

  Vector(const int& n) : size(2 * n), last(n)
  {
    vec = new T[2 * n];
    T def_val = T();
    for (int i = 0; i < 2 * n; i++) vec[i] = def_val;
  }

  Vector(const int& n, T def_val) : size(2 * n), last(n)
  {
    vec = new T[2 * n];
    for (int i = 0; i < 2 * n; i++) vec[i] = def_val;
  }
  Vector(T init_arr[])
  {
    vec = init_arr;
    size = sizeof(init_arr) / sizeof(init_arr[0]);
  }
  ~Vector()
  {
    delete[] vec;
  }

  T& operator[](const int& i)
  {
    if (i >= last) exit(1);
    return vec[i];
  }

  void Resize(const int& new_size)
  {
    T* new_vec = new T[new_size];
    T def_val = T();
    for (int i = 0; i < new_size; i++) new_vec[i] = (i < size ? vec[i] : def_val);
    size = new_size;
    last = new_size;
    delete[]vec;
    vec = new_vec;
  }
  void Push_back(const T& new_element)
  {
    if (last >= size)
    {
      int buf = last;
      Resize(size * 2);
      last = buf;
    }
    vec[last] = new_element;
    last++;
  }
  T Pop()//rename
  {
    if (last == 0) exit(1);
    last--;
    return vec[last];
  }
  T& Front()//rename
  {
    return vec[last - 1];
  }
  int Size()
  {
    return last;
  }
};

int main()
{
  int a[] = { 1,2,3 };
  Vector <int> v(a);
  std::cout << v[1];

  return 0;
}
