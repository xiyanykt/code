#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
using LL = long long;

int main(){

#ifdef LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    while(T--){
        LL n;
        cin >> n;
        for(LL i = n * 2; ; i += 2){
            LL t = __lg(i);
            if (i / 2 - t + 1 == n){
                cout << i << '\n';
                break;
            }
        }
    }

}