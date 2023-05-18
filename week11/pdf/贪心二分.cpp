/*
 * @Description:
 * @Author: 唐健峰
 * @Date: 2023-05-15 12:30:20
 * @LastEditors: ${author}
 * @LastEditTime: 2023-05-15 12:50:31
 */
#include <iostream>
#include <vector>
#include <random>
#define LENGTH 1000000; // 数组长度
#define RANGE 1000000   // 数字范围
using namespace std;
int LAS(vector<int> &nums)
{
    vector<int> d;
    for (int i = 0; i < nums.size(); i++)
    {
        int left = 0, right = d.size() - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (d[mid] < nums[i])
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        if (left >= d.size())
        {
            d.push_back(nums[i]);
        }
        else
        {
            d[left] = nums[i];
        }
    }
    return d.size();
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
    LAS(nums);
    end = clock();
    cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    return 0;
}