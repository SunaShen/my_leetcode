// @File   : 307_NumArray.cpp
// @Source : https://leetcode-cn.com/problems/range-sum-query-mutable/
// @Title  : 307. 区域和检索 - 数组可修改
// @Auther : sun_ds
// @Date   : 2020/4/12

/**  题目描述：
    给定一个整数数组  nums，求出数组从索引 i 到 j  (i ≤ j) 范围内元素的总和，包含 i,  j 两点。

    update(i, val) 函数可以通过将下标为 i 的数值更新为 val，从而对数列进行修改。

    示例:

    Given nums = [1, 3, 5]

    sumRange(0, 2) -> 9
    update(1, 2)
    sumRange(0, 2) -> 8
    说明:

    数组仅可以在 update 函数下进行修改。
    你可以假设 update 函数与 sumRange 函数的调用次数是均匀分布的。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/range-sum-query-mutable
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 区间查询，单点更新
 *
 * 1.树状数组
 *  树状数组是线段树的一种
 *  https://www.cnblogs.com/xenny/p/9739600.html
 *
 *
 * 2.线段树
 *  线段树是一种非常灵活的数据结构，它可以用于解决多种范围查询问题
 *  比如在对数时间内从数组中找到最小值、最大值、总和、最大公约数、最小公倍数等。
 *  数组 A[0,1,…,n−1] 的线段树是一个二叉树，其中每个节点都包含数组的一个子范围 [i…j] 上的聚合信息（最小值、最大值、总和等）
 *  其左、右子节点分别包含范围 [i…(i+j)/2] 和 [(i+j)/2+1…j]上的信息。
 *
 *  线段树可以分为以下三个步骤：
 *      1）从给定数组构建线段树的预处理步骤。
 *      2）修改元素时更新线段树。
 *      3）使用线段树进行区域和检索。
 *
 *  构建线段树：
 *      我们从叶节点开始，用输入数组的元素 a[0,1,…,n−1] 初始化它们。然后我们逐步向上移动到更高一层来计算父节点的和，直到最后到达线段树的根节点。
 *      复杂度 O(N)
 *  更新线段树：
 *      自下而上，更新存储a[i]节点的的各节点。
 *      复杂度 O(logN)
 *  区域和检索：
 *      我们可以通过以下方式使用线段树进行区域和检索 [L,R]：
 *      算法保持循环不变：l≤r 以及已经算出 [L…l] 和 [r…R] 的总和，其中 l 和 r 分别是计算总和时的左边界和右边界。
 *      每次迭代的范围 [l,r] 都会缩小，直到在算法的大约 logn 次迭代后两个边界相遇为止
 *      复杂度 O(logN)
 *
 *
 */

//树状数组
class NumArray {
private:
    vector<int> nums;
    vector<int> tree;
    int n;
public:

    NumArray(vector<int>& nums):nums(nums) {
        n = nums.size();
        tree.resize(nums.size()+1,0);
        for(int i=0;i<nums.size();i++){
            add(i,nums[i]);
        }
    }

    int lowbit(int x){
        return x&-x;
    }

    void add(int i, int val) {
        //树状数组范围1~n
        //输入范围0~n-1
        //为了统一
        i++;
        while(i<=n){
            tree[i] += val;
            i = i + lowbit(i);
        }
    }

    void update(int i, int val) {
        //加上差值
        int add = val - nums[i];
        nums[i] = val;
        i++;
        while(i<=n){
            tree[i] += add;
            i = i + lowbit(i);
        }
    }

    int getsum(int i){
        int res = 0;
        i++;
        while(i>0){
            res += tree[i];
            i = i - lowbit(i);
        }
        return res;
    }

    int sumRange(int i, int j) {
        return getsum(j) - getsum(i-1);
    }
};


//线段树
/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */

class NumArray {
private:
    vector<int> tree;
    int n;
public:

    NumArray(vector<int>& nums){
        if(nums.size()>0){
            n = nums.size();
            tree.resize(2*n);
            buildTree(nums);
        }
    }

    void buildTree(vector<int>& nums){
        for(int i=n,j=0;i<2*n;i++,j++){
            tree[i] = nums[j];
        }
        for(int i=n-1;i>0;i--){
            tree[i] = tree[i*2] + tree[i*2+1];
        }
    }

    void update(int i, int val) {
        i+=n;
        tree[i] = val;
        while(i>0){
            int left = i;
            int right = i;
            //判断此时i对应的是第tree[i] = tree[i*2] + tree[i*2+1];中后面的 tree[i*2]还是tree[i*2+1]
            if(i%2 == 0){
                right = i + 1;
            }else{
                left = i - 1;
            }
            //更新  自下而上更新，从叶子节点开始
            tree[i/2] = tree[left] + tree[right];
            i /= 2;
        }
    }

    int sumRange(int i, int j) {
        i+=n;
        j+=n;
        int sum=0;
        //自底向上求和
        while(i<=j){
            //只占当前区间的后半段
            if((i%2) == 1){
                sum += tree[i];
                i++;
            }
            //只占当前区间的前半段
            if((j%2) == 0){
                sum += tree[j];
                j--;
            }
            //否则是完整的区间，从上一层求得
            i /= 2;
            j /= 2;
        }
        return sum;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */

