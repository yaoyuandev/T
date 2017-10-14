
最简分数实数逼近
a1 = 100000, a2 = 1, ans = 100000;
ll xl = 0, yl = 1, xr = 1, yr = 0, xm, ym;
while(yl + yr <= 100000) {
    xm = xl + xr;
    ym = yl + yr;
    if(check(xm, ym, a1, a2, kk)) {a1 = xm, a2 = ym;}
    if(get(xm, ym, kk)) {xr = xm, yr = ym;}
    else {xl = xm, yl = ym;}
 }
struct heap {
    priority_queue<int> p, q;
    void init() {
        while(!p.empty()) p.pop();
        while(!q.empty()) q.pop();
    }
    void add(int x) {p.push(x);}
    void del(int x) {q.push(x);}
    int top() {
        while(1) {
            if(p.empty()) return -INF;
            else if(!q.empty() && p.top() == q.top()) {p.pop(); q.pop();}
            else return p.top();
        }
    }
    int toptwo() {
        int a = top(); del(a);
        int b = top(); add(a);
        if(b == -INF) return a == -INF ? a : 0;
        else return max(a + b, 0);
    }
}