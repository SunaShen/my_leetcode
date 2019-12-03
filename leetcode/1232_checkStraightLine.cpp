// @File   : 1232_checkStraightLine.cpp
// @Source : https://leetcode-cn.com/problems/check-if-it-is-a-straight-line/
// @Title  : 缀点成线
// @Auther : sun_ds
// @Date   : 2019/10/24

/*  题目描述：
在一个 XY 坐标系中有一些点，我们用数组 coordinates 来分别记录它们的坐标，其中 coordinates[i] = [x, y] 表示横坐标为 x、纵坐标为 y 的点。

请你来判断，这些点是否在该坐标系中属于同一条直线上，是则返回true，否则请返回false。

 

示例 1：



输入：coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
输出：true
示例 2：



输入：coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
输出：false
 

提示：

2 <= coordinates.length <= 1000
coordinates[i].length == 2
-10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
coordinates 中不含重复的点

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/check-if-it-is-a-straight-line
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
 * 求给定点集是否共线
 *
 * 1.通过斜率
 * 使用斜率来判断共线，首先求出前两点的斜率，然后求后面每一点与第一点的斜率，如不相等则返回false
 * 注意考虑斜率为无穷大时，单独考虑
 * 同时，注意斜率为float类型。两整数相除时要(float)强制转换！！
 *
 * 2.将斜率转换成乘法
 * 更方便。不用考虑斜率无穷大和强制转换float
 *
 *
 *
 *
 */


//使用斜率来判断共线，首先求出前两点的斜率，然后求后面每一点与第一点的斜率，如不相等则返回false
//注意考虑斜率为无穷大时，单独考虑
//同时，注意斜率为float类型。两整数相除时要(float)强制转换！！
class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int n = coordinates.size();
        int flag = 0;
        float k = 0;
        if(coordinates[1][0] == coordinates[0][0]){
            flag = 1;
        }else{
            k = (coordinates[1][1] - coordinates[0][1]) / (float)(coordinates[1][0] - coordinates[0][0]);
        }
        for(int i=2;i<n;++i){
            if(coordinates[i][0] == coordinates[0][0]){
                if(flag){
                    continue;
                }else{
                    return false;
                }
            }
            else if(k == (coordinates[i][1] - coordinates[0][1]) / (float)(coordinates[i][0] - coordinates[0][0]))
                continue;
            else{
                return false;
            }
        }
        return true;
    }
};


//避免使用斜率，斜率是除法形式，除法转为乘法！！！

class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int n = coordinates.size();
        int x = coordinates[1][0] - coordinates[0][0];
        int y = coordinates[1][1] - coordinates[0][1];
        for(int i=2;i<n;++i){
            int x1 = coordinates[i][0] - coordinates[0][0];
            int y1 = coordinates[i][1] - coordinates[0][1];
            if(y*x1!=y1*x)
                return false;
        }
        return true;
    }
};