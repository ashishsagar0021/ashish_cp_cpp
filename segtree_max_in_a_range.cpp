struct segtree
{
    int size;
    vector<int> values;
    void init(int n)
    {
        size = 1;
        while (size < n)size *= 2;
        values.assign(2 * size, 0);
    }
    void build(vector<int>&a, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            if (lx < (int)a.size())
            {
                values[x] = a[lx];
            }
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m, rx);
        values[x] = max(values[2 * x + 1] , values[2 * x + 2]);
    }
    void build(vector<int> &a)
    {
        build(a, 0, 0, size);
    }
    void set(int i, int v, int x, int lx, int rx)
    {
        if (rx - lx == 1)
        {
            values[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if (i < m)
        {
            set(i, v, 2 * x + 1, lx, m);
        }
        else
        {
            set(i, v, 2 * x + 2, m, rx);
        }
        values[x] = max(values[2 * x + 1] , values[2 * x + 2]);
    }
    void set(int i, int v)
    {
        set(i, v, 0, 0, size);
    }
    int calc(int l, int r, int x, int lx, int rx)
    {
        if (lx >= r or l >= rx) return INT_MIN;
        if (lx >= l and rx <= r) return values[x];
        int m = (lx + rx) / 2;
        int s1 = calc(l, r, 2 * x + 1, lx, m);
        int s2 = calc(l, r, 2 * x + 2, m, rx);
        return max(s1 , s2);
    }
    int calc(int l, int r)
    {
        return calc(l, r, 0, 0, size);
    }
};