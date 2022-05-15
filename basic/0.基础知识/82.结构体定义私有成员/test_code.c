#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "private_person.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    Person *p = PersonNew("bennyhuo", 10, NULL);
    printf("name: %s\n", PersonGetName(p));
    printf("age: %d\n", PersonGetAge(p));
    PersonToString(p);
    PersonSetIntro(&p, "Kotlin GDE");
    PersonToString(p);
    PersonDestroy(&p);
    
    return 0;
}