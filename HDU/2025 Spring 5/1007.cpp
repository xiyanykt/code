#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <bitset>
#include <algorithm>
using namespace std;

const int MAXN = 6000; // 定义 bitset 的大小

struct Commit {
    vector<int> parents;    // 父亲编号
    bitset<MAXN> mask;      // 祖先信息，commit i 对应下标 i-1
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        cin.ignore(); // 读取换行

        // commits[0]不使用，提交编号从1开始
        vector<Commit> commits;
        commits.resize(1);
        // 初始化提交 1
        Commit first;
        first.parents.clear();
        first.mask.reset();
        first.mask.set(0, true); // 提交1，对应 bit 0 置1
        commits.push_back(first);
        int commitCount = 1;
        
        // 分支管理：分支名 -> 当前指向的提交编号
        map<string, int> branches;
        branches["main"] = 1;
        string HEAD = "main";
        
        // 辅助函数：判断 a 是否为 b 的祖先，即 b 的 mask 中下标 a-1 是否为 true
        auto isAncestor = [&](int a, int b) -> bool {
            return commits[b].mask.test(a - 1);
        };
        
        for (int i = 0; i < n; i++){
            string line;
            getline(cin, line);
            if(line.empty()) { i--; continue; }
            istringstream iss(line);
            string cmd;
            iss >> cmd;
            if(cmd == "commit"){
                // commit: 当前分支指向的提交作为父亲，新建节点
                int cur = branches[HEAD];
                int newId = commitCount + 1;
                Commit newCommit;
                // 父亲只有 cur
                newCommit.parents.push_back(cur);
                // 继承父亲的 mask
                newCommit.mask = commits[cur].mask;
                // 设置新提交对应的 bit，新提交对应下标 newId-1
                newCommit.mask.set(newId - 1, true);
                commits.push_back(newCommit);
                branches[HEAD] = newId;
                commitCount = newId;
            }
            else if(cmd == "branch"){
                string token;
                iss >> token;
                if(token == "-d"){
                    // 删除分支：branch -d <branch_name>
                    string branchName;
                    iss >> branchName;
                    // 题目保证不会删除当前分支，若不存在则跳过
                    if(branches.count(branchName))
                        branches.erase(branchName);
                } else {
                    // 创建分支：branch <branch_name> [<node>]
                    string branchName = token;
                    if(branches.count(branchName)) continue; // 已存在则跳过
                    int node = branches[HEAD]; // 默认指向当前分支的提交
                    if(iss >> token){ // 若有节点参数
                        node = stoi(token);
                    }
                    branches[branchName] = node;
                }
            }
            else if(cmd == "checkout"){
                // checkout <branch_name>
                string branchName;
                iss >> branchName;
                HEAD = branchName;
            }
            else if(cmd == "reset"){
                // reset [node]
                string token;
                if(iss >> token){
                    int node = stoi(token);
                    branches[HEAD] = node;
                }
                // 如果没有参数，则指向当前节点，无操作
            }
            else if(cmd == "merge"){
                // merge <branch_name>
                string branchName;
                iss >> branchName;
                int X = branches[HEAD];         // 当前分支提交
                int Y = branches[branchName];     // 被合并分支提交
                if(X == Y) continue; // 相同则不操作
                if(isAncestor(X, Y)){
                    // 当前分支提交是 Y 的祖先，则快进：将当前分支指向 Y
                    branches[HEAD] = Y;
                }
                else if(isAncestor(Y, X)){
                    // 若 Y 是当前分支的祖先，则无需操作
                    continue;
                }
                else{
                    // 否则创建一个合并提交，两个父亲为 X 与 Y
                    int newId = commitCount + 1;
                    Commit newCommit;
                    newCommit.parents.push_back(X);
                    newCommit.parents.push_back(Y);
                    // 合并两个父亲的 mask
                    newCommit.mask = commits[X].mask | commits[Y].mask;
                    // 设置自己对应的 bit
                    newCommit.mask.set(newId - 1, true);
                    commits.push_back(newCommit);
                    branches[HEAD] = newId;
                    commitCount = newId;
                }
            }
            // 其他命令不可能出现
        }
        
        // 输出
        // 第一部分：输出分支数及各分支（按字典序）
        cout << branches.size() << "\n";
        vector<pair<string,int>> branchList(branches.begin(), branches.end());
        sort(branchList.begin(), branchList.end(), [](const pair<string,int>& a, const pair<string,int>& b){
            return a.first < b.first;
        });
        for(auto &p : branchList){
            cout << p.first << " " << p.second << "\n";
        }
        // 第二部分：输出总提交数
        cout << commitCount << "\n";
        // 输出每个提交节点的父亲信息（提交编号从1到 commitCount）
        for (int id = 1; id <= commitCount; id++){
            // 父亲编号按升序输出
            vector<int> ps = commits[id].parents;
            sort(ps.begin(), ps.end());
            cout << ps.size();
            for (int p : ps){
                cout << " " << p;
            }
            cout << "\n";
        }
    }
    return 0;
}
