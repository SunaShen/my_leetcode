// @File   : 1267_countServers.cpp
// @Source : https://leetcode-cn.com/problems/count-servers-that-communicate/
// @Title  : 统计参与通信的服务器
// @Auther : sun_ds
// @Date   : 2019/11/29

/**  题目描述：
    这里有一幅服务器分布图，服务器的位置标识在 m * n 的整数矩阵网格 grid 中，1 表示单元格上有服务器，0 表示没有。

    如果两台服务器位于同一行或者同一列，我们就认为它们之间可以进行通信。

    请你统计并返回能够与至少一台其他服务器进行通信的服务器的数量。

     

    示例 1：



    输入：grid = [[1,0],[0,1]]
    输出：0
    解释：没有一台服务器能与其他服务器进行通信。
    示例 2：



    输入：grid = [[1,0],[1,1]]
    输出：3
    解释：所有这些服务器都至少可以与一台别的服务器进行通信。
    示例 3：



    输入：grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
    输出：4
    解释：第一行的两台服务器互相通信，第三列的两台服务器互相通信，但右下角的服务器无法与其他服务器通信。
     

    提示：

    m == grid.length
    n == grid[i].length
    1 <= m <= 250
    1 <= n <= 250
    grid[i][j] == 0 or 1


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/count-servers-that-communicate
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 同行或同列有服务器就证明该点服务器能够通信
 * 求所有能通信的服务器数量
 *
 *
 * 1.行列分别统计，去除重复
 *   先按照行统计。计算一行中等于1的个数，若大于1，则ans加上这个值，
 *   并把这些1的位置置为2，表示已经记录过，在列搜索时只当做判断，但不记入ans
 *   按照列统计，统计每一列等于1和2的个数，若大于1，将等于1的个数计入ans
 *
 *
 *   使用2来避免行列重复计数，避免重叠
 *
 * 2.统计各行列服务器个数，再遍历能通信的条件为该行或该列服务器数量大于1
 *   遍历，维护col和row数组，保存着各行列服务器数量
 *   遍历，该点为1且col或row在该行列大于1，则ans加一
 *
 *
 */

//
class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        for(int i=0;i<m;++i){
            int temp = 0, first;
            for(int j=0;j<n;++j){
                if(grid[i][j]==1){
                    temp+=1;
                    if(temp>1)
                        grid[i][j]=2;
                    else
                        first=j;
                }
            }
            if(temp>1){
                ans += temp;
                grid[i][first] = 2;
            }
        }
        for(int j=0;j<n;++j){
            int temp1 = 0,temp2 = 0;
            for(int i=0;i<m;++i){
                if(grid[i][j]==1){
                    temp1+=1;
                }else if(grid[i][j]==2){
                    temp2+=1;
                }
            }
            if(temp1+temp2>1)
                ans += temp1;
        }
        return ans;
    }
};


class Solution {
public:
    int countServers(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = 0;
        vector<int> row_num(m,0);
        vector<int> col_num(n,0);
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(grid[i][j]==1){
                    ++row_num[i];
                    ++col_num[j];
                }
            }
        }
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(grid[i][j]==1&&(row_num[i]>1||col_num[j]>1))
                    ++ans;
            }
        }
        return ans;
    }
};



