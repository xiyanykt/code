#include <bits/stdc++.h>
using namespace std;
class SAM
{
    const int shift = 48, sigma = 10;
    struct node
    {
        int ch[10];
        int len;
        int father;
        long long cnt;
        node()
        {
            memset(ch, 0, sizeof(ch));
            len = father = cnt = 0;
        }
    } NIL;
    vector<node> t;
    vector<vector<int>> graph;
    int last, ind;
    void insert(int c)
    {
        int p = last;
        int np = last = ++ind;
        t.push_back(NIL);
        t[np].len = t[p].len + 1;
        t[np].cnt = 1;
        for (; p && !t[p].ch[c]; p = t[p].father)
            t[p].ch[c] = np;
        if(!p)
            t[np].father = 1;
        else
        {
            int q = t[p].ch[c];
            if (t[p].len + 1 == t[q].len)
                t[np].father = q;
            else
            {
                int nq = ++ind;
                t.push_back(t[q]);
                t[nq].cnt = 0;
                t[nq].len = t[p].len + 1;
                t[q].father = t[np].father = nq;
                for (; p && t[p].ch[c] == q; p = t[p].father)
                    t[p].ch[c] = nq;
            }
        }
    }
 
public:
    SAM(string s)
    {
        last = ind = 1;
        t.push_back(NIL);
        t.push_back(NIL);
        for (auto i : s)
            insert(i - shift);
        graph.resize(t.size());
        for (int i = 2; i <= ind;i++)
            graph[t[i].father].push_back(i);
        function<void(int)> dfs = [&](int place)
        {
            for (auto i : graph[place])
            {
                dfs(i);
                t[place].cnt += t[i].cnt;
            }
        };
        dfs(1);
    }
    long long query()
    {
        long long ans = 0;
        function<void(int, int)> dfs = [&](int place, int father)
        {
            long long pre = t[place].len - t[t[place].father].len;
            for (int i = 0; i < 9;i++)
            {
                int x = t[place].ch[i], y = t[place].ch[i + 1];
                while (x && y)
                {
                    ans += t[x].cnt * t[y].cnt * pre;
                    x = t[x].ch[9];
                    y = t[y].ch[0];
                }
            }
            for (auto i : graph[place])
                dfs(i, place);
        };
        t[0].len = -1;
        dfs(1, 0);
        return ans;
    }
};
int main()
{
    int n;
    string s;
    cin >> n >> s;
    SAM solve(s);
    printf("%lld", solve.query());
    return 0;
}
