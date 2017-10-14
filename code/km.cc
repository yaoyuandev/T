struct KM // 二分图最优匹配
{
    int n; //总点数
    vector<int> g[N];
    int g2[N][N];
    void init(int nn)
    {
        n = nn;
        mem(g, 0), mem(g2, 0);
    }
    void add_edge(int u, int v, int w)
    {
        g[u].push_back(v);
        g2[u][v] = w;
    }
    int lx[N], ly[N], match[N], lcheck[N], rcheck[N];
    const int INF = INT_MAX;
    bool dfs(int u)
    {
        lcheck[u] = true;
        for (int v : g[u]) {
            if (lx[u] + ly[v] == g2[u][v] && !rcheck[v]) {
                rcheck[v] = true;
                if (match[v] == -1 || dfs(match[v])) {
                    match[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    void update()
    {
        int a = INF;
        rep(u, 1, n) {
            if (lcheck[u]) {
                for (int v : g[u]) {
                    if (!rcheck[v]) {
                        a = min(a, lx[u] + ly[v] - g2[u][v]);
                    }
                }
            }
        }
        rep(i, 1, n) {
            if (lcheck[i]) lx[i] -= a;
            if (rcheck[i]) ly[i] += a;
        }
    }
    int calc()
    {
        rep(i, 1, n) {
            lx[i] = *max_element(g2[i]+1, g2[i]+n+1);
            ly[i] = 0;
            match[i] = -1;
        }
        rep(i, 1, n) {
            for (;;) {
                mem(lcheck, 0);
                mem(rcheck, 0);
                if (dfs(i)) break; else update();
            }
        }
        int ans = 0;
        rep(i, 1, n) if (~match[i]) ans += lx[match[i]] + ly[i];
        return ans;
    }
};
int solve(int n, KM &solver)
{
    solver.init(n);
    rep(i, 1, n) rep(j, 1, n) {
        int x;
        scanf("%d", &x);
        solver.add_edge(i, j, x);
    }
    return solver.calc();
}
int main()
{
    KM solver;
    int n;
    while (~scanf("%d", &n)) printf("%d\n", solve(n, solver));
}