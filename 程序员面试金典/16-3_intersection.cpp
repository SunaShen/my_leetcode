// @File   : 16-3_intersection.cpp
// @Source : https://leetcode-cn.com/problems/intersection-lcci/
// @Title  : 面试题 16.03. 交点
// @Auther : sun_ds
// @Date   : 2020/4/12

/**  题目描述：
    给定两条线段（表示为起点start = {X1, Y1}和终点end = {X2, Y2}），如果它们有交点，请计算其交点，没有交点则返回空值。

    要求浮点型误差不超过10^-6。若有多个交点（线段重叠）则返回 X 值最小的点，X 坐标相同则返回 Y 值最小的点。

     

    示例 1：

    输入：
    line1 = {0, 0}, {1, 0}
    line2 = {1, 1}, {0, -1}
    输出： {0.5, 0}
    示例 2：

    输入：
    line1 = {0, 0}, {3, 3}
    line2 = {1, 1}, {2, 2}
    输出： {1, 1}
    示例 3：

    输入：
    line1 = {0, 0}, {1, 1}
    line2 = {1, 0}, {2, 1}
    输出： {}，两条线段没有交点
     

    提示：

    坐标绝对值不会超过 2^7
    输入的坐标均是有效的二维坐标
    通过次数2,049提交次数4,019

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/intersection-lcci
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 数学劝退。。
 *
 * https://leetcode-cn.com/problems/intersection-lcci/solution/c-yi-ban-shi-qiu-jiao-dian-by-time-limit/
 *
 */


class Solution {
public:
    const double EPS = 1e-7;
    template<typename T1, typename T2, typename T3>
    bool isPointInLine(const T1 &p, const T2 &s, const T3 &e) {
        // p点坐标 s和e为线段起点和终点
        // 判断 dist(s,p) + dist(p,e) == dist(s,e) 是否满足。若点p在线段s-e上，则符合条件
        double d1 = sqrt((p[0] - s[0])*(p[0] - s[0]) + (p[1] - s[1])*(p[1] - s[1]));
        double d2 = sqrt((p[0] - e[0])*(p[0] - e[0]) + (p[1] - e[1])*(p[1] - e[1]));
        double d3 = sqrt((s[0] - e[0])*(s[0] - e[0]) + (s[1] - e[1])*(s[1] - e[1]));
        if(fabs(d1 + d2 - d3) <= EPS) {
            return true;
        }
        return false;
    }
    vector<double> getIntersectionOfParallelLine(vector<int> &s1, vector<int> &e1, vector<int> &s2, vector<int> &e2) {
        vector<vector<double>> res;
        if(isPointInLine(s1, s2, e2)) {
            res.push_back(vector<double>{double(s1[0]), double(s1[1])});
        }
        if(isPointInLine(e1, s2, e2)) {
            res.push_back(vector<double>{double(e1[0]), double(e1[1])});
        }
        if(isPointInLine(s2, s1, e1)) {
            res.push_back(vector<double>{double(s2[0]), double(s2[1])});
        }
        if(isPointInLine(e2, s1, e1)) {
            res.push_back(vector<double>{double(e2[0]), double(e2[1])});
        }
        if(res.size() == 0) {
            return vector<double>{};
        }
        //若有多个交点（线段重叠）则返回 X 值最小的点，X 坐标相同则返回 Y 值最小的点
        sort(res.begin(), res.end(), [](const vector<double> &l, const vector<double> &r)->bool {
            return l[0] < r[0];
        });
        return res[0];
    }
    vector<double> getParam(const vector<int> &point1, const vector<int> &point2) {
        //A = y2-y1, B = x1-x2, C = x2y1-x1y2
        double a = point2[1] - point1[1];
        double b = point1[0] - point2[0];
        double c = point2[0]*point1[1] - point1[0]*point2[1];
        return vector<double>{a, b, c};
    }
    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        int dx1 = end1[0] - start1[0];
        int dy1 = end1[1] - start1[1];

        int dx2 = end2[0] - start2[0];
        int dy2 = end2[1] - start2[1];

        if(dx1*dy2 == dx2*dy1) {    //平行
            return getIntersectionOfParallelLine(start1, end1, start2, end2);
        }

        //获得直线方程一般式三个参数 A,B,C
        vector<double> p1 = getParam(start1, end1);
        vector<double> p2 = getParam(start2, end2);

        //求交点
        double x = double(p2[2]*p1[1] - p1[2]*p2[1]) / double(p1[0]*p2[1] - p2[0]*p1[1]);
        double y = double(p1[2]*p2[0] - p2[2]*p1[0]) / double(p1[0]*p2[1] - p2[0]*p1[1]);

        //交点即在线段1上又在线段2上
        vector<double> point{x, y};
        if(isPointInLine(point, start1, end1) && isPointInLine(point, start2, end2)) {
            return point;
        }
        return vector<double> {};
    }
};
