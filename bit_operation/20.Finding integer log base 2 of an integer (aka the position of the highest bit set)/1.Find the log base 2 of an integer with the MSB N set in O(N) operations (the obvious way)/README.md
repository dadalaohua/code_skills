# Find the log base 2 of an integer with the MSB N set in O(N) operations (the obvious way)

### Find the log base 2 of an integer with the MSB N set in O(N) operations (the obvious way)



�� O(N) �������ҵ�һ�������Ķ������� 2��MSB N ����Ϊ O(N)���Զ��׼��ķ�����

��O(N)�������ҵ���2Ϊ��MSB N��������log(���Եķ���)



```
unsigned int v; // 32-bit word to find the log base 2 of
unsigned int r = 0; // r will be lg(v)

while (v >>= 1) // unroll for more speed...
{
  r++;
}
```

The log base 2 of an integer is the same as the position of the highest  bit set (or most significant bit set, MSB).  The following log base 2  methods are faster than this one.

�����Ķ������� 2 �����λ�����������Чλ����MSB����λ����ͬ�� ����� log base 2 ��������������졣

������2Ϊ�׵Ķ��������λ��(�������Чλ����MSB)��λ����ͬ�������log��2Ϊ�׵ķ��������ַ����졣

http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious

