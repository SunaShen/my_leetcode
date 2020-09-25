// @File   : 315_countSmaller.cpp
// @Source : https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/
// @Title  : 315. 计算右侧小于当前元素的个数
// @Auther : sun_ds
// @Date   : 2020/7/11

/**  题目描述：
    给定一个整数数组 nums，按要求返回一个新数组 counts。数组 counts 有该性质： counts[i] 的值是  nums[i] 右侧小于 nums[i] 的元素的数量。

    示例:

    输入: [5,2,6,1]
    输出: [2,1,1,0]
    解释:
    5 的右侧有 2 个更小的元素 (2 和 1).
    2 的右侧仅有 1 个更小的元素 (1).
    6 的右侧有 1 个更小的元素 (1).
    1 的右侧有 0 个更小的元素.

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.树状数组  前缀和
 *
 *  树状数组：动态维护前缀和
 *   单点更新：i 位置的值 + v
 *   区间查询：查询i 位置之前的前缀和
 *
 *  修改和查询时间都为 O(log(N))
 *
 *  构建桶(桶内元素升序排列)记录每个元素出现次数。
 *  防止数字不连续，导致桶过大，使用 去重 hash 节约空间。
 *  （将原数组去重后排序，原数组每个数映射到去重排序后这个数对应位置的下标）
 *
 *  逆序遍历，并不断的将遍历的值放入桶中，右边比当前值大的值的个数为桶中当前位置的前缀和。
 *
 *
 */

class Solution {
private:
    //原数组为nums，
    //将nums离散化，此处是排序+去重，转化为数组a
    vector<int> a;
    //将nums对应a的元素update到树状数组c
    vector<int> c;

    //resize树状数组大小
    void init(int len) {
        c.resize(len);
    }

    //lowbit为二进制中最低位的1的值
    int lowbit(int x) {
        return x & (-x);
    }

    //单点更新，从子节点更新到所有父节点(祖父节点等一直往上到上限c.size())
    void update(int pos) {
        while (pos < c.size()) {
            c[pos] += 1;
            pos += lowbit(pos);
        }
    }

    //查询，实际是求和[0,...,pos]，即求1~pos的元素数量
    //如c[8]，在update时，a[1],a[2],a[3],...,a[8]都会使c[8]增加一个value（该题中我们设置为1）
    //res += c[8]，然后8减去lowbit为0。
    //也可以拿c[6]举例，c[6] =a[5]+a[6]，lowbit后，c[4] = a[1]+a[2]+a[3]+a[4]
    int query(int pos) {
        int res = 0;
        while (pos) {
            res += c[pos];
            pos -= lowbit(pos);
        }
        return res;
    }

    //离散化处理
    void Discretization(vector<int>& nums) {
        //拷贝数组 [5,4,5,3,2,1,1,1,1,1]
        a.assign(nums.begin(), nums.end());
        //排序[1,1,1,1,1,2,3,4,5,5]
        sort(a.begin(), a.end());
        //去重[1,2,3,4,5]
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    int getId(int x) {
        //lower_bound返回第一个不小于x的迭代器
        //[1,2,3,4,5]中1，减去begin()再加1，得到id（1-5）
        return lower_bound(a.begin(), a.end(), x) - a.begin() + 1;
    }

public:
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> res;
        int n = nums.size();
        //题解是+5，其实+1就够了，树状数组中我们不使用0下标，所以需扩展1位空间
        //当然直接用n结果也是对的。这里再推敲推敲
        init(n+1);

        //将nums转化为a
        Discretization(nums);

        for (int i=n-1; i>=0; --i) {
            //倒序处理
            int id = getId(nums[i]);
            //查询严格小于id的元素数量，所以使用id-1
            res.push_back(query(id-1));
            //更新id，其实更新也可以提前，因为查询是id-1，所以更新操作不影响当前结果
            update(id);
        }
        //倒序处理再倒序回来。如果不是用push_back，直接用下标可以不用在这里再倒序
        reverse(res.begin(), res.end());
        return res;
    }
};

