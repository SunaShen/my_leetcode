// @File   : 15_threeSum.cpp
// @Source : https://leetcode-cn.com/problems/3sum/
// @Title  : 三数之和
// @Auther : sun_ds
// @Date   : 2019/10/31

/*  题目描述：
    给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

    注意：答案中不可以包含重复的三元组。

    例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

    满足要求的三元组集合为：
    [
      [-1, 0, 1],
      [-1, -1, 2]
    ]


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/3sum
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/




/*
 * 三数之和
 * 数组中三个数之和为0.并且不能重复
 *
 * 循环双指针
 *
 * 三数之和为0，必须有正有负或者全为0
 * 首先按照升序将vector排序
 * 固定一个值i，从左向右扫描
 * i的值必须小于等于0.不然0<i<=左<=右,不可能和为0
 * 同时防止i的值重复，在i>0时若i与i-1值相同，则continue
 * 从i到n之间使用双指针选取两个值，向中间收缩，判断必须左<右。
 * 双指针收缩三种情况：
 * 1)若三值之和为0，存入结果, 则左指针++，右指针--。为防止重复，该加加减减必须获得不与当前相同的值，不然就会重复。
 * 2)若三值之和大于0，则右指针--，使整体的和更小。(同时，注意重复，尽量减到一个不同的值，不是也没关系，若是相同值下一次还是执行到此地接着--，直到不同)
 * 3)若三值之和小于0，则左指针++，使整体的和更大。(同时，注意重复，尽量加到一个不同的值，不是也没关系，若是相同值下一次还是执行到此地接着++，直到不同)
 *
 * i循环结束，重新指定左右指针，左=i+1 右=n-1
 *
 */


class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;
        for(int i=0;i<n&&nums[i]<=0;++i){
            if(i>0 && nums[i] == nums[i-1]) continue;
            int j = i + 1, k = n - 1;
            while(j<k){
                int b = nums[j], c = nums[k];
                int temp = nums[i] + b + c;
                if(temp == 0){
                    ans.push_back({nums[i],nums[j],nums[k]});
                    while(++j < n && nums[j]==b);
                    while(--k > i+2 && nums[k]==c);
                }else if(temp < 0){
                    while(++j < n && nums[j]==b);
                }else if(temp > 0){
                    while(--k > i+2 && nums[k]==c);
                }
            }
        }
        return ans;
    }
};


class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        vector<vector<int>> ans;
        for(int i=0;i<n - 2&&nums[i]<=0;++i){
            //防止重复
            if(i>0 && nums[i] == nums[i-1]) continue;
            int j = i + 1, k = n - 1;
            while(j<k){
                int temp = nums[i] + nums[j] + nums[k];
                if(temp == 0){
                    ans.push_back({nums[i],nums[j],nums[k]});
                    //防止重复，必须do到值变了才行。
                    do{
                        ++j;
                    }while(j < k && nums[j]==nums[j-1]);
                    do{
                        --k;
                    }while(k > j && nums[k]==nums[k+1]);
                }else if(temp < 0){
                    //只用++j也可，若值相同还是会进来的，会一直加到不进来。
                    // ++j;
                    do{
                        ++j;
                    }while(j < n && nums[j]==nums[j-1]);
                }else if(temp > 0){
                    //只用--k也可，若值相同还是会进来的，会一直加到不进来。
                    // --k;
                    do{
                        --k;
                    }while(k > n - 2 && nums[k]==nums[k+1]);
                }
            }
        }
        return ans;
    }
};