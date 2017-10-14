void initp() {
    for(int j = 1; (1 << j) <= n; j++)
        for(int i = 1; i <= n; i++) if(p[i][j - 1])//一定要有这个if
            p[i][j] = p[p[i][j - 1]][j - 1];
}
int LCA(int u, int v) {
    if(d[u] < d[v]) swap(u, v);
int lim;
//确定最大的2^lim不超过d[u]
    for(lim = 0; (1 << lim) <= d[u]; lim++); lim--;
int ret = 0;
//把u上升到v相同的高度
    for(int i = lim; i >= 0; i--) if(d[u] - (1 << i) >= d[v]) u = p[u][i];
    if(u == v) return u; //一定要有这个判断
    for(int i = lim; i >= 0; i--) if(p[u][i] != p[v][i]) {u = p[u][i]; v = p[v][i];}
    return p[u][0];
}
