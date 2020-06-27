原型：int strcmp(const char firststring[], const char secondstring);
功能：比较两个字符串firststring和secondstring

注意：
1、两个字符串从左到右按照 ACSII 码值大小比较，直到出现不同的字符或者遇到’\0’为止；
2、若出现不相同的字符，则以第一对不相同的字符的比较结果为准；
3、字符串1等于字符串2，函数值为0，字符串1大于字符串2，函数值为正整数，字符串1小于字符串2，函数值为负整数；
4、两个字符串不能直接用str1>str2这种方式比较，必须用strcmp()函数。
