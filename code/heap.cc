struct Node 
{
    int index;
    int tag;
    int l;
    bool operator<(Node ano) const
    {
        return l!=ano.l?l<ano.l:index>ano.index;
    }
};
Node heap[51111];
int heapsz;
int a[2<<21]; // 编号为i的在heap的位置
void swim(int p)
{
        while (p > 1 && heap[p / 2] < heap[p])
        {
            swap(a[heap[p].tag],a[heap[p/2].tag]);
            swap(heap[p],heap[p/2]);
            p/=2;
        }
}
void sink(int p)
{
    while(p * 2 <= heapsz)
    {
        p *= 2;
        if (p+1<=heapsz) p|=heap[p]<heap[p+1];
        swap(a[heap[p].tag],a[heap[p/2].tag]);
        swap(heap[p],heap[p/2]);
    }
}