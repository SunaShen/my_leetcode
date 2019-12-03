// @File   : 18_fourSum.cpp
// @Source : https://leetcode-cn.com/problems/4sum/
// @Title  : 四数之和
// @Auther : sun_ds
// @Date   : 2019/11/7

/*  题目描述：
    给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

    注意：

    答案中不可以包含重复的四元组。

    示例：

    给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。

    满足要求的四元组集合为：
    [
      [-1,  0, 0, 1],
      [-2, -1, 1, 2],
      [-2,  0, 0, 2]
    ]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/4sum
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/




/*
 * 四数之和
 * 类似15.三数之和
 *
 * 排序
 * 两层for循环加双指针
 *
 * 多利用元素的顺序特征
 * 判断当前元素是否与上一元素相同，若相同则跳过。
 * 优化
 * 判断本次最大和最小值，若不符合直接continue跳过。
 *
 */



#include <iostream>
#include <vector>


using namespace std;

//class Solution {
//public:
//    vector<vector<int>> fourSum(vector<int>& nums, int target) {
//        int n = nums.size();
//        sort(nums.begin(),nums.end());
//        vector<vector<int>> ans;
//        for(int i=0;i<n-3;++i){
//            if(i>0&&nums[i]==nums[i-1]) continue;
//            for(int j=i+1;j<n-2;++j){
//                if(j>i+1&&nums[j]==nums[j-1]) continue;
//                int k = j+1, m = n-1;
//                while(k<m){
//                    int sum = nums[i] + nums[j] + nums[k] + nums[m];
//                    if(sum == target){
//                        ans.push_back({nums[i],nums[j],nums[k],nums[m]});
//                        k = k + 1; m = m - 1;
//                        while(k<m&&nums[k] == nums[k-1]) ++k;
//                        while(m>k&&nums[m] == nums[m+1]) --m;
//                    }else if(sum < target){
//                        ++k;
//                        while(k<m&&nums[k] == nums[k-1]) ++k;
//                    }else{
//                        --m;
//                        while(m>k&&nums[m] == nums[m+1]) --m;
//                    }
//                }
//            }
//        }
//        return ans;
//    }
//};


//注意剪枝？？？？
class Solution {
public:
    vector <vector<int>> fourSum(vector<int> &nums, int target) {
        vector <vector<int>> ans;
        int n = nums.size();
        if (n < 4) return ans;

        sort(nums.begin(), nums.end());
        vector<int> tmp;

        // 从第 i 位开始寻找 4 个数的组合
        for (int i = 0; i < n - 3; i++) { // i 的值最大只能为 n - 4，即倒数第 4 位
            // 4 个数不允许重复，所以如果当前第 1 个数与之前的相同则跳过
            if (i > 0 && nums[i - 1] == nums[i])
                continue;

            // 若从第 i 位开始的最小的数字组合都比 target 大，找不到满足条件的组合，结束循环
            if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
                break;

            // 若从第 i 位开始的最大的数字组合都比 target 小，找不到满足条件的组合，结束循环
            if (nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target)  // smallest sum for j
                continue;

            // 从第 j 位开始寻找 3 个数的组合
            for (int j = i + 1; j < n - 2; j++) { // j 的值最大只能为 n - 3，即倒数第 3 位
                // 4 个数不允许重复，所以如果当前第 2 个数与之前的相同则跳过
                if (j > i + 1 && nums[j - 1] == nums[j])
                    continue;

                // 若从第 i 位开始的最大的数字组合都比 target - nums[i] 大，找不到满足条件的组合，结束循环
                if (nums[j] + nums[j + 1] + nums[j + 2] > target - nums[i])
                    break;

                // 若从第 i 位开始的最大的数字组合都比 target - nums[i] 小，找不到满足条件的组合，结束循环
                if (nums[j] + nums[n - 2] + nums[n - 1] < target - nums[i])
                    continue;

                int l = j + 1;
                int r = n - 1;

                int tmp = target - nums[i] - nums[j];

                while (l < r) {
                    int sum = nums[l] + nums[r];
                    if (sum == tmp) {
                        ans.push_back({nums[i], nums[j], nums[l], nums[r]});
                        do { l++; } while (l < r && nums[l] == nums[l - 1]);
                        do { r--; } while (l < r && nums[r] == nums[r + 1]);
                    } else if (sum < tmp) {
                        l++;
                    } else {
                        r--;
                    }
                }
            }
        }
        return ans;
    }
};



int main(int argc, char * argv[])
{
    vector<int> num{-1,2,2,-5,0,-1,4};
    Solution su;
    auto res = su.fourSum(num,3);
    for(auto k : res){
        for(auto j:k){
            cout << j << " ";
        }
        cout << endl;
    }
    return 0;
}


