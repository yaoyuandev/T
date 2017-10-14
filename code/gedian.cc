int pre[MAXN], iscut[MAXN], dfs_clock = 0;
int dfs(int u, int fa) {
int lowu = pre[u] = ++dfs_clock;
int child = 0;
for(int i = 0; i < g[u].size(); i++) {
int v = g[u][i];
  if(!pre[v]) {
child++;
     	int lowv = dfs(v, u);
      lowu = min(lowu, lowv);
      if(lowv >= pre[u]) iscut[u] = true;
//if lowv > pre[u] (u, v) is bridge

        }
        else if(pre[v] < pre[u] && v != fa) lowu = min(lowu, pre[v]);
}
if(fa < 0 && child == 1) iscut[u] = false;
    return lowu;
}

