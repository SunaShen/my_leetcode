// @File   : 1_twoSum.cpp
// @Source : https://leetcode-cn.com/problems/two-sum/
// @Title  : 两数之和
// @Auther : sun_ds
// @Date   : 2019/9/3

/*  题目描述：
    给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

    你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

    示例:

    给定 nums = [2, 7, 11, 15], target = 9

    因为 nums[0] + nums[1] = 2 + 7 = 9
    所以返回 [0, 1]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/two-sum
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/



/*
 *
 * 使用键值对形式
 * 1.用2层for循环，先加入map，在遍历find，需要考虑不能find到自己本身
 * 2.用1层for循环，直接find，没有再加入map
 *
 *
 *
 * map与unordered_map的区别：
 * map由红黑树实现，默认按照键值排序的
 * unordered_map由hash实现，无序的
 *
 * 对顺序有要求选择map,查找问题使用unordered_map
 *
 * map与unordered_map操作相同
 * 插入：
 * map.insert(make_pair(key,value))
 * 查找：
 * map.find()
 * 未找到，返回值为 map.end()
 *
 *
 */


#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int len = nums.size();
        unordered_map<int, int> log;
        vector<int> res;
        for(int i=0;i<len;i++)
        {
            if(log.find(target-nums[i]) != log.end())
            {
                res.push_back(log[target-nums[i]]);
                res.push_back(i);
                return res;
            }
            log[nums[i]] = i;
//            log.insert(make_pair(nums[i], i));
        }
        return res;
    }
};



int main()
{

    vector<int> nums = {5, 7, 3, 11, 15};
    int target = 10;
    Solution su;
    auto res = su.twoSum(nums, target);

    for(int i=0;i<res.size();i++)
    {
        cout<< res.at(i) << ",";
    }
    cout << endl;

    cout << "finish" << endl;
    return 0;
}



