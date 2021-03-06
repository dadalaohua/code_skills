# 内省排序Introsort

内省排序（英语：Introsort）是由David Musser在1997年设计的排序算法。这个排序算法首先从快速排序开始，当递归深度超过一定深度（深度为排序元素数量的对数值）后转为堆排序。采用这个方法，内省排序既能在常规数据集上实现快速排序的高性能，又能在最坏情况下仍保$O(nlogn)$的时间复杂度。由于这两种算法都属于比较排序算法，所以内省排序也是一个比较排序算法。

在快速排序算法中，一个关键操作就是选择基准点（Pivot）：元素将被此基准点分开成两部分。最简单的基准点击择算法是使用第一个或者最后一个元素，但这在排列已部分有序的序列上性能很糟。Niklaus Wirth为此设计了一个快速排序的变体，使用处于中间的元素来防止在某些特定序列上性能退化为$O(n^{2})$的状况。这个3基准中位数选择算法从序列的第一，中间和最后一个元素获取中位数来作为基准，虽然这个算法在现实世界的数据上性能表现良好，但经过精心设计的“破解序列”仍能大幅降低此变体算法的性能。这样就有攻击者精心设计序列发送到因特网服务器以进行拒绝服务（DoS）攻击的潜在可能性。

Musser研究指出，在针对3基准中位数选择算法设计的100,000个元素的“破解序列”上，内省排序的运行时间是这种3基准快速排序的1 / 200。在Musser的算法中，最终较小范围内数据的排序由Sedgewick提出的小数据排序算法完成。

https://zh.wikipedia.org/wiki/%E5%86%85%E7%9C%81%E6%8E%92%E5%BA%8F

https://en.wikipedia.org/wiki/Introsort
