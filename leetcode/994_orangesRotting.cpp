// @File   : 994_orangesRotting.cpp
// @Source : https://leetcode-cn.com/problems/rotting-oranges/
// @Title  : 994. 腐烂的橘子
// @Auther : sun_ds
// @Date   : 2020/3/4

/**  题目描述：
    在给定的网格中，每个单元格可以有以下三个值之一：

    值 0 代表空单元格；
    值 1 代表新鲜橘子；
    值 2 代表腐烂的橘子。
    每分钟，任何与腐烂的橘子（在 4 个正方向上）相邻的新鲜橘子都会腐烂。

    返回直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1。

     

    示例 1：



    输入：[[2,1,1],[1,1,0],[0,1,1]]
    输出：4
    示例 2：

    输入：[[2,1,1],[0,1,1],[1,0,1]]
    输出：-1
    解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个正向上。
    示例 3：

    输入：[[0,2]]
    输出：0
    解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。
     

    提示：

    1 <= grid.length <= 10
    1 <= grid[0].length <= 10
    grid[i][j] 仅为 0、1 或 2


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/rotting-oranges
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.bfs
 * 每个橘子可以感染上下左右四个橘子，定义int dx[4] = {-1,0,1,0};int dy[4] = {0,-1,0,1};控制搜索方向。
 * 使用queue或vector存储当前这一代的烂橘子。
 * 遍历当前带烂橘子，每个烂橘子执行上下左右搜索，满足坐标关系且为好橘子的位置也变成烂橘子，入队(存入)。并记录代数++。
 * 最终知道下一代没有橘子，结束循环。
 * 判断烂橘子数和所有橘子数是否相等。若相等返回代数(分钟)，否则返回-1.
 *
 *
 *
 *
 */


class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int dx[4] = {-1,0,1,0};
        int dy[4] = {0,-1,0,1};
        queue<pair<int,int>> q;
        int count_0 = 0, count = 0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==2){
                    q.push(make_pair(i,j));
                    count++;
                }else if(grid[i][j]==0){
                    count_0++;
                }
            }
        }
        int time = 0;
        while(!q.empty()){
            int len = q.size();
            for(int c=0;c<len;c++){
                pair<int,int> pos = q.front();
                q.pop();
                for(int k=0;k<4;k++){
                    int x = pos.first + dx[k], y = pos.second + dy[k];
                    if(x>=0&&x<m&&y>=0&&y<n&&grid[x][y]==1){
                        q.push(make_pair(x,y));
                        count++;
                        grid[x][y]=2;
                    }
                }
            }
            if(!q.empty()) time++;
        }
        if(count+count_0 == m*n) return time;
        else return -1;
    }
};




class Solution {
public:
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> s_index;
        int count_0 = 0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==2){
                    vector<int> temp{i,j};
                    s_index.push_back(temp);
                }else if(grid[i][j]==0){
                    count_0++;
                }
            }
        }
        int count = 0;
        int len = 0,o_len = 0;
        int flag = 1;
        while(flag){
            flag = 0;
            len = s_index.size();
            for(int i=o_len;i<len;i++){
                int x = s_index[i][0],y = s_index[i][1];
                for(int k=0;k<4;k++){
                    int x_temp = x+dx[k],y_temp = y+dy[k];
                    if(x_temp>=0&&x_temp<m&&y_temp>=0&&y_temp<n&&grid[x_temp][y_temp]==1){
                        flag = 1;
                        s_index.push_back(vector<int>{x_temp,y_temp});
                        grid[x_temp][y_temp] = 2;
                    }
                }
            }
            if(flag)   count++;
            o_len = len;
        }
        if(s_index.size()+count_0 == m*n) return count;
        else return -1;
    }
};

