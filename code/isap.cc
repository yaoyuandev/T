struct ISAP {
    struct Edge {
      int from, to, cap, flow;
      bool operator < (const Edge& b) {
        return from < b.from || (from == b.from && to < b.to);
      }
    };
    
    
      int  n, m, s, t;
      vector<Edge> edges;
      vector<int> g[MAXN];   // 邻接表，g[i][j]表示结点i的第j条边在e数组中的序号
      bool vis[MAXN];        // BFS使用
      int d[MAXN];           // 从起点到i的距离
      int cur[MAXN];        // 当前弧指针
      int p[MAXN];          // 可增广路上的上一条弧
      int num[MAXN];        // 距离标号计数
    
      void add_edge(int from, int to, int cap) {
        edges.push_back((Edge){from, to, cap, 0});
        edges.push_back((Edge){to, from, 0, 0});
        m = edges.size();
        g[from].push_back(m-2);
        g[to].push_back(m-1);
      }
    
      bool BFS() {
        memset(vis, 0, sizeof(vis));
        queue<int> Q;
        Q.push(t);
        vis[t] = 1;
        d[t] = 0;
        while(!Q.empty()) {
          int x = Q.front(); Q.pop();
          for(int i = 0; i < g[x].size(); i++) {
            Edge& e = edges[g[x][i]^1];
            if(!vis[e.from] && e.cap > e.flow) {
              vis[e.from] = 1;
              d[e.from] = d[x] + 1;
              Q.push(e.from);
            }
          }
        }
        return vis[s];
      }
    
      void init(int nn) {
        n = nn;
          mem(g, 0);
        edges.clear();
      }
    
      void ClearFlow() {
        for(int i = 0; i < edges.size(); i++) edges[i].flow = 0;    
      }
    
      int Augment() {
        int x = t, a = inf;
        while(x != s) {
          Edge& e = edges[p[x]];
          a = min(a, e.cap-e.flow);
          x = edges[p[x]].from;
        }
        x = t;
        while(x != s) {
          edges[p[x]].flow += a;
          edges[p[x]^1].flow -= a;
          x = edges[p[x]].from;
        }
        return a;
      }
    
      int max_flow(int s, int t, int need) {
        this->s = s; this->t = t;
        int flow = 0;
        BFS();
        memset(num, 0, sizeof(num));
        for(int i = 0; i < n; i++) num[d[i]]++;
        int x = s;
        memset(cur, 0, sizeof(cur));
        while(d[s] < n) {
          if(x == t) {
            flow += Augment();
            if(flow >= need) return flow;
            x = s;
          }
          int ok = 0;
          for(int i = cur[x]; i < g[x].size(); i++) {
            Edge& e = edges[g[x][i]];
            if(e.cap > e.flow && d[x] == d[e.to] + 1) { // Advance
              ok = 1;
              p[e.to] = g[x][i];
              cur[x] = i; // 注意
              x = e.to;
              break;
            }
          }
          if(!ok) { // Retreat
            int m = n-1; // 初值注意
            for(int i = 0; i < g[x].size(); i++) {
              Edge& e = edges[g[x][i]];
              if(e.cap > e.flow) m = min(m, d[e.to]);
            }
            if(--num[d[x]] == 0) break;
            num[d[x] = m+1]++;
            cur[x] = 0; // 注意
            if(x != s) x = edges[p[x]].from;
          }
        }
        return flow;
      }
    
      vector<int> Mincut() { // call this after maxflow
        BFS();
        vector<int> ans;
        for(int i = 0; i < edges.size(); i++) {
          Edge& e = edges[i];
          if(!vis[e.from] && vis[e.to] && e.cap > 0) ans.push_back(i);
        }
        return ans;
      }
    
      void Reduce() {
        for(int i = 0; i < edges.size(); i++) edges[i].cap -= edges[i].flow;
      }
    
      void print() {
        printf("Graph:\n");
        for(int i = 0; i < edges.size(); i++)
          printf("%d->%d, %d, %d\n", edges[i].from, edges[i].to , edges[i].cap, edges[i].flow);
      }
    };