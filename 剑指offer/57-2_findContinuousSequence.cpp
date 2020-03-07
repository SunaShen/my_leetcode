// @File   : 57-2_findContinuousSequence.cpp
// @Source : https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof/
// @Title  : 面试题57 - II. 和为s的连续正数序列
// @Auther : sun_ds
// @Date   : 2020/3/6

/**  题目描述：
    输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。

    序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。

     

    示例 1：

    输入：target = 9
    输出：[[2,3,4],[4,5]]
    示例 2：

    输入：target = 15
    输出：[[1,2,3,4,5],[4,5,6],[7,8]]
     

    限制：

    1 <= target <= 10^5

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/he-wei-sde-lian-xu-zheng-shu-xu-lie-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.双指针
 *  双指针指向区间的左右。并用等差数列求和公式求和。
 *      若sum < target时，继续添加后续元素，使得sum更大，r++。
 *      当sum > target时，最小的元素出去，l--，直到不满足sum > target。
 *      当sum == target时，当前队列中的序列满足条件，存储，并l--。继续下面的循环。
 *  结束标志l==r。即序列中空了。
 * 2.队列
 *  使用队列存储连续正整数序列。并使用sum统计队列中各元素的和。
 *      当sum < target时，继续添加后续元素，使得sum更大，也即是更接近target。
 *      当sum > target时，最小的元素依次出队，直到不满足sum > target。
 *      当sum == target时，当前队列中的序列满足条件，存储，并将队首出队。继续下面的循环。
 *  循环结束标志为index<=(target/2+1)，由于是连续正整数序列并且至少包含两个数，所以若入队了index>(target/2+1)，
 *  它和他前面一个数的和一定大于target了。所以没必要继续计算了。
 *
 *
 *
 */

//双指针
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>>vec;
        vector<int> res;
        for (int l = 1, r = 2; l < r;){
            int sum = (l + r) * (r - l + 1) / 2;
            if (sum == target){
                res.clear();
                for (int i = l; i <= r; ++i) res.push_back(i);
                vec.push_back(res);
                l++;
            }
            else if (sum < target) r++;
            else l++;
        }
        return vec;
    }
};

//队列
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        if(target<3) return {};
        vector<vector<int>> res;
        int sum = 0;
        deque<int> q;
        int index = 0;
        while(index<=(target/2+1)){
            if(sum==target){
                vector<int> temp(q.cbegin(),q.cend());
                res.push_back(temp);
                sum -= q.front();
                q.pop_front();
            }else if(sum > target){
                while(sum>target){
                    sum -= q.front();
                    q.pop_front();
                }
            }else{
                index++;
                sum += index;
                q.push_back(index);
            }
        }
        return res;
    }
};



