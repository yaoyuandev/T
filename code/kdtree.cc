#include <bits/stdc++.h>  
using namespace std;  
const int N = 50080;
const int K = 5;
typedef pair<int, int> Pair;
struct Node  
{  
    int x[K], d;
    bool f;
    static int k, cd;
    void read() {
      for (int i = 0; i < k; i++) {
        cin >> x[i];
      }
      f = 0;
    }
    bool operator < (Node node) const {
      return x[cd] < node.x[cd];
    }
};
int Node::k = 0, Node::cd = 0; 
int mid(int l, int r)
{
  return l + (r - l) / 2;
} 
int dist(Node a, Node b) //算k维的距离
{  
    int res = 0;  
    for(int i = 0;i < Node::k; i++)  
        res += (a.x[i] - b.x[i])*(a.x[i] - b.x[i]);  
    return res;  
}  
Node a[N];
priority_queue<Pair> pq;  // 距离 下标
void build(int l, int r, int d)  
{  
    if (l > r) return;
    int m = mid(l, r);
    Node::cd = d;
    nth_element(a+l,a+m,a+r+1); //保证第n大的在第n的位置,类似快排的基准
    //这样就可以保证a[m]是中间的 这样树就可以建的非常平均
    a[m].d = d; //这个点的维度是d
    if(l == r) //到了叶节点了
    {  
        a[m].f = true; //应是是不是叶节点的意思
        return;  
    }  
    build(l, m-1,(d+1)%Node::k); //递归建树
    build(m+1,r, (d+1)%Node::k);  
}
int num;
void fd(int l, int r, Node tar)  
{  
    if (l > r) return;  
    int m = mid(l, r);
    int d = dist(a[m], tar); 
    if(a[m].f) {   //如果是叶子
      if(pq.size() < num) { // 还每找满m个
        pq.push(make_pair(d, m));
      } else if(d < pq.top().first) { // 已经找了m个了,要删了 并且是比当前最远点小
        pq.pop(); 
        pq.push(make_pair(d, m));
      }  
      return;  
    }  
    int t = tar.x[a[m].d] - a[m].x[a[m].d];
    // 要调查的点和 这个节点的距离
    if(t > 0) { // 右子树
      fd(m+1, r, tar); //先在右子树
      if(pq.size() < num) {  
        pq.push(make_pair(d, m));
        fd(l,m-1,tar); // 再找左子树  
      } else {      
        if(d < pq.top().first) {
          pq.pop();
          pq.push(make_pair(d, m));
        }
        if(pq.top().first > t*t) fd(l,m-1,tar);  
      }  
    } else { // 
      fd(l,m-1,tar);  
      if(pq.size() < num) {  
        pq.push(make_pair(d, m));  
        fd(m+1,r,tar);  
      } else {  
        if(pq.top().first > d) {
            pq.pop();  
            pq.push(make_pair(d, m));
        }  
        if (pq.top().first > t*t) fd(m+1,r,tar);  
      }
    }  
}
void solve(int n, int k)
{
  Node::k = k;
  for (int i = 0; i < n; i++) a[i].read();
  build(0, n-1, 0);
  int t;  
  cin >> t;
  while (t--) {
    Node q;
    q.read();
    while (!pq.empty()) pq.pop();
    cin >> num; // 题目中需要找与q距离最近的num个点
    fd(0, n-1, q);
    vector<int> ans;
    while (!pq.empty()) {
      ans.push_back(pq.top().second);
      pq.pop();
    }
    printf("the closest %d points are:\n",num);  
    for(int j = num - 1; j >= 0; j--) {  
      for(int kk = 0;kk < k;kk++) {  
        kk == 0 ? cout << a[ans[j]].x[kk] : cout << ' ' << a[ans[j]].x[kk];
      }
      cout << endl;
    }
  }
}  
int main()  
{  
  int n, k;
  while(cin >> n >> k) solve(n, k);
}  