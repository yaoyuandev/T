bool solve()
{
    int n, k;
    scanf("%d%d", &n, &k);
    int a[N];  
    int dp[N];  
    int g[N]; 
    rep(i, 1, n) scanf("%d", &a[i]), g[i] = inf;
    int ans1 = 0;
    rep(i, 1, n) {
        int k = upper_bound(g+1, g+1+n, a[i]) - g;
        dp[i] = k;
        g[k] = a[i];
        ans1 = max(ans1, k);
    }