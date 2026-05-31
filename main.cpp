#include<iostream>
#include<vector>
#include<stdlib.h>
#define MAX_DISTENCE 1000
using namespace std;
/*
1.初始化数组dist、path和s；
2.while (s中的元素个数<n)
	2.1 在dist[n]中求最小值，其下标为k；
	2.2 输出dist[j]和path[j]；
	2.3 修改数组dist和path；
	2.4 将顶点vk添加到数组s中；
*/
int getindex(char ch, char vertex[], int n);
void printRoad(int index, int path[], char vertex[], int startIndex) {
	if (index == startIndex) {
		cout << vertex[index];
		return;
	}
	if (path[index] == -1) {
		return;
	}
	printRoad(path[index], path, vertex, startIndex);
	cout << "->" << vertex[index];
}
void minroad(char start, int n, int m, int arc[][100], char vertex[]) {
	int dist[100], path[100], s[100], startIndex=getindex(start,vertex,n);
	for (int i = 0;i < n;i++) {
		dist[i] = arc[startIndex][i];
		s[i] = 0;
		if (i == startIndex) {
			dist[i] = 0;   
			path[i] = -1;
		}
		else if (dist[i] < MAX_DISTENCE) {
			path[i] = startIndex;
		}
		else {
			path[i] = -1;
		}
	}
	s[startIndex] = 1;int s_num = 1;
	while (s_num < n) {
		int min = MAX_DISTENCE, minIndex = -1;
		for (int i = 0;i < n;i++) {
			if (s[i] != 1 && dist[i] < min) {
				min = dist[i];
				minIndex = i;
			}
		}
		if (minIndex == -1) break;
		s[minIndex] = 1;s_num++;
		
		for (int i = 0;i < n;i++) {
			if (s[i] != 1 && arc[minIndex][i] < MAX_DISTENCE && arc[minIndex][i] + dist[minIndex] < dist[i]) {
				dist[i] = arc[minIndex][i] + dist[minIndex];
				path[i] = minIndex;
			}
		}
	}
	for (int i = 0;i < n;i++) {
		if (i == startIndex) continue;
		if (dist[i] < MAX_DISTENCE) {
			cout << "从" << start << "到" << vertex[i] << "顶点的最短路径长度为：" << dist[i] << endl;
			cout << "从" << start << "到" << vertex[i] << "顶点的最短路径为：";
			printRoad(i, path, vertex, startIndex);
			cout << endl;
		}
		else {
			cout << "从" << start << "到" << vertex[i] << "没有路径." << endl;
		}
	}
}
int getindex(char ch, char vertex[], int n) {
	for (int i = 0;i < n;i++) {
		if (vertex[i] == ch) {
			return i;
		}
	}
	return -1;
}
int main()
{
	int n, m, arc[100][100];
	char vertex[100];
	cout << "请输入顶点个数和边的个数：" << endl;
	cin >> n >> m;
	cout << "请输入顶点的值" << endl;
	for (int i = 0;i < n;i++) {
		cin >> vertex[i];
	}
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++) {
			arc[i][j] = MAX_DISTENCE;
		}
	}
	cout << "依次输入边的起点编号，终点编号和权值" << endl;
	for (int i = 0;i < m;i++) {
		int from, to, weight;
		cin >> from >> to >> weight;
		arc[from][to] = weight;
	}
	char s;
	cout << "请输入起始顶点：" << endl;
	cin >> s;
	cout << "输出从" << s << "到各个顶点的最短路径：" << endl;
	minroad(s, n, m, arc, vertex);
	return 0;
}
/*
请输入顶点个数和边的个数：5 7
请输入顶点的值A B C D E
依次输入边的起点编号，终点编号和权值
0 1 10
0 3 30
0 4 100
1 2 50
2 4 10
3 4 60
3 2 20
请输入起始顶点：B
输出从B到各个顶点的最短路径：

从B到A没有路径.

从B到C顶点的最短路径长度为：50
从B到C顶点的最短路径为：B->C

从B到D没有路径.

从B到E顶点的最短路径长度为：60
从B到E顶点的最短路径为：B->C->E
*/