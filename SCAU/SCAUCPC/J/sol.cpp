#include <bits/stdc++.h>
#define x first
#define y second
#define int long long
#define sqrt sqrtl
#define all(x) (x).begin(),(x).end()
#define mem(x,y,l,r) for(int _=l;_<=r;_++) x[_]=y;
#define jxjxjx

using namespace std;
// #ifndef ONLINE_JUDGE
// #include "debug.h"
// #else
// #define debug(...) (void)42
// #endif

typedef pair<int, int> pii;
typedef pair<char, int> pci;
const int N = 2e6 + 10, mod = 998244353;

int e[N], ne[N], h[N], w[N], idx;
int d[N];
int dis[N];

void add(int a, int b, int c)
{
    e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}

void solve()
{
    int n, m, x;
    cin >> n >> m >> x;
    mem(h, -1, 1, n);

    for (int i = 1; i <= n; i++)
    {
        cin >> d[i];
    }

    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }

    mem(dis, 1e17, 1, n);

    dis[1] = -d[1];

    for (int i = 1; i <= n; i++)
    {
        //debug(i,dis[i]);
        for (int j = h[i]; j != -1; j = ne[j])
        {
            int k = e[j];
            if (k > i)
            {
                if (dis[k] > w[j] - d[k] + dis[i])
                {
                    dis[k] = w[j] - d[k] + dis[i];
                }
            }
        }
    }

    if (dis[n] >= 1E17 / 2)
    {
        cout << -1 << "\n";
    }
    else cout << x - dis[n] << "\n";

}


signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(20);
    int tt = 1;
    //cin>>tt;
    while (tt--) solve();
    return 0;
}
