int mu[MAXN], prm[MAXN], vis[MAXN];
void getmu(int n) {
    int sz = 0;
    mu[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!vis[i]) prm[++sz] = i, mu[i] = -1;
        for(int j = 1; j <= sz && prm[j] * i <= n; j++) {
            vis[i * prm[j]] = 1;
            if(i % prm[j] == 0) {mu[i * prm[j]] = 0; break;}
            mu[i * prm[j]] = -mu[i];
        }
    }
}
