// @File   : 19_removeNthFromEnd.cpp
// @Source : https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/
// @Title  : 删除链表的倒数第N个节点
// @Auther : sun_ds
// @Date   : 2019/11/11

/*  题目描述：
    给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。

    示例：

    给定一个链表: 1->2->3->4->5, 和 n = 2.

    当删除了倒数第二个节点后，链表变为 1->2->3->5.
    说明：

    给定的 n 保证是有效的。

    进阶：

    你能尝试使用一趟扫描实现吗？



    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
 * 删除链表的倒数第 n 个节点
 *
 * 1.两次遍历
 *   使用第一次遍历获取链表长度L。
 *   第二次遍历到第L-n+1位，将L-n+1位的next指向next的next即完成删除倒数第n元素
 *
 * 2.一次遍历(双指针)
 *   双指针，使得两指针之间相差n个元素，则当右边指针指向NULL时，左边指针指向L-n+1位
 *   将L-n+1位的next指向next的next即完成删除倒数第n元素
 *
 *   双指针时，不用考虑n会超过数组长度。由题目保证！
 *   (说明：给定的 n 保证是有效的。),考虑题目没有保证时做法？
 *
 * 注意。
 * 链表问题，注意使用dumy节点。
 * ListNode *dumy = new ListNode(0);
 * dumy->next = head;
 *
 *
 */


//双指针
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dumy = new ListNode(0);
        dumy->next = head;

        ListNode* p1 = dumy;
        ListNode* p2 = dumy;

        //给定的 n 保证是有效的。
        int i=0;
        while(i<=n){
            p2 = p2->next;
            ++i;
        }
        // if(i<n) return NULL;

        while(p2){
            p2 = p2->next;
            p1 = p1->next;
        }
        p1->next = p1->next->next;
        return dumy->next;
    }
};