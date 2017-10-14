ll C(ll n, ll m)
{
	ll c = 1;
	for (int i = 1; i <= m; i++) {
		c *= (n - m + i);
		if (c % i == 0) c /= i;
	}
	return c;
}