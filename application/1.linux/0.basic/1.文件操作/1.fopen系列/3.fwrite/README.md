����
C �⺯�� size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) �� ptr ��ָ��������е�����д�뵽������ stream �С�
����
������ fwrite() ������������
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
����
ptr -- ����ָ��Ҫ��д���Ԫ�������ָ�롣
size -- ����Ҫ��д���ÿ��Ԫ�صĴ�С�����ֽ�Ϊ��λ��
nmemb -- ����Ԫ�صĸ�����ÿ��Ԫ�صĴ�СΪ size �ֽڡ�
stream -- ����ָ�� FILE �����ָ�룬�� FILE ����ָ����һ���������
����ֵ
����ɹ����ú�������һ�� size_t ���󣬱�ʾԪ�ص��������ö�����һ�������������͡������������ nmemb ������ͬ�������ʾһ������
