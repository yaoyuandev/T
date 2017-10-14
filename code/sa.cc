int sa[MAXN], rk[MAXN], ht[MAXN], cnt[MAXN], t1[MAXN], t2[MAXN];
void getsa(int m) {
    int *x = t1, *y = t2;
    for(int i = 0; i < m; i++) cnt[i] = 0;
    for(int i = 0; i < n; i++) cnt[x[i] = s[i]]++;
    for(int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
for(int i = n - 1; i >= 0; i--) sa[--cnt[x[i]]] = i;
//sa数组从0到n-1
    for(int k = 1; ; k *= 2) {
        int p = 0;
        //2nd
        for(int i = n - k; i < n; i++) y[p++] = i;
        for(int i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
        //1st
        for(int i = 0; i < m; i++) cnt[i] = 0;
        for(int i = 0; i < n; i++) cnt[x[y[i]]]++;
        for(int i = 1; i < m; i++) cnt[i] += cnt[i - 1];
        for(int i = n - 1; i >= 0; i--) sa[--cnt[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1; x[sa[0]] = 0;
        for(int i = 1; i < n; i++)
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] && sa[i] + k < n && sa[i - 1] + k < n) ? p - 1 : p++;
        if(p >= n) break;
        m = p;
    }
}
void getheight() {
    int k = 0;
    for(int i = 0; i < n; i++) rk[sa[i]] = i;
for(int i = 0; i < n; i++) {
		if(rk[i] == 0) continue;
        if(k) k--;
        int j = sa[rk[i] - 1];
        while(s[i + k] == s[j + k] && i + k < n && j + k < n) k++;
        ht[rk[i]] = k;
    }
}
