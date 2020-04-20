// @File   : 912_sortArray.cpp
// @Source : https://leetcode-cn.com/problems/sort-an-array/
// @Title  : 912. 排序数组
// @Auther : sun_ds
// @Date   : 2020/3/31

/**  题目描述：
    给你一个整数数组 nums，将该数组升序排列。

     

    示例 1：

    输入：nums = [5,2,3,1]
    输出：[1,2,3,5]
    示例 2：

    输入：nums = [5,1,1,2,0,0]
    输出：[0,0,1,1,2,5]
     

    提示：

    1 <= nums.length <= 50000
    -50000 <= nums[i] <= 50000

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/sort-an-array
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 *
 * 排序
 * 1.归并
 *  需要额外空间
 * 2.快排
 *  pivot
 * 3.堆排
 *  len很重要
 * 4.计数
 *  桶的大小
 *
 *
 */

//归并排序 需要额外空间
class Solution {
public:
    vector<int> temp;
    void merge_sort(vector<int>& nums,int l,int r){
        if(l>=r) return;
        int mid = (l+r)/2;
        merge_sort(nums,l,mid);
        merge_sort(nums,mid+1,r);
        int i=l,j=mid+1;
        int cnt=0;
        while(i<=mid&&j<=r){
            if(nums[i]<nums[j]){
                temp[cnt++] = nums[i++];
            }else{
                temp[cnt++] = nums[j++];
            }
        }
        if(i<=mid) for(;i<=mid;i++) temp[cnt++] = nums[i];
        if(j<=r) for(;j<=mid;j++) temp[cnt++] = nums[j];
        for(int i=0;i<cnt;i++) nums[i+l] = temp[i];
    }
    vector<int> sortArray(vector<int>& nums) {
        temp.resize(nums.size(),0);
        merge_sort(nums,0,nums.size()-1);
        return nums;
    }
};
//快排
class Solution {
public:
    int pivot(vector<int>& nums,int start,int end){
        int x = nums[end];
        int i = start, j = start;
        for(;j<end;j++){
            if(nums[j]<x){
                swap(nums[i],nums[j]);
                i++;
            }
        }
        swap(nums[i],nums[end]);
        return i;
    }
    void sort_p(vector<int>& nums,int left,int right){
        if(left>=right) return;
        int p = pivot(nums,left,right);
        sort_p(nums,left,p-1);
        sort_p(nums,p+1,right);
    }
    vector<int> sortArray(vector<int>& nums) {
        sort_p(nums,0,nums.size()-1);
        return nums;
    }
};
//优先队列
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        priority_queue<int> q;
        for(auto i:nums){
            q.push(i);
        }
        for(auto iter=nums.rbegin();iter!=nums.rend();iter++){
            *iter = q.top();
            q.pop();
        }
        return nums;
    }
};
//堆排 len参数很有必要
class Solution {
public:
    void heap_modify(vector<int>& nums,int i,int len){
        for(;((i<<1)+1)<=len;){
            int l = (i<<1) + 1;
            int r = (i<<1) + 2;
            int large = 0;
            if(l<=len&&nums[l]>nums[i]){
                large = l;
            }else{
                large = i;
            }
            if(r<=len&&nums[r]>nums[large]){
                large = r;
            }
            if(large!=i){
                swap(nums[large],nums[i]);
                i = large;
            }else{
                break;
            }
        }
    }
    void build_heap(vector<int>& nums,int len){
        for(int i=len/2;i>=0;i--){
            heap_modify(nums,i,len);
        }l
    }
    void heap_sort(vector<int>& nums){
        int len = nums.size()-1;
        build_heap(nums,len);
        for(int i=len;i>0;i--){
            swap(nums[i],nums[0]);
            len--;
            heap_modify(nums,0,len);
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        heap_sort(nums);
        return nums;
    }
};
//计数排序
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        vector<int> counter(100001,0);
        for(auto i:nums){
            counter[i+50000]++;
        }
        vector<int> res;
        for(int i=0;i<counter.size();i++){
            if(counter[i]!=0){
                res.insert(res.end(),counter[i],i-50000);
            }
        }
        return res;
    }
};

