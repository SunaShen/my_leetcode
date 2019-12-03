// @File   : 1219_getMaximumGold.cpp
// @Source : https://leetcode-cn.com/problems/path-with-maximum-gold/
// @Title  : 黄金矿工
// @Auther : sun_ds
// @Date   : 2019/10/7

/*  题目描述：
    你要开发一座金矿，地质勘测学家已经探明了这座金矿中的资源分布，并用大小为 m * n 的网格 grid 进行了标注。每个单元格中的整数就表示这一单元格中的黄金数量；如果该单元格是空的，那么就是 0。

    为了使收益最大化，矿工需要按以下规则来开采黄金：

    每当矿工进入一个单元，就会收集该单元格中的所有黄金。
    矿工每次可以从当前位置向上下左右四个方向走。
    每个单元格只能被开采（进入）一次。
    不得开采（进入）黄金数目为 0 的单元格。
    矿工可以从网格中 任意一个 有黄金的单元格出发或者是停止。
     

    示例 1：

    输入：grid = [[0,6,0],[5,8,7],[0,9,0]]
    输出：24
    解释：
    [[0,6,0],
     [5,8,7],
     [0,9,0]]
    一种收集最多黄金的路线是：9 -> 8 -> 7。
    示例 2：

    输入：grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
    输出：28
    解释：
    [[1,0,7],
     [2,0,6],
     [3,4,5],
     [0,3,0],
     [9,0,20]]
    一种收集最多黄金的路线是：1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7。
     

    提示：

    1 <= grid.length, grid[i].length <= 15
    0 <= grid[i][j] <= 100
    最多 25 个单元格中有黄金。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/path-with-maximum-gold
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 设置一定的规则，使得开采收益最大化
 *
 * 二维矩阵最大15*15，且最多25个单元格中有黄金
 *
 * 遍历每一个起始点，使用dfs搜索，求取全局最优。
 *
 * 熟悉dfs结构--即回溯法。
 * 1.gold清零
 * 2.遍历4中移动方式是否可以继续dfs
 * 3.恢复gold的值
 * 上下左右移动，使用dx[4]，dy[4]
 *
 * 全局变量 res 保存最优值
 *
 *
 *
 */



#include <iostream>
#include <vector>

using namespace std;



class Solution {
public:
    int dx[4] = {0,1,0,-1};
    int dy[4] = {1,0,-1,0};
    int gold[20][20],m,n,res;
    void dfs(int x, int y, int cur)
    {
        int reg = gold[x][y]; gold[x][y] = 0;
        cur += reg;
        res = max(res, cur);

        for(int i=0;i<4;i++)
        {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if(0<=tx&&tx<m&&0<=ty&&ty<n&&gold[tx][ty]!=0) dfs(tx,ty,cur);
        }

        gold[x][y] = reg;
    }
    int getMaximumGold(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        for(int i=0;i<m;i++) for(int j=0;j<n;j++) gold[i][j] = grid[i][j];

        res = 0;
        for(int i=0;i<m;i++) for(int j=0;j<n;j++) if(gold[i][j]!=0) dfs(i,j,0);
        return res;
    }
};

int main()
{
    vector<vector<int>> grid = {{1,0,7},{2,0,6},{3,4,5},{0,3,0},{9,0,20}};
    Solution su;
    auto res = su.getMaximumGold(grid);

    cout << res << endl;
    cout << "finish" << endl;
    return 0;
}