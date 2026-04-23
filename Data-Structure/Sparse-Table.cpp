struct sparseTable
{
    vector <vector<int>> data;
    vector <int> logs;

    int marge (const int &l , const int &r)
        {return gcd (l ,r);}

    sparseTable (const vector <int> &a)
    {
        int n = a.size();

        logs.resize(n + 1);
        for (int i = 2 ; i <= n ; i++)
            logs[i] = logs[i / 2] + 1;

        data.resize(logs[n] + 1 , vector <int>(n));
        data[0] = a;

        for (int i = 1 ; i <= logs[n] ; i++)
        {
            int len = (1 << i);
            for (int j = 0 ; j + len <= n ; j++)
                data[i][j] = marge(data[i - 1][j] , data[i - 1][j + (len >> 1)]);
        }
    }

    int get (const int &l , const int &r)
    {
        int len = r - l + 1;
        int level = logs[len];

        return marge(data[level][l] , data[level][r - (1 << level) + 1]);
    }
};
