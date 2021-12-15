#include <iterator>
#include <list>
#include <random>
#include <iostream>
#include <algorithm>

bool toss_a_coin()
{
  std::random_device rd;
  std::mt19937 mersenne(rd());
  return mersenne() % 2;
}
// неудачная попытка в итераторы
/*template <class T>
class Bid_Itrt
{
private:
  T* ptr;
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T*;
  using ref = T&;
  Bid_Itrt(): ptr(nullptr) {}
  Bid_Itrt(T* p): ptr(p){};
  ~Bid_Itrt() {delete ptr;}

  // копирование
  Bid_Itrt(const Bid_Itrt & src)
  {
    if(src.ptr)
    {
      ptr = new T;
      *ptr = *src.ptr;
    }
    else ptr = nullptr;
  }
  Bid_Itrt& operator=(const Bid_Itrt& src)
  {
    if(src == *this) return *this;
    delete ptr;
    if(src.ptr)
    {
      ptr = new T;
      *ptr = *src.ptr;
    }
    else ptr = nullptr;
    return *this;
  }
  // перемещение
  Bid_Itrt(Bid_Itrt && src) : ptr(src.ptr)
  {
    src.ptr = nullptr;
  }
  Bid_Itrt& operator=(Bid_Itrt&& src)
  {
    if(src == *this) return *this;
    delete ptr;
    ptr = src.ptr;
    src.ptr = nullptr;
  }

  ref operator*() const {return *this;}
  pointer operator->() const {return this;}
  Bid_Itrt& operator++() {ptr++; return *this;}
  Bid_Itrt operator++(int) {return ++(*this);}
  Bid_Itrt& operator--() {ptr--; return *this;}
  Bid_Itrt operator--(int) {return --(*this);}
  bool operator==(const Bid_Itrt& i) {return *i.ptr == *this->ptr;}
  bool operator!=(const Bid_Itrt& i) {return !(i == this);}
};
*/

template <class T>
class node
{
public:
  T val;
  typename std::list<node<T>>::iterator down;
  node() : val(), down() {}
  node(T v,
       typename std::list<node<T> >::iterator d)
        : val(v), down(d) {}

};

template <class T>
class Skip_List
{
private:
  std::list<std::list<node<T>>> mem;

public:
  Skip_List() : mem(1) {}
  typename std::list<node<T>>::iterator begin() {return mem.begin()->begin();}
  typename std::list<node<T>>::iterator end() {return mem.begin()->end();}
  void insert(T src)
  {
    bool coin = true;
    auto buf_down = mem.begin()->end();
    if(mem.begin()->size() == 0)
    {
      mem.begin()->push_back(node<T>(src, buf_down));
      buf_down = mem.begin()->end();
      --buf_down;
    }
    else
    {
      for (auto it = mem.begin(); it != mem.end() && coin; it++)
      {
        if (src > (it->rbegin())->val)
        {
          it->push_back(node<T>(src, buf_down));
          buf_down = it->end();
          --buf_down;
        }
        else
        {
          for (auto i = it->begin(); i != it->end(); i++)
            if (src <= i->val)
            {
              it->insert(i, node<T>(src, buf_down));
              buf_down = i;
              --buf_down;
              break;
            }
        }
        coin = toss_a_coin();
      }
    }
    if(coin)
    {
      mem.push_back(std::list<node<T>>());
      mem.rbegin()->push_back(node<T>(src, buf_down));
    }
  }
  void insert(T* begin, T* end)
  {
    for(T* it = begin; it != end; it++)
      insert(*it);
  }
  Skip_List(T* begin, T* end) : mem()
  {
    for(T* i = begin; i != end; i++)
      mem.insert(*i);
  }
  Skip_List(const Skip_List& src) : mem(src.mem){}
  Skip_List& operator=(const Skip_List& src)
  {
    if(*src == *this) return *this;
    mem = src.mem;
    return *this;
  }
  Skip_List(Skip_List && src) : mem(src.mem)
  {
    src.mem = std::list<std::list<node<T>>>();
  }
  Skip_List& operator=(Skip_List&& src)
  {
    if(*src == *this) return *this;
    mem = src.mem;
    src.mem = std::list<std::list<node<T>>>();
    return *this;
  }
  bool empty()
  {
    return mem.begin()->empty();
  }
  bool size()
  {
    return mem.begin()->size();
  }

  typename std::list<node<T>>::iterator find(T src)
  {
    auto it = mem.rbegin();
    auto i = it->begin();
    bool buf;
    for(it; it != mem.rend(); ++it)
    {
      buf = true;
      for(i; i != it->end(); ++i)
      {
        if(i->val == src)
        {
          for(; i->down != mem.begin()->end();)i = i->down;
          return i;
        }
        if(i->val > src && i != it->begin())
        {
          if(i->down == mem.begin()->end()) return end();
          i--;
          i = i->down;
          buf = false;
          break;
        }
        if(i->val > src && i == it->begin())
        {
          if(i->down == mem.begin()->end()) return end();
          it++;
          i = it->begin();
          it--;
          buf = false;
          break;
        }
      }
      if(buf)
      {
        if(i == it->begin())
        {
          if(i->down == mem.begin()->end()) return end();
          i = i->down;
        }
        else
        {
          if ((--i)->down == mem.begin()->end())return end();
          i = i->down;
        }
      }
    }
    return end();
  }

  void show()
  {
    for(auto it = mem.rbegin(); it != mem.rend(); it++)
    {
      for(auto i = it->begin(); i != it->end(); i++)
        std::cout << i->val << " ";
      std::cout << std::endl;
    }
  }

  void f()
  {
    for(auto it = mem.rbegin()->begin(); it != mem.rbegin()->end(); it++)
    {
      auto i = it->down;
      for(;i != mem.begin()->end();)
      {
        std::cout << i->val << " ";
        i = i->down;
      }
    }
  }
};


int main()
{
  std::vector<int> v = {2, 5, 1, 7, 0, 4, 8, 6, 3, 9};
  /*for(int i = 0; i < 10; i++) v[i] = i;
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(v.begin(), v.end(), g);
  for(int  i = 0; i < 10; i++) std::cout << v[i] << " ";
  std::cout << std::endl;*/
  Skip_List <int> s;
  for(int i = 0; i < 10; i++)
    s.insert(v[i]);
  s.show();
  std::cout <<1111111 << std::endl;
  std::cout << s.find(9)->val;
  return 0;
}