#include <bits/stdc++.h>
#define log(x) cout << #x << " = " << (x) << endl
#define mem(x, y) memset((x), (y), sizeof((x)))
#define rep(i, l, r) for (int (i) = (l); (i) <= (r); (i)++)
using namespace std;
typedef long long ll;
/*---金牌---*/
const int N = 200 + 9;
const int INF = 0x3f3f3f3f;
const int MAXN = 10*N;
int low[MAXN*10];
int n, m;
struct Dinic
{
    struct Edge
    {
      int from, to, cap, flow;
    };
    vector<Edge> edges;
    vector<int> g[MAXN];
    void init() {
        mem(g, 0);
        edges.clear();
    }
    void add_edge(int from, int to, int cap) {
      edges.push_back((Edge){from, to, cap, 0});
      edges.push_back((Edge){to, from, 0, 0});
      int m = edges.size();
      g[from].push_back(m - 2);
      g[to].push_back(m - 1);
    }
    int s, t;
    bool vis[MAXN];
    int d[MAXN], cur[MAXN];
    bool BFS()
    {
      memset(vis, 0, sizeof(vis));
      queue<int> q;
      q.push(s);
      d[s] = 0;
      vis[s] = true;
      while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = 0; i < g[x].size(); i++) {
          Edge& e = edges[g[x][i]];
          if (!vis[e.to] && e.cap > e.flow) {
            vis[e.to] = true;
            d[e.to] = d[x] + 1;
            q.push(e.to);
          }
        }
      }
      return vis[t];
    }
    int DFS(int x, int a)
    {
      if (x == t || a == 0) return a;
      int flow = 0;
      int f;
      for (int& i = cur[x]; i < g[x].size(); i++) {
        Edge& e = edges[g[x][i]];
        if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0) {
          e.flow += f;
          edges[g[x][i]^1].flow -= f;
          flow += f;
          a -= f;
          if (a == 0) break;
        }
      }
      return flow;
    }
    int max_flow(int ss, int tt)
    {
        s = ss, t = tt;
      int flow = 0;
      while (BFS()) {
        memset(cur, 0, sizeof(cur));
        flow += DFS(s, INF);
      }
      return flow;
    }
    void solve(int source, int sink)
    {
        max_flow(source, sink);
        int sz = g[source].size() - 1;
        bool flag = true;
        rep(i, 0, sz) {
            if (edges[g[source][i]].flow < edges[g[source][i]].cap) {
                puts("NO");
                flag = false;
            }
        }
        if (flag) {
            puts("YES");
            rep(i, 1, m) {
               //log(low[i]);
                printf("%d\n", edges[i*2+1].cap-edges[i*2+1].flow + low[i]);
            }
        }
    }
};
void solve(Dinic &solver)
{
    solver.init();
    scanf("%d", &m);
    int source = n + 1, sink = n + 2;
    // sink -> source cap : inf
    solver.add_edge(sink, source, INF);
    int in[N];
    mem(in, 0);
    mem(low, 0);
    rep(i, 1, m) {
        int u, v, b, c;
        scanf("%d%d%d%d", &u, &v, &b, &c);
        low[i] = b; // 流量下界
        in[u] -= b;
        in[v] += b;
        solver.add_edge(u, v, c - b);
    }
    rep(i, 1, n) {
        if (in[i] < 0) {
            solver.add_edge(i, sink, -in[i]);
        } else if (in[i] > 0) {
            solver.add_edge(source, i, in[i]);
        }
    }
    solver.solve(source, sink);
}
int main()
{
    Dinic solver;
    while (~scanf("%d", &n)) solve(solver);
}