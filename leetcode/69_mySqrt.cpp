// @File   : 69_mySqrt.cpp
// @Source : https://leetcode-cn.com/problems/sqrtx/
// @Title  : 69. x 的平方根
// @Auther : sun_ds
// @Date   : 2020/5/9

/**  题目描述：
    实现 int sqrt(int x) 函数。

    计算并返回 x 的平方根，其中 x 是非负整数。

    由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。

    示例 1:

    输入: 4
    输出: 2
    示例 2:

    输入: 8
    输出: 2
    说明: 8 的平方根是 2.82842...,
         由于返回类型是整数，小数部分将被舍去。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/sqrtx
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 求平方根
 * 1.二分法试出来
 *  从1-x之间进行二分查找，找到一个值的平方==x，或者是平方最接近x的略小的值。
 *
 */

class Solution {
public:
    int mySqrt(int x) {
        int l=1,r=x;
        while(l<=r){
            long long mid = l + ((r - l) >> 1);
            if(mid*mid==x)return mid;
            else if(mid*mid<x) r = mid-1;
            else l = mid+1;
        }
        return r;
    }
};

class Solution {
public:
    int mySqrt(int x) {
        if(x==1) return 1;
        //x = [2,3]都不会进入循环直接返回r=1
        //x>=4 进入循环不会影响
        int l=2,r=x/2;
        while(l<=r){
            //mid*mid容易溢出
            long long mid = l + ((r - l) >> 1);
            if(mid*mid==x) return mid;
            else if(mid*mid > x) r = mid-1;
            else l = mid + 1;
        }
        return r;
    }
};



