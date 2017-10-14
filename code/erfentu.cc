int uN,vN;
vector<int> g[MAXN];
int linker[MAXN];
bool used[MAXN];
bool dfs(int u) {
    for(int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if(!used[v]) {
            used[v]=true;
            if(linker[v] == -1 || dfs(linker[v])) {
                linker[v]=u;
                return true;
            }
        }
    }
    return false;
}
int hungary() {
    int res=0;
    memset(linker, -1, sizeof(linker));
    for(int u=0; u < uN; u++)
    {
        memset(used, 0, sizeof(used));
        if(dfs(u)) res++;
    }
    return res;
}
