struct Edge {
    int u, v, w;
    bool operator < (const Edge& rhs) const {
        return w < rhs.w;
    }
}edges[8 * MAXN];
struct node {
    int x, y, id;
    bool operator < (const node& rhs) const {
        return x == rhs.x ? y > rhs.y : x > rhs.x;
    }
}nd[MAXN];
int ecnt, n, k, sz;
int sq[MAXN];
int minv[MAXN], pos[MAXN];
int p[MAXN];
int lowbit(int x) {return x & -x;}
void update(int x, int val, int id) {
    while(x) {
        if(val < minv[x]) {
            minv[x] = val; pos[x] = id;
        }
        x -= lowbit(x);
    }
}
int query(int x) {
    int ans = 1 << 30, ret = 0;
    while(x <= sz) {
        if(minv[x] < ans) {
            ans = minv[x]; ret = pos[x];
        }
        x += lowbit(x);
    }
    //cout << ans << endl;
    return ret;
}
int fp(int x) {return p[x] == x ? x : p[x] = fp(p[x]);}
void addEdge(int u, int v, int w) {
    edges[ecnt++] = (Edge) {u, v, w};
}
void solve() {
    for(int dir = 0; dir < 4; dir++) {
        if(dir == 1 || dir == 3)
            for(int i = 1; i <= n; i++) swap(nd[i].x, nd[i].y);
        else if(dir == 2)
            for(int i = 1; i <= n; i++) nd[i].x = -nd[i].x;
        sort(nd + 1, nd + n + 1);
        for(int i = 1; i <= n; i++) sq[i] = nd[i].y - nd[i].x;
        sort(sq + 1, sq + n + 1);
        sz = unique(sq + 1, sq + n + 1) - (sq + 1);
        for(int i = 1; i <= sz; i++) {minv[i] = (1 << 30); pos[i] = 0;}
        for(int i = 1; i <= n; i++) {
            int p = lower_bound(sq + 1, sq + sz + 1, nd[i].y - nd[i].x) - sq;
            int v = query(p);
            //cout << p << ' ' << v << endl;
            if(v) addEdge(nd[i].id, nd[v].id, abs(nd[i].x - nd[v].x) + abs(nd[i].y - nd[v].y));
            update(p, nd[i].x + nd[i].y, i);
        }
    }
    sort(edges, edges + ecnt);
    int cnt = 0;
    for(int i = 1; i <= n; i++) p[i] = i;
    for(int i = 0; i < ecnt; i++) {
        Edge e = edges[i];
        int x = fp(e.u), y = fp(e.v);
        if(x != y) {
            p[x] = y;
            if(++cnt == n - k) {cout << e.w << endl; break;}
            //cout << cnt << endl;
        }
    }
}
