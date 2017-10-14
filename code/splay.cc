int ch[MAXN][2], fa[MAXN], val[MAXN], sz[MAXN], cnt[MAXN];
int rt, ncnt;
void update(int r) {sz[r] = sz[ch[r][0]] + sz[ch[r][1]] + cnt[r];}
void rot(int x) {
    int y = fa[x], z = fa[y], d = ch[y][1] == x;
    ch[y][d] = ch[x][d^1], fa[ch[y][d]] = y;
    ch[x][d^1] = y; fa[y] = x;
    fa[x] = z;
    if(z) ch[z][ch[z][1] == y] = x;
    update(y);
}
void splay(int r, int tp) {
    for(int y, z; (y = fa[r]) != tp; rot(r)) {
        z = fa[y];
        if(z == tp) continue;
        if((ch[z][0] == y) == (ch[y][0] == r)) rot(y);
        else rot(r);
    }
    if(!tp) rt = r;
    update(r);
}
void ins(int r, int x) {
    int y = 0;
    while(r && val[r] != x) {y = r; r = ch[r][val[r] < x];}
    if(r) ++cnt[r];
    else {
        r = ++ncnt;
        sz[r] = cnt[r] = 1;
        val[r] = x; fa[r] = y;
        ch[r][0] = ch[r][1] = 0;
        if(y) ch[y][val[y] < x] = r;
    }
    splay(r, 0);
}
void get(int v) {
    int x = rt; if(!x) return;
    while(ch[x][val[x] < v] && val[x] != v) x = ch[x][val[x] < v];
    splay(x, 0);
}
int getrk(int v) {
    get(v);
    return sz[ch[rt][0]];
}
int getkth(int x) {
    int y = rt, p;
    if(x > sz[rt]) return 0;
    while(1) {
        p = ch[y][0];
        if(sz[p] + cnt[y] < x) {
            x -= sz[p] + cnt[y];
            y = ch[y][1];
        }
        else if(sz[p] >= x) y = p;
        else return val[y];
    }
}
int nxt(int x, bool op) {
    get(x);
    if((val[rt] > x && op) || (val[rt] < x && !op)) return rt;
    int p = ch[rt][op];
    while(ch[p][op^1]) p = ch[p][op^1];
    return p;
}
void del(int v) {
    int p = nxt(v, 0), s = nxt(v, 1);
    splay(p, 0);
    splay(s, p);
    p = ch[s][0];
    if(cnt[p] > 1) -- cnt[p], splay(p, 0);
    else ch[s][0] = 0;
}
