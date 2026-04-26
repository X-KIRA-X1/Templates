struct treeNode
{
    int val;
    treeNode () : val(0) {}
    treeNode (int x) : val (x){}
};

struct segmentTree
{
    int size;
    vector <treeNode> data;

    segmentTree (int n)
    {
        size = 1;
        while (n > size) size <<= 1;
        data.resize (size * 2 , treeNode());
    }

    static treeNode merge (const treeNode &l , const treeNode &r)
    {
        treeNode ret (l.val ^ r.val);
        return ret;
    }

    void build (const vector <int> &a , int node , int lx , int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < a.size())
                data[node] = treeNode(a[lx]);
            return;
        }

        int mid = (lx + rx) / 2;
        build (a , node * 2 + 1 , lx , mid);
        build(a , node * 2 + 2 , mid , rx);

        data[node] = merge (data[node * 2 + 1] , data[node * 2 + 2]);
    }

    void build (const vector <int> &a)
    {build(a , 0 , 0 , size);}

    void set (int idx , int val , int node , int lx , int rx)
    {
        if (rx - lx == 1)
        {
            data[node] = treeNode(data[node].val ^ val);
            return;
        }

        int mid = (lx + rx) / 2;
        if (idx < mid)
            set (idx , val , node * 2 + 1 , lx , mid);
        else
            set (idx , val , node * 2 + 2 , mid , rx);

        data[node] = merge (data[node * 2 + 1] , data[node * 2 + 2]);
    }

    void set (int idx , int val)
    {set (idx , val , 0 , 0 , size);}

    treeNode get (int l , int r , int node , int lx , int rx)
    {
        if (r <= lx or l >= rx)
            return treeNode();
        if (lx >= l and rx <= r)
            return data[node];

        int mid = (lx + rx) / 2;
        auto left = get (l , r , node * 2 + 1 , lx , mid);
        auto right = get (l , r , node * 2 + 2 , mid , rx);

        return merge (left , right);
    }

    treeNode get (int l, int r) {
        return get(l, r, 0, 0, size);
    }
};
