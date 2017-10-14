//rt = 1
int ncnt, last, ch[MAXN][26], val[MAXN], par[MAXN];
int c[MAXN], rk[MAXN];
void init(int x, int v) {
    memset(ch[x], 0, sizeof(ch[x]));
    par[x] = 0; val[x] = v;
}
void add(int x) {
    int p = last, np = ++ncnt;
    memset(ch[np], 0, sizeof(ch[np]));
    init(np, val[p] + 1);
    while(p && !ch[p][x]) {
        ch[p][x] = np;
        p = par[p];
    }
    if(p == 0) par[np] = 1;
    else {
        int q = ch[p][x];
        if(val[p] + 1 == val[q]) par[np] = q;
        else {
            int nq = ++ncnt;
            memcpy(ch[nq], ch[q], sizeof(ch[q]));
            val[nq] = val[p] + 1;
            par[nq] = par[q];
            par[q] = nq;
            par[np] = nq;
            while(p && ch[p][x] == q) {
                ch[p][x] = nq;
                p = par[p];
            }
        }
    }
    last = np;
}
void tsort() {
    memset(c, 0, sizeof(c));
    for(int i = 1; i <= ncnt; i++) c[val[i]]++;
    for(int i = 1; i <= ncnt; i++) c[i] += c[i - 1];
    for(int i = 1; i <= ncnt; i++) rk[c[val[i]]--] = i;
}
