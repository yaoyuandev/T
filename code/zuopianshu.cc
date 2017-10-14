#include <bits/stdc++.h>
#define rep(i, l, r) for (int (i) = (l); (i) <= (r); (i)++)
using namespace std;
int n,m,ans;
struct Data{int fa,x,dis,l,r;};
const int MAXN = 100001;
Data q[MAXN];
int find(int x)
{
    return x==q[x].fa?x:q[x].fa=find(q[x].fa);
}
int merge(int x,int y)
{
    if(!x) return y;
    if(!y) return x;
    if(q[x].x<q[y].x) swap(x,y);
    q[x].r=merge(q[x].r,y);
    q[q[x].r].fa=x;
    if(q[q[x].l].dis<q[q[x].r].dis) swap(q[x].l,q[x].r);
    if(!q[x].r) q[x].dis=0;
    else q[x].dis=q[q[x].r].dis+1;
    return x;
}
int pop(int x)
{
    int l=q[x].l,r=q[x].r;
    q[l].fa=l,q[r].fa=r;
    q[x].l=q[x].r=q[x].dis=0;
    return merge(l,r);
}
void slove()
{
    int x,y,u,v,l1,l2;
    rep(i, 1, n) {
        scanf("%d", &q[i].x);
        q[i].fa=i;
        q[i].l=q[i].r=q[i].dis=0;
     }
    scanf("%d", &m);
    rep(i, 1, m) {
        scanf("%d%d", &x, &y);
        l1=find(x), l2=find(y);
        if(l1 == l2){printf("-1\n");continue;}
        q[l1].x/=2;u=pop(l1);u=merge(u,l1);
        q[l2].x/=2;v=pop(l2);v=merge(v,l2);
        ans=merge(u,v);
        printf("%d\n",q[ans].x);
    }
}
int main()
{
    while(~scanf("%d",&n)) slove();
}