// @File   : 10.01_merge.cpp
// @Source : https://leetcode-cn.com/problems/sorted-merge-lcci/
// @Title  : 面试题 10.01. 合并排序的数组
// @Auther : sun_ds
// @Date   : 2020/3/3

/**  题目描述：
    给定两个排序后的数组 A 和 B，其中 A 的末端有足够的缓冲空间容纳 B。 编写一个方法，将 B 合并入 A 并排序。

    初始化 A 和 B 的元素数量分别为 m 和 n。

    示例:

    输入:
    A = [1,2,3,0,0,0], m = 3
    B = [2,5,6],       n = 3

    输出: [1,2,2,3,5,6]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/sorted-merge-lcci
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * A和B已经符合升序排列，A和B按序合并到A中
 *
 * 1.A和B先合并后排序
 *
 * 2.A和B逆序合并。
 *  由于A的最右侧是空间，所以采用逆序合并。
 *  使用三个指针，一个指向当前要合并放置的索引位置index，一个是A中最后一个元素(最大)的索引i，另一个是B中最后一个元素(最大)的索引j。
 *  判断A[i]和B[j]的大小，将大的值先放入A的末尾index。
 *  当i和j都小于0时，即排序完毕。
 *  但由于是放置到A中的特殊性，所以当j<0时，剩下的A是不用动的，即可以结束。
 *  而若i<0,则需要把B剩下的j各元素复制到A的开头。
 *
 *
 *
 *
 */

//逆序 双指针
class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {
        int index = m + n - 1;
        int i = m-1, j = n-1;
        while(i>=0||j>=0){
            int temp;
            if(i < 0) temp = B[j--];
            else if(j < 0) temp = A[i--];
            else temp = A[i] >= B[j] ? A[i--]:B[j--];
            A[index--] = temp;
        }
    }
};

class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {
        int index = m + n - 1;
        int i = m-1, j = n-1;
        while(i>=0&&j>=0){
            int temp;
            if(A[i] >= B[j]){
                temp = A[i--];
            }else{
                temp = B[j--];
            }
            A[index--] = temp;
        }
        if(i<0&&j>=0){
            for(int k = 0; k <= j; k++){
                A[k] = B[k];
            }
        }
    }
};

//优秀题解
class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {
        int index = m + n - 1;
        int i = m-1, j = n-1;
        while(j>=0){
            A[index--] = (i>=0 && A[i]>=B[j]) ? A[i--]:B[j--];
        }
    }
};


