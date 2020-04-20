// @File   : 66_constructArr.cpp
// @Source : https://leetcode-cn.com/problems/gou-jian-cheng-ji-shu-zu-lcof/
// @Title  : 面试题66. 构建乘积数组
// @Auther : sun_ds
// @Date   : 2020/4/10

/**  题目描述：
    给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，其中 B 中的元素 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

     

    示例:

    输入: [1,2,3,4,5]
    输出: [120,60,40,30,24]
     

    提示：

    所有元素乘积之和不会溢出 32 位整数
    a.length <= 100000


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/gou-jian-cheng-ji-shu-zu-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 使用两个数组保存，当前位置左边和右边的乘积。
 * 则当前位置的值为left[i]*right[i]
 *
 * 可以节省一个数组，在最终遍历的时候用一个变量代替。
 *
 *
 */


//使用两个数组
class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        int n = a.size();
        vector<int> left(n,1);
        vector<int> right(n,1);
        vector<int> b(n,0);
        for(int i=1;i<n;i++){
            left[i] = left[i-1]*a[i-1];
        }
        for(int i=n-2;i>=0;i--){
            right[i] = right[i+1]*a[i+1];
        }
        for(int i=0;i<n;i++){
            b[i] = left[i]*right[i];
        }
        return b;
    }
};
//使用一个数组
class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        int n = a.size();
        vector<int> left(n,1);
        vector<int> b(n,0);
        for(int i=1;i<n;i++){
            left[i] = left[i-1]*a[i-1];
        }
        int right=1;
        for(int i=n-1;i>=0;i--){
            b[i] = left[i]*right;
            right *= a[i];
        }
        return b;
    }
};


