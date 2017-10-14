ll phi(ll n){
    ll ans = n,a = n;    
    for(ll i = 2; i * i <= a; i++){    
        if(a % i == 0){    
            ans = ans / i * (i - 1);
            while(a % i == 0) a /= i;    
        }    
    }    
    if(a > 1) ans = ans / a * (a - 1);    
    return ans;    
}   