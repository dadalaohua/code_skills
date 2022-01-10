/************************************************************************/
/*                                                                      */
/************************************************************************/
#include "ubench.h"

#if !defined(_MSC_VER)
#include <unistd.h>

UBENCH(c, tenth_of_a_second) { usleep(100 * 1000); }
#endif

UBENCH(c, do_nothing) {
  static char a[8 * 1024 * 1024];
  static char b[8 * 1024 * 1024];
  UBENCH_DO_NOTHING(a);
  memcpy(b, a, sizeof(a));
  UBENCH_DO_NOTHING(b);
}

UBENCH_EX(c, ex)
{
  int b[1024];
  int i;
  int sum;
  memset(b, 0x0, sizeof(b));

  UBENCH_DO_BENCHMARK()
  {
    sum = 0;
    for(i = 0; i < 1024; ++i)
      sum += i;
  }
}

struct c_my_fixture {
  char *data;
};

UBENCH_F_SETUP(c_my_fixture) {
  const int size = 128 * 1024 * 1024;
  ubench_fixture->data = (char *)malloc(size);
  memset(ubench_fixture->data, ' ', size - 1);
  ubench_fixture->data[size - 1] = '\0';
  ubench_fixture->data[size / 2] = 'f';
}

UBENCH_F_TEARDOWN(c_my_fixture) { free(ubench_fixture->data); }

UBENCH_F(c_my_fixture, strchr) {
  UBENCH_DO_NOTHING(strchr(ubench_fixture->data, 'f'));
}

UBENCH_F(c_my_fixture, strrchr) {
  UBENCH_DO_NOTHING(strrchr(ubench_fixture->data, 'f'));
}

UBENCH_EX_F(c_my_fixture, strrchr_ex)
{
  char data[128*4];
  memcpy(data, ubench_fixture->data, sizeof(data));
  data[sizeof(data)-1] = '\0';
  
  UBENCH_DO_BENCHMARK()
  {
    UBENCH_DO_NOTHING(strchr(data, 'f'));
  }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
UBENCH_MAIN()
// int main(int argc, char* argv[])
// {
    
    // return 0;
// }