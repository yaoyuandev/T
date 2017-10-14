void build(node* &now, node* &pre, int l, int r, int x) {
    now = &tn[ncnt++];
    *now = *null;
    int mid = (l + r) / 2;
    if(l == r) {
        *now = *pre;
        now->val++;
        return;
    }
    if(x <= sq[mid]) {
        build(now->ch[0], pre->ch[0], l, mid, x);
        now->ch[1] = pre->ch[1];
        now->maintain();
    }
    else {
        build(now->ch[1], pre->ch[1], mid + 1, r, x);
        now->ch[0] = pre->ch[0];
        now->maintain();
    }
}
