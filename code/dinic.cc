int bfs(int s, int t) {
    memset(vis, false, sizeof(vis));
    queue<int> q;
    q.push(s);
    vis[s] = true; d[s] = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = 0; i < g[u].size(); i++) {
            Edge e = edges[g[u][i]];
            if(vis[e.v]) continue;//不能再走访问过的点
            if(e.cap > e.flow) {
                d[e.v] = d[u] + 1;
                vis[e.v] = true;
                q.push(e.v);
            }
        }
    }
    return vis[t];
}
int dfs(int u, int a, int t) {
    if(a == 0 || u == t) return a;
    int flow = 0, f;
    for(int &i = cur[u]; i < g[u].size(); i++) {
        Edge &e = edges[g[u][i]];
        if(d[e.v] == d[u] + 1 && (f = dfs(e.v, min(a, e.cap - e.flow), t)) > 0) {//如果从v走还可以增广
            e.flow += f;
            edges[g[u][i]^1].flow -= f;
            flow += f;
            a -= f;
            if(a == 0) break;
        }
    }
    return flow;
}
int dinic(int s, int t) {
    int flow = 0;
    while(bfs(s, t)) {
        memset(cur, 0, sizeof(cur));
        flow += dfs(s, INF, t);
    }
    return flow;
}
