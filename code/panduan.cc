#include <cstdio>
#include <iostream>
using namespace std;
const int maxn = 1e8;
struct P
{
  int x, y;
};
int ccw(P a, P b, P c)
{
  return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
P a[maxn];
int main()
{
  for (;;)
  {
    int n;
    cin >> n;
    if (n == 0) break;
    for (int i = 0; i < n; i++)
      cin >> a[i].x >> a[i].y;
    bool flag = true;
    a[n++] = a[0];
    a[n++] = a[1];
    for (int i = 0; i < n - 3; i++)
      if (ccw(a[i], a[i + 1], a[i + 2]) * ccw(a[i + 1], a[i + 2], a[i + 3]) < 0)
      {
        flag = false;
        break;
      }
    if (flag) puts("convex"); else puts("concave");
  }
}