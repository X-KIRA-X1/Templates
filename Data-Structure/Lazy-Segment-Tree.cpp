struct treeNode
{
    int sum , lazy;
    bool isLazy;
    treeNode () : sum(-1) , lazy (0) , isLazy (false) {}
    treeNode (int x) : sum(x) , lazy (0) , isLazy (false){}

    void update (int val , int lx , int rx)
    {
        sum |= val;
        lazy |= val;
        isLazy = true;
    }
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
        treeNode ret (l.sum & r.sum);
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

    void propagate (int node , int lx , int rx)
    {
        if (rx - lx == 1 or data[node].isLazy == false)
            return;

        int mid = (lx + rx) / 2;
        data[node * 2 + 1].update(data[node].lazy , lx , mid);
        data[node * 2 + 2].update(data[node].lazy , mid , rx);

        data[node].lazy = 0;
        data[node].isLazy = false;
    }

    void set (int l , int r , int val , int node , int lx , int rx)
    {

        propagate (node , lx , rx);
        if (r <= lx or l >= rx)
            return;
        if (lx >= l and rx <= r)
        {
            data[node].update (val , lx , rx);
            return;
        }        

        int mid = (lx + rx) / 2;
        set (l , r , val , node * 2 + 1 , lx , mid);
        set (l , r , val , node * 2 + 2 , mid , rx);

        data[node] = merge (data[node * 2 + 1] , data[node * 2 + 2]);
    }

    void set (int l , int r , int val)
    {set (l , r , val , 0 , 0 , size);}

    treeNode get (int l , int r , int node , int lx , int rx)
    {
        propagate (node , lx , rx);
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
