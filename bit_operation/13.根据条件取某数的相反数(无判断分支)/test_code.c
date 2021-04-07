#include <stdio.h>
#include <stdbool.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

//If you need to negate only when a flag is false, then use the following  to avoid branching:
// Flag indicating we should not negate v.
// Input value to negate if fDontNegate is false.
int Conditionally_negate_a_value_false(int val, bool fDontNegate)
{
    return (fDontNegate ^ (fDontNegate - 1)) * val;  // result = fDontNegate ? v : -v;
}

//If you need to negate only when a flag is true, then use this:
// Flag indicating if we should negate v.
// Input value to negate if fNegate is true.
int Conditionally_negate_a_value_true(int val, bool fNegate)
{
    return (val ^ -fNegate) + fNegate;    // result = fNegate ? -v : v;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("%d, %d, %d\n", 10, true, Conditionally_negate_a_value_false(10, true));
    printf("%d, %d, %d\n", 10, false, Conditionally_negate_a_value_false(10, false));
    
    printf("%d, %d, %d\n", -10, true, Conditionally_negate_a_value_false(-10, true));
    printf("%d, %d, %d\n", -10, false, Conditionally_negate_a_value_false(-10, false));
    
    printf("%d, %d, %d\n", 10, true, Conditionally_negate_a_value_true(10, true));
    printf("%d, %d, %d\n", 10, false, Conditionally_negate_a_value_true(10, false));
    
    printf("%d, %d, %d\n", -10, true, Conditionally_negate_a_value_true(-10, true));
    printf("%d, %d, %d\n", -10, false, Conditionally_negate_a_value_true(-10, false));
    
    return 0;
}