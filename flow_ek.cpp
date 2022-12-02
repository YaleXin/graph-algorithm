/*
 * @Author      : YaleXin
 * @Email       : me@yalexin.top
 * @LastEditors : YaleXin
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
const int MAXLEN = 1001;


int capacity[MAXLEN][MAXLEN] = {0};
// 记录路径上的前驱，用于添加反向边和回溯法求增广路
int pre[MAXLEN];
int vertexNum, arcNum;

int BFS(int start, int end, vector<vector<int> > &adjTable) {
    for (int i = 1; i <= vertexNum; i++) pre[i] = -1;
    int flow[vertexNum + 1], queue[vertexNum + 1], front = 0, rear = 0;
    // 源节点的流初始化为正无穷，意味着源点边(start,v)上的流取决于容量capacity[start][v]
    flow[start] = 32767;
    std::queue <int> que;

    // 源点进队列
    que.push(start);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (u == end) break;
        for(int i = 0; i < adjTable[u].size(); i++){
            // 对于每一条边(u,v)，如果邻接点v尚未访问过，且边容量有剩余
            int v = adjTable[u][i];
            if(v != start && capacity[u][v] > 0 && pre[v] == -1){
                pre[v] = u;
                flow[v] = min(capacity[u][v], flow[u]);
                que.push(v);

            }
        }
    }
    // 残余网络中不存在增广路
    if (pre[end] == -1)
        return -1;
    else
        return flow[end];
}
int getMaxFlow(int S, int T, vector<vector<int> > &adjTable) {
    int minF, preIndex, th, sum = 0;
    while ((minF = BFS(S, T, adjTable)) != -1) {
        // 更新残留网络
        th = T;
        stack<int>stk;
        preIndex = pre[th];
        while (preIndex != -1) {
            stk.push(preIndex);
            capacity[th][preIndex] += minF;
            capacity[preIndex][th] -= minF;
            th = preIndex;
            preIndex = pre[th];
        }
        // 输出增广路径
        cout << "This time, the flow is " << minF;
        cout << " and the augmenting path is :";
        while(!stk.empty()){
            cout << stk.top() << " -> ";
            stk.pop();
        }
        cout << T << endl;
        sum += minF;
    }
    return sum;
}
int main() {
    
    int SVertex, TVertex;
    cout << "Please enter the number of points and directed edges, as well as the source and sink vertex id: " << endl;
    cin >> vertexNum >> arcNum >> SVertex >> TVertex;

    // 邻接表，下标从 1 开始
    vector<vector<int> >adjTable(vertexNum + 1);

    cout << "Please enter the capacity of each directed edge in the format u v capacity:" << endl;
    int u, v, c;
    for (int i = 1; i <= arcNum; i++) {
        cin >> u >> v >> c;
        capacity[u][v] = c;
        adjTable[u].push_back(v);
    }
    int maxFlow = getMaxFlow(SVertex, TVertex, adjTable);
    cout << "The max flow is " << maxFlow << endl;
    return 0;
}
/*

4 6 1 4
1 3 5
1 4 20
1 2 10
3 4 50
3 2 30
2 4 40



6 9 1 6
1 2 8
1 3 7
2 4 9
2 5 3
2 3 5
3 5 9
4 6 7
5 4 6
5 6 10


*/
