// @File   : 230_kthSmallest.cpp
// @Source : https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/
// @Title  : 二叉搜索树中第K小的元素
// @Auther : sun_ds
// @Date   : 2020/1/15

/**  题目描述：
    给定一个二叉搜索树，编写一个函数 kthSmallest 来查找其中第 k 个最小的元素。

    说明：
    你可以假设 k 总是有效的，1 ≤ k ≤ 二叉搜索树元素个数。

    示例 1:

    输入: root = [3,1,4,null,2], k = 1
       3
      / \
     1   4
      \
       2
    输出: 1
    示例 2:

    输入: root = [5,3,6,2,4,null,null,1], k = 3
           5
          / \
         3   6
        / \
       2   4
      /
     1
    输出: 3
    进阶：
    如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 k 小的值，你将如何优化 kthSmallest 函数？



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 * 返回二叉搜索树的第K小值
 *
 * 由二叉搜索树性质，中序遍历升序排列。
 * 因此，获得中序遍历，第k个数即为第k小值。
 *
 * 1.递归_中序遍历
 *  使用递归将中序遍历的值存储在res中。
 *  返回res[k-1]即为第k小值
 *
 * 2.递归_中序遍历 + 提前终止
 *  递归时使用i记录是第几个数，当i==k时，即为返回值。
 *  使res = 当前root->val，并将find置为true。停止递归。
 *
 * 3.迭代_中序遍历 + 提前终止
 *  使用迭代法进行中序遍历。用i来记录是第几个数。
 *  当i==k时，当前的值即为第k小的值。
 *
 */


//中序遍历
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> res;
    void func(TreeNode* root){
        if(root == NULL) return;
        func(root->left);
        res.push_back(root->val);
        func(root->right);
    }
    int kthSmallest(TreeNode* root, int k) {
        func(root);
        return res[k-1];
    }
};


//中序遍历+提前终止
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void func(TreeNode* root,bool& find,int &res,int &i,int k){
        if(root == NULL||find) return;
        func(root->left, i, k);
        if((++i) == k){
            find = true;
            res = root->val;
            return;
        }
        func(root->right, i, k);
    }
    int kthSmallest(TreeNode* root, int k) {
        int i=0,res=-1;
        bool find=false;
        func(root,res,find,i,k);
        return res;
    }
};



//迭代+提前终止
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        if(root == NULL) return {};
        stack<TreeNode*> q;
        TreeNode* temp = root;
        int i=0;
        while(!q.empty()||temp!=NULL){
            if(temp!= NULL){
                q.push(temp);
                temp = temp->left;
            }else{
                temp = q.top();
                q.pop();
                i++;
                if(i == k) return temp->val;
                temp = temp->right;
            }
        }
        return -1;
    }
};