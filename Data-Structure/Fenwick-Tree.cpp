// 1-Indexed
struct fenwickTree
{
    int n;
    vector <int> data;

    fenwickTree(int size)
    {
        n = 1;
        while (n < size) n <<= 1;
        data.resize(n + 1 , 0);
    }

    void add (int i , int v)
    {
        while (i <= n)
        {
            data[i] += v;
            i += (i & -i);
        }
    }

    int get (int i)
    {
        int res = 0;
        while (i > 0)
        {
            res += data[i];
            i -= (i & -i);
        }

        return res;
    }

    int lowerBound (int sum)
    {
        int i = 0;
        for (int step = n ; step > 0 ; step >>= 1)
        {
            if (data[i + step] < sum)
            {
                sum -= data[i + step];
                i += step;
            }
        }

        return i + 1;
    }
};
