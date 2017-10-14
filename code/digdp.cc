//基本上都是这个模板，但是有点慢
int dp(int pos, int sum, int lz, int lim) {
    if(!lim && !lz && d[pos][sum] != -1) return d[pos][sum];
    if(pos == 0) return sum >= 33;
    int bd = lim ? s[pos] : 1;
    int res = 0;
    for(int i = 0; i <= bd; i++) {
        if(i == 0) {
            if(lz) res += dp(pos - 1, sum, lz, lim && i == bd);
            else res += dp(pos - 1, sum + 1, 0, lim && i == bd);
        }
        else res += dp(pos - 1, sum - 1, 0, lim && i == bd);
    }
    if(!lim && !lz) d[pos][sum] = res;
    return res;
}
int solve(int x) {
    int cnt = 0;
    while(x) {
        if(x & 1) s[++cnt] = 1;
        else s[++cnt] = 0;
        x /= 2;
    }
    return dp(cnt, 33, 1, 1);
}
