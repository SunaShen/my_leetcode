// @File   : 118_generate.cpp
// @Source : https://leetcode-cn.com/problems/pascals-triangle/
// @Title  : 杨辉三角
// @Auther : sun_ds
// @Date   : 2019/10/17

/*  题目描述：
    给定一个非负整数 numRows，生成杨辉三角的前 numRows 行。



    在杨辉三角中，每个数是它左上方和右上方的数的和。

    示例:

    输入: 5
    输出:
    [
         [1],
        [1,1],
       [1,2,1],
      [1,3,3,1],
     [1,4,6,4,1]
    ]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/pascals-triangle
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/*
 * 杨辉三角
 * 可以归类为动态规划问题
 * 已知上一行就可以得到下一行
 * 需要处理两边的1，以及边界问题
 *
 */



//class Solution {
//public:
//    vector<vector<int>> generate(int numRows) {
//        if(numRows==1)
//            return vector<vector<int>>{{1}};
//        vector<vector<int>> res;
//        vector<int> a{1};
//        res.push_back(a);
//        for(int i=1;i<numRows;i++){
//            vector<int> temp{1};
//            for(int j=0;j<i-1;j++){
//                temp.push_back(res[i-1][j]+res[i-1][j+1]);
//            }
//            temp.push_back(1);
//            res.push_back(temp);
//        }
//        return res;
//    }
//};

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res;
        for(int i=0;i<numRows;i++){
            vector<int> temp(i+1,1);
            if(i>1){
                for(int j=1;j<i;j++){
                    temp[j] = res[i-1][j-1]+res[i-1][j];
                }
            }
            res.push_back(temp);
        }
        return res;
    }
};