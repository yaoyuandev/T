void dfs1(int u, int fa, int dep) {
    sz[u] = 1; d[u] = dep; ch[u] = 0; p[u] = fa;
    for(int i = head[u]; i != -1; i = ed[i].next) {
        int v = ed[i].v;
        if(v == fa) continue;
        dfs1(v, u, dep + 1);
        sz[u] += sz[v];
        if(sz[v] > sz[ch[u]]) ch[u] = v;
    }
}
void dfs2(int u, int rt) {
    idx[u] = id++;
    top[u] = rt;
    if(ch[u]) dfs2(ch[u], rt);
    for(int i = head[u]; i != -1; i = ed[i].next) {
        int v = ed[i].v;
        if(v == p[u] || v == ch[u]) continue;
        dfs2(v, v);
    }
}
int ask(int u, int v) {
    int ret = 0;
while(top[u] != top[v]) {
    //一定是top[u]的深度大于等于top[v]
        if(d[top[u]] < d[top[v]]) swap(u, v);
        ret = max(ret, query(1, 1, n, idx[top[u]], idx[u]));
        u = p[top[u]];
    }
    if(d[u] < d[v]) swap(u, v);
    if(u != v) ret = max(ret, query(1, 1, n, idx[ch[v]], idx[u]));
    return ret;
}
