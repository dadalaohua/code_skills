/*******************************************************************************
* CRC算法名称   : CRC-16/X25
* 多项式公式    : x16 + x12 + x5 + 1
* 宽度          : 16
* 多项式        : 1021
* 初始值        : FFFF
* 结果异或值    : FFFF
* 输入反转      : true
* 输出反转      : true
*******************************************************************************/

/*******************************************************************************
* CRC算法参数模型解释： 
* CRC算法名称 NAME  ：参数模型名称。 
* 宽度        WIDTH ：宽度，即CRC比特数。 
* 多项式      POLY  ：生成项的简写，以16进制表示 
* 初始值      INIT  ：这是算法开始时寄存器（crc）的初始化预置值，十六进制表示。 
* 结果异或值  REFIN ：待测数据的每个字节是否按位反转，True或False。 
* 输入反转    REFOUT：在计算后之后，异或输出之前，整个数据是否按位反转，True或False。 
* 输出反转    XOROUT：计算结果与此参数异或后得到最终的CRC值。
*******************************************************************************/

表格计算方式
    在crc_common中计算

    int i;
    CRC_16 CRC_16_temp;
    CRC_16_temp.poly          = 1021;
    CRC_16_temp.InitValue     = 0x0000;//计算时初始值采用0
    CRC_16_temp.xor           = 0x0000;//计算时结果异或值采用0
    CRC_16_temp.InputReverse  = TRUE;
    CRC_16_temp.OutputReverse = TRUE;
    
    //计算从0x00 - 0xff 数值
    for(i = 0; i < sizeof(test_arr); i++)
    {
        if(i%8 == 0)
            printf("\n");
        
        printf("0x%.4x, ", crc16(&test_arr[i], 1, CRC_16_temp));
    }
    printf("\n");

表格查询方式
输入反转      : true
输出反转      : true
crc = (crc >> 8) ^ crc_table[(crc ^ *ptr++) & 0xff];

结果异或值    : FFFF
crc ^= 0xffff;
结果相当于取反