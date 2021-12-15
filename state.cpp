#include <iostream>
#include <set>
#include <random>
#include <utility>
#include <chrono>
#include <fstream>
using namespace std;
class State
{
public:
  virtual bool contains(int s) const { return false; }
};

class DiscreteState : public State
{
private:
  int const state;
public:
  DiscreteState(int state) : state(state) { }
  bool contains(int s) const {return s == state;}
};

class SegmentState : public State
{
private:
  int const beg, end;
public:
  SegmentState(int beg, int end) : beg(beg), end(end) { }
  bool contains(int s) const {return s >= beg && s <= end;}
};

class SetState : public State
{
private:
  std::set<int> const states;
public:
  SetState(std::set<int> const& src) : states(src) { }
  bool contains(int s) const {return states.count(s) > 0;}
};

class OrState : public State
{
private:
  State& s1;
  State& s2;
public:
  OrState(State& s1, State& s2) : s1(s1), s2(s2) {}
  bool contains(int s) const {return s1.contains(s) || s2.contains(s);}
};

class AndState : public State
{
private:
  State& s1;
  State& s2;
public:
  AndState(State& s1, State& s2) : s1(s1), s2(s2) {}
  bool contains(int s) const {return s1.contains(s) && s2.contains(s);}
};

class SegmentStateGaps : public State
{
private:
  SegmentState const states;
  std::set<int> const gaps;
public:
  SegmentStateGaps(SegmentState const& src, std::set<int> const& setsrc) : states(src), gaps(setsrc) { };
  bool contains(int s) const {return (states.contains(s) && (gaps.count(s) == 0));}
};

class SegmentStateComplement : public State
{
private:
  SegmentState const states;
  std::set<int> const complement;
public:
  SegmentStateComplement(SegmentState const& src, std::set<int> const& setsrc) :
                         states(src), complement(setsrc) { };
  bool contains(int s) const {return (states.contains(s) || (complement.count(s) > 0));}
};

class SegmentStateGapsAndComp : public State {
private:
  SegmentStateComplement segment_comp;
  SegmentStateGaps segment_gaps;
public:
  SegmentStateGapsAndComp(SegmentState const& src, std::set<int> const& setgaps, std::set<int> const& setcomp) :
                          segment_comp(src, setcomp), segment_gaps(src, setgaps) { };
  bool contains(int s) const {return segment_comp.contains(s) && segment_gaps.contains(s);}
};

class ProbabilityTest
{
private:
  unsigned seed;
  int test_min, test_max;
  unsigned test_count;
public:
  ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count) :
                 seed(seed), test_min(test_min), test_max(test_max), test_count(test_count) { }
  float operator()(State const& s) const
  {
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<int> dstr(test_min, test_max);
    unsigned good = 0;
    for (unsigned cnt = 0; cnt != test_count; ++cnt)
      if (s.contains(dstr(rng))) ++good;
    return static_cast<float>(good) / static_cast<float>(test_count);
  }
};

int main()
{
  DiscreteState d(1);
  SegmentState s(0,10);
  SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 90, 99});
  ProbabilityTest pt(10,0,100,100000);
  cout << pt(d) << endl;
  cout << pt(s) << endl;
  cout << pt(ss) << endl;
  SegmentState s(-10000, 10000);
  SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 90, 99, 0, 1259, 4346, 2338, 32578, 9534, -325856, -8543, -3758, 3295, 999999, 634824, -237542, 111163, 147798, 888888, 3468, -255671, 444, 4444, 5656, 4567, 912991, 995692, -145624, -991569, 1000, 6, 87, 676887});
  SetState ss_plus({14224, 34589, 57263, 775855, 232323, 486947, 57000, 60445, 98990, 66499, 21010, 12059, 43546, 27338, 32578, 95348, -325856, -86543, -33758, 32295, 999999, 634824, -237542, 111163, 147798, 888888, 34468, -255671, 44478, 45444, 56456, 45637, 912991, 995692, -145624, -991569, 100000, 60000, 87777, 676887});
  SetState ss_minus({1, 3, 5, 7, 23, 48, 57, 60, 90, 99, 0, 1259, 4346, 2338, 3258, 9534, -3856, -8543, -3758, 3295, 9999, 6324, -2372, 1163, 1798, 8888, 3468, -2671, 444, 4444, 5656, 4567, 9191, 5692, -124, -9915, 1000, 6, 87, 6768});

  OrState h(s, ss_plus);
  //тест для интервала
  std::ofstream out_file;
  out_file.open ("/home/mechhedgehog/Downloads/out.txt");
  for(int i = 100; i <= 1000; i += 10){
      ProbabilityTest pt(678 ,-100000,100000, i);
      out_file << i << ";  " << pt(s) << "\n";
  }
  out_file.close();

  //тест для набора чисел
  std::ofstream out_file2;
  out_file2.open ("/home/mechhedgehog/Downloads/out.txt");
  for(int i = 100; i <= 1000; i += 10){
      ProbabilityTest pt(7777 ,-10000,10000,i);
      out_file2 << i << ";  " << pt(ss) << "\n";
  }
  out_file2.close();

  // тест для интервала со вставками
  std::ofstream out_file3;
  out_file3.open ("/home/mechhedgehog/Downloads/out.txt");
  for(int i = 10000; i <= 100000; i += 100)
  {
    ProbabilityTest pt(7564 ,-100000, 100000, i);
    out_file3 << i << ";  " << pt(h) << "\n";
  }
  return 0;
}