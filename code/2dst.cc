#include <bits/stdc++.h>
using namespace std;
const int MAXN = 800 * 4 + 10;
int mx[MAXN][MAXN], mn[MAXN][MAXN], g[810][810];
int n;
void buildy(int xo, int o, int l, int r, int x) {
    if(l == r) {
        if(x != -1) mx[xo][o] = mn[xo][o] = g[x][l];
        else {
            int xlch = xo * 2, xrch = xlch + 1;
            mx[xo][o] = max(mx[xlch][o], mx[xrch][o]);
            mn[xo][o] = min(mn[xlch][o], mn[xrch][o]);
        }
        return;
    }
    int mid = (l + r) / 2, lch = o * 2, rch = lch + 1;
    buildy(xo, lch, l, mid, x);
    buildy(xo, rch, mid + 1, r, x);
    mx[xo][o] = max(mx[xo][lch], mx[xo][rch]);
    mn[xo][o] = min(mn[xo][lch], mn[xo][rch]);
}
void buildx(int o, int l, int r) {
    if(l == r) {
        buildy(o, 1, 1, n, l);
        return;
    }
    int mid = (l + r) / 2, lch = o * 2, rch = lch + 1;
    buildx(lch, l, mid);
    buildx(rch, mid + 1, r);
    buildy(o, 1, 1, n, -1);
}
void updatey(int xo, int o, int l, int r, int y, int v) {
    if(l == r) {
        if(v != -1) mn[xo][o] = mx[xo][o] = v;
        else {
            int xlch = xo * 2, xrch = xlch + 1;
            mx[xo][o] = max(mx[xlch][o], mx[xrch][o]);
            mn[xo][o] = min(mn[xlch][o], mn[xrch][o]);
        }
        return;
    }
    int mid = (l + r) / 2, lch = o * 2, rch = lch + 1;
    if(y <= mid) updatey(xo, lch, l, mid, y, v);
    else updatey(xo, rch, mid +1, r, y, v);
    mx[xo][o] = max(mx[xo][lch], mx[xo][rch]);
    mn[xo][o] = min(mn[xo][lch], mn[xo][rch]);
}
void updatex(int o, int l, int r, int x, int y, int v) {
    if(l == r) {
        updatey(o, 1, 1, n, y, v);
        return;
    }
    int mid = (l + r) / 2, lch = o * 2, rch = lch + 1;
    if(mid >= x) updatex(lch, l, mid, x, y, v);
    else updatex(rch, mid + 1, r, x, y, v);
    updatey(o, 1, 1, n, y, -1);
}
int minv, maxv;
void queryy(int xo, int o, int l, int r, int yl, int yr) {
    if(yl <= l && r <= yr) {
        minv = min(minv, mn[xo][o]);
        maxv = max(maxv, mx[xo][o]);
        return;
    }
    int mid = (l + r) / 2, lch = o * 2, rch = lch + 1;
    if(mid >= yl) queryy(xo, lch, l, mid, yl, yr);
    if(mid < yr) queryy(xo, rch, mid + 1, r, yl, yr);
}
void queryx(int o, int l, int r, int xl, int xr, int yl, int yr) {
    if(xl <= l && r <= xr) {
        queryy(o, 1, 1, n, yl, yr);
        return;
    }
    int mid = (l + r) / 2, lch = o * 2, rch = lch + 1;
    if(mid >= xl) queryx(lch, l, mid, xl, xr, yl, yr);
    if(mid < xr) queryx(rch, mid + 1, r, xl, xr, yl, yr);
}
int main() {
    int T; scanf("%d", &T);
    int cas = 1;
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                scanf("%d", &g[i][j]);
        buildx(1, 1, n);
        int q; scanf("%d", &q);
        printf("Case #%d:\n", cas++);
        while(q--) {
            int x, y, len; scanf("%d%d%d", &x, &y, &len);
            int xl = max(1, x - len / 2), xr = min(n, x + len / 2), yl = max(1, y - len / 2), yr = min(n, y + len / 2);
            minv = 1 << 30, maxv = -minv;
            queryx(1, 1, n, xl, xr, yl, yr);
            int ans = (maxv + minv) / 2;
            updatex(1, 1, n, x, y, ans);
            printf("%d\n", ans);
        }
    }
}
