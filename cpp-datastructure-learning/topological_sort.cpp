#include<iostream>
#include<stack>
#include<stdlib.h>
#include<vector>
#include<queue>
using namespace std;
int main()
{
	stack<int> s;
	int count = 0, vertexNum, a;
	cin >> vertexNum >> a;
	vector<vector<int>> graph(vertexNum + 1);//可以简单理解为二维数组，储存输入的边graph[i][j]，i行里存下标为i的顶点的出度定点下标
	vector<int> in(vertexNum + 1, 0);//储存入度，本题输入边从1开始为了方便故浪费一个空间
	priority_queue<int, vector<int>, greater<int>> zeroInDegree;//用小顶堆（greater）可以让下标小的先输出,不写greater默认大的先输出
	for (int i = 0;i < a;i++) {
		int v1, v2;
		cin >> v1 >> v2;
		graph[v1].push_back(v2);
		in[v2]++;
	}
	for (int i = 1; i <= vertexNum; i++) {
		if (in[i] == 0) {
			zeroInDegree.push(i);
		}
	}
	while (!zeroInDegree.empty()) {
		int cur = zeroInDegree.top();
		zeroInDegree.pop();
		cout << "v" << cur << " ";
		count++;
		for (int i = 0;i < graph[cur].size();i++) {
			int next = graph[cur][i];
			in[next]--;//这里用next储存当前pop出的点指向的下一个顶点，使代码更可读，也更方便修改复用，多用这种写法不要把graph[cur][i]死放进去
			if (in[next] == 0) {
				zeroInDegree.push(next);
			}
		}

	}
	if (count != vertexNum) {
		cout << endl << "图中存在环，无法完成拓扑排序！" << endl;
	}
	return 0;
}
/*
	自我算法总结：
	1.拓扑排序有效的解决了图结构中达成前驱节点才可以达成后驱节点问题，举个例子点科技树
	2.具体算法
		2.1 需要用到的数据结构都在上面了
		2.2 寻找入度为0的下标（in）压入queue
		2.3 输出第一个点，pop出队，count++
		2.4 在graph里面找该顶点的出度点，让它的入度减一，并判断是否为0，为0压入队列
		2.5 最后判断count是否与顶点数相等，如果不相等，代表成环不符合拓扑排序条件
*/
