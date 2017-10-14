#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
const int maxn = 100010;
int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    string s[maxn];
    for (int ii = 0; ii < n; ii++)
    {
      string ss;
      cin >> ss;
      ss = ss + ss;
      bool flag = false;
      int i = 0, j = 1, k = 0, l = ss.size() / 2, p = 0;
      while (i < l && j < l)
      {
        k = 0;
        while (ss[i + k] == ss[j + k] && k < l) k++;
        if (k == l)
        {
          p = i;
          flag = true;
          break;
        }
        if (ss[i + k] > ss[j + k])
          if (i + k + 1 > j) i = i + k + 1; else i = j + 1;
        else if (j + k + 1 > i) j = j + k + 1;
        else j = i + 1;
      }
      if (!flag)
      if (i < j) p = i; else p = j;
      s[ii] = ss.substr(p, l);
    }
    sort(s, s + n);
    int ans = 1;
    for (int i = 1; i < n; i++)
      if (s[i] != s[i - 1]) ans++;
    printf("%d\n", ans);
  }
}