void getsz(int u, int fa) {
    sz[u] = 1; f[u] = 0;
    for(int i = head[u]; i != -1; i = ed[i].next) {
        int v = ed[i].v;
        if(v == fa || vis[v]) continue;
        getsz(v, u);
        sz[u] += sz[v];
        f[u] = max(f[u], sz[v]);
    }
}
//找到最大子树最小的点作为分治的中心
void getrt(int r, int u, int fa) {
    //用父边所连的子树更新f
    f[u] = max(f[u], sz[r] - sz[u]);
    if(f[u] < minf) {minf = f[u]; rt = u;}
    for(int i = head[u]; i != -1; i = ed[i].next) {
        int v = ed[i].v;
        if(v == fa || vis[v]) continue;
        getrt(r, v, u);
    }
}
int solve(int u) {
    minf = n;
    getsz(u, 0);
    getrt(u, u, 0);
    vis[rt] = 1;
    int ret = getdp(rt); //分治的结果
    for(int i = head[rt]; i != -1; i = ed[i].next) {
        int v = ed[i].v;
        if(!vis[v]) ret = max(ret, solve(v));
    }
    return ret;
}
