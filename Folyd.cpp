/*
 * @Author      : YaleXin
 * @Email       : me@yalexin.top
 * @LastEditors : YaleXin
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;
const int MAX_NODE_LEN = 100, INF = 0x7ffffff;
// 使用邻接矩阵
int adj[MAX_NODE_LEN][MAX_NODE_LEN];

int dp[MAX_NODE_LEN][MAX_NODE_LEN];
int n, m;

void Floyd(){
    // 直接使用邻接矩阵构造
    copy(&adj[0][0], &adj[0][0] + MAX_NODE_LEN * MAX_NODE_LEN, &dp[0][0]);

    int pre[MAX_NODE_LEN][MAX_NODE_LEN];
    memset(pre, 0, sizeof 0);

    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++){
                if (dp[i][k] + dp[k][j] < dp[i][j]){
                    dp[i][j] = dp[i][k] + dp[k][j];
                    pre[i][j] = k;
                }
            }
    cout << "=============solution===========" << endl;
    for(int u = 1; u <= n; u++){
        cout << "----------start from "<< u << " ----------" << endl;
        for(int v = 1; v <= n; v++){
            // 如果二者之间不是无穷大，即存在 u 到 v 的路径
            if (dp[u][v] != 0x1f1f1f1f){
                stack<int>st;
                int p = pre[u][v];
                st.push(v);
                while(p != 0){
                    st.push(p);
                    p = pre[u][p];
                }
                cout << "The distance between " << u <<
                " and " << v << " is " << dp[u][v] << " and path is :" << u;
                while(!st.empty()){
                    cout  << " -> "<< st.top();
                    st.pop();
                }
                cout << endl;
            }
        }

    }
}
int main(){
    // 有向图
    // 节点开始的下标是 1
    cout << "please input the number of nodes and edges of the graph" << endl;
    cin >> n >> m;
    cout << "please input the weight of each directed edge, such as 1 2 3, to indicate that the weight of the edge between node 1 and node 2 is 3" << endl;
    int u, v, w;

    // 初始化任意两点之间的距离为无穷大
    memset(adj, 0x1f, sizeof adj);
    for(int i = 1; i <= n; i++)adj[i][i] = 0;
    for(int i = 1; i <= m; i++){
        cin >> u >> v >> w;
        adj[u][v] = w;
    }
    Floyd();
    return 0;
}
/*

6 10
1 2 6
1 3 4
2 4 2
2 5 2
3 2 1
3 4 3
3 5 3
4 6 1
5 4 4
5 6 8


*/