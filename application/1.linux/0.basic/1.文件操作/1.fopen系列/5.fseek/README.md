����
C �⺯�� int fseek(FILE *stream, long int offset, int whence) ������ stream ���ļ�λ��Ϊ������ƫ�� offset������ offset ��ζ�ŴӸ����� whence λ�ò��ҵ��ֽ�����

����
������ fseek() ������������
int fseek(FILE *stream, long int offset, int whence)

����
stream -- ����ָ�� FILE �����ָ�룬�� FILE �����ʶ������
offset -- ������� whence ��ƫ���������ֽ�Ϊ��λ��
whence -- ���Ǳ�ʾ��ʼ���ƫ�� offset ��λ�á���һ��ָ��Ϊ���г���֮һ��

����              ����
SEEK_SET        �ļ��Ŀ�ͷ
SEEK_CUR        �ļ�ָ��ĵ�ǰλ��
SEEK_END        �ļ���ĩβ

����ֵ
����ɹ�����ú��������㣬���򷵻ط���ֵ��
