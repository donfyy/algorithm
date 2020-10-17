#include <vector>
#include <iostream>
using namespace std;
void selectSort(vector<int> &nums)
{
    const int n = nums.size();
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (nums[j] > nums[j + 1])
            {
                swap(nums[j], nums[j + 1]);
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    vector<int> nums = {1, 5, 3, 2, 6, 4};
    selectSort(nums);
    cout << "[";
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << ",";
    }
    cout << "]" << endl;
    return 0;
}