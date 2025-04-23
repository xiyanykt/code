/*
                                        ⠄⠄⢰⣿⠿⠄⡀⠄⠄⠄⠘⣷⡀⠄⠢⣄⠄⠄⠄⠄⠄⠄⠄⣠⠖⠁⠄⠄⠄
                                        ⠄⣤⢸⣿⣿⣆⠣⠄⠄⠄⠄⠸⣿⣦⡀⠙⢶⣦⣄⡀⠄⡠⠞⠁⢀⡴⠄⠄⠄
                                        ⢰⣿⣎⣿⣿⣿⣦⣀⠄⠄⠄⠄⠹⣿⣿⣦⢄⡙⠻⠿⠷⠶⠤⢐⣋⣀⠄⠄⠄
                                        ⢸⣿⠛⠛⠻⠿⢿⣿⣧⢤⣤⣄⣠⡘⣿⣿⣿⡟⠿⠛⠂⠈⠉⠛⢿⣿⠄⠄⠄
                                        ⠄⡇⢰⣿⣇⡀⠄⠄⣝⣿⣿⣿⣿⣿⣿⣿⣿⣶⣿⡄⠄⠈⠄⣷⢠⡆⠄⠄⠄
                                        ⢹⣿⣼⣿⣯⢁⣤⣄⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⣴⠶⣲⣵⠟⠄⠄⠄⠄
                                        ⠄⢿⣿⣿⣿⣷⣮⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣾⣟⣡⡴⠄⠄⠄⠄
                                        ⠄⠰⣭⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⡀⠄⠄⠄
                                        ⠄⠄⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣭⣶⡞⠄⠄⠄⠄
                                        ⠄⠄⠐⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠄⠄⠄⠄⠄
                                        ⠄⠄⠄⠈⠻⣿⣿⣿⣿⣿⣿⣯⣿⣯⣿⣾⣿⣿⣿⣿⣿⡿⠋⠄⠄⠄⠄⠄⠄
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
#define f(i,a,b) for(i=a; i<b; i++)
#define get(n) ll n; cin>>n
#define gets(s) string s; cin>>s
#define all(v) v.begin(),v.end()
#define getv(v,n) vector<ll> v(n); f(_,0,n) cin >> v[_];
#define seev(a) for(auto $:a){cout<<$<<" ";}cout<<endl;
#define see2d(a) for(auto &x:a){for(auto &y:x){cout<<y<<" ";}cout<<endl;}
#define getvp(v,n) vector<pair<ll,ll>> v(n); f(_,0,n){get(o);get(w);v[_].first=o;v[_].second=w;}
#define seevp(a) for(auto $:a){cout<<$.first<<" "<<$.second<<endl;}
#define vl vector<ll>
#define vp vector<pair<ll,ll>>
#define vvl(v,n,m) vector<vector<ll>> v(n, vector<ll> (m, 0))
#define bs(n,x) bitset<n> (x).to_string()
#define pl pair<ll,ll>
const ll INF = 1e18;
const ll INFI = 1e9;
const ll mod = 1e9 + 7;
const ll mod2 = 998244353;
#define MAXN 200005
bool vps(const pair<ll, ll> &a, const pair<ll, ll> &b)
{
	return (a.second < b.second);
}
bool cmp(const pair<ll, ll> &a, const pair<ll, ll> &b)
{
	if (a.first != b.first) return (a.first < b.first);
	return (a.second > b.second);
}
long long power(long long a, long long b)
{
	long long res = 1;
	a %= mod;
	while (b > 0) {
		if (b & 1)
			res = (res * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return res;
}
ll euclid_gcd(ll a, ll b, ll& x, ll& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll x1, y1;
	ll d = euclid_gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - y1 * (a / b);
	return d;
}



void solve() {
	ll i = 0, j = 0, flag = 0, ans = 0, _ = 0;
	get(n); gets(s);
	ll cnt = 0, cnt1 = 0;
	f(i, 1, n) {
		if (s[i] == '0' && s[i - 1] == '0')cnt++;
	}
	f(i, 1, n) {
		if (s[i] == '1' && s[i - 1] == '1')cnt1++;
	}
	if (cnt1 > 1 || cnt > 1) {
		cout << "NO" << endl;
		return;
	}
	ll num0 = count(all(s), '0');
	ll num1 = count(all(s), '1');
	if (abs(num1 - num0) > 1) {
		cout << "NO" << endl; return;
	}
	cout << "YES" << endl;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll tt = 1;
	cin >> tt;
	while (tt--) {
		solve();
	}
}
//s.substr(pos,len)