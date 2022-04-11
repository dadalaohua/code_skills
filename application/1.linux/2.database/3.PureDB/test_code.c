#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "puredb_p.h"
#include "puredb_read.h"
#include "puredb_write.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    PureDBW dbw;
    char key[42];
    char data[42];
    
    if (puredbw_open(&dbw, "puredb.index", "puredb.data", "puredb.pdb") != 0) {
        perror("Can't create the database");
        return 0;
    }
    
    for(int i = 0; i < 3000; i++) {
        snprintf(key, sizeof key, "%u", i);
        snprintf(data, sizeof data, "%u", i + 10);
        
        if (puredbw_add_s(&dbw, key, data) != 0) {
            return 0;
        }
    }
    
    if (puredbw_close(&dbw) != 0) {
        return 0;
    }
    
    puredbw_free(&dbw);
    
    PureDB db;
    off_t retpos;
    size_t retlen;
    char *founddata;
    
    if (puredb_open(&db, "puredb.pdb") != 0) {
        perror("Can't open the database");
        return 0;
    }
    
    for(int i = 0; i < 100; i++) {
        snprintf(key, sizeof key, "%u", i);
        snprintf(data, sizeof data, "%u", i + 10);
        
        if (puredb_find_s(&db, key, &retpos, &retlen) != 0) {
            fprintf(stderr, "The key wasn't found\n");
            return 0;
        }
        
        if ((founddata = puredb_read(&db, retpos, retlen)) != NULL) {
            printf("founddata %s\n", founddata);
            if (strcmp(founddata, data) != 0) {
                fprintf(stderr, "Wrong data\n");
                return 0;
            }
            puredb_read_free(founddata);
        }
    }
    
    if (puredb_close(&db) != 0) {
        perror("The database couldn't be properly closed");
    }
    
    return 0;
}