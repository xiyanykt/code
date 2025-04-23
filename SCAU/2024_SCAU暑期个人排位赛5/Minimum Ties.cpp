#include<bits/stdc++.h>

using i64 = int64_t;

int main(void) {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	/*std::map<int,int>mp;
	 mp[1]=-1;
	 mp[2]=0;
	 mp[3]=1;

	 std::vector<int>a(5);

	 for(int i=1;i<=3;i+=1){
	     for(int j=1;j<=3;j+=1){
	         for(int k=1;k<=3;k+=1){
	             for(int x=1;x<=3;x+=1){
	                 for(int y=1;y<=3;y+=1){
	                     for(int z=1;z<=3;z+=1){
	                         std::vector<int>a(5);
	                        if(mp[i]==-1){
	                             a[2]+=3;
	                        }
	                        if(mp[i]==0){
	                             a[1]+=1,a[2]+=1;
	                        }
	                        if(mp[i]==1){
	                             a[1]+=3;
	                        }

	                         if(mp[j]==-1){
	                             a[3]+=3;
	                        }
	                        if(mp[j]==0){
	                             a[1]+=1,a[3]+=1;
	                        }
	                        if(mp[j]==1){
	                             a[1]+=3;
	                        }

	                         if(mp[k]==-1){
	                             a[4]+=3;
	                        }
	                        if(mp[k]==0){
	                             a[1]+=1,a[4]+=1;
	                        }
	                        if(mp[k]==1){
	                             a[1]+=3;
	                        }

	                         if(mp[x]==-1){
	                             a[3]+=3;
	                        }
	                        if(mp[x]==0){
	                             a[2]+=1,a[3]+=1;
	                        }
	                        if(mp[x]==1){
	                             a[2]+=3;
	                        }

	                        if(mp[y]==-1){
	                             a[4]+=3;
	                        }
	                        if(mp[y]==0){
	                             a[2]+=1,a[4]+=1;
	                        }
	                        if(mp[y]==1){
	                             a[2]+=3;
	                        }

	                        if(mp[z]==-1){
	                             a[4]+=3;
	                        }
	                        if(mp[z]==0){
	                             a[3]+=1,a[4]+=1;
	                        }
	                        if(mp[z]==1){
	                             a[3]+=3;
	                        }

	                        if(a[1]==a[2] and a[2]==a[3] and a[3]==a[4]){
	                             std::cout<<mp[i]<<" "<<mp[j]<<" "<<mp[k]<<" "<<mp[x]<<" "<<mp[y]<<" "<<mp[z]<<"\n";
	                        }
	                     }
	                 }
	             }
	         }
	     }
	 }
	*/

	auto solve = [&]() {
		int n;
		std::cin >> n;

		if (n == 2) {
			std::cout << 0 << "\n";
			return;
		}

		std::vector<int>a(n + 1);
		if (n % 2 == 1) {
			int alt = 1;
			for (int i = 1; i <= n; i += 1) {
				for (int j = i + 1; j <= n; j += 1) {
					std::cout << alt << " ";
					if (alt == 1) {
						a[i] += 3;
					} else if (alt == -1) {
						a[j] += 3;
					} else {
						a[i] += 1, a[j] += 1;
					}
					alt = alt == 1 ? -1 : 1;
				}
			}
			/*            std::cout<<"\n";

			            for(int i=1;i<=n;i+=1){
			                std::cout<<a[i]<<" ";
			            }*/
			std::cout << "\n";
		} else {
			for (int i = 1; i <= n - 1; i += 1) {
				int alt = (i % 2 == 1 ? 1 : -1);
				for (int j = i + 1; j <= n; j += 1) {
					if (i % 2 == 1 and j == i + 1) {
						std::cout << 0 << " ";
						a[i] += 1, a[j] += 1;
					} else {
						std::cout << alt << " ";
						if (alt == 1) {
							a[i] += 3;
						} else {
							a[j] += 3;
						}
						alt = alt == 1 ? -1 : 1;
					}
				}
			}
			/* std::cout<<"\n";

			 for(int i=1;i<=n;i+=1){
			     std::cout<<a[i]<<" ";
			 }*/
			std::cout << "\n";
		}
	};

	int t = 1;
	std::cin >> t;
	while (t--) {
		solve();
	}

	return 0;
}
