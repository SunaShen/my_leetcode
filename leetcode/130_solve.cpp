// @File   : 130_solve.cpp
// @Source : https://leetcode-cn.com/problems/surrounded-regions/
// @Title  : 130. 被围绕的区域
// @Auther : sun_ds
// @Date   : 2020/4/21

/**  题目描述：
    给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。

    找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。

    示例:

    X X X X
    X O O X
    X X O X
    X O X X
    运行你的函数后，矩阵变为：

    X X X X
    X X X X
    X X X X
    X O X X
    解释:

    被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/surrounded-regions
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dfs
 * 从四个边界的'O'开始扩张。
 * 没有被扩张到的位置，都应该是'X'
 *
 *
 */


class Solution {
private:
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
public:
    void dfs(vector<vector<char>>& board,vector<vector<bool>>& flag,int x,int y){
        if(x<0||x>=board.size()||y<0||y>=board[0].size()||board[x][y]=='X'||flag[x][y]==false) return;
        flag[x][y] = false;
        for(int k=0;k<4;k++){
            int next_x = x + dx[k];
            int next_y = y + dy[k];
            dfs(board,flag,next_x,next_y);
        }
    }
    void solve(vector<vector<char>>& board) {
        if(board.size()==0||board[0].size()==0) return;

        int m = board.size();
        int n = board[0].size();

        vector<vector<bool>> flag(m,vector<bool>(n,true));

        for(int i=0;i<m;i++){
            if(board[i][0]=='O'){
                dfs(board,flag,i,0);
            }
            if(board[i][n-1]=='O'){
                dfs(board,flag,i,n-1);
            }
        }
        for(int j=0;j<n;j++){
            if(board[0][j]=='O'){
                dfs(board,flag,0,j);
            }
            if(board[m-1][j]=='O'){
                dfs(board,flag,m-1,j);
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(board[i][j]=='O'&&flag[i][j]){
                    board[i][j]='X';
                }
            }
        }
    }
};

