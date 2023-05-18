/*
 * @Description:
 * @Author: 唐健峰
 * @Date: 2023-05-11 13:05:15
 * @LastEditors: ${author}
 * @LastEditTime: 2023-05-15 13:06:18
 */
#include <iostream>
#include <vector>
#include <random>
#define LENGTH 100;   // 数组长度
#define RANGE 1000000 // 数字范围
using namespace std;
int longestAscendingSubsequence(vector<int> &nums)
{
    int n = nums.size();
    vector<int> v(n, 1);
    int result = 1;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (nums[j] < nums[i])
            {
                v[i] = max(v[i], v[j] + 1);
            }
        }
        result = result < v[i] ? v[i] : result;
    }
    return result;
}
int main()
{
    std::default_random_engine e;
    std::uniform_int_distribution<int> u(-1 * RANGE, RANGE);
    e.seed(time(nullptr));
    int length = LENGTH;
    vector<int> nums;
    for (int j = 0; j < length; j++)
    {
        int a = u(e);
        nums.push_back(a);
    }
    clock_t start, end;
    start = clock();
    longestAscendingSubsequence(nums);
    end = clock();
    cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    return 0;
}