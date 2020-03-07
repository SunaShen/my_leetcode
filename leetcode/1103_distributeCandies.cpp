// @File   : 1103_distributeCandies.cpp
// @Source : https://leetcode-cn.com/problems/distribute-candies-to-people/
// @Title  : 1103. 分糖果 II
// @Auther : sun_ds
// @Date   : 2020/3/5

/**  题目描述：
    排排坐，分糖果。

    我们买了一些糖果 candies，打算把它们分给排好队的 n = num_people 个小朋友。

    给第一个小朋友 1 颗糖果，第二个小朋友 2 颗，依此类推，直到给最后一个小朋友 n 颗糖果。

    然后，我们再回到队伍的起点，给第一个小朋友 n + 1 颗糖果，第二个小朋友 n + 2 颗，依此类推，直到给最后一个小朋友 2 * n 颗糖果。

    重复上述过程（每次都比上一次多给出一颗糖果，当到达队伍终点后再次从队伍起点开始），直到我们分完所有的糖果。注意，就算我们手中的剩下糖果数不够（不比前一次发出的糖果多），这些糖果也会全部发给当前的小朋友。

    返回一个长度为 num_people、元素之和为 candies 的数组，以表示糖果的最终分发情况（即 ans[i] 表示第 i 个小朋友分到的糖果数）。

     

    示例 1：

    输入：candies = 7, num_people = 4
    输出：[1,2,3,1]
    解释：
    第一次，ans[0] += 1，数组变为 [1,0,0,0]。
    第二次，ans[1] += 2，数组变为 [1,2,0,0]。
    第三次，ans[2] += 3，数组变为 [1,2,3,0]。
    第四次，ans[3] += 1（因为此时只剩下 1 颗糖果），最终数组变为 [1,2,3,1]。
    示例 2：

    输入：candies = 10, num_people = 3
    输出：[5,2,3]
    解释：
    第一次，ans[0] += 1，数组变为 [1,0,0]。
    第二次，ans[1] += 2，数组变为 [1,2,0]。
    第三次，ans[2] += 3，数组变为 [1,2,3]。
    第四次，ans[0] += 4，最终数组变为 [5,2,3]。
     

    提示：

    1 <= candies <= 10^9
    1 <= num_people <= 1000


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/distribute-candies-to-people
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 循环分配糖果
 *
 * 1.暴力法
 * 循环分配，一直到没有糖果。
 *
 * 2.公式法
 * 分配的糖果1，2，3，4，5....是个等差数列。
 * 假设分配了完整的p次。则 p(p+1)/2 <= candies 并且 candies - p(p+1)/2 < p+1 (不够下一次完整分)
 * 通过不等式可以求出，sqrt(2*candies+1/4)-3/2<p<=sqrt(2*candies+1/4)-1/2 该区间长度为1，且p必为整数，所以区间内的整数即为p
 * p = (int)(sqrt(2*candies+1/4)-1/2) 向下取整
 * 每人被分配的次数 rows = p/num_people;(不含最后一行) 最后一个获得完整分配的后面一个序号 col = p%num_people;
 * 最后一次完整分配后剩下的 r = (int)(candies - 0.5*p*(p+1));总数-完整分配的。
 *
 * 每个位置分配到的糖果数也符合等差数列，公差为num_people.
 * 所以不含最后一行，每个位置分配到的糖果数为 (i+1)*rows + num_people*(int)(rows*(rows-1)*0.5)  i从0开始的，而第一个位置为1.
 * 判断i<col，若满足条件，表示最后一行分陪给当前位置了，当前位置糖果数需要加 i+1 + r*num_people
 * 而第i==col个，需要补上剩下的不完整分配的糖果数r
 *
 * 最终得到结果
 *
 *
 *
 */


//暴力法
class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> res(num_people,0);
        int i=0;
        while(candies!=0){
            res[i%num_people] += min(candies,i+1);
            candies -= min(candies,i+1);
            i++;
        }
        return res;
    }
};

//公式法
class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        int p = (int)(sqrt(0.5+2*candies)-0.5); //最后一个完成的分到糖数或完成的轮数
        int r = (int)(candies - 0.5*p*(p+1)); //剩余的不够分一次的糖数
        int rows = p/num_people, col = p%num_people;
        vector<int> res(num_people,0);
        //i从0开始，做适当调整
        for(int i=0;i<num_people;i++){
            res[i] = (i+1)*rows + num_people*(int)(rows*(rows-1)*0.5); //等差数列求和
            if(i<col) res[i] += i+1+rows*num_people; //比正常的多一轮
        }
        res[col] += r; //不够的补给下一个
        return res;
    }
};


