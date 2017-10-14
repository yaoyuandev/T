const int N = 1000000 + 9;
bool p[N];
int a[N];
int main()
{
  int n;
  cin >> n;
  int cnt = 0;
  for (int i = 0; i <= n; i++) p[i] = true;
  for (int i = 2; i <= n; i++) {
    if (p[i]) a[cnt++] = i;
    for (int j = 0; j < cnt; j++) {
        if (i * a[j] > n) break;
        p[i * a[j]] = false;
        if (i % a[j] == 0) break;
    }
  }
  cout << cnt << endl;
}