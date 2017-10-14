void getfail() {
    f[0] = f[1] = 0;
    for(int i = 1; i < n; i++) {
        int j = f[i];
		//找到与当前后缀匹配的最靠右的前缀的位置
        while(j && c[i] != c[j]) j = f[j];
	    f[i + 1] = c[i] == c[j] ? j + 1 : 0;
    }
}
void findp(char *T, char *P, int* f) {
	int n = strlen(T), m = strlen(P);
	int j = 0;
	for(int i = 0; i < n; i++) {
		//如果不匹配就往前找
        while(j && P[j] != T[i]) j = f[j];
        if(P[j] == T[i]) j++;
        if(j == m) printf("%d\n", i - m + 1);
	}
}
