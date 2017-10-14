int len = strlen(s);
int n = 1, pre = 0, ans = 0;
ss[0] = '$';
for(int i = 0; i < len; i++) {
    ss[n++] = '#';
    ss[n++] = s[i];
}
ss[n] = '#';
for(int i = 1; i < n; i++) {
//pre是在i之前半径延伸地最远的点
//如果pre的区间包含了i，那么i延伸的区间是i向右和i关于pre的对称点向左          
延伸的较小值
if(i < pre + p[pre])p[i] = min(p[pre – (i – pre)], p[pre] + pre - i);
else p[i] = 1;
//继续扩展i的回文区间
while(ss[i - p[i]] == ss[i + p[i]]) ++p[i];
//用i更新pre
    if(pre + p[pre] < i + p[i]) pre = i;
}
