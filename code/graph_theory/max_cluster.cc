/*
最大团搜索算法
Si = {vi, vi+1, ... , vn}
mc[i] = MC(Si) = 点集合 Si 的最大团
MC(V) = mc[1]
mc[i] = mc[i+1] || mc[i] = mc[i+1] + 1 因为最多增加一个点
后一种情况发生是在 Si 中找到一个包含vi的团
所以只要搜 是否在 Si 中有一个包含vi且比当前最大团还大的团
*/
#include <bits/stdc++.h>
#define rep(i, l, r) for (int (i) = (l); (i) <= (r); (i)++)
#define log(x) cout << #x << " = " << x << endl
#define mem(x, y) memset((x), (y), sizeof(x))
using namespace std;
int n, ans;
bool found;
const int N = 50 + 9;
int g[N][N];
int len[N], mc[N], li[N][N];
void dfs(int sz)
{
    if (len[sz] == 0) {
        if (sz > ans) {
            ans = sz;
            found = true;
        }
    }
    for (int k = 0; k < len[sz] && !found; k++) {
        if (sz + len[sz] - k <= ans) break;
        int i = li[sz][k];
        if (sz + mc[i] <= ans) break;
        len[sz+1] = 0;
        for (int j = k + 1; j < len[sz]; j++) {
            if (g[i][li[sz][j]]) 
                li[sz+1][len[sz+1]++] = li[sz][j];
        }
        dfs(sz+1); 
    }
}
int max_cluster()
{
    mc[n] = ans = 1;
    for (int i = n - 1; i; i--) {
        found = false;
        len[1] = 0;
        rep(j, i+1, n) {
            if (g[i][j]) li[1][len[1]++] = j;
        }
        dfs(1);
        mc[i] = ans;
    }
    return ans;
}
int solve()
{
    rep(i, 1, n) rep(j, 1, n) scanf("%d", &g[i][j]);
    return max_cluster();
}
int main()
{
    for (;;) {
        scanf("%d", &n);
        if (n == 0) break;
        printf("%d\n", solve());
    }
}