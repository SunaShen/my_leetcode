// @File   : 968_minCameraCover.cpp
// @Source : https://leetcode-cn.com/problems/binary-tree-cameras/
// @Title  : 968. 监控二叉树
// @Auther : sun_ds
// @Date   : 2020/9/22

/**  题目描述：
    给定一个二叉树，我们在树的节点上安装摄像头。

    节点上的每个摄影头都可以监视其父对象、自身及其直接子对象。

    计算监控树的所有节点所需的最小摄像头数量。

     

    示例 1：



    输入：[0,0,null,0,0]
    输出：1
    解释：如图所示，一台摄像头足以监控所有节点。
    示例 2：



    输入：[0,0,null,0,null,0,null,null,0]
    输出：2
    解释：需要至少两个摄像头来监视树的所有节点。 上图显示了摄像头放置的有效位置之一。

    提示：

    给定树的节点数的范围是 [1, 1000]。
    每个节点的值都是 0。


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/binary-tree-cameras
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1. 递归
 * 考虑每个子树 root 节点的状态，有如下三种：
 *  a) 根节点必须有摄像头的情况。
 *  b) 根节点没有被自己父节点覆盖，根节点可以有摄像头也可以没有(没有被父节点覆盖，只能自己来或者借助子节点装)。
 *  c) 根节点已被自己父节点覆盖，根节点可以有摄像头也可以没有(被父节点覆盖了，根节点想装就装)。
 *
 *  对于节点 root 而言，设其左右孩子对应的状态分别为(la, lb, lc), (ra, rb, rc).
 *
 *  a = 1 + lc + rc;  当前节点有摄像头，对应左右孩子为被父节点覆盖了即情况 c。
 *  b = min(a, min(la+rb, lb+ra));  当前节点没有被其父节点覆盖，所以只能借助自己安装 a 或者 子节点安装
 *      1. la+rb(左孩子安装 a，右孩子为不被父节点覆盖 b)
 *      2. lb+ra(右孩子安装 a，左孩子为不被父节点覆盖 b)
 *      3. la+ra(左孩子装 a，右孩子也装 a)。 可知 la+ra 一定大于等于 la+rb 和 lb+ra。可以省略该情况。
 *  c = min(a, lb+rb); 当前节点被父节点覆盖了，所以可以自己装 或者 不装(两个孩子都为不被父节点覆盖的情况 b)
 *
 * (la, lb, lc), (ra, rb, rc) 组合方式一共 9 种。上面使用了其中的 5 种。
 *
 * 另外四种为无效状态。
 *  la+rc(root和左孩子都装)
 *  lc+ra(root和右孩子都装)
 *  lb+rc(一个被父节点覆盖一个没有，矛盾)
 *  lc+rb(一个被父节点覆盖一个没有，矛盾).
 *
 *
 * 边界条件，叶子节点的孩子节点(空节点)
 *  假设 root 为叶子节点，那么无法在空节点上放摄像头，设置 a 为无效值， 而 b、c 都可以为 0。
 *
 * 最终结果为 b， 不被父节点覆盖(他也没有父节点了)
 *
 *
 * 时间复杂度 O(N)
 * 空间复杂度 O(N)
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
struct Status {
    int a, b, c;
};

class Solution {
public:
    Status dfs(TreeNode* root) {
        if (!root) {
            return {INT_MAX / 2, 0, 0};
        }
        auto [la, lb, lc] = dfs(root->left);
        auto [ra, rb, rc] = dfs(root->right);
        int a = lc + rc + 1;
        int b = min(a, min(la + rb, ra + lb));
//        int b = min(a, min(la + rb, min(ra + lb, la + ra)));
        int c = min(a, lb + rb);
        return {a, b, c};
    }

    int minCameraCover(TreeNode* root) {
        // c++17 结构化绑定
        auto [a, b, c] = dfs(root);
        return b;
    }
};
