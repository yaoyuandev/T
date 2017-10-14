ll mul_mod(ll x, ll y, ll mod = MOD)
{
    return x * y % MOD;
}
m[1] = 1;
inv[1] = 1;
for (n = 2; ;n++) {
    s[n] = s[n - 1] + n;
    m[n] = mul_mod(m[n - 1], n);
    inv[n] = (MOD - MOD / n) * inv[MOD % n] % MOD;
    if (s[n] > MAXX) break;
}