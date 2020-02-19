// @File   : 1346_checkIfExist.cpp
// @Source : https://leetcode-cn.com/problems/check-if-n-and-its-double-exist/
// @Title  : 检查整数及其两倍数是否存在
// @Auther : sun_ds
// @Date   : 2020/2/17

/**  题目描述：
    给你一个整数数组 arr，请你检查是否存在两个整数 N 和 M，满足 N 是 M 的两倍（即，N = 2 * M）。

    更正式地，检查是否存在两个下标 i 和 j 满足：

    i != j
    0 <= i, j < arr.length
    arr[i] == 2 * arr[j]
     

    示例 1：

    输入：arr = [10,2,5,3]
    输出：true
    解释：N = 10 是 M = 5 的两倍，即 10 = 2 * 5 。
    示例 2：

    输入：arr = [7,1,14,11]
    输出：true
    解释：N = 14 是 M = 7 的两倍，即 14 = 2 * 7 。
    示例 3：

    输入：arr = [3,1,7,11]
    输出：false
    解释：在该情况下不存在 N 和 M 满足 N = 2 * M 。
     

    提示：

    2 <= arr.length <= 500
    -10^3 <= arr[i] <= 10^3

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/check-if-n-and-its-double-exist
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 1.暴力法
 *  遍历所有数字，看是否满足2倍关系。(需要判断i!=j)
 *
 * 2.双指针
 *  利用2倍关系特性，移动双指针。直到找到满足2倍的情况。
 *
 * 3.map
 *  各数次出现的次数存在map中，再依次查找2倍数字是否在，且对于特殊数字0需要满足至少有2个。
 *
 */

//暴力法
class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        for(int i=0;i<arr.size();i++){
            for(int j=0;j<arr.size();j++){
                if(i == j) continue;
                if(arr[i] == 2 * arr[j]) return true;
            }
        }
        return false;
    }
};


//双指针
class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int p1=0, p2=0;
        while(p1<n&&p2<n){
            if((arr[p2] == 2*arr[p1])&&(p1!=p2)){
                return true;
            }else if(arr[p2] < 2*arr[p1]){
                ++p2;
            }else{
                ++p1;
            }
        }
        return false;
    }
};

//map
class Solution {
public:
    bool checkIfExist(vector<int>& arr) {
        int n = arr.size();
        map<int,int> m;
        m.clear();
        for(int i=0;i<n;i++){
            m[arr[i]]++;
        }
        for(int i=0;i<n;i++){
            if(arr[i] == 0){
                if(m[2*arr[i]] > 1) return true;
            }else{
                if(m[2*arr[i]] > 0) return true;
            }
        }
        return false;
    }
};

