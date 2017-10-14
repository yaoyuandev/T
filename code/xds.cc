#include <bits/stdc++.h>
using namespace std;
const int MAXM = 1E6 + 9;
const int MAXR = 20 + 9;
const int INF = INT_MAX / 10;
struct Node
{
    int setv, addv, sumv, minv, maxv;
    Node()
    {
        setv = -1, addv = 0, sumv = 0, minv = 0, maxv = 0;
    }
};
struct Tree
{
    Node tree[4 * MAXM];
    int mid(int l, int r)
    {
        return l + (r-l) / 2;
    }
    void pushdown(int o)
    {
        int lc(o*2), rc(o*2+1);
        if (tree[o].setv >= 0) {
            tree[lc].setv = tree[rc].setv = tree[o].setv;
            tree[lc].addv = tree[rc].addv = 0;
            tree[o].setv = -1;
        }
        if (tree[o].addv) {
            tree[lc].addv += tree[o].addv;
            tree[rc].addv += tree[o].addv;
            tree[o].addv = 0;
        }
    }
    void maintain(int o, int l, int r)
    {
        int lc(o*2), rc(o*2+1);
        if (r > l) {
            tree[o].sumv = tree[lc].sumv + tree[rc].sumv;
            tree[o].minv = min(tree[lc].minv,tree[rc].minv);
            tree[o].maxv = max(tree[lc].maxv,tree[rc].maxv);
        }
        if (tree[o].setv >= 0) {
            tree[o].minv = tree[o].maxv = tree[o].setv;
            tree[o].sumv = (r-l+1)*tree[o].setv;
        }
        if (tree[o].addv) {
            tree[o].minv += tree[o].addv;
            tree[o].maxv += tree[o].addv;
            tree[o].sumv += (r-l+1) * tree[o].addv;
        }
    }
    void update(int o, int l, int r, int op, int ql, int qr, int v)
    {
        int lc(o*2), rc(o*2+1);
        if (ql <= l && qr >= r) {
            if (op == 1) tree[o].addv += v;
            else {
                tree[o].setv = v;
                tree[o].addv = 0;
            }
        } else {
            pushdown(o);
            int m = mid(l, r);
            if (ql <= m) update(lc, l, m, op, ql, qr, v); else maintain(lc, l, m);
            if (qr > m) update(rc, m+1, r, op, ql, qr, v); else maintain(rc, m+1, r);
        }
        maintain(o, l, r);
    }
    Node query(int o, int l, int r, int ql, int qr)
    {
        Node res;
        int lc(o*2), rc(o*2+1), m(mid(l, r));
        maintain(o, l, r);
        if (ql <= l && qr >= r) {
            res.sumv = tree[o].sumv;
            res.minv = tree[o].minv;
            res.maxv = tree[o].maxv;
        } else {
            pushdown(o);
            Node lres;
            lres.minv = INF, lres.maxv = -INF;
            Node rres(lres);
            if (ql <= m) lres = query(lc, l, m, ql, qr); else maintain(lc, l, m);
            if (qr > m) rres = query(rc, m+1, r, ql, qr); else maintain(rc, m+1, r);
            res.sumv = lres.sumv + rres.sumv;
            res.minv = min(lres.minv, rres.minv);
            res.maxv = max(lres.maxv, rres.maxv);
        }
        return res;
    }
};
Tree tree[MAXR];
void solve(int r, int c, int m)
{
    for (int i(1); i <= r; i++) tree[i].tree[1].setv = 0;
    while (m--) {
        int op, x1, y1, x2, y2;
        scanf("%d%d%d%d%d", &op, &x1, &y1, &x2, &y2);
        if (op < 3) {
            int v;
            scanf("%d", &v);
            for (int i(x1); i <= x2; i++) tree[i].update(1, 1, c, op, y1, y2, v);
        } else {
            Node ans;
            ans.sumv = 0, ans.minv = INF, ans.maxv = -INF;
            for (int i(x1); i <= x2; i++) {
                Node res(tree[i].query(1, 1, c, y1, y2));
                ans.sumv += res.sumv;
                ans.minv = min(ans.minv, res.minv);
                ans.maxv = max(ans.maxv, res.maxv);
            }
            printf("%d %d %d\n", ans.sumv, ans.minv, ans.maxv);
        }
    }
}
int main()
{
    //freopen("in", "r", stdin);
    int r, c, m;
    while (scanf("%d%d%d", &r, &c, &m) != EOF) {
        solve(r, c, m);
    }
}