// @File   : 289_gameOfLife.cpp
// @Source : https://leetcode-cn.com/problems/game-of-life/
// @Title  : 289. 生命游戏
// @Auther : sun_ds
// @Date   : 2020/4/2

/**  题目描述：
    根据 百度百科 ，生命游戏，简称为生命，是英国数学家约翰·何顿·康威在 1970 年发明的细胞自动机。

    给定一个包含 m × n 个格子的面板，每一个格子都可以看成是一个细胞。每个细胞都具有一个初始状态：1 即为活细胞（live），或 0 即为死细胞（dead）。每个细胞与其八个相邻位置（水平，垂直，对角线）的细胞都遵循以下四条生存定律：

    如果活细胞周围八个位置的活细胞数少于两个，则该位置活细胞死亡；
    如果活细胞周围八个位置有两个或三个活细胞，则该位置活细胞仍然存活；
    如果活细胞周围八个位置有超过三个活细胞，则该位置活细胞死亡；
    如果死细胞周围正好有三个活细胞，则该位置死细胞复活；
    根据当前状态，写一个函数来计算面板上所有细胞的下一个（一次更新后的）状态。下一个状态是通过将上述规则同时应用于当前状态下的每个细胞所形成的，其中细胞的出生和死亡是同时发生的。

     

    示例：

    输入：
    [
      [0,1,0],
      [0,0,1],
      [1,1,1],
      [0,0,0]
    ]
    输出：
    [
      [0,0,0],
      [1,0,1],
      [0,1,1],
      [0,1,0]
    ]
     

    进阶：

    你可以使用原地算法解决本题吗？请注意，面板上所有格子需要同时被更新：你不能先更新某些格子，然后使用它们的更新后的值再更新其他格子。
    本题中，我们使用二维数组来表示面板。原则上，面板是无限的，但当活细胞侵占了面板边界时会造成问题。你将如何解决这些问题？


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/game-of-life
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 遍历每个位置，统计8个位置活细胞个数。
 * 若当前为活细胞，周围有2或3活细胞 则可以存活，否则死
 * 若当前为死细胞，周围有3个活细胞，则复活，否则不变
 * 1.使用额外空间
 *  由于各细胞状态同时更新，为防止污染原始数据，采用额外空间保存更新后状态。
 * 2.利用位
 *  board中每个值都为32bit 但他的值为1或0，只用了最后1bit。
 *  所以我们使用最后1bit表示他初始状态，用第二位表示更新后状态。互不影响
 *  最后board中的值右移，更新状态覆盖初始状态
 *
 *
 */

//额外空间
class Solution {
private:
    int dx[8] = {-1,0,1,0,-1,-1,1,1};
    int dy[8] = {0,-1,0,1,-1,1,-1,1};
public:
    void gameOfLife(vector<vector<int>>& board) {
        if(board.size()==0||board[0].size()==0) return;
        int m=board.size(),n=board[0].size();
        vector<vector<int>> ans(m,vector<int>(n,0));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                int count = 0;
                for(int k=0;k<8;k++){
                    int cur_x = i + dx[k];
                    int cur_y = j + dy[k];
                    if(cur_x>=0&&cur_x<m&&cur_y>=0&&cur_y<n&&board[cur_x][cur_y]==1){
                        count++;
                    }
                }
                if(board[i][j]==1){
                    if(count==2||count==3) ans[i][j] = 1;
                }else{
                    if(count==3) ans[i][j] = 1;
                }
            }
        }
        board = ans;
    }
};
//原地操作 充分利用32bit
class Solution {
private:
    int dx[8] = {-1,0,1,0,-1,-1,1,1};
    int dy[8] = {0,-1,0,1,-1,1,-1,1};
public:
    void gameOfLife(vector<vector<int>>& board) {
        if(board.size()==0||board[0].size()==0) return;
        int m=board.size(),n=board[0].size();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                int count = 0;
                for(int k=0;k<8;k++){
                    int cur_x = i + dx[k];
                    int cur_y = j + dy[k];
                    if(cur_x>=0&&cur_x<m&&cur_y>=0&&cur_y<n){
                        //取初始状态 最低位
                        count += board[cur_x][cur_y]&1;
                    }
                }
                //board中的最低位存储初始的状态 第二位存储更新后状态
                if(board[i][j]==1){
                    if(count==2||count==3) board[i][j] |= 2;
                }else{
                    if(count==3) board[i][j] |= 2;
                }
            }
        }
        //使用更新后状态右移覆盖初始状态
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                board[i][j] >>= 1;
            }
        }
    }
};

