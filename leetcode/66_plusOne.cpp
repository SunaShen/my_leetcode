// @File   : 66_plusOne.cpp
// @Source : https://leetcode-cn.com/problems/plus-one/
// @Title  : 加一
// @Auther : sun_ds
// @Date   : 2019/9/4


/*  题目描述：
    给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。

    最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

    你可以假设除了整数 0 之外，这个整数不会以零开头。

    示例 1:

    输入: [1,2,3]
    输出: [1,2,4]
    解释: 输入数组表示数字 123。
    示例 2:

    输入: [4,3,2,1]
    输出: [4,3,2,2]
    解释: 输入数组表示数字 4321。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/plus-one
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 数字一位一位的存储在vector中，实现对该数字的+1操作
 * 主要考虑进位，以及vector长度
 *
 * 对于长度超限的使用*条件表达式*判断
 * 进位与长度统一决定循环的条件，并是或的关系！
 * 很多存储在string，vector中的数值进行运算，都采用类似的格式。
 *
 * 注意：
 * vector不能使用负的索引进行反向索引。
 * 如，vector<int> nums; nums[-1]并不是倒数第一个值！！！
 *
 *
 */


#include <iostream>
#include <vector>

using namespace std;





// version 0.1

//class Solution {
//public:
//    vector<int> plusOne(vector<int>& digits) {
//        int c = 1, i = digits.size();
//        vector<int> res;
//
//        while(c!=0)
//        {
//            i--;
//            c = i<0 ? 0:(digits[i]+1)/10;
//            res.insert(res.begin(), i<0 ? 1:(digits[i]+1)%10);
//        }
//        if(i>0)
//        {
//            res.insert(res.begin(), digits.begin(), digits.begin() + i);
//        }
//        return res;
//    }
//};


//version 0.2
//4ms

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int c = 1, i = digits.size();
        vector<int> res;
        while(c!=0 || i>0)
        {
            i--;
            res.insert(res.begin(), i<0 ? 1:(digits[i]+c)%10);
            c = i<0 ? 0:(digits[i]+c)/10;
        }
        return res;
    }
};

// 精选题解
// 1.加1后该位不为0，即没进位，直接return。
// 2.加1后该位为0，继续。直到循环结束还没return，那该数必为99,999或9999.返回，100，1000，10000.
// 8ms

//class Solution {
//public:
//    vector<int> plusOne(vector<int>& digits) {
//        for(int i = digits.size()-1; i>=0; i--)
//        {
//            digits[i]++;
//            digits[i] = digits[i]%10;
//            if(digits[i] != 0)
//                return digits;
//        }
//        vector<int> res(digits.size() + 1);
//        res[0] = 1;
//        return res;
//    }
//};





int main()
{
    vector<int> nums = {9, 8, 9, 9};

    Solution su;
    auto res = su.plusOne(nums);

    for(auto iter=res.begin();iter!=res.end();iter++)
    {
        cout<< *iter << ",";
    }
    cout << endl;
    cout << "finish" << endl;
    return 0;
}