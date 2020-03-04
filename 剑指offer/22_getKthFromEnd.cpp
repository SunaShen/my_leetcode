// @File   : 22_getKthFromEnd.cpp
// @Source : https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof/
// @Title  : 面试题22. 链表中倒数第k个节点
// @Auther : sun_ds
// @Date   : 2020/3/4

/**  题目描述：
    输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。例如，一个链表有6个节点，从头节点开始，它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个节点是值为4的节点。

     

    示例：

    给定一个链表: 1->2->3->4->5, 和 k = 2.

    返回链表 4->5.

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/lian-biao-zhong-dao-shu-di-kge-jie-dian-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 返回倒数第k个节点
 *
 * 1.双指针
 * 设置两个指针cur和res。
 * 起始指向head，然后先让cur向前走k步。
 * 随后，两指针同步向前。
 * cur指向NULL时，res也就指向倒数第k个节点了
 *
 * 时间复杂度O(N)
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
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* cur = head;
        ListNode* res = head;

        for(int i=0;i<k;i++){
            cur = cur->next;
        }
        while(cur){
            cur = cur->next;
            res = res->next;
        }
        return res;
    }
};