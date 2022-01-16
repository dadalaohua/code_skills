#include <stdio.h>
#include <string.h>
#include "lmdb.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int rc;
    MDB_env *env;
    MDB_dbi dbi;
    MDB_val key, data;
    MDB_txn *txn;
    MDB_cursor *cursor;
    char strKey[50];
    char strValue[50];
    printf("lmdb version:%s\n",mdb_version(0, 0, 0));
    rc = mdb_env_create(&env);
    if(rc){
        printf("mdb_env_create error,detail:%s\n", mdb_strerror(rc));
        return -1;
    }
    
    //打开数据库，如果目录为空，将在该目录内初始化一个数据库
    rc = mdb_env_open(env, "./testdb", 0, 0644);
    if(rc){
        printf("mdb_env_open error,detail:%s\n", mdb_strerror(rc));
        return -1;
    }

    rc = mdb_txn_begin(env, NULL, 0, &txn);
    if(rc){
        printf("mdb_txn_begin error,detail:%s\n", mdb_strerror(rc));
        return -1;
    }

    rc = mdb_dbi_open(txn, NULL, 0, &dbi);
    if(rc){
        printf("mdb_dbi_open error,detail:%s\n", mdb_strerror(rc));
        return -1;
    }

    sprintf(strKey, "%s", "key");
    sprintf(strValue, "%s", "value");
    key.mv_size = strlen(strKey)*sizeof(char);
    key.mv_data = strKey;
    data.mv_size = strlen(strValue)*sizeof(char);
    data.mv_data = strValue;
    
    //写入key-value数据
    rc = mdb_put(txn, dbi, &key, &data, 0);

    //提交
    rc = mdb_txn_commit(txn);
    if (rc) {
        fprintf(stderr, "mdb_txn_commit: (%d) %s\n", rc, mdb_strerror(rc));
        goto leave;
    }

    rc = mdb_txn_begin(env, NULL, MDB_RDONLY, &txn);
    rc = mdb_cursor_open(txn, dbi, &cursor);
    
    //遍历数据库中所有key-value数据
    while ((rc = mdb_cursor_get(cursor, &key, &data, MDB_NEXT)) == 0) {
        memset(strKey, 0, sizeof(strKey));
        memset(strValue, 0, sizeof(strValue));
        strncpy(strKey, (const char*)key.mv_data, (int)key.mv_size);
        strncpy(strValue, (const char*)data.mv_data, (int)data.mv_size);
        printf("key:%s, value:%s\n",strKey, strValue);
    }

    mdb_cursor_close(cursor);
    mdb_txn_abort(txn);

leave:
    mdb_dbi_close(env, dbi);
    mdb_env_close(env);
    return 0;
}