// @File   : 1300_findBestValue.cpp
// @Source : https://leetcode-cn.com/problems/sum-of-mutated-array-closest-to-target/
// @Title  : 1300. 转变数组后最接近目标值的数组和
// @Auther : sun_ds
// @Date   : 2020/6/14

/**  题目描述：
    给你一个整数数组 arr 和一个目标值 target ，请你返回一个整数 value ，使得将数组中所有大于 value 的值变成 value 后，数组的和最接近  target （最接近表示两者之差的绝对值最小）。

    如果有多种使得和最接近 target 的方案，请你返回这些整数中的最小值。

    请注意，答案不一定是 arr 中的数字。

     

    示例 1：

    输入：arr = [4,9,3], target = 10
    输出：3
    解释：当选择 value 为 3 时，数组会变成 [3, 3, 3]，和为 9 ，这是最接近 target 的方案。
    示例 2：

    输入：arr = [2,3,5], target = 10
    输出：5
    示例 3：

    输入：arr = [60864,25176,27249,21296,20204], target = 56803
    输出：11361
     

    提示：

    1 <= arr.length <= 10^4
    1 <= arr[i], target <= 10^5

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/sum-of-mutated-array-closest-to-target
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.排序+遍历
 *  arr 升序排列
 *  sum 记录当前位置前的和
 *  int temp = (double)(target - sum) / (n - i) + 0.5 - 1e-9;
 *  当前值大于平均值时，将后面所有值换成 temp 则最接近 target ，符合题目要求。
 *  需要决定上取整还是下取整，使用 + 0.5 四舍五入。但是当 = 0.5 时，此时上取整下取整效果一样，但是题目要求取小的，所以 - 1e-9
 *
 *
 */

class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
        int n = arr.size();
        sort(arr.begin(),arr.end());
        int sum=0;
        for(int i=0;i<n;i++){
            // 决定上取整还是下取整
            // 使用 + 0.5 四舍五入。但是当 = 0.5 时，此时上取整下取整效果一样，但是题目要求取小的，所以 - 1e-9
            int temp = (double)(target - sum) / (n - i) + 0.5 - 1e-9;
            if(temp < arr[i]){
                return temp;
            }
            sum += arr[i];
        }
        return arr[n-1];
    }
};
