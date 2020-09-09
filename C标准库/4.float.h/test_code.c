#include <stdio.h>
#include <float.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("FLT_ROUNDS   = %d\n", FLT_ROUNDS);
    
    printf("FLT_RADIX    = %d\n", FLT_RADIX);
    
    printf("FLT_MANT_DIG = %d\n", FLT_MANT_DIG);
    printf("DBL_MANT_DIG = %d\n", DBL_MANT_DIG);
    printf("LDBL_DIG     = %d\n", LDBL_DIG);
    
    printf("FLT_MIN_EXP  = %d\n", FLT_MIN_EXP);
    printf("DBL_MIN_EXP  = %d\n", DBL_MIN_EXP);
    printf("LDBL_MIN_EXP = %d\n", LDBL_MIN_EXP);
    
    printf("FLT_MIN_10_EXP  = %d\n", FLT_MIN_10_EXP);
    printf("DBL_MIN_10_EXP  = %d\n", DBL_MIN_10_EXP);
    printf("LDBL_MIN_10_EXP = %d\n", LDBL_MIN_10_EXP);

    printf("FLT_MAX_EXP     = %d\n", FLT_MAX_EXP);
    printf("DBL_MAX_EXP     = %d\n", DBL_MAX_EXP);
    printf("LDBL_MAX_EXP    = %d\n", LDBL_MAX_EXP);

    printf("FLT_MAX_10_EXP     = %d\n", FLT_MAX_10_EXP);
    printf("DBL_MAX_10_EXP     = %d\n", DBL_MAX_10_EXP);
    printf("LDBL_MAX_10_EXP    = %d\n", LDBL_MAX_10_EXP);

    printf("FLT_MAX     = %.10e\n", FLT_MAX);
    printf("DBL_MAX     = %.10e\n", DBL_MAX);
    printf("LDBL_MAX    = %.10Le\n", LDBL_MAX);
    
    printf("FLT_EPSILON     = %.10e\n", FLT_EPSILON);
    printf("DBL_EPSILON     = %.10e\n", DBL_EPSILON);
    printf("LDBL_EPSILON    = %.10Le\n", LDBL_EPSILON);
    
    printf("FLT_MIN     = %.10e\n", FLT_MIN);
    printf("DBL_MIN     = %.10e\n", DBL_MIN);
    printf("LDBL_MIN    = %.10Le\n", LDBL_MIN);
    
    printf("The maximum value of float = %.10e\n", FLT_MAX);
    printf("The minimum value of float = %.10e\n", FLT_MIN);

    printf("The number of digits in the number = %d\n", FLT_MANT_DIG);
    
    return 0;
}