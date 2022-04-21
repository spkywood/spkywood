## 快速排序

快速排序是一种递归实现的排序算法，初始化选择一个基准值（一般以第一个值为基准），将数组按照基准值分为前后两部分，前面一部分都比基准值小，后面一部分都比基准值大，然后对前后两部分递归执行，最后即有序。

```java
/**
 * @Author: longfellow
 * @Date: 2020/7/14 10:39 下午
 * @Version: 1.0
 */
public class QuickSort {
    public int[] quickSort(int[] nums){
        int m = 0;
        int n = nums.length-1;
        helpSort(nums, m, n);

        return nums;
    }

    private void helpSort(int[] nums, int m, int n) {
        int left = m, right = n;
        if (nums.length <= 0 || left >= right) return;
        int tmp = nums[left];   // 选择基准值
        while (left < right){
            while (left<right && nums[right] >= tmp) {
                --right;        // 从后往前找比基准值小的值
            }
            nums[left] = nums[right];   // 较小值交换到前面
            while (left< right && nums[left] <= tmp) {
                ++left;         // 从前往后找比基准值大的值
            }
            nums[right] = nums[left];   // 较大值交换到后面
        }
        nums[left] = tmp;
        helpSort(nums, m, left-1);
        helpSort(nums, left+1, n);
    }
}
```