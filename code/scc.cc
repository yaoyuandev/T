int dfs(int u) {
    pre[u] = low[u] = ++dfs_clock;
    s.push(u);
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if(!pre[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else if(!sccno[v]) {
            low[u] = min(low[u], pre[v]);
        }
}
//如果low[u] == pre[u]，那么它就是这个scc的第一个点
    if(low[u] == pre[u]) {
        scc_cnt++;
        for(;;) {
            int temp = s.top(); s.pop();
            sccno[temp] = scc_cnt;
            if(temp == u) break;
        }
    }
}
void find_scc(int n) {
    memset(pre, 0, sizeof(pre));
    memset(low, 0, sizeof(low));
    memset(sccno, 0, sizeof(sccno));
    dfs_clock = scc_cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(!pre[i]) dfs(i);
    }
}
