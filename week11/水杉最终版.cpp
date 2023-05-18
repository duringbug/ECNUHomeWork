/*
 * @Description:
 * @Author: 唐健峰
 * @Date: 2023-05-11 14:54:03
 * @LastEditors: ${author}
 * @LastEditTime: 2023-05-18 12:57:17
 */
#include <iostream>
#include <vector>
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
    int K;
    cin >> K;
    for (int i = 0; i < K; i++)
    {
        int length = 0;
        cin >> length;
        vector<int> nums;
        for (int j = 0; j < length; j++)
        {
            int a;
            cin >> a;
            nums.push_back(a);
        }
        cout << LAS(nums) << " ";
    }
    return 0;
}