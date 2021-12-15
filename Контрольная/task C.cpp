#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <string>
using namespace std;



int main()
{
  int n, m, buf_i, bf;
  string buf_s;
  map <int, int> s;
  cin >> n;
  for(int i = 0; i < n; i++)
  {
    cin >> buf_s >> buf_i;
    bf = atoi(buf_s.substr(0,2).c_str()) +
         atoi(buf_s.substr(3,2).c_str()) * 100 +
         atoi(buf_s.substr(6,4).c_str()) * 10000;
    if(s.find(bf) != s.end())
      s[bf] = max(s[bf], buf_i);
    else
      s[bf] = buf_i;
  }
  int max = 0;

  for(auto i = s.begin(); i != s.end(); i++)
  {
    if(i->second > max) max = i->second;
    else i->second = max;
  }
  cin >> m;
  for(int i = 0; i < m; i++)
  {
    cin >> buf_s;
    bf = atoi(buf_s.substr(0,2).c_str()) +
         atoi(buf_s.substr(3,2).c_str()) * 100 +
         atoi(buf_s.substr(6,4).c_str()) * 10000;
    auto it = s.lower_bound(bf);
    if(it == s.end()) cout << max << endl;
    else if(it->first == bf) cout << it->second << endl;
    else if(it == s.begin()) cout << 0 << endl;
    else cout <<(--it)->second << endl;
  }
  return 0;
}
