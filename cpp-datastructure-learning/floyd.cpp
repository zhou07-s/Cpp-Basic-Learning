#include<iostream>
#include<stack>
#include<stdlib.h>
#include<vector>
#include<queue>
#include <climits>
#define MAX_DISTANCE 100
using namespace std;
/*
	Floyd算法伪代码
1 初始化距离数组dist，路径数组path 2 k进行VNum次的更新
  --2.1 更新两个二维矩阵，取出dist矩阵中的每一个元素，与同一行第k列，
  同一列第k行的元素之和相比较
  --2.2 考虑通过第k顶点，从i到k 从k到j，是否拉近了i j 之间的距离
  --2.3 如果拉近了距离，就更新dist和path两个数组
	3 输出结果

	输入输出
第一行输入顶点和边的个数vertexNum和arcNum
第二行输入顶点的值
下面多行输入边的起点和终点的值，边的权值。
*/
int findIndex(const vector<string>& vertices, const string& vertex) {
    for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == vertex) {
            return i;
        }
    }
    return -1;
}

//获取路径，path[i][j]里面存着j的前驱节点
string getPath(int i, int j, const vector<vector<int>>& path, const vector<string>& vertices) {
    string result = "";
    int current = j;

    while (current != i) {
        result = vertices[current] + result;
        current = path[i][current];
    }
    result = vertices[i] + result;//这里字符串拼接顺序很重要，因为path记录前驱

    return result;
}
int main() {
    int vertexNum, arcNum;
    cout << "请输入顶点个数和边的个数：" << endl;
    cin >> vertexNum >> arcNum;

    vector<string> vertices(vertexNum);
    cout << "请输入顶点的值" << endl;
    for (int i = 0; i < vertexNum; i++) {
        cin >> vertices[i];
    }

    vector<vector<int>> dist(vertexNum, vector<int>(vertexNum, INT_MAX));
    vector<vector<int>> path(vertexNum, vector<int>(vertexNum,-1));
    //这个初始化没见过,可以回头复习

    for (int i = 0; i < vertexNum; i++) {
        dist[i][i] = 0;
        path[i][i] = i;
    }
    cout << "请输入边依附的两个顶点和权值:" << endl;
    for (int i = 0; i < arcNum; i++) {
        string start, end;
        int weight;
        
        cin >> start >> end >> weight;

        int u = findIndex(vertices, start);
        int v = findIndex(vertices, end);

        if (weight < dist[u][v]) {
            dist[u][v] = weight;
            path[u][v] = u;
        }
    }

    // 2. k进行VNum次的更新
    for (int k = 0; k < vertexNum; k++) {
        // 2.1 更新两个二维矩阵，取出dist矩阵中的每一个元素
        for (int i = 0; i < vertexNum; i++) {
            for (int j = 0; j < vertexNum; j++) {
                // 2.2 考虑通过第k顶点，从i到k 从k到j，是否拉近了i j之间的距离
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {//检查是否可以作为中间点
                    int newDist = dist[i][k] + dist[k][j];
                    // 2.3 如果拉近了距离，就更新dist和path两个数组
                    if (newDist < dist[i][j]) {
                        dist[i][j] = newDist;
                        path[i][j] = path[k][j];//关键点：j 的前驱是 k→j 路径上 j 的前驱，如果直接为k,可能k->j最开始也没有路径，有可能也是通过另一个节点链成的
                    }
                }
            }
        }
    }
    cout << "显示每对顶点间的最短路径：" << endl;
    // 3. 输出结果
    for (int i = 0; i < vertexNum; i++) {
        for (int j = 0; j < vertexNum; j++) {
            if (i == j) continue;

            if (dist[i][j] == INT_MAX) {
                cout << "<" << vertices[i] << "," << vertices[j] << "> 无路径" << endl;
            }
            else {
                string pathStr = getPath(i, j, path, vertices);
                cout << "<" << vertices[i] << "," << vertices[j]
                    << "> 的最短路径为：" << pathStr
                    << " 最短路径长度为：" << dist[i][j] << endl;
            }
        }
    }

    return 0;
}
/*
	请输入顶点个数和边的个数：3 5
请输入顶点的值a b c
请输入边依附的两个顶点和权值:
a b 4
b a 6
b c 2
c a 3
a c 11
显示每对顶点间的最短路径：
<a,b> 的最短路径为：ab 最短路径长度为：4
<a,c> 的最短路径为：abc 最短路径长度为：6
<b,a> 的最短路径为：bca 最短路径长度为：5
<b,c> 的最短路径为：bc 最短路径长度为：2
<c,a> 的最短路径为：ca 最短路径长度为：3
<c,b> 的最短路径为：cab 最短路径长度为：7
无路径情况
输出 <0,1> 无路径
*/


/*
    自我总结
    1.Floyd算法核心在于三重循环，第一层循环可以选取所有的点，第二层循环和第三层循环一起可以检查它是否同时有入度和出度（判断中间点）
    2.关键数据结构：距离数组dist，路径数组path
*/