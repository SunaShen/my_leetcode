// @File   : 836_isRectangleOverlap.cpp
// @Source : https://leetcode-cn.com/problems/rectangle-overlap/
// @Title  : 836. 矩形重叠
// @Auther : sun_ds
// @Date   : 2020/3/18

/**  题目描述：
    矩形以列表 [x1, y1, x2, y2] 的形式表示，其中 (x1, y1) 为左下角的坐标，(x2, y2) 是右上角的坐标。

    如果相交的面积为正，则称两矩形重叠。需要明确的是，只在角或边接触的两个矩形不构成重叠。

    给出两个矩形，判断它们是否重叠并返回结果。

     

    示例 1：

    输入：rec1 = [0,0,2,2], rec2 = [1,1,3,3]
    输出：true
    示例 2：

    输入：rec1 = [0,0,1,1], rec2 = [1,0,2,1]
    输出：false
     

    提示：

    两个矩形 rec1 和 rec2 都以含有四个整数的列表的形式给出。
    矩形中的所有坐标都处于 -10^9 和 10^9 之间。
    x 轴默认指向右，y 轴默认指向上。
    你可以仅考虑矩形是正放的情况。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/rectangle-overlap
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 求矩阵重叠
 * 矩阵重叠情况有好多种，但是不重叠的情况比较少
 *
 * 1.求不重叠
 *  假设1位基准，2不和1重叠，则必定在1的上下左右四个方向上。其中x2，y2是矩阵最大值，x1，y1是矩阵最小值。
 *  通过判断rec2[0] >= rec1[2] || rec2[2] <= rec1[0]||rec2[1] >= rec1[3] || rec2[3] <= rec1[1]右左上下
 *  满足其中一个条件即不重叠
 *
 * 2.投影
 *  将矩阵分别投影到x轴和y轴，判断是否有重叠，即在坐标轴上区间是否相交。
 *  也是判断不重叠容易。
 *
 *
 *
 *
 */

//逆向，求不重叠
class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        //逆向思维 2在1的 右 左 上 下 不重叠
        if(rec2[0] >= rec1[2] || rec2[2] <= rec1[0]||rec2[1] >= rec1[3] || rec2[3] <= rec1[1])
            return false;
        return true;
    }
};

//逆向求不重叠，算投影
class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        bool x_overlap = !(rec1[2] <= rec2[0] || rec2[2] <= rec1[0]);
        bool y_overlap = !(rec1[3] <= rec2[1] || rec2[3] <= rec1[1]);
        return x_overlap && y_overlap;
    }
};
