size_t strcspn(const char *string, const char *strCharSet); 
查找strCharSet串中任何一个字符在string串中首次出现的位置序号, 包含字符串结束符NULL. 
返回一个整数值, 指定在string中全部由非characters中的字符组成的子串的长度. 如果string以一个包含在strCharSet中的字符开头, 函数将返回0值. 
