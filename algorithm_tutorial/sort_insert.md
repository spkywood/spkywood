## 插入排序

从已经排好序的数组中，从后往前找到需要插入的位置

```java
/**
 * @Author: longfellow
 * @Date: 2020/7/15 10:53 上午
 * @Version: 1.0
 */
public class InsertSort {
    public int[] insertSort(int[] nums) {
        int len = nums.length;
        for (int i = 1; i < len; i++) {
            int tmp = nums[i];
            for (int j = i; j >= 0 ; j--) {
                if (j> 0 && tmp < nums[j-1]) {
                    nums[j] = nums[j-1];
                } else {
                    nums[j] = tmp;
                    break;
                }
            }
        }

        return nums;
    }
}
```