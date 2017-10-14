Divide_Conquer(Q, AL, AR)
//Q是当前处理的操作序列
//WANT是要求的贡献，CURRENT为已经累计的贡献(记录的是1~AL-1内所有修改的贡献)
//[AL, AR]是询问的答案范围区间
if AL = AR then
    将Q中所有是询问操作的答案设为AL
end if
//我们二分答案,AM为当前的判定答案
AM = (AL+AR) / 2
//Solve是主处理函数,只考虑参数满足判定标准[AL, AM]的修改的贡献,因为CURRENT域中已经记录了[1,AL-1]的修改的贡献了,这一步是保证时间复杂度的关键,因为SOLVE只于当前Q的长度有关,而不与整个操作序列的长度有线性关系,这保证了主定理解出来只多一个log
Solve(Q, AL, AM)
//Solve之后Q中各个参数满足判定标准的修改对询问的贡献被存储在ANS数组
//Q1,Q2为了两个临时数组，用于划分操作序列
for i = 1 to Length(Q) do
    if (Q[i].WANT <= Q[i].CURRENT + ANS[i]) then
        //当前已有贡献不小于要求贡献,说明最终答案应当不大于判定答案
        向数组Q1末尾添加Q[i]
    else
        //当前已有贡献小于要求贡献,说明最终答案应当大于判定答案
        //这里是整体二分的关键,把当前贡献累计入总贡献,以后不再重复统计!
        Q[i].CURRENT = Q[i].CURRENT + ANS[i]
        向数组Q2末尾添加Q[i]
    end if
end for
//分治,递归处理
Divide_Conquer(Q1, AL, AM)
Divide_Conquer(Q2, AM+1, AR)
以上别人的伪代码 非常清楚

带修改的整体二分
void cal(int ql, int qr, int l, int mid) {
    for(int i = ql; i <= qr; i++) {
        if(nd[i].k) nd[i].cnt = query(nd[i].r) - query(nd[i].l - 1);
        else if(nd[i].r <= mid) update(nd[i].l, nd[i].cnt);
    }
    for(int i = ql; i <= qr; i++) if(nd[i].r <= mid && (!nd[i].k)) update(nd[i].l, -nd[i].cnt);
}
void divide(int ql, int qr, int l, int r) {
    if(l == r) {
        for(int i = ql; i <= qr; i++) if(nd[i].k) ans[nd[i].id] = l;
        return;
    }
    int mid = (l + r) / 2;
    cal(ql, qr, l, mid);
    int p1 = 0, p2 = 0;
    for(int i = ql; i <= qr; i++) {
        if(nd[i].k) {
            if(nd[i].cnt >= nd[i].k) t1[++p1] = nd[i];
            else {
                nd[i].k -= nd[i].cnt;
                t2[++p2] = nd[i];
            }
        }
        else {
            if(nd[i].r <= mid) t1[++p1] = nd[i];
            else t2[++p2] = nd[i];
        }
    }
    for(int i = 1; i <= p1; i++) nd[ql - 1 + i] = t1[i];
    for(int i = 1; i <= p2; i++) nd[ql + p1 - 1 + i] = t2[i];
    if(p1) divide(ql, ql + p1 - 1, l, mid);
    if(p2) divide(ql + p1, qr, mid + 1, r);
}
