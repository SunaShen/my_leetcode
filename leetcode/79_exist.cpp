// @File   : 79_exist.cpp
// @Source : https://leetcode-cn.com/problems/word-search/
// @Title  :79. 单词搜索
// @Auther : sun_ds
// @Date   : 2020/3/5

/**  题目描述：
    给定一个二维网格和一个单词，找出该单词是否存在于网格中。

    单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

    示例:

    board =
    [
      ['A','B','C','E'],
      ['S','F','C','S'],
      ['A','D','E','E']
    ]

    给定 word = "ABCCED", 返回 true.
    给定 word = "SEE", 返回 true.
    给定 word = "ABCB", 返回 false.

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/word-search
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dfs
 *  深度优先遍历
 *  每一个位置后面都有四个位置可以选择。
 *  直到找到一条路径和字符串相等，即返回true.
 *  否则，坐标超限或字符不相等或当前字符用过都返回false.(剪枝)
 *
 *  记录是否用过的技巧。表示当前位置用过，置为一个字符串中不会出现的字符，如'/'。则判断字符是否相等的时候，间接的判断了是否用过。
 *  但，记得用完，还要恢复字符值。即回溯的过程。
 *
 *  使用额外对应大小的数组flag记录也可以，但形参要用引用，不然内存超限。
 *
 *
 *
 *
 */

class Solution {
public:
    bool func(vector<vector<char>>& board,string& word,int i,int j,int index){
        //判断边界 判断是否相等 判断是否用过 由于用过的变成board[i][j]=='/'，所以是否用过和相等一起判断了
        if(i<0||i>=board.size()||j<0||j>=board[0].size()||board[i][j]!=word[index]) return false;
        //找完了
        if(index == word.size()-1) return true;
        //使用标志位标记使用过
        char temp = board[i][j];
        board[i][j] = '/';
        //上下左右搜索
        bool res = func(board,word,i-1,j,index+1)||func(board,word,i+1,j,index+1)||func(board,word,i,j-1,index+1)||func(board,word,i,j+1,index+1);
        //还原之前的位置
        board[i][j] = temp;
        return res;
    }
    bool exist(vector<vector<char>>& board, string word) {
        if(board.size()==0||board[0].size()==0||word.size()==0) return false;
        int m = board.size(), n = board[0].size();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(func(board,word,i,j,0)) return true;
            }
        }
        return false;
    }
};


//使用flag来记录是否用过
//func中的形参flag要用引用，不然内存超限。
class Solution {
public:
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
    bool func(vector<vector<char>>& board,vector<vector<int>>& flag,string& word,int i,int j,int index){
        if(board[i][j]!=word[index]||flag[i][j]!=0) return false;
        if(index == word.size()-1){
            return true;
        }
        flag[i][j] = 1;
        for(int k=0;k<4;++k){
            int x = i+dx[k], y = j+dy[k];
            if(x>=0&&x<board.size()&&y>=0&&y<board[0].size()){
                if(func(board,flag,word,x,y,index+1)) return true;
            }
        }
        flag[i][j] = 0;
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        if(board.size()==0||board[0].size()==0||word.size()==0) return false;
        int m = board.size(), n = board[0].size();
        vector<vector<int>> flag(m,vector<int>(n,0));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(func(board,flag,word,i,j,0)) return true;
            }
        }
        return false;
    }
};