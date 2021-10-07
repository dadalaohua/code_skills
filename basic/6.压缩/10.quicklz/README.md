# QuickLZ

http://www.quicklz.com/download.html
http://www.quicklz.com/manual.html

Please read following before using QuickLZ. Version 1.5.x supports following settings:

QLZ_COMPRESSION_LEVEL	Set to 1, 2 or 3. Level 1 gives the fastest compression speed while level 3 gives the fastest decompression speed.

设置为 1、2 或 3。级别 1 提供最快的压缩速度，而级别 3 提供最快的解压速度。

QLZ_STREAMING_BUFFER	Because LZ compression is based on finding repeated strings, compression ratio can degrade if a data entity is being split into smaller packets (less than 10 - 50 Kbytes) that are compressed individually.

由于 LZ 压缩基于查找重复字符串，因此如果将数据实体拆分为单独压缩的较小数据包（小于 10 - 50 KB），则压缩率会降低。

Set to 0 to disable streaming mode or to 100000 or 1000000 (suggested values) to enable and make QuickLZ store a history buffer of QLZ_STREAMING_BUFFER bytes in size.

设置为 0 以禁用流模式或设置为 100000 或 1000000（建议值）以启用并使 QuickLZ 存储大小为 QLZ_STREAMING_BUFFER 字节的历史缓冲区。

When enabled, data must be decompressed in the same order as it was compressed. Further issues apply - see the manual for the C version.

启用后，数据必须按照与压缩相同的顺序进行解压缩。其他问题适用 - 请参阅 C 版本的手册。

QLZ_MEMORY_SAFE	If enabled, decompression of corrupted data cannot crash, meaning that it's guaranteed to terminate and guaranteed not to make spurious memory access. Enabling decreases decompression speed in the order of 15-20%.

由于性能原因，这些设置不能在运行时动态指定。对于 C 版本，必须在 quicklz.h 文件的开头指定它们，然后必须编译库。对于 DLL 版本，每个设置排列都有一个 DLL 文件。 C# 和 Java 版本仅提供一个设置。

Because of performance reasons these settings cannot be specified dynamically at runtime. For the C version, they must be specified in the beginning of the quicklz.h file whereafter the library must be compiled. For the DLL version one DLL file exists for each permutation of settings. The C# and Java versions only offer a single setting.

如果启用，损坏数据的解压缩不会崩溃，这意味着它保证终止并保证不会进行虚假内存访问。启用可将减压速度降低 15-20%。

Data must be decompressed with the same setting of QLZ_COMPRESSION_LEVEL and QLZ_STREAMING_BUFFER as it was compressed.

数据必须使用与压缩时相同的 QLZ_COMPRESSION_LEVEL 和 QLZ_STREAMING_BUFFER 设置进行解压缩。
