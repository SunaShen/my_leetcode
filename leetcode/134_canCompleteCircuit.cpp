// @File   : 134_canCompleteCircuit.cpp
// @Source : https://leetcode-cn.com/problems/gas-station/
// @Title  : 134. 加油站
// @Auther : sun_ds
// @Date   : 2020/3/26

/**  题目描述：
    在一条环路上有 N 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

    你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

    如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1。

    说明: 

    如果题目有解，该答案即为唯一答案。
    输入数组均为非空数组，且长度相同。
    输入数组中的元素均为非负数。
    示例 1:

    输入:
    gas  = [1,2,3,4,5]
    cost = [3,4,5,1,2]

    输出: 3

    解释:
    从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
    开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
    开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
    开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
    开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
    开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
    因此，3 可为起始索引。
    示例 2:

    输入:
    gas  = [2,3,4]
    cost = [3,4,3]

    输出: -1

    解释:
    你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
    我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
    开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
    开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
    你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
    因此，无论怎样，你都不可能绕环路行驶一周。

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/gas-station
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 *
 * 1.遍历 两层循环
 *   以每个节点为起点，统计能否循环一圈。
 * 2.遍历 中间跳过一些
 *   遍历从i--j若到不了j+1，则下次从j+1开始。而不需要判断以i+1--j之间。
 *   因为i到不了j但是i可以到i+1，所以i给了i+1一些余量油都到不了j+1，所以以i+1为起点一定到不了j+1
 *
 * 3.总剩余油量 最低点为起点
 * 遍历，统计总油量，以总油量最小值为起点
 * 以spare最小值位置为起点 以此为起点spare=0，则spare全程大于0，完成循环
 * https://leetcode-cn.com/problems/gas-station/solution/shi-yong-tu-de-si-xiang-fen-xi-gai-wen-ti-by-cyayc/
 */

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        for(int i=0;i<n;i++){
            if(gas[i]<cost[i]) continue;
            else{
                int cur = 0;
                for(int j=0;j<n;j++){
                    cur += gas[(i+j)%n] - cost[(i+j)%n]; //循环 取余
                    if(cur < 0) break;
                }
                if(cur>=0) return i;
            }
        }
        return -1;
    }
};


class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();

        int total_tank = 0; //总油量
        int curr_tank = 0; //当前油量
        int starting_station = 0;
        for (int i = 0; i < n; ++i) {
            total_tank += gas[i] - cost[i];
            curr_tank += gas[i] - cost[i];
            // If one couldn't get here,
            //如果到不了这里，则从下个位置为起点开始判断，中间的不用判断了。
            if (curr_tank < 0) {
                // Pick up the next station as the starting one.
                starting_station = i + 1;
                // Start with an empty tank.
                curr_tank = 0;
            }
        }
        //最后用总油量判断是否可达
        return total_tank >= 0 ? starting_station : -1;
    }
};


class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int len = gas.size();
        int spare = 0;
        int minSpare = INT_MAX;
        int minIndex = 0;
        //spare 为当前总剩余油量
        //以spare最小值位置为起点 以此为起点spare=0，则spare全程大于0，完成循环
        for (int i = 0; i < len; i++) {
            spare += gas[i] - cost[i];
            if (spare < minSpare) {
                minSpare = spare;
                minIndex = i;
            }
        }

        //若最后spare < 0 ，则车不可能走完全程的。
        return spare < 0 ? -1 : (minIndex + 1) % len;
    }
};