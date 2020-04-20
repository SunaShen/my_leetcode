// @File   : 892_surfaceArea.cpp
// @Source : https://leetcode-cn.com/problems/surface-area-of-3d-shapes/
// @Title  : 892. 三维形体的表面积
// @Auther : sun_ds
// @Date   : 2020/3/25

/**  题目描述：
    在 N * N 的网格上，我们放置一些 1 * 1 * 1  的立方体。

    每个值 v = grid[i][j] 表示 v 个正方体叠放在对应单元格 (i, j) 上。

    请你返回最终形体的表面积。

     

    示例 1：

    输入：[[2]]
    输出：10
    示例 2：

    输入：[[1,2],[3,4]]
    输出：34
    示例 3：

    输入：[[1,0],[0,2]]
    输出：16
    示例 4：

    输入：[[1,1,1],[1,0,1],[1,1,1]]
    输出：32
    示例 5：

    输入：[[2,2,2],[2,1,2],[2,2,2]]
    输出：46
     

    提示：

    1 <= N <= 50
    0 <= grid[i][j] <= 50


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/surface-area-of-3d-shapes
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.加法
 *  考虑每个位置立方体贡献的表面积
 *  若当前位置grid[i][j]==0，则没有贡献任何表面积
 *  若当前位置grid[i][j]！=0，首先贡献上下面2个。其次判断其四个侧面与旁边位置高度的关系。漏出的面为max(当前高度-旁边高度，0)。
 *
 * 2.减法
 *  表面积 = 6*立方体个数 - 2*重合的面数
 *  立方体个数遍历统计
 *  重合面数，单方向统计(避免重复计算)，即只考虑当前位置的左上是否有重合。重合面为min(当前高度，旁边高度)
 *  最终得到表面积
 *
 *
 *
 */

//加法
class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        if(grid.size()==0||grid[0].size()==0) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==0) continue;
                //上面+下面
                res += 2;
                //判断四个侧面贡献的面积
                res += i-1>=0 ? max(grid[i][j]-grid[i-1][j],0) : grid[i][j];
                res += i+1<m ? max(grid[i][j]-grid[i+1][j],0) : grid[i][j];
                res += j-1>=0 ? max(grid[i][j]-grid[i][j-1],0) : grid[i][j];
                res += j+1<n ? max(grid[i][j]-grid[i][j+1],0) : grid[i][j];
            }
        }
        return res;
    }
};
//减法
class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        if(grid.size()==0||grid[0].size()==0) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int cube = 0, face = 0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                cube += grid[i][j];
                if(grid[i][j]>1) face += grid[i][j] - 1;
                //只算左上
                if(i>0){
                    // 当前柱子与上边柱子的接触面数量
                    face += min(grid[i][j],grid[i-1][j]);
                }
                if(j>0){
                    // 当前柱子与左边柱子的接触面数量
                    face += min(grid[i][j],grid[i][j-1]);
                }
            }
        }
        // res = 6*立方体个数 - 2*接触面个数
        return 6*cube - 2*face;
    }
};