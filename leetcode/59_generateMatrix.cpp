// @File   : 59_generateMatrix.cpp
// @Source : https://leetcode-cn.com/problems/spiral-matrix-ii/
// @Title  : 螺旋矩阵 II
// @Auther : sun_ds
// @Date   : 2019/11/27

/**  题目描述：
    给定一个正整数 n，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。

    示例:

    输入: 3
    输出:
    [
     [ 1, 2, 3 ],
     [ 8, 9, 4 ],
     [ 7, 6, 5 ]
    ]

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/spiral-matrix-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/** 生成螺旋矩阵
 * 顺时针旋转，从左到右 从上到下 从右到左 从下到上。
 *
 *
 * 生成一个 n×n 空矩阵 mat，随后模拟整个向内环绕的填入过程：
 *  定义当前左右上下边界 l,r,t,b，初始值 num = 1，迭代终止值 tar = n * n；
 *  当 num <= tar 时，始终按照 从左到右 从上到下 从右到左 从下到上 填入顺序循环，每次填入后：
 *      执行 num += 1：得到下一个需要填入的数字；
 *      更新边界：例如从左到右填完后，上边界 t += 1，相当于上边界向内缩1。
 *  使用num <= tar而不是l < r || t < b作为迭代条件，是为了解决当n为奇数时，矩阵中心数字无法在迭代过程中被填充的问题。
 * 最终返回 mat 即可
 *
 * 作者：jyd
 * 链接：https://leetcode-cn.com/problems/spiral-matrix-ii/solution/spiral-matrix-ii-mo-ni-fa-she-ding-bian-jie-qing-x/
 * 来源：力扣（LeetCode）
 * 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 *
 *
 * 动态边界，精妙
 * 自动控制向里收缩。
 *
 */

//
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ans(n);
        for(int i=0;i<ans.size();++i){
            ans[i].resize(n);
        }
        //模拟边界 l,r,t,b,左右上下
        int l=0,r=n-1,t=0,b=n-1,cnt=1;
        while(cnt<=(n*n)){
            for(int i=l;i<=r;++i) ans[t][i] = cnt++;
            ++t;
            for(int i=t;i<=b;++i) ans[i][r] = cnt++;
            --r;
            for(int i=r;i>=l;--i) ans[b][i] = cnt++;
            --b;
            for(int i=b;i>=t;--i) ans[i][l] = cnt++;
            ++l;
        }
//        while(1){
//            for(int i=l;i<=r;++i) ans[t][i] = cnt++;
//            if(++t>b) break;
//            for(int i=t;i<=b;++i) ans[i][r] = cnt++;
//            if(--r<l) break;
//            for(int i=r;i>=l;--i) ans[b][i] = cnt++;
//            if(--b>t) break;
//            for(int i=b;i>=t;--i) ans[i][l] = cnt++;
//            if(++l>r) break;
//        }
        return ans;
    }
};

