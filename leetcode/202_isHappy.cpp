// @File   : 202_isHappy.cpp
// @Source : https://leetcode-cn.com/problems/happy-number/
// @Title  : 202. 快乐数
// @Auther : sun_ds
// @Date   : 2020/4/30

/**  题目描述：
    编写一个算法来判断一个数 n 是不是快乐数。

    「快乐数」定义为：对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和，然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。如果 可以变为  1，那么这个数就是快乐数。

    如果 n 是快乐数就返回 True ；不是，则返回 False 。

     

    示例：

    输入：19
    输出：true
    解释：
    12 + 92 = 82
    82 + 22 = 68
    62 + 82 = 100
    12 + 02 + 02 = 1

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/happy-number
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 循环计算各个位置上数字的平方和，若平方和为1，该数为快乐数，返回true。
 * 否则，进行无限循环的数不是快乐数，返回false。
 * 核心思想，无限循环 == 有环
 * 原因：对于int来说，最大的n为‭‭214748364，则平方和最大的数为1999999999，其平方和为1+81*9=724.
 *      即表明，int范围内的任何数的平方和都在0~724之间，为一个有限的数字。
 *      若不是快乐数进行无限的循环下去，则必定存在环(之前经过的数，再次经过)。
 *
 * 1.set记录经过的数
 *   循环计算数字各个位置上的平方和，若平方和为1，则返回true。
 *   否则继续。
 *   若之前经过过这个数，再次经过，那么将形成环，该数一定不是快乐数。返回false。
 *
 * 2.快慢指针
 *   将724个数看做链表上的各个节点，相互转移，从n节点出发，判断之间有没有环。
 *   快指针每次走两部，慢指针每次走一步。
 *   若快指针的值==慢指针的值，且值不为1则表示有环返回false，若值为1则表示是快乐数返回true。
 *
 *
 *
 */


class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> s;
        s.insert(n);
        while(n){
            int temp = 0;
            while(n){
                temp += (n%10)*(n%10);
                n /= 10;
            }
            if(temp == 1) return true;
            //判断当前值是否出现过，若出现过会造成环(死循环)，直接返回false。
            if(s.count(temp)) return false;
            s.insert(temp);
            n = temp;
        }
        return false;
    }
};
class Solution {
public:
    int squareSum(int n){
        int sum = 0;
        while(n){
            int bit = n%10;
            sum += bit*bit;
            n /= 10;
        }
        return sum;
    }
    bool isHappy(int n) {
        int slow = n;
        int fast = squareSum(n);
        while(slow!=fast){
            slow = squareSum(slow);
            fast = squareSum(squareSum(fast));
        }
        return slow == 1;
    }
};


