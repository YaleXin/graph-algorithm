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
using namespace std;
const int MAX_NODE_LEN = 100, INF = 0x7ffffff;
struct Edge{
    Edge(int _w, int _v):w(_w),v(_v){}
    // �ڽӱߵ�Ȩ�ͽڵ�
    int w, v;
    bool operator> (const Edge &a)const{return w > a.w;}
};
void Dijkstra(vector<vector<Edge> > &adjTable, int edge_num, int start_idx){
    int node_num = adjTable.size();
    // ʹ�����޶��н����Ż������ٻ�ȡ��Сֵ�Ļ���
    priority_queue<Edge, vector<Edge>, greater<Edge> > que;
    int d[MAX_NODE_LEN];
    // ��ʼ��ÿ���㵽Դ��ľ���Ϊ�����
    fill(d, d + MAX_NODE_LEN, INF);
    // ʹ��һ�������Ǹýڵ��Ƿ��Ѿ��ҵ����·��
    bool visited[MAX_NODE_LEN];
    memset(visited, false, sizeof visited);
    // ���ڻ�����·��
    int pre[MAX_NODE_LEN];
    fill(pre, pre + MAX_NODE_LEN, start_idx);
    // ��Դ�㿪ʼ
    d[start_idx] = 0;
    que.push(Edge(d[start_idx], start_idx));
    while(!que.empty()){
        // ȡ��ͷ������������С��Ȩ��
        Edge front = que.top();
        que.pop();
        int u = front.v;
        // ����õ��Ѿ���������·��
        if(visited[u])continue;
        visited[u] = true;
        // ����õ�������ڽӵ�
        for(int i = 0; i < adjTable[u].size(); i++){
            int v = adjTable[u][i].v, w = adjTable[u][i].w;
            // ����ܹ����� u������Դ��� v ֮��ľ���
            if (d[u] + w < d[v]){
                d[v] = d[u] + w;
                que.push(Edge(d[v], v));
                pre[v] = u;
            }
        }
    }
    cout << "=============solution===========" << endl;
    // ���·��
    for(int u = 0; u < node_num; u++){
         stack<int>st;
         int p = pre[u];
         st.push(u);
         while(p != start_idx){
             st.push(p);
             p = pre[p];
         }
         cout << "The distance between" << start_idx <<
         "and " << u << " is " << d[u] << " and path is :" << start_idx;
         while(!st.empty()){
             cout  << " -> "<< st.top();
             st.pop();
         }
         cout << endl;
    }
}
int main(){
    // ����ͼ
    // Ĭ��Դ���±��� 0
    cout << "please input the number of nodes and edges of the graph" << endl;
    int n, m;
    cin >> n >> m;
    cout << "please input the weight of each directed edge, such as 1 2 3, to indicate that the weight of the edge between node 1 and node 2 is 3" << endl;
    // �ڽӱ�
    vector<vector<Edge> >adjTable(n);
    int u, v, w;
    for(int i = 1; i <= m; i++){
        cin >> u >> v >> w;
        adjTable[u].push_back({w, v});
    }
    Dijkstra(adjTable, m, 0);
    return 0;
}
/*

5 8
0 1 6
0 2 4
1 3 2
1 4 2
2 1 1
2 3 3
2 4 3
4 3 4


6 10
0 1 6
0 2 4
1 3 2
1 4 2
2 1 1
2 3 3
2 4 3
4 3 4
3 5 1
4 5 8

*/