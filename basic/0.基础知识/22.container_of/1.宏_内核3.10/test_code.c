#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE, MEMBER)	__compiler_offsetof(TYPE, MEMBER)
#else
#define offsetof(TYPE, MEMBER)	((size_t)&((TYPE *)0)->MEMBER)
#endif

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})


/************************************************************************/
/*                                                                      */
/************************************************************************/
struct test
{
    char i ;
    char j;
    int  k;
};

void test_function(char *val)
{
    struct test * ptemp;
    
    ptemp = container_of(val, struct test, j);
    
    printf("ptemp->i %d ptemp->j %d ptemp->k %d\n",
            ptemp->i , ptemp->j, ptemp->k);
}

/****************************/

int main(int argc, char* argv[])
{
    struct test temp;
    
    temp.i = 1;
    temp.j = 20;
    temp.k = 500;
    
    printf("temp.i %d temp.j %d temp.k %d\n",
            temp.i , temp.j, temp.k);
    
    test_function(&temp.j);
    
    return 0;
}