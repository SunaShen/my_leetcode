// @File   : 52_totalNQueens.cpp
// @Source : https://leetcode-cn.com/problems/n-queens-ii/
// @Title  : 52. N皇后 II
// @Auther : sun_ds
// @Date   : 2020/10/17

/**  题目描述：
    n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。



    上图为 8 皇后问题的一种解法。

    给定一个整数 n，返回 n 皇后不同的解决方案的数量。

    示例:

    输入: 4
    输出: 2
    解释: 4 皇后问题存在如下两个不同的解法。
    [
     [".Q..",  // 解法 1
      "...Q",
      "Q...",
      "..Q."],

     ["..Q.",  // 解法 2
      "Q...",
      "...Q",
      ".Q.."]
    ]
     

    提示：

    皇后，是国际象棋中的棋子，意味着国王的妻子。皇后只做一件事，那就是“吃子”。当她遇见可以吃的棋子时，就迅速冲上去吃掉棋子。当然，她横、竖、斜都可走一或 N-1 步，可进可退。（引用自 百度百科 - 皇后 ）


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/n-queens-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.回溯法
 *  遍历row行
 *  在每个行中遍历0~n-1选取一个列。
 *  则当前候选位置为 [row][col]
 *  判断当前位置是否和前面位置冲突，遍历过程，只用考虑左上，右上和上面。
 *  若不满足，则跳过，选取下一个col。
 *  若满足，则将temp中对应位置[row][col]置为'Q'.
 *  继续递归，将row+1.
 *  返回后，回溯，将位置[row][col]置为'.'.
 *
 *  当row == temp.size() == n
 *  完成n皇后的排列了，res 加 1。
 *
 * 最终res中存储符合条件的个数
 */

class Solution {
public:
    bool isvalid(vector<string>& temp,int row,int col){
        //判断列是否被用过。
        //行不用判断，应为是row控制的，每一个固定一个。
        for(int i=0;i<row;i++){
            if(temp[i][col]=='Q') return false;
        }
        //判断左上角对角线
        int x = row-1,y = col-1;
        while(x>=0&&y>=0){
            if(temp[x--][y--]=='Q') return false;
        }
        //判断右上角对角线
        x = row-1;
        y = col+1;
        while(x>=0&&y<temp.size()){
            if(temp[x--][y++]=='Q') return false;
        }
        return true;
    }
    void backtrack(int& res,vector<string>& temp,int row){
        if(row==temp.size()){
            res++;
            return;
        }
        for(int col=0;col<temp[0].size();col++){
            if(!isvalid(temp,row,col)) continue;
            //回溯
            temp[row][col] = 'Q';
            backtrack(res,temp,row+1);
            temp[row][col] = '.';
        }
    }
    int totalNQueens(int n) {
        int res = 0;
        vector<string> temp(n,string(n,'.'));
        backtrack(res,temp,0);
        return res;
    }
};