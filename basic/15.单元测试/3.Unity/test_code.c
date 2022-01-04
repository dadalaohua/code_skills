#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unity.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
void setUp(void) {
    // set stuff up here
    printf("setUp\n");
}

void tearDown(void) {
    // clean stuff up here
    printf("tearDown\n");
}

void test_function_should_doBlahAndBlah(void) {
    //test stuff
    printf("test_function_should_doBlahAndBlah\n");
}

void test_function_should_doAlsoDoBlah(void) {
    //more test stuff
    printf("test_function_should_doAlsoDoBlah\n");
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_function_should_doBlahAndBlah);
    RUN_TEST(test_function_should_doAlsoDoBlah);
    return UNITY_END();
}