// @File   : 18_deleteNode.cpp
// @Source : https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof/
// @Title  : 面试题18. 删除链表的节点
// @Auther : sun_ds
// @Date   : 2020/3/4

/**  题目描述：
    给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。

    返回删除后的链表的头节点。

    注意：此题对比原题有改动

    示例 1:

    输入: head = [4,5,1,9], val = 5
    输出: [4,1,9]
    解释: 给定你链表中值为 5 的第二个节点，那么在调用了你的函数之后，该链表应变为 4 -> 1 -> 9.
    示例 2:

    输入: head = [4,5,1,9], val = 1
    输出: [4,5,9]
    解释: 给定你链表中值为 1 的第三个节点，那么在调用了你的函数之后，该链表应变为 4 -> 5 -> 9.
     

    说明：

    题目保证链表中节点的值互不相同
    若使用 C 或 C++ 语言，你不需要 free 或 delete 被删除的节点

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/shan-chu-lian-biao-de-jie-dian-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 删除链表中对应值的节点
 *
 * 单向链表，删除当前节点，需要保存前序节点。设置两个指针pre和cur，分别指向前一个和当前。
 * 创建哑节点dummy，处理删除第一个值head的可能性。
 *
 *
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        //哑结点
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* pre = dummy;
        ListNode* cur = head;
        while(cur){
            if(cur->val == val){
                pre->next = cur->next;
                break;
            }
            pre = cur;
            cur = cur->next;
        }
        return dummy->next;
    }
};