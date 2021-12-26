#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>

#include "jwHash.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/
int basic_test(void)
{
    // create
    jwHashTable * table = create_hash(10);
    if(!table) {
        // fail
        return 1;
    }
    
    // add a few values
    char * str1 = "string 1";
    char * str2 = "string 2";
    char * str3 = "string 3";
    char * str4 = "string 4";
    char * str5 = "string 5";
    add_str_by_int(table,0,str1);
    add_str_by_int(table,1,str2);
    add_str_by_int(table,2,str3);
    add_str_by_int(table,3,str4);
    add_str_by_int(table,4,str5);
    
    char * sstr1; get_str_by_int(table,0,&sstr1);
    char * sstr2; get_str_by_int(table,1,&sstr2);
    char * sstr3; get_str_by_int(table,2,&sstr3);
    char * sstr4; get_str_by_int(table,3,&sstr4);
    char * sstr5; get_str_by_int(table,4,&sstr5);
    printf("got strings: \n1->%s\n2->%s\n3->%s\n4->%s\n5->%s\n",sstr1,sstr2,sstr3,sstr4,sstr5);
    
    del_by_int(table, 0);
    del_by_int(table, 1);
    del_by_int(table, 2);
    del_by_int(table, 3);
    del_by_int(table, 4);
    
    // Test hashing by string
    char * strv1 = "Jonathan";
    char * strv2 = "Zevi";
    char * strv3 = "Jude";
    char * strv4 = "Voldemort";
    
    add_str_by_str(table,"oldest",strv1);
    add_str_by_str(table,"2ndoldest",strv2);
    add_str_by_str(table,"3rdoldest",strv3);
    add_str_by_str(table,"4tholdest",strv4);
    
    char * sstrv1; get_str_by_str(table,"oldest",&sstrv1);
    char * sstrv2; get_str_by_str(table,"2ndoldest",&sstrv2);
    char * sstrv3; get_str_by_str(table,"3rdoldest",&sstrv3);
    char * sstrv4; get_str_by_str(table,"4tholdest",&sstrv4);
    printf("got strings:\noldest->%s \n2ndoldest->%s \n3rdoldest->%s \n4tholdest->%s\n",
        sstrv1,sstrv2,sstrv3,sstrv4);
    return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define NUMTHREADS 6
#define HASHCOUNT 1000000

typedef struct threadinfo {jwHashTable *table; int start;} threadinfo;
void thread_func(void *arg)
{
    threadinfo *info = arg;
    char buffer[512];
    int i = info->start;
    jwHashTable *table = info->table;
    free(info);
    for(;i<HASHCOUNT;i+=NUMTHREADS) {
        sprintf(buffer,"%d",i);
        add_int_by_str(table,buffer,i);
    }
}

int thread_test(void)
{
    // create
    jwHashTable * table = create_hash(HASHCOUNT>>2);

    // hash a million strings into various sizes of table
    struct timeval tval_before, tval_done1, tval_done2, tval_writehash, tval_readhash;
    gettimeofday(&tval_before, NULL);
    int t;
    pthread_t * threads[NUMTHREADS];
    for(t=0;t<NUMTHREADS;++t) {
        pthread_t * pth = malloc(sizeof(pthread_t));
        threads[t] = pth;
        threadinfo *info = (threadinfo*)malloc(sizeof(threadinfo));
        info->table = table; info->start = t;
        pthread_create(pth,NULL,(void *)thread_func,info);
    }
    for(t=0;t<NUMTHREADS;++t) {
        pthread_join(*threads[t], NULL);
    }
    gettimeofday(&tval_done1, NULL);
    int i,j;
    int error = 0;
    char buffer[512];
    for(i=0;i<HASHCOUNT;++i) {
        sprintf(buffer,"%d",i);
        get_int_by_str(table,buffer,&j);
        if(i!=j) {
            printf("Error: %d != %d\n",i,j);
            error = 1;
        }
    }
    if(!error) {
        printf("No errors.\n"); 
    }
    gettimeofday(&tval_done2, NULL);
    timersub(&tval_done1, &tval_before, &tval_writehash);
    timersub(&tval_done2, &tval_done1, &tval_readhash);
    printf("\n%d threads.\n",NUMTHREADS);
    printf("Store %d ints by string: %ld.%06ld sec, read %d ints: %ld.%06ld sec\n",HASHCOUNT,
        (long int)tval_writehash.tv_sec, (long int)tval_writehash.tv_usec,HASHCOUNT,
        (long int)tval_readhash.tv_sec, (long int)tval_readhash.tv_usec);
    
    return 0;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    if( 0 == basic_test() ) {
        printf("basic_test:\tPassed\n");
    }
    
    if( 0==thread_test() ) {
        printf("thread_test:\tPassed\n");
    }
    
    return 0;
}