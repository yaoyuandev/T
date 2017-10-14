ll qPow (ll a, ll k) {
    ll ans = 1;
    while (k) {
        if (k&1)
            ans = (ans * a) % p;
        a = (a * a) % p;
        k /= 2;
    }
    return ans;
}

ll C (ll a, ll b, ll p) {
    if (a < b)
        return 0;
    if (b > a - b)
        b = a - b;

    ll up = 1, down = 1;
    for (ll i = 0; i < b; i++) {
        up = up * (a-i) % p;
        down = down * (i+1) % p;
    }
    return up * qPow(down, p-2) % p; // 逆元
}
ll lucas (ll a, ll b, ll p) {
    if (b == 0)
        return 1;
    return C(a%p, b%p, p) * lucas(a/p, b/p, p) % p;
}
