int cnt = 1, ans = 0;
priority_queue<edge> pq;
for(int i = 0; i < g[1].size(); i++) pq.push(g[1][i]);
while(!pq.empty()) {
    edge t = pq.top(); pq.pop();
    int v = t.v;
    if(p[v] != 1) {
        cnt++; ans += t.w;
        p[v] = 1;
for(int i = 0; i < g[v].size(); i++) if(p[g[v][i].v] != 1) pq.push(g[v][i]);
    }
    if(cnt == n) break;
}
