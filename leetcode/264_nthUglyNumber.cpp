// @File   : 264_nthUglyNumber.cpp
// @Source : https://leetcode-cn.com/problems/ugly-number-ii/
// @Title  : 丑数 II
// @Auther : sun_ds
// @Date   : 2020/1/17

/**  题目描述：
    编写一个程序，找出第 n 个丑数。

    丑数就是只包含质因数 2, 3, 5 的正整数。

    示例:

    输入: n = 10
    输出: 12
    解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
    说明:  

    1 是丑数。
    n 不超过1690。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/ugly-number-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 输出第n个丑数
 *
 *
 *  下一个丑数等于之前的丑数*2，3，5得到。
 *  因此，为了生成后面的丑数，需要将之前的每个丑数都分别乘2，3，5。
 *  循环下去，即可得到所有的丑数。
 *  但是直接这样每个数乘以2，3，5的话，里面的丑数不满足递增的条件。
 *  但为了得到第n个丑数，需要加入的次序满足递增。
 *
 *  因此，分别维护三个队列or指针。分别保存着未被2，3，5乘的当前位置之前的丑数。
 *  且有转移方程。 dp[i] = min(2 * dp[l_2], 3 * dp[l_3], 5 * dp[l_5])
 *
 *  也可使用最小堆维持有序性。
 *
 * 1.三队列
 *  使用队列存储未被2，3，5乘的当前位置之前的丑数
 *  dp[l_2], dp[l_3], dp[l_5]为各队列的队头。
 *  若此次dp[i]选中了各队头，则该队列出队。
 *  所有队列将dp[i]入队，等待后续乘2，3，5
 *  直到完成for循环，得到第n个丑数。
 *
 *  速度慢。。应该使用三指针。
 *
 *
 * 2.三指针
 *  使用vector存储前n各丑数。
 *  并设l_2，l_3，l_5三个指针代表未被乘2，3，5的位置。
 *  若dp[i]选中了各指针位置的丑数，则指针后移一位。
 *  循环。
 *  直到完成for循环，得到所有的前n个丑数。
 *
 *
 *
 * 3.最小堆
 *  当前位置前的丑数依次乘2，3，5并加入堆中。
 *  从堆顶依次取一个数。取n次，即得到第n个丑数。
 *
 */

//三队列
class Solution {
public:
    int nthUglyNumber(int n) {
        queue<int> q1,q2,q3;
        q1.push(1);
        q2.push(1);
        q3.push(1);
        int temp=1;
        for(int i=1;i<n;++i){
            int t1=q1.front()*2;
            int t2=q2.front()*3;
            int t3=q3.front()*5;
            temp = min(t1,min(t2,t3));
            //不能if else 防止重复计算丑数 如 2*3 和 3*2
            if(temp == t1) q1.pop();
            if(temp == t2) q2.pop();
            if(temp == t3) q3.pop();
            q1.push(temp);
            q2.push(temp);
            q3.push(temp);
        }
        return temp;
    }
};



//三指针
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> temp{1};
        int q1=0,q2=0,q3=0;
        int t1,t2,t3,t;
        for(int i=1;i<n;++i){
            t1=temp[q1]*2;
            t2=temp[q2]*3;
            t3=temp[q3]*5;
            t = min(t1,min(t2,t3));
            //不能if else  防止重复计算丑数 如 2*3 和 3*2
            if(t == t1) q1++;
            if(t == t2) q2++;
            if(t == t3) q3++;
            temp.push_back(t);
        }
        return temp[n-1];
    }
};