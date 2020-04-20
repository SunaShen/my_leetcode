// @File   : 1162_maxDistance.cpp
// @Source : https://leetcode-cn.com/problems/as-far-from-land-as-possible/
// @Title  : 1162. 地图分析
// @Auther : sun_ds
// @Date   : 2020/3/29

/**  题目描述：
    你现在手里有一份大小为 N x N 的『地图』（网格） grid，上面的每个『区域』（单元格）都用 0 和 1 标记好了。其中 0 代表海洋，1 代表陆地，你知道距离陆地区域最远的海洋区域是是哪一个吗？请返回该海洋区域到离它最近的陆地区域的距离。

    我们这里说的距离是『曼哈顿距离』（ Manhattan Distance）：(x0, y0) 和 (x1, y1) 这两个区域之间的距离是 |x0 - x1| + |y0 - y1| 。

    如果我们的地图上只有陆地或者海洋，请返回 -1。

     

    示例 1：



    输入：[[1,0,1],[0,0,0],[1,0,1]]
    输出：2
    解释：
    海洋区域 (1, 1) 和所有陆地区域之间的距离都达到最大，最大距离为 2。
    示例 2：



    输入：[[1,0,0],[0,0,0],[0,0,0]]
    输出：4
    解释：
    海洋区域 (2, 2) 和所有陆地区域之间的距离都达到最大，最大距离为 4。
     

    提示：

    1 <= grid.length == grid[0].length <= 100
    grid[i][j] 不是 0 就是 1

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/as-far-from-land-as-possible
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.bfs
 * 转换思维，考虑从每个陆地为原点，bfs几轮(扩张几轮)，海洋全部被覆盖。
 * 轮数即为要求的最远海洋距离最近陆地的距离。
 *
 * 有多块陆地，对应多个起点。考虑有一个虚拟源节点，该虚拟源节点连着各陆地。
 * 则，问题又转换成单源bfs。
 * 因此，首先将各陆地入队。
 * 然后再一层一层的bfs。
 * 直到没有海洋(没有可以入队的)，统计层数，即为最远距离。
 *
 *
 *
 */


class Solution {
private:
    int dx[4] = {-1,0,1,0};
    int dy[4] = {0,-1,0,1};
public:
    int maxDistance(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int,int>> q;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1)  q.push(make_pair(i,j));
            }
        }
        if(q.size()==0||q.size()==m*n) return -1; //全陆地全海洋
        int res = 0;
        while(!q.empty()){
            int len = q.size();
            for(int i=0;i<len;i++){
                auto temp = q.front();
                q.pop();
                int cur_x = temp.first;
                int cur_y = temp.second;
                for(int k=0;k<4;k++){
                    int temp_x = cur_x + dx[k];
                    int temp_y = cur_y + dy[k];
                    if(temp_x>=0&&temp_x<m&&temp_y>=0&&temp_y<n&&grid[temp_x][temp_y]==0){
                        q.push(make_pair(temp_x,temp_y));
                        grid[temp_x][temp_y] = 1;
                    }
                }
            }
            res++;
        }
        return res - 1;
    }
};


