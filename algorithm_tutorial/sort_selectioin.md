## 选择排序

```java
public class SelectSort {
    public int[] selectSort(int[] nums) {
        int size = nums.length;
        for (int i = 0; i < size-1; i++) {
            int min = i;
            for (int j = i+1; j < size; j++) {
                if (nums[j] < nums[min]) {
                    min = j;
                }
            }
            int tmp = nums[min];
            nums[min] = nums[i];
            nums[i] = tmp;
        }
        return nums;
    }
}
```