#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <string>
using namespace std;



int main()
{

  int h1, id;
  double h3, h4, h5, neu, h7;
  int n;
  cin >> n;
  map <int, multiset <double> > m;
  for(int i = 0; i < n; i++)
  {
    cin >> h1 >> id >> h3 >> h4 >> h5 >> neu >> h7;
    m[id].insert(neu);
  }
  set <pair<double, int>> st;
  for(auto i : m)
    if(i.second.size() != 1) st.insert(make_pair(*i.second.rbegin() - *i.second.begin(), i.first));
  int j = 0;
  for(auto it = st.begin(); it != st.end() && j < 3; it++, j++) cout << it->second << " ";
  if(st.size() == 0) cout << -1;
  return 0;
}