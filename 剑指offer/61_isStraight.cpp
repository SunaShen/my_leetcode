// @File   : 61_isStraight.cpp
// @Source : https://leetcode-cn.com/problems/bu-ke-pai-zhong-de-shun-zi-lcof/
// @Title  : 面试题61. 扑克牌中的顺子
// @Auther : sun_ds
// @Date   : 2020/4/6

/**  题目描述：
    从扑克牌中随机抽5张牌，判断是不是一个顺子，即这5张牌是不是连续的。2～10为数字本身，A为1，J为11，Q为12，K为13，而大、小王为 0 ，可以看成任意数字。A 不能视为 14。

     

    示例 1:

    输入: [1,2,3,4,5]
    输出: True
     

    示例 2:

    输入: [0,0,1,2,5]
    输出: True
     

    限制：

    数组长度为 5 

    数组的数取值为 [0, 13] .

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/bu-ke-pai-zhong-de-shun-zi-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.排序
 * 忽略大小王。每两个数字之间的空洞为 temp[i] - temp[i-1] - 1. 其中i和i-1位置都是除大小王外的数字
 * 记录大小王个数，看够不够填充空洞的。
 *
 * 其次。如果有除大小王之外的重复数字，则肯定不满足顺子。
 *
 * 2.不排序
 * 5连顺子特性。最大值-最小值+1 = 5;
 * 找到最大值和最小值(不包括王=0)，计算 最大值-最小值+1
 * 若 最大值-最小值+1 > 5 肯定不能完成顺子
 * 若 最大值-最小值+1 <=5 可以构成顺子。 小于5的用0填充位置到5
 *
 * 除此之外，还要排除有重复数字的情况。若出现除了王之外的重复数字，一定不满足
 *
 *
 */



//丑陋的代码
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        vector<int> bucket(14,0);
        vector<int> temp;
        //计数排序
        for(auto i:nums) bucket[i]++;
        for(int i=0;i<14;i++){
            while(bucket[i]!=0){
                temp.push_back(i);
                bucket[i]--;
            }
        }
        int jocker=0;
        bool first = false;
        int old = 0;
        for(int i=0;i<5;i++){
            if(temp[i]==0){
                jocker++;
            }else{
                if(!first){
                    old = temp[i];
                    first = true;
                }else{
                    //有重复数字 肯定不满足
                    if(temp[i] == old) return false;
                    int a = temp[i] - old - 1;
                    old = temp[i];
                    if(jocker >= a){
                        jocker -= a;
                    }else{
                        // 大小王不够填充，不满足
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

//排序
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int jocker = 0 ;
        for(int i=0;i<4;i++){
            if(nums[i]==0){
                jocker++;
            }else{
                //有重复数字
                if(nums[i]==nums[i+1]) return false;
                //空洞大小
                int c = nums[i+1] - nums[i] - 1;
                //王是否能补偿空洞
                if(jocker>=c) jocker-=c;
                else return false;
            }
        }
        return true;
    }
};

//不排序
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        vector<bool> m(14,false);    //统计重复数字
        int max_card = INT_MIN;
        int min_card = INT_MAX;
        for(auto i:nums){
            if(i==0) continue; //不统计王
            if(m[i]) return false; //遇到重复数字了。
            m[i]=true;
            max_card = max(max_card,i);
            min_card = min(min_card,i);
        }
        return max_card - min_card + 1 <= 5;
    }
};


