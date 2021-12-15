#include <iostream>
template <class T>

class Grid {
private:
  T* memory;
  size_t x_size, y_size;

public:

  Grid(size_t x_size, size_t y_size, T def_val) : x_size(x_size), y_size(y_size)
  {
    if (x_size * y_size == 0) throw "invalid size";
    memory = new T[x_size * y_size];

    for (int i = 0; i < x_size * y_size; i++) memory[i] = def_val;
  }
  Grid(size_t x_size, size_t y_size) : x_size(x_size), y_size(y_size)
  {
    if (x_size * y_size == 0) throw "invalid size";
    memory = new T[x_size * y_size];
    T def_val = T();
    for (int i = 0; i < x_size * y_size; i++) memory[i] = def_val;
  }
  ~Grid()
  {
    delete[] memory;
  }
  T operator() (size_t x_ind, size_t y_ind) const
  {
    if (x_ind >= x_size || y_ind >= y_size) throw "invalid index";
    return memory[x_ind + y_ind * x_size];
  }
  T& operator()(size_t x_ind, size_t y_ind)
  {
    if (x_ind >= x_size || y_ind >= y_size) throw "invalid index";
    return memory[x_ind + y_ind * x_size];
  }

  size_t get_xsize() const
  {
    return x_size;
  }
  size_t get_ysize() const
  {
    return y_size;
  }

  Grid& operator=(const T& value)
  {
    Grid <T> buf(x_size, y_size, value);
    for (int i = 0; i < x_size * y_size; i++) memory[i] = value;
    return buf;
  }

  template <class Tfriend>
  friend std::ostream& operator<<(std::ostream& out, Grid <Tfriend> const& gr);
  template <class Tfriend>
  friend std::istream& operator>>(std::istream& in, Grid <Tfriend>& gr);

};
template <class T>
std::ostream& operator<<(std::ostream& out, Grid<T> const& gr)
{
  for (int i = 0; i < gr.get_ysize(); i++)
  {
    for (int j = 0; j < gr.get_xsize(); j++)
      out << gr(j, i) << " ";
    out << "\n";
  }
  return out;
}
template <class T>
std::istream& operator>>(std::istream& in, Grid<T>& gr)
{
  for (int i = 0; i < gr.y_size; i++)
    for (int j = 0; j < gr.x_size; j++)
      in >> gr(j, i);
  return in;
}
int main()
{

  Grid<float> g(3, 3);
  g = 3.3;
  std::cout << g;
  return 0;
}