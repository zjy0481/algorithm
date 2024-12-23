#include <iostream>
#include <vector>

using namespace std;

// 辅助函数：合并两个有序数组，并计算逆序对的数量
int merge(vector<double>& nums, int left, int mid, int right) {
    vector<double> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    int count = 0;

    // 合并两个有序数组
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            temp[k++] = nums[i++];
        } else {
            temp[k++] = nums[j++];
            count += mid - i + 1; // 计算逆序对的数量
        }
    }

    // 将剩余的元素复制到临时数组中
    while (i <= mid) {
        temp[k++] = nums[i++];
    }
    while (j <= right) {
        temp[k++] = nums[j++];
    }

    // 将临时数组中的元素复制回原数组
    for (i = 0; i < temp.size(); i++) {
        nums[left + i] = temp[i];
    }

    return count;
}

// 辅助函数：递归地计算逆序对的数量
int mergeSort(vector<double>& nums, int left, int right) {
    if (left >= right) {
        return 0;
    }

    int mid = left + (right - left) / 2;
    int count = 0;

    // 递归地计算左半部分和右半部分的逆序对数量
    count += mergeSort(nums, left, mid);
    count += mergeSort(nums, mid + 1, right);

    // 合并两个有序数组，并计算跨两个部分的逆序对数量
    count += merge(nums, left, mid, right);

    return count;
}

int main() {
    // vector<double> nums = {10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};   输出45
    vector<double> nums = {10.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};      // 输出9
    int n = nums.size();
    int result = mergeSort(nums, 0, nums.size()-1);
    cout << "逆序对的数量为: " << result << endl;
    return 0;
}
