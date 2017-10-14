int dfs(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if(!pre[v]) {
            s.push(node(u, v));
            child++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if(lowv >= pre[u]) {
                iscut[u] = true;
                bcc[++bcc_cnt].clear();
                for(;;) {
                    node temp = s.top(); s.pop();
			//注意割顶可能包含在多个bcc中，bccno不是唯一的标准
                    if(bccno[temp.u] != bcc_cnt) 
		{bcc[bcc_cnt].push_back(temp.u); bccno[temp.u] = bcc_cnt;}
                    if(bccno[temp.v] != bcc_cnt) 
		{bcc[bcc_cnt].push_back(temp.v); bccno[temp.v] = bcc_cnt;}
                    if(temp.u == u && temp.v == v) break;
                }
            }
        }
        else if(pre[v] < pre[u] && v != fa) {
            s.push(node(u, v));
            lowu = min(lowu, pre[v]);
        }
    }
    if(fa < 0 && child == 1) iscut[u] = false;
    return lowu;
}
void find_bcc(int n) {
    memset(pre, 0, sizeof(pre));
    memset(iscut, false, sizeof(iscut));
    memset(bccno, 0, sizeof(bccno));
    dfs_clock = bcc_cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(!pre[i]) dfs(i, -1);
    }
}
