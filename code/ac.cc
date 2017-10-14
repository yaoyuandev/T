void getfail() {
    queue<int> q;
    for(int i = 0; i < 26; i++) if(ch[0][i]) q.push(ch[0][i]); 
    while(!q.empty()) {
        int rt = q.front(); q.pop();
        for(int i = 0; i < 26; i++) {
            int u = ch[rt][i];
            if(!u) {ch[rt][i] = ch[fail[rt]][i]; continue;} 
			//如果本来没有u节点 那么就走失配边 从而形成了图
            q.push(u);
            int v = fail[rt];
            while(v && !ch[v][i]) v = fail[v];
            fail[u] = ch[v][i];
			//Trie中一个节点可能匹配了多个 所以还要记录上一个匹配的后缀	
            last[u] = val[fail[u]] ? fail[u] : last[fail[u]];
        }
    }
}
void print(int j) {
    if(j) {
        printf("%d: %d", j, val[j]);
        print(last[j]);
    }
}
void findp(char * T) {
    int len = strlen(T);
    int j = 0;
    for(int i = 0; i < n; i++) {
        int x = T[i] - 'a';
        while(j && !ch[j][x]) j = fail[j];
        j = ch[j][x];
        if(val[j]) print(j);
        else if(last[j]) print(last[j]);
    }
}
