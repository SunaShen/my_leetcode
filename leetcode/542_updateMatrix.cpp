// @File   : 542_updateMatrix.cpp
// @Source : https://leetcode-cn.com/problems/01-matrix/
// @Title  : 542. 01 矩阵
// @Auther : sun_ds
// @Date   : 2020/4/15

/**  题目描述：
    给定一个由 0 和 1 组成的矩阵，找出每个元素到最近的 0 的距离。

    两个相邻元素间的距离为 1 。

    示例 1:
    输入:

    0 0 0
    0 1 0
    0 0 0
    输出:

    0 0 0
    0 1 0
    0 0 0
    示例 2:
    输入:

    0 0 0
    0 1 0
    1 1 1
    输出:

    0 0 0
    0 1 0
    1 2 1
    注意:

    给定矩阵的元素个数不超过 10000。
    给定矩阵中至少有一个元素是 0。
    矩阵中的元素只在四个方向上相邻: 上、下、左、右。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/01-matrix
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.bfs
 *  从0的位置开始bfs，上下左右扩张。
 *  遇到位置为1，且并没有遍历过的位置，更新距离 = 前一个位置的距离 + 1。以第一个遍历到的距离为自己的距离(默认距离最小)
 *  然后将当前位置入队。。
 *  即每个位置元素只入队出队一次。
 *
 * 2.dp
 *  当前位置 = 上下左右位置 + 1来更新。
 *  当然，起始条件，位置为0的距离直接为0.
 *
 * 使用左上->右下 和 右下->左上两次遍历。更新，获得每个位置的最小值。
 *
 */

//bfs
class Solution {
private:
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> flag(m,vector<int>(n,0));
        vector<vector<int>> ans(m,vector<int>(n,0));
        queue<pair<int,int>> q;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j]==0){
                    q.push(make_pair(i,j));
                    flag[i][j]=1;
                }
            }
        }
        while(!q.empty()){
            auto temp = q.front();
            q.pop();
            int x = temp.first;
            int y = temp.second;
            for(int k=0;k<4;k++){
                int x_t = x + dx[k];
                int y_t = y + dy[k];
                if(x_t>=0&&x_t<m&&y_t>=0&&y_t<n&&!flag[x_t][y_t]){
                    ans[x_t][y_t] = ans[x][y]+1;
                    flag[x_t][y_t] = 1;
                    q.push(make_pair(x_t,y_t));
                }
            }
        }
        return ans;
    }
};

//bfs 层层扩张
class Solution {
private:
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> ans(m,vector<int>(n,-1));
        queue<pair<int,int>> q;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j]==0){
                    q.push(make_pair(i,j));
                    ans[i][j] = 0;
                }
            }
        }
        int depth = 0;
        while(!q.empty()){
            int len = q.size();
            depth++;
            for(int kk=0;kk<len;kk++){
                auto temp = q.front();
                q.pop();
                int x = temp.first;
                int y = temp.second;
                for(int k=0;k<4;k++){
                    int x_t = x + dx[k];
                    int y_t = y + dy[k];
                    if(x_t>=0&&x_t<m&&y_t>=0&&y_t<n&&ans[x_t][y_t]==-1){
                        ans[x_t][y_t] = depth;
                        q.push(make_pair(x_t,y_t));
                    }
                }
            }
        }
        return ans;
    }
};

//dp
class Solution {
private:
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m,vector<int>(n,INT_MAX/2));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j]==0){
                    dp[i][j] = 0;
                }
            }
        }
        //注意遍历顺序 dp当前值更新要以已更新过的值来更新
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(i-1>=0){
                    //从上边更新
                    dp[i][j] = min(dp[i][j],dp[i-1][j]+1);
                }
                if(j-1>=0){
                    //从左边更新
                    dp[i][j] = min(dp[i][j],dp[i][j-1]+1);
                }
            }
        }
        //注意遍历顺序 dp当前值更新要以已更新过的值来更新
        for(int i=m-1;i>=0;i--){
            for(int j=n-1;j>=0;j--){
                if(i+1<m){
                    //从下边更新
                    dp[i][j] = min(dp[i][j],dp[i+1][j]+1);
                }
                if(j+1<n){
                    //从右边更新
                    dp[i][j] = min(dp[i][j],dp[i][j+1]+1);
                }
            }
        }
        return dp;
    }
};

