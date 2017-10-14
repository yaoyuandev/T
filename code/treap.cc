struct node {
        node* ch[2];
        int w, sum, v, k;
        void maintain() {sum = w + ch[0]->sum + ch[1]->sum;}
        int cmp(int vv) {return vv == v ? -1 : vv > v;}
        bool operator < (const node& rhs) {return k < rhs.k;}
    }nd[MAXN *10];
    node* null, *rt;
    int ncnt;
    void rot(node*& o, int d) {
    node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
    //一定先维护o，因为o是k的子节点
    o->maintain(); k->maintain();
        o = k;
    }
    void ins(node*& o, int x) {
        if(o == null) {
            o = &nd[ncnt++];
            *o = *null;
            o->v = x; o->k = rand();
            o->w = 1; o->maintain();
        }
        else {
            int d = o->cmp(x);
            if(d == -1) {o->w++; o->sum++;}
            else {
                ins(o->ch[d], x);
                o->maintain();
                if(o < o->ch[d]) rot(o, d^1);
            }
        }
    }
    void del(node*& o, int x) {
        if(o == null) return;
        int d = o->cmp(x);
        if(d == -1) {
            if(o->w > 1) {o->w--; o->sum--;}
            else {
                if(o->ch[0] != null && o->ch[1] != null) {
                    int dd = o->ch[0] > o->ch[1];
                    rot(o, dd);
                    del(o->ch[dd], x);
                }
                else o = o->ch[0] == null ? o->ch[1] : o->ch[0];
            }
        }
        else del(o->ch[d], x);
        o->maintain();
    }
    int getrk(node* o, int x) {
        if(o == null) return 0;
        int d = o->cmp(x);
        if(d == -1) return o->ch[0]->sum + 1;
        else {
            if(d == 1) return o->ch[0]->sum + o->w + getrk(o->ch[1], x);
            return getrk(o->ch[0], x);
        }
    }
    int getkth(node* o, int x) {
        if(o == null) return 0;
        int ls = o->ch[0]->sum, cs = o->w;
        if(x <= ls) return getkth(o->ch[0], x);
        else if(x > ls && x <= ls + cs) return o->v;
        else return getkth(o->ch[1], x - ls - cs);
    }
    int ans;
    //找第一个小于x的数
    void getpre(node* o, int x) {
        if(o == null) return;
        if(x > o->v) {
            ans = o->v;
            getpre(o->ch[1], x);
        }
        else getpre(o->ch[0], x);
    }
    //第一个大于x的数
    void getnxt(node* o, int x) {
        if(o == null) return;
        if(x < o->v) {
            ans = o->v;
            getnxt(o->ch[0], x);
        }
        else getnxt(o->ch[1], x);
    }
    
    
    