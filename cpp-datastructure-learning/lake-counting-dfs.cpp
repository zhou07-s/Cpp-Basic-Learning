#include <iostream>
#include <cstring>
using namespace std;
/*
整个农场被划分为一个矩形网格，包含N（1 <= N <= 100）行和M（1 <= M <= 100）列。
网格中的每个单元格要么干燥，要么被淹没，其中恰好有K个（1 <= K <= N*M）单元格处于淹没状态。
连通规则：上下左右相邻的水域算同一个湖
输入 * 第1行：三个用空格分隔的整数：N、M和K * 第2至K+1行：第i+1行描述一个水下位置，包含两个用空格分隔的整数，分别表示该位置的行和列：R和 C
输出 * 第1行：最大湖泊所包含的单元格数量。

*/
const int MAX = 105;
// 网格：true=有水，false=没水
bool grid[MAX][MAX];
// 访问标记：true=已经统计过
bool vis[MAX][MAX];
int n, m, k;
// 上下左右四个方向
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
// 当前连通块的大小
int cnt;

// 深度优先搜索
void dfs(int x, int y) {
    // 越界、没水、已经访问过 → 直接返回
    if (x < 1 || x > n || y < 1 || y > m || !grid[x][y] || vis[x][y])
        return;

    vis[x][y] = true; // 标记为已访问
    cnt++; // 连通块大小+1

    // 遍历四个方向
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        dfs(nx, ny);
    }
}

int main() {
    // 初始化数组
    memset(grid, false, sizeof(grid));
    memset(vis, false, sizeof(vis));

    cin >> n >> m >> k;
    // 标记有水的格子
    for (int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        grid[r][c] = true;
    }

    int max_size = 0;
    // 遍历整个网格
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // 如果是未访问的水域，开始搜索
            if (grid[i][j] && !vis[i][j]) {
                cnt = 0;
                dfs(i, j);
                // 更新最大湖大小
                if (cnt > max_size)
                    max_size = cnt;
            }
        }
    }

    cout << max_size << endl;
    return 0;
}
/*
    总结：
    1.遇到很多变量复用的情况可以定义全局变量避免大量传参，比如cnt
    在这个情况下，如果是局部变量每次深搜完要重新设为0，容易忘记定义全局变量很好的避免了这一点
    2.可优化部分将visited和grid合为一体
    用0表示没有水，1表示有水，2表示有水且访问，减少代码但是可读性变差。
    3.深度搜索，传递一个起点，通过条件判断要不要调dfs函数，
    关键点就是找到条件和找到下一个函数传的参数也就是下一个节点的下标，其他的递归会为你搞定。
*/