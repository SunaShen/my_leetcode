// @File   : 372_superPow.cpp
// @Source : https://leetcode-cn.com/problems/super-pow/
// @Title  : 超级次方
// @Auther : sun_ds
// @Date   : 2019/10/30

/*  题目描述：
    你的任务是计算 a^b 对 1337 取模，a 是一个正整数，b 是一个非常大的正整数且会以数组形式给出。

    示例 1:

    输入: a = 2, b = [3]
    输出: 8
    示例 2:

    输入: a = 2, b = [1,0]
    输出: 1024

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/super-pow
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 *
 * 超级次方
 * a的b次方，b可能会很大，并且b的各个位数使用vector保存。。(凶残)
 * 值可能很大，因此需要对1337取模
 *
 * 分两步计算
 * 1.首先获得各个位数对应的次方数，即个位对应a^1,十位对应a^10,百位对应a^100……………………
 *   其中 a^1 -> a^10 -> a^100依次获得
 * 2.然后获取b中对应位数上的数字，即得到(a^1)^b[n-1]，(a^10)^b[n-2],(a^100)^b[n-3].
 *   将各个位置的值对应相乘，即的最终结果。res = (a^1)^b[n-1]*(a^10)^b[n-2]*(a^100)^b[n-3]*……
 *
 * 其中包含数的10次方，以及b[i]次方。可以使用循环自己实现，也可以使用快速幂的循环形式。因为次方数<=10，因此差别应该不是很大吧。
 *
 * 需要注意，对1337取模这个操作。
 *
 * 取模运算规律：
 *
 *  【基本性质】
 *  若p|(a-b)，则a≡b (% p)。例如 11 ≡ 4 (% 7)， 18 ≡ 4(% 7)
 *  (a % p)=(b % p)意味a≡b (% p)
 *  对称性：a≡b (% p)等价于b≡a (% p)
 *  传递性：若a≡b (% p)且b≡c (% p) ，则a≡c (% p)
 *
 *  【运算规则】
 *  模运算与基本四则运算有些相似，但是除法例外。其规则如下：
 *  (a + b) % p = (a % p + b % p) % p （1）
 *  (a - b) % p = (a % p - b % p) % p （2）
 *  (a * b) % p = (a % p * b % p) % p （3）
 *  a ^ b % p = ((a % p)^b) % p （4）
 *  结合律：
 *  ((a+b) % p + c) % p = (a + (b+c) % p) % p （5）
 *  ((a*b) % p * c)% p = (a * (b*c) % p) % p （6）
 *  交换律：
 *  (a + b) % p = (b+a) % p （7）
 *  (a * b) % p = (b * a) % p （8）
 *  分配律：
 *  (a+b) % p = ( a % p + b % p ) % p （9）
 *  ((a +b)% p * c) % p = ((a * c) % p + (b * c) % p) % p （10）
 *
 *  【重要定理】
 *  若a≡b (% p)，则对于任意的c，都有(a + c) ≡ (b + c) (%p)；（11）
 *  若a≡b (% p)，则对于任意的c，都有(a * c) ≡ (b * c) (%p)；（12）
 *  若a≡b (% p)，c≡d (% p)，则 (a + c) ≡ (b + d) (%p)，(a - c) ≡ (b - d) (%p)，
 *  (a * c) ≡ (b * d) (%p)； （13）
 *
 */


//12ms
class Solution {
public:
    int superPow(int a, vector<int>& b) {
        int n = b.size();
        int curr = a % 1337;
        int ans = 1;
        for(int i=n-1;i>=0;--i){
            if(b[i] != 0){
                int t = 1;
                for(int k=0;k<b[i];++k) t = (t * curr)%1337;
                ans = (ans*t)%1337;
            }
            int temp = 1;
            for(int j=0;j<10;++j) temp = (temp * curr)%1337;
            curr = temp;
        }
        return ans;
    }
};

//8ms
class Solution {
public:
    int myPow(int x,int n){
        int res = 1;
        for(int i=n;i>0;i/=2){
            if(i%2) res = (res * x) % 1337;
            x = (x * x) % 1337;
        }
        return res;
    }
    int superPow(int a, vector<int>& b) {
        int n = b.size();
        int curr = a % 1337;
        int ans = 1;
        for(int i=n-1;i>=0;--i){
            ans = ans%1337 * myPow(curr,b[i])%1337;
            curr = myPow(curr,10) % 1337;
        }
        return ans;
    }
};



