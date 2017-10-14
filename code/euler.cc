// 傻逼写的
int phi[MAXN];
void init() {
    memset(phi, 0, sizeof(phi));
    phi[1] = 1;
    for(int i = 2; i < MAXN; i++) if(!phi[i])
        for(int j = i; j < MAXN; j += i) {
            if(!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i - 1);
        }
}
// 聪明人写的
void init()
{
  for (int i = 2; i < maxb; i++)
    if (f[i] == 0)
      for (int j = i; j < maxb; j += i)
      {
        if (f[j] == 0) f[j] = j;
        f[j] = (f[j] / i) * (i - 1);
      }
  for (int i = 1; i < maxb; i++)
    f[i] += f[i - 1];
}