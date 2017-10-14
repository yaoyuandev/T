struct qnode {
    int l, r, id;
    ll a, b;
    bool operator < (const qnode& rhs) const {
        return dv[l] == dv[rhs.l] ? dv[r] < dv[rhs.r] : dv[l] < dv[rhs.l];
    }
}qn[MAXN];
int bd = (int)sqrt(n);
for(int i = 1; i <=n; i++) {
    dv[i] = (i - 1) / bd + 1;
}
