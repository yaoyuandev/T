double a[MAXN][MAXN];
double ans[MAXN];
bool f[MAXN];//自由变量
int sgn(double x) {return (x > eps) - (x < -eps);}
//x 0~equ - 1, y 0~var
int gauss(int equ, int var) {
    int k = 0, col = 0;
    memset(f, true, sizeof(f));
    for(k = 0; k < equ && col < var; k++, col++) {
        int r = k;
        for(int i = k + 1; i < equ; i++)
            if(fabs(a[i][col]) > fabs(a[r][col])) r = i;
        if(r != k) for(int j = k; j <= var; j++) swap(a[r][j], a[k][j]);
        if(a[k][col] == 0) {k--; continue;}
        for(int i = k + 1; i < equ; i++) if(a[i][col]) {
            for(int j = var; j >= col; j--) a[i][j] -= a[i][col] / a[k][col] * a[k][j];
        }
    }
    for(int i = k; i < equ; i++) if(sgn(a[i][col]) != 0) return 0;
    if(k < var) {
        for(int i = k - 1; i >= 0; i--) {
            int cnt = 0, p;
            for(int j = 0; j < var; j++)
                if(sgn(a[i][j]) && f[j])
                    cnt++, p = j;
            if(cnt > 1) continue;
            double t = a[i][var];
            for(int j = 0; j < var; j++)
                if(sgn(a[i][j]) && j != p)
                    t -= a[i][j] * ans[j];
            ans[p] = t / a[i][p];
            f[p] = 0;
        }
    }
    for(int i = var - 1; i >= 0; i--) {
        double t = a[i][var];
        for(int j = i + 1; j < var; j++)
            if(sgn(a[i][j]))
                t -= a[i][j] * ans[j];
        ans[i] = t / a[i][i];
    }
    return 1;
}
