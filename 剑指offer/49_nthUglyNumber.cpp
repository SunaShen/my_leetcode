// @File   : 49_nthUglyNumber.cpp
// @Source : https://leetcode-cn.com/problems/chou-shu-lcof/
// @Title  : 面试题49. 丑数
// @Auther : sun_ds
// @Date   : 2020/3/30

/**  题目描述：
    我们把只包含因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。

     

    示例:

    输入: n = 10
    输出: 12
    解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
    说明:  

    1 是丑数。
    n 不超过1690。
    注意：本题与主站 264 题相同：https://leetcode-cn.com/problems/ugly-number-ii/



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/chou-shu-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 使用三个指针q1，q2，q3.
 * q1只乘2，q2只乘3，q3只乘5
 * 每一轮，找最小的加进去，并指针后移一位。
 * 最终得到的第n个即为结果
 *
 * 每一个丑数乘以2，3，5还是一个丑数。
 * 为了保证有序，每一轮选最小的放入vector
 *
 *
 *
 */

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> temp = {1};
        int q1=0,q2=0,q3=0;
        int t1=0,t2=0,t3=0,t=0;
        for(int i=1;i<n;i++){
            t1 = temp[q1]*2;
            t2 = temp[q2]*3;
            t3 = temp[q3]*5;
            t = min(min(t1,t2),t3);
            if(t == t1) q1++;
            if(t == t2) q2++;
            if(t == t3) q3++;
            temp.push_back(t);
        }
        return temp[n-1];
    }
};

