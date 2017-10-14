const double pi = atan(1.0) * 4;
 
struct complex {
	double a, b;
	complex(double aa = 0.0, double bb = 0.0) { a = aa; b = bb; }
	complex operator +(const complex &e) { return complex(a + e.a, b + e.b); }
	complex operator -(const complex &e) { return complex(a - e.a, b - e.b); }
	complex operator *(const complex &e) { return complex(a * e.a - b * e.b, a * e.b + b * e.a); }
};
 
void change(complex * y, long long len) {
	long long i, j, k;
	for (i = 1, j = len / 2; i < len - 1; i++) {
		if (i < j) swap(y[i], y[j]);
		k = len / 2;
		while (j >= k) {
			j -= k;
			k /= 2;
		}
		if (j < k) j += k;
	}
}
 
void fft(complex *y, long long len, long long on) {
	change(y, len);
	for (int h = 2; h <= len; h <<= 1) {
		complex wn(cos(-on * 2 * pi / h), sin(-on * 2 * pi / h));
		for (int j = 0; j < len; j += h) {
			complex w(1, 0);
			for (int k = j; k < j + h / 2; k++) {
				complex u = y[k];
				complex t = w * y[k + h / 2];
				y[k] = u + t;
				y[k + h / 2] = u - t;
				w = w * wn;
			}
		}
	}
	if (on == -1)
		for (int i = 0; i < len; i++)
			y[i].a /= len;
}
 