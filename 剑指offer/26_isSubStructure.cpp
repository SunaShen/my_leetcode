// @File   : 26_isSubStructure.cpp
// @Source : https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/
// @Title  : 面试题26. 树的子结构
// @Auther : sun_ds
// @Date   : 2020/3/10

/**  题目描述：
    输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)

    B是A的子结构， 即 A中有出现和B相同的结构和节点值。

    例如:
    给定的树 A:

         3
        / \
       4   5
      / \
     1   2
    给定的树 B：

       4 
      /
     1
    返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。

    示例 1：

    输入：A = [1,2,3], B = [3,1]
    输出：false
    示例 2：

    输入：A = [3,4,5,1,2], B = [4,1]
    输出：true
    限制：

    0 <= 节点个数 <= 10000

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 判断子树
 *
 * 1.递归
 *  判断当前A节点和B节点是否相等，如果相等继续判断左子树右子树是否相等。知道判断到B空，返回true。而如果B没空，A空了返回false。
 *  如果不满足，则接着继续以A的其他节点为起点，还是以B的起始为起点，开始递归。
 *
 * 2.分成两部分
 *  编写函数只判断当前以A和B为起点的树是否相同。
 *  主函数return dfs(A,B)||isSubStructure(A->left,B)||isSubStructure(A->right,B)
 *  即要么相等，要么重新以A其他节点为起点继续遍历
 *
 *
 *
 *
 */


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
    TreeNode* B;
public:
    bool dfs(TreeNode* a, TreeNode* b){
        if(b==NULL) return true;
        if(a==NULL) return false;
        if(a->val == b->val){
            //如果相等，接着判断其左子树右子树是否相同
            if(dfs(a->right,b->right)&&dfs(a->left,b->left)){
                return true;
            }
        }
        //证明上面没成功，接着移动A的节点，而B还是从原始的开始
        return dfs(a->right, B)||dfs(a->left, B);
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(A==NULL||B==NULL) return false;
        this->B=B;
        return dfs(A,B);
    }
};

//优雅
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
    //判断从根节点a开始，是否和b相同
    bool dfs(TreeNode* a, TreeNode* b){
        if(b==NULL) return true;
        if(a==NULL) return false;
        if(a->val != b->val) return false;
        return dfs(a->right, b->right)&&dfs(a->left, b->left);
    }
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if(A==NULL||B==NULL) return false;
        //以当前判断dfs，不成功再搜索A的不同节点作为起点与B比
        return dfs(A,B)||isSubStructure(A->left,B)||isSubStructure(A->right,B);
    }
};