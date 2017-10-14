void euler(int u) {
    stack<int> st;
    st.push(u);
    nxt[st.size()] = -1;
    while(!st.empty()) {
        int a = st.top();
        int i;
        for(i = last[a]; i < 26; i++) if(!vis[a][i]) {
            vis[a][i] = 1;
            st.push(g[a][i]);
            nxt[st.size()] = i;
            last[a] = i + 1;
            break;
        }
        if(i == 26) {
            if(nxt[st.size()] != -1) ans.push_back((char)(nxt[st.size()] + 'a'));
            st.pop();
        }
    }
}
