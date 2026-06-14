struct DSU
{
    vector <int> parent , size;
    int numberOfSets;

    DSU (int n)
    {
        parent.resize(n + 1);
        size.resize(n + 1);

        for (int i = 1 ; i <= n ; i++)
            parent[i] = i , size[i] = 1;

        numberOfSets = n;
    }

    int getParent (int u)
    {
        if (parent[u] == u)
            return u;

        return parent[u] = getParent(parent[u]);
        /*
        Note : There is no need to update the size of some nodes after path comp 
        because we only care about the representers of the sets and they will be updated as wanted
        */
    }

    void unite (int u , int v) // unites by size
    {
        u = getParent(u);
        v = getParent(v);

        if (u == v)
            return;

        if (size[u] < size[v])
            swap(u , v);

        size[u] += size[v];
        numberOfSets--;
        parent[v] = u;
    }
};
