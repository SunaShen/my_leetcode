// @File   : 200_numIslands.cpp
// @Source : https://leetcode-cn.com/problems/number-of-islands/
// @Title  : 200. 岛屿数量
// @Auther : sun_ds
// @Date   : 2020/4/20

/**  题目描述：
    给定一个由 '1'（陆地）和 '0'（水）组成的的二维网格，计算岛屿的数量。一个岛被水包围，并且它是通过水平方向或垂直方向上相邻的陆地连接而成的。你可以假设网格的四个边均被水包围。

    示例 1:

    输入:
    11110
    11010
    11000
    00000

    输出: 1
    示例 2:

    输入:
    11000
    11000
    00100
    00011

    输出: 3

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/number-of-islands
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * dfs经过的点置为0.
 * for循环遍历各个位置，为1就进行dfs，并且岛屿数量res++
 *
 *
 */
class Solution {
private:
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
public:
    void dfs(vector<vector<char>>& grid,int x, int y){
        if(x<0||x>=grid.size()||y<0||y>=grid[0].size()||grid[x][y]=='0') return;
        grid[x][y]='0';
        for(int k=0;k<4;k++){
            dfs(grid,x+dx[k],y+dy[k]);
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        if(grid.size()==0||grid[0].size()==0) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]=='1'){
                    dfs(grid,i,j);
                    res++;
                }
            }
        }
        return res;
    }
};
