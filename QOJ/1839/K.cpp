#include<bits/stdc++.h>
using namespace std;
using i64 = long long;

void solve () {
    
    int n,m,k;
    cin>>n>>m>>k;

    vector<vector<int>> g(n+1,vector<int>(m+1));


    map<int,int> rep;

    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=m;j++)
    	{
    		cin>>g[i][j];
    		rep[(i-1)*m+j]=(g[i][j]+m-1)/m;
    		//cout<<i<<" "<<j<<" "<<g[i][j]<<" "<<
    	}
    }


    map<int,int> cnt;
    map<int,int> t;


    t[0]+=n;

    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=m;j++)
    	{
    		int pos = rep[(i-1)*m+j];
	    	t[cnt[pos]]--;
	    	if(t[cnt[pos]]==0)
	    	{
	    		t.erase(cnt[pos]);
	    	}
	    	//cout<<(i-1)*m+j<<" "<<pos<<"\n";

	    	cnt[pos]++;
	    	t[cnt[pos]]++;

	    	if(m-(*t.rbegin()).first<=k && (i-1)*m+j>=m)
	    	{
	    		cout<<(i-1)*m+j<<"\n";
	    		return; ;
	    	}
    	}

    }





}

int main () {
    cin.tie(nullptr)->ios::sync_with_stdio(false);

    int t = 1;
    cin >> t;

    while (t --) {
        solve();
    }
    return 0;
}
