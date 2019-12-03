// @File   : 2_addTwoNumbers.cpp
// @Source : https://leetcode-cn.com/problems/add-two-numbers/
// @Title  : 两数相加
// @Auther : sun_ds
// @Date   : 2019/12/3

/**  题目描述：
    给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

    如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

    您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

    示例：

    输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
    输出：7 -> 0 -> 8
    原因：342 + 465 = 807

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/add-two-numbers
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 链表加法
 *
 * 对应为相加，并设置c记录进位
 * while循环
 * 两个链表各位上有值或者有进位，都继续执行加法。
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* head = dummy;
        int c = 0;
        while(l1||l2||c){
            int v1 = 0, v2 = 0;
            if(l1){
                v1 = l1->val;
                l1 = l1->next;
            }
            if(l2){
                v2 = l2->val;
                l2 = l2->next;
            }
            head->next = new ListNode((v1 + v2 + c)%10);
            head = head->next;
            c = (v1 + v2 + c)/10;
        }
        return dummy->next;
    }
};