扩展欧几里得
//ax + by = d, d = gcd(a, b)
void gcd(ll a , ll b ,ll &d, ll &x,ll &y){
    if(!b) {d = a; x = 1; y = 0; return;}
    else{
        gcd(b , a % b ,d , y , x);
        y -= x * (a / b);
        return;
    }
}

逆元
//a在模n下的逆元，a和n互素才有逆元
ll inv(ll a, ll n) {
    ll d, x, y;
    gcd(a, n, d, x, y);
    return d == 1 ? (x + n) % n : -1;
}
