## 冒泡排序

冒泡排序是相邻元素比较，较大的后移，类似于水中上升的气泡，不断上升，这也是冒泡排序名称的由来。每趟排序之后有一个最大元素归位到最后一位。

```java
/**
 * @Author: longfellow
 * @Date: 2020/7/14 9:13 下午
 * @Version: 1.0
 */
public class BubbleSort {
    public int[] bubbleSort(int[] nums){
        int m = nums.length;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m-i-1; j++) {   // j+1 防止溢出
                if (nums[j] > nums[j+1]){       // 相邻元素比较，较大值后移
                    int tmp = nums[j];
                    nums[j] = nums[j+1];
                    nums[j+1] = tmp;
                }
            }
        }

        return nums;
    }
}
```

冒泡排序是一种稳定的排序算法，空间复杂度为O(1),时间复杂度为O(n<sup>2</sup>)