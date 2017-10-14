// n个方程 x ≡ a[i](mod m[i]) i = 0..n-1
ll china(int n, ll *a, ll *m)
{
    ll M = m[0], R = a[0];
    for (int i = 1; i < n; i++) {
        ll d = __gcd(M, m[i]);
        ll c = a[i] - R;
        if (c % d) return -1;
        ll k1, k2;
        extgcd(M,m[i],d,k1, k2);
        k1 = (c /d * k1) % (m[i]/d);
        R = R + k1 * M;
        M = M /d * m[i];
        R %= M;
    }
    if (R < 0) R += M;
    return R;
}