// @File   : 695_maxAreaOfIsland.cpp
// @Source : https://leetcode-cn.com/problems/max-area-of-island/
// @Title  : 695. 岛屿的最大面积
// @Auther : sun_ds
// @Date   : 2020/3/15

/**  题目描述：
    给定一个包含了一些 0 和 1的非空二维数组 grid , 一个 岛屿 是由四个方向 (水平或垂直) 的 1 (代表土地) 构成的组合。你可以假设二维矩阵的四个边缘都被水包围着。

    找到给定的二维数组中最大的岛屿面积。(如果没有岛屿，则返回面积为0。)

    示例 1:

    [[0,0,1,0,0,0,0,1,0,0,0,0,0],
     [0,0,0,0,0,0,0,1,1,1,0,0,0],
     [0,1,1,0,1,0,0,0,0,0,0,0,0],
     [0,1,0,0,1,1,0,0,1,0,1,0,0],
     [0,1,0,0,1,1,0,0,1,1,1,0,0],
     [0,0,0,0,0,0,0,0,0,0,1,0,0],
     [0,0,0,0,0,0,0,1,1,1,0,0,0],
     [0,0,0,0,0,0,0,1,1,0,0,0,0]]
    对于上面这个给定矩阵应返回 6。注意答案不应该是11，因为岛屿只能包含水平或垂直的四个方向的‘1’。

    示例 2:

    [[0,0,0,0,0,0,0,0]]
    对于上面这个给定的矩阵, 返回 0。

    注意: 给定的矩阵grid 的长度和宽度都不超过 50。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/max-area-of-island
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dfs 递归
 *  遍历以每个位置为起点，使用dfs求的连通块大小。
 *  取最大值。
 * 2.栈迭代实现dfs
 * 3.队列迭代实现bfs
 *
 *
 */


class Solution {
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
public:
    int func(vector<vector<int>>& grid, int i, int j){
        if(i<0||i>=grid.size()||j<0||j>=grid[0].size()||grid[i][j]!=1) return 0;
        int c = 1;
        //遍历过后要标记，否则会循环造成死循环。
        grid[i][j] = 2;
        for(int k=0;k<4;k++){
            int x = i+dx[k], y = j+dy[k];
            c += func(grid,x,y);
        }
        return c;
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int res=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                res = max(res, func(grid,i,j));
            }
        }
        return res;
    }
};

//栈实现dfs
class Solution {
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int res = 0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                int cur = 0;
                stack<int> x;
                stack<int> y;
                x.push(i);
                y.push(j);
                while(!x.empty()){
                    int cur_i = x.top(), cur_j = y.top();
                    x.pop();y.pop();
                    if(cur_i<0||cur_i>=grid.size()||cur_j<0||cur_j>=grid[0].size()||grid[cur_i][cur_j]!=1)
                        continue;
                    cur++;
                    grid[cur_i][cur_j] = 2;
                    for(int k=0;k<4;k++){
                        int next_i = cur_i + dx[k], next_j = cur_j + dy[k];
                        x.push(next_i);
                        y.push(next_j);
                    }
                }
                res = max(res,cur);
            }
        }
        return res;
    }
};
//队列 bfs
class Solution {
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int res = 0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                int cur = 0;
                queue<int> x;
                queue<int> y;
                x.push(i);
                y.push(j);
                while(!x.empty()){
                    int cur_i = x.front(), cur_j = y.front();
                    x.pop();y.pop();
                    if(cur_i<0||cur_i>=grid.size()||cur_j<0||cur_j>=grid[0].size()||grid[cur_i][cur_j]!=1)
                        continue;
                    cur++;
                    grid[cur_i][cur_j] = 2;
                    for(int k=0;k<4;k++){
                        int next_i = cur_i + dx[k], next_j = cur_j + dy[k];
                        x.push(next_i);
                        y.push(next_j);
                    }
                }
                res = max(res,cur);
            }
        }
        return res;
    }
};