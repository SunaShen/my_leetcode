// @File   : 46_translateNum.cpp
// @Source : https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof/
// @Title  : 面试题46. 把数字翻译成字符串
// @Auther : sun_ds
// @Date   : 2020/3/28

/**  题目描述：
    给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。

     

    示例 1:

    输入: 12258
    输出: 5
    解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"
     

    提示：

    0 <= num < 231

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/ba-shu-zi-fan-yi-cheng-zi-fu-chuan-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.递归(字符串)
 *  转成字符串，使用substr截取后面字符串继续递归
 *  当字符串为空，记录为一种分类方法。
 *  递归截取一位字符，当做翻译。
 *  或者递归截取二位字符，即当前字符为1且后面还有字符或者当前字符为2且后面字符小于6，则可以组成两位数继续递归。
 * 2.递归(整数)
 *
 * 3.动态规划
 *  dp[i] = dp[i-1] + dp[i-2]
 *  dp[i-2]要判断可不可以分成两位数翻译
 *
 */

class Solution {
public:
    int res = 0;
    void dfs(string num){
        if(num.empty()){
            res++;
            return;
        }
        dfs(num.substr(1));
        if(num.size()>1&&(num[0]=='1'||(num[0]=='2'&&num[1]>='0'&&num[1]<='5')))
            dfs(num.substr(2));
    }
    int translateNum(int num) {
        dfs(to_string(num));
        return res;
    }
};

class Solution {
public:
    int translateNum(int num) {
        if(num<9) return 1;
        int temp = num%100;
        //分成只能一位翻译和可以1位或两位翻译 两种情况
        if(temp<=9||temp>=26) return translateNum(num/10);
        else return translateNum(num/10) + translateNum(num/100);
    }
};

class Solution {
public:
    int translateNum(int num) {
        string nums = to_string(num);
        vector<int> dp(nums.size()+1,0);//数组中存储的是前i个字符翻译的个数
        dp[0] = 1;//认为空字符串也可以翻译一种

        for(auto i = 1;i <= nums.size();i++)
        {
            //当前字符单独翻译时
            if(nums[i-1] >= '0' && nums[i-1] <= '9')
                dp[i] = dp[i] + dp[i-1];
            //当前字符和前一个字符组合翻译时
            if(i > 1)
            {
                int temp = (nums[i-2] - '0') * 10 + (nums[i-1] - '0');
                if(temp >= 10 && temp <= 25)
                    dp[i] = dp[i] + dp[i-2];
            }
        }
        return dp[nums.size()];
    }
};

