#include <bits/stdc++.h>
using namespace std;
const int N = 1000, MOD = 1E9 + 7;
struct Mat
{
    int a[N][N];
    int n, m;
    Mat(int n, int m) : n(n), m(m) {memset(a, 0, sizeof(a));}
    void eye()
    {
        memset(a, 0, sizeof(a));
        for (int i = 0; i < n; i++) a[i][i] = 1;
    }
    void print()
    {
        for (int i = 0; i < n; i++) {
            cout << endl;
            for (int j = 0; j < m; j++)
                cout << ' ' << a[i][j];
        }
    }
};
Mat mul(Mat A, Mat B)
{
    Mat t(A.n, B.m);
    for (int i = 0; i < A.n; i++)
        for (int j = 0; j < B.m; j++)
            for (int k = 0; k < A.m; k++)
                t.a[i][j] = (t.a[i][j] + A.a[i][k] * B.a[k][j] % MOD) % MOD;
    return t;
}
Mat pow(Mat A, int n)
{
    Mat t(A.n, A.m);
    t.eye();
    while (n > 0) {
        if (n % 2) t = mul(t, A);
        A = mul(A, A);
        n /= 2;
    }
    return t;
}
int det(Mat A)
{
  int cnt = 0,ans = 1, n = A.n;
  for(int i = 0; i < n; i++) {
    for(int j = i+1; j < n; j++) {
      int x = i, y = j;
      while(A.a[y][i]) {
        int t = A.a[x][i] / A.a[y][i];
        for(int k = 0; k < n; k++) {
          A.a[x][k] = A.a[x][k] - A.a[y][k]*t;
        }
        swap(x, y);
      }
      if(x != i) {
        for(int k = 0; k < n; k++) {
          swap(A.a[x][k], A.a[y][k]);
        }
        cnt ^= 1;
      }
    }
    if(A.a[i][i] == 0) return 0;
    else ans *= A.a[i][i];
  }
  if(cnt) ans *= -1;
    return ans;
}