// @File   : 17_printNumbers.cpp
// @Source : https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof/
// @Title  : 面试题17. 打印从1到最大的n位数
// @Auther : sun_ds
// @Date   : 2020/3/4

/**  题目描述：
    输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

    示例 1:

    输入: n = 1
    输出: [1,2,3,4,5,6,7,8,9]
     

    说明：

    用返回一个整数列表来代替打印
    n 为正整数


    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/da-yin-cong-1dao-zui-da-de-nwei-shu-lcof
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
/**
 *
 * 输出所有的10进制n位的数
 *
 * 1.直接for循环1~pow(10,n)
 *   输出各个数
 *
 * 2.字符串代替数字
 *  防止数过大超过int以及long，将数都表示成字符串。
 *  字符串执行++程序，若不超过位数，将字符串转成数值型。stoi。存储，返回。
 *
 *  使用string同理
 *
 * 3.递归实现全排列
 *  一共n各位置，每个位置都能放0~9十个数。
 *  递归遍历所有情况，并存储。
 *  得到结果。
 *
 *
 */

//不考虑大数
class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int> res;
        for(int i=1,max=pow(10,n);i<max;i++){
            res.push_back(i);
        }
        return res;
    }
};

//字符串代替数字
class Solution {
public:
    vector<int> res;
    vector<int> printNumbers(int n) {
        if (n <= 0) return res;
        //创建一个能容纳最大值的字符数组,由于有一位要存储'\0'，因此要开大一格
        char* number = new char[n + 1];
        //初始全部设置为0
        memset(number, '0', n);
        number[n] = '\0';//第n位设为'\0'
        while (!Increment(number))
        {
            PrintNumber(number);
        }
        delete[]number;//注意要释放内存
        return res;
    }
    bool Increment(char* number) {//形参传递char*指针
        bool isOverflow = false;//检测是否越界
        int nTakeOver = 0;//存储进位
        int nLength = strlen(number);//长度为n,不是n+1
        for (int i = nLength - 1; i >= 0; i--)
        {
            int nSum = number[i] - '0' + nTakeOver;
            //最好用完进位清零。
            nTakeOver = 0;
            if (i == nLength - 1)
                //如果是第一位，进位
            {
                nSum++;
            }
            if (nSum >= 10)
                //有进位
            {
                if (i == 0)
                    //如果是最高位有进位，说明超过了给定得到最大值，越界
                {
                    isOverflow = true;
                }
                else//非最高位有进位
                {
                    nTakeOver = 1;
                    number[i] = nSum - 10 + '0';//对第i位进行设置
                }
            }
            else//没有进位,前面的都不用动了。所以nTakeOver用完不清零也没关系。。
                //设置第i位数字
                //并直接跳出循环
            {
                number[i] = nSum + '0';
                break;
            }
        }
        return isOverflow;
    }
    void PrintNumber(char* number)
    //形参传递char*指针，此处改变形参number指向的位置，不会使原始的number指针所指位置改变
    {
        string s = "";
        bool isBegin0 = true;
        while (*number != '\0')
        {
            if (isBegin0 && *number != '0') isBegin0 = false;
            //跳过首部的0，而不是所有的0。
            //碰到'0'，则不输出
            if (!isBegin0)
            {
                s += *number;
            }
            number++;
        }
        int num = stoi(s);//转为整数
        res.push_back(num);
    }
};

//全排列 递归
class Solution{
public:
    vector<int> res;
    vector<int> printNumbers(int n) {
        if (n <= 0) return res;
        string number(n, '0');
        for (int i = 0; i <= 9; i++)
            //从高位到低位进行全排列
        {
            number[0] = i + '0';//首字符赋初值
            permutationNumbers(number, n, 1);//设置下一位
        }
        return res;
    }
    //对数字全排列
    void permutationNumbers(string& number, int length, int index) {
        if (index == length) {//递归边界
            saveNumber(number);//存储结果
            return;
        }
        else
        {
            for (int i = 0; i <= 9; i++)
            {
                number[index] = '0' + i;//设置第index位的字符
                permutationNumbers(number, length, index + 1);
            }
        }
    }
    //存储结果
    //只能存储前导非0的排列
    void saveNumber(string number) {
        bool isBegin0 = true;
        string tempStr = "";
        string::iterator it = number.begin();
        while (it != number.end())
        {
            if (isBegin0 && *it != '0') isBegin0 = false;
            if (!isBegin0) {
                tempStr += *it;
            }
            it++;
        }
        //从高位到低位全排列，要注意首字符为0时，tempStr为空，不能执行stoi
        if (tempStr != "") {
            int tempNum = stoi(tempStr);
            res.push_back(tempNum);
        }
    }
};
