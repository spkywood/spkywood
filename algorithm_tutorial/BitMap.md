# BitMap

## BitMap的原理

BitMap 的基本原理就是用一个 bit 位来存放某种状态，适用于大规模数据，但数据状态又不是很多的情况。通常是用来判断某个数据存不存在的。

举个例子在Java里面一个int类型占4个字节，也就是4*8=32bit，大多数时候我们一个int类型仅仅表示一个整数，但其实如果映射成位存储的话，一个int类型 是可以存储32个bit状态的。

也就是说使用1G的内存，换算成 `bit=1024 * 1024 * 1024 * 8` 约等于86亿个bit，注意换算的方式 `GB=>MB=>KB=>Byte=>Bit`。如果存储int类型，能存储多少个？我们 算下 `1024 * 1024 * 1024 / 4` 约等于2亿6千万个int类型。

从上面的计算的结果来看，在面对海量数据的时候，如果能够采用bit存储，那么在存储空间方面可以大大节省。

在Java里面，其实已经有对应实现的数据结构类 `java.util.BitSet` 了，`BitSet` 的底层使用的是 `long` 类型的数组来存储元素。

也就是说，假设我想排序或者查找的总数N=10000，那么，我申请的数组大小如下：

如果是int类型：`int temp[]=new int[1+N/32]`，也就是312+1=313

如果是long类型：`long temp[]=new long[1+N/64]`，也就是156+1=157

这里注意Java里面的整数除法是向下取整的，所以数组长度还需要加上1.

```
a[0]---------> 0 -31 ->bit表示[0000000000000000000000000000000000000]
a[1]---------> 32-63 ->bit表示[0000000000000000000000000000000000000]
a[2]---------> 64-95 ->bit表示[0000000000000000000000000000000000000]
```

## BitMap处理大数据问题的场景：

1. 给定40亿个不重复的 int的整数，没排过序的，然后再给一个数，如何快速判断这个数是否在那40亿个数当中。

> 解法：遍历40亿数字，映射到BitMap中，然后对于给出的数，直接判断指定的位上存在不存在即可。

2. 使用位图法判断整形数组是否存在重复

> 解法：遍历一遍，存在之后设置成1，每次放之前先判断是否存在，如果存在，就代表该元素重复。

3. 使用位图法进行元素不重复的整形数组排序

> 解法：遍历一遍，设置状态1，然后再次遍历，对状态等于1的进行输出，参考计数排序的原理。

4. 在2.5亿个整数中找出不重复的整数，注，内存不足以容纳这2.5亿个整数

> 解法1：采用2-Bitmap（每个数分配2bit，00表示不存在，01表示出现一次，10表示多次，11无意义）。

> 解法2：采用两个BitMap，即第一个Bitmap存储的是整数是否出现，接着，在之后的遍历先判断第一个BitMap里面是否出现过，如果出现就设置第二个BitMap对应的位置也为1，最后遍历BitMap，仅仅在一个BitMap中出现过的元素，就是不重复的整数。

> 解法3：分治+Hash取模，拆分成多个小文件，然后一个个文件读取，直到内存装的下，然后采用Hash+Count的方式判断即可。

该类问题的变形问题，如已知某个文件内包含一些电话号码，每个号码为8位数字，统计不同号码的个数。 8位最多99 999 999，大概需要99m个bit，大概10几m字节的内存即可。 （可以理解为从0-99 999 999的数字，每个数字对应一个Bit位，所以只需要99M个Bit==12MBytes，这样，就用了小小的12M左右的内存表示了所有的8位数的电话）