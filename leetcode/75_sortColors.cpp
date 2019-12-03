// @File   : 75_sortColors.cpp
// @Source : https://leetcode-cn.com/problems/sort-colors/
// @Title  : 颜色分类
// @Auther : sun_ds
// @Date   : 2019/11/19

/**  题目描述：
    给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

    此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

    注意:
    不能使用代码库中的排序函数来解决这道题。

    示例:

    输入: [2,0,2,1,1,0]
    输出: [0,0,1,1,2,2]
    进阶：

    一个直观的解决方案是使用计数排序的两趟扫描算法。
    首先，迭代计算出0、1 和 2 元素的个数，然后按照0、1、2的排序，重写当前数组。
    你能想出一个仅使用常数空间的一趟扫描算法吗？

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/sort-colors
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/** 颜色分类
 * 将是三个数字排序？聚成三类
 *
 * 1.计数加重写
 *   统计0，1，2三个数字出现的次数，并依次重写
 *
 * 2.三指针
 *   使用三个指针，p1指向元素左边全为0，p2指针指向元素右边全为2，curr指向当前检测元素
 *   若nums[curr]==0  swap(nums[curr],nums[p1]); ++curr; ++p1;
 *   若nums[curr]==2  swap(nums[curr],nums[p2]); --p2;
 *   若nums[curr]==1  ++curr;
 *
 *   注意:
 *   在nums[curr]==0 时，curr与p1位置元素交换。由于p1在curr左边，所以nums[p1]被扫描过，故交还给curr时，++curr跳过
 *   在nums[curr]==2 时，curr与p2位置原色交换。由于p2在curr右边，所以nums[p2]未被扫描过，故交还给curr时，curr需检测。故不用++curr。
 *
 * 3.快排思想
 *   两次遍历
 *   第一次遍历，将nums[i]==0的都放到左边
 *   第二次遍历，将nums[j]==2的都放到右边
 *  类似分两步的三指针。
 *
 *
 */

//基础方法，计数加重写
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int cnt[3] = {0};
        for(auto i:nums) ++cnt[i];
        nums.clear();
        for(int i=0;i<3;++i){
            for(int j=0;j<cnt[i];++j){
                nums.push_back(i);
            }
        }
    }
};

//荷兰国旗问题
//三指针 复杂度O(n)
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int p1 = 0, curr = 0;
        int p2 = nums.size() - 1;
        int tmp = 0;
        while(curr<=p2){
            if(nums[curr]==0){
                tmp = nums[p1];
                nums[p1] = nums[curr];
                nums[curr] = tmp;
                ++p1;
                ++curr;
            }else if(nums[curr]==2){
                tmp = nums[p2];
                nums[p2] = nums[curr];
                nums[curr] = tmp;
                --p2;
            }else{
                ++curr;
            }
        }
    }
};