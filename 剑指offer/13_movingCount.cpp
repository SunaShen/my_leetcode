// @File   : 13_movingCount.cpp
// @Source : https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof/
// @Title  : 面试题13. 机器人的运动范围
// @Auther : sun_ds
// @Date   : 2020/3/5

/**  题目描述：
    地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？

     

    示例 1：

    输入：m = 2, n = 3, k = 1
    输出：3
    示例 1：

    输入：m = 3, n = 1, k = 0
    输出：1
    提示：

    1 <= n,m <= 100
    0 <= k <= 20

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/ji-qi-ren-de-yun-dong-fan-wei-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.dfs
 * 使用flag数组记录当前位置是否来过
 * 递归结束条件，1.位置越界 2.行坐标和列坐标的数位之和大于k 3.之前来过
 * 对每个节点执行四个方向搜索
 *
 * 最后统计flag中1的个数，即为到达的格子数。
 *
 * 2.dfs
 *  计算数位和的规律
 *  (i+1)%10!=0?s_i+1:s_i-8
 *  巧妙
 *
 *
 *
 *
 */

class Solution {
public:
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
    int Sum(int num1,int num2){
        int sum = 0;
        while(num1){
            sum += num1%10;
            num1 /= 10;
        }
        while(num2){
            sum += num2%10;
            num2 /= 10;
        }
        return sum;
    }
    void func(vector<vector<int>>& flag, int i, int j, int k){
        //判断flag[i][j]==1很重要，不然死循环了。来来回回。
        if(i<0||i>=flag.size()||j<0||j>=flag[0].size()||Sum(i,j)>k||flag[i][j]==1){
            return;
        }
        flag[i][j] = 1;
        for(int r=0;r<4;r++){
            int x = i + dx[r],y = j + dy[r];
            func(flag,x,y,k);
        }
        return;
    }
    int movingCount(int m, int n, int k) {
        vector<vector<int>> flag(m,vector<int>(n,0));
        func(flag,0,0,k);
        int res = 0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(flag[i][j]==1) res++;
            }
        }
        return res;
    }
};


class Solution {
public:
    int m,n,k;
    int func(int i, int j, int s_i, int s_j,vector<vector<bool>>& flag){
        if(i<0||i>=m||j<0||j>=n||s_i+s_j>k||flag[i][j]) return 0;
        flag[i][j] = true;
        return 1+func(i+1,j,(i+1)%10!=0?s_i+1:s_i-8,s_j,flag)+func(i,j+1,s_i,(j+1)%10!=0?s_j+1:s_j-8,flag);
    }
    int movingCount(int m, int n, int k) {
        this->m = m;
        this->n = n;
        this->k = k;
        vector<vector<bool>> flag(m,vector<bool>(n,false));
        return func(0,0,0,0,flag);
    }
};

