����
C �⺯�� size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) �Ӹ����� stream ��ȡ���ݵ� ptr ��ָ��������С�
����
������ fread() ������������
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
����
ptr -- ����ָ�������С�ߴ� size*nmemb �ֽڵ��ڴ���ָ�롣
size -- ����Ҫ��ȡ��ÿ��Ԫ�صĴ�С�����ֽ�Ϊ��λ��
nmemb -- ����Ԫ�صĸ�����ÿ��Ԫ�صĴ�СΪ size �ֽڡ�
stream -- ����ָ�� FILE �����ָ�룬�� FILE ����ָ����һ����������
����ֵ
�ɹ���ȡ��Ԫ���������� size_t ���󷵻أ�size_t ������һ�������������͡���������� nmemb ������ͬ������ܷ�����һ��������ߵ������ļ�ĩβ��
