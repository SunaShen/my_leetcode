// @File   : 1207_uniqueOccurrences.cpp
// @Source : https://leetcode-cn.com/problems/unique-number-of-occurrences/
// @Title  : 独一无二的出现次数
// @Auther : sun_ds
// @Date   : 2019/10/17

/*  题目描述：
    给你一个整数数组 arr，请你帮忙统计数组中每个数的出现次数。

    如果每个数的出现次数都是独一无二的，就返回 true；否则返回 false。

     

    示例 1：

    输入：arr = [1,2,2,1,1,3]
    输出：true
    解释：在该数组中，1 出现了 3 次，2 出现了 2 次，3 只出现了 1 次。没有两个数的出现次数相同。
    示例 2：

    输入：arr = [1,2]
    输出：false
    示例 3：

    输入：arr = [-3,0,1,-3,1,1,1,-3,10,0]
    输出：true
     

    提示：

    1 <= arr.length <= 1000
    -1000 <= arr[i] <= 1000

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/unique-number-of-occurrences
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 统计各数字出现次数，出现次数各不相同返回true，否则false
 *
 * 1.使用map统计各数字出现次数，既而各出现次数查看是否相同
 * 2.使用数组(数据量不大)，节省构建map等等的时间，速度更快
 *
 *
 * 注意:
 * 针对数据量较小的数字统计，用数组更快。
 */



//麻烦
//class Solution {
//public:
//    bool uniqueOccurrences(vector<int>& arr) {
//        int n = arr.size();
//        map<int,int> m;
//        m.clear();
//        for(auto i:arr) m[i]++;
//        vector<int> r;
//        for(auto i:m){
//            vector<int>::iterator iter = find(r.begin( ), r.end( ),i.second);
//            if(iter == r.end()) //没找到
//                r.push_back(i.second);
//            else
//                return false;
//        }
//        return true;
//    }
//};

//直接用数组操作
class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        int cnt1[2050] = {0};
        int cnt2[1050] = {0};
        memset(cnt1,0,sizeof(cnt1));
        memset(cnt2,0,sizeof(cnt2));
        for(auto i:arr) cnt1[i+1000]++;
        for(auto j:cnt1) cnt2[j]++;
        //注意不能从k=0，开始，英文cnt2中好多0哇。
        for(int k=1;k<=1000;k++) if(cnt2[k]>1) return false;
        return true;
    }
};