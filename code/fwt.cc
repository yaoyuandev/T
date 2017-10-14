//位运算多项式卷积
void FWT(int *a, int n) {
    for(int d = 1; d < n; d<<=1)
        for(int m = d<<1, i = 0; i < n; i += m)
            for(int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = (x + y) % MOD, a[i + j + d] = (x - y + MOD) % MOD;
                //xor:a[i+j]=x+y,a[i+j+d]=(x-y+mod)%mod;  
                //and:a[i+j]=x+y;
                //or:a[i+j+d]=x+y;
            }
}
void UFWT(int *a, int n) {
    for(int d = 1; d < n; d <<= 1)
        for(int m = d<<1, i = 0; i < n; i += m)
            for(int j = 0; j < d; j++) {
                int x = a[i + j], y = a[i + j + d];
                a[i + j] = (ll)(x + y) * inv2 % MOD, a[i + j + d] = ((ll)(x - y) * inv2 % MOD + MOD) % MOD;
                //xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;  
                //and:a[i+j]=x-y;  
                //or:a[i+j+d]=y-x;
            }
}
void conv(int *a, int *b, int n) {
    FWT(a, n);
    FWT(b, n);
    for(int i = 0; i < n; i++) a[i] = (ll)a[i] * b[i] % MOD;
    UFWT(a, n);
}
