char *strpbrk(const char *string, const char *strCharSet); 
查找strCharSet串中任何一个字符在string串中首次出现的位置, 不包含字符串结束符NULL. 
返回一个指针, 指向strCharSet中任一字符在string中首次出现的位置. 如果两个字符串参数不含相同字符, 则返回NULL值. 
