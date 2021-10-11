#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
    {
    "semantic": {
        "slots":    {
            "name": "张三"
        }
    },
    "rc":   0,
    "operation":    "CALL",
    "service":  "telephone",
    "text": "打电话给张三"
}
*/
void printjson(cJSON * root)//以递归的方式打印json的最内层键值对
{
    int i;
    char *out = NULL;
    
    for(i = 0; i<cJSON_GetArraySize(root); i++)   //遍历最外层json键值对
    {
        cJSON * item = cJSON_GetArrayItem(root, i);        
        if(cJSON_Object == item->type)      //如果对应键的值仍为cJSON_Object就递归调用printJson
            printjson(item);
        else                                //值不为json对象就直接打印出键和值
        {
            printf("%s->", item->string);
            out = cJSON_Print(item);
            printf("%s\n", out);free(out);
        }
    }
}

void deconstruction_test(void)
{
    char * jsonStr = "{\"semantic\":{\"slots\":{\"name\":\"张三\"}}, \"rc\":0, \"operation\":\"CALL\", \"service\":\"telephone\", \"text\":\"打电话给张三\"}";
    cJSON * root = NULL;
    cJSON * item = NULL;//cjson对象
 
    root = cJSON_Parse(jsonStr);     
    if (!root) 
    {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
    }
    else
    {
        char *out = NULL;
        
        printf("%s\n", "有格式的方式打印Json:"); 
        out = cJSON_Print(root);
        printf("%s\n\n", out);free(out);
        printf("%s\n", "无格式方式打印json：");
        out = cJSON_PrintUnformatted(root);
        printf("%s\n\n", out);free(out);
 
        printf("%s\n", "一步一步的获取name 键值对:");
        printf("%s\n", "获取semantic下的cjson对象:");
        item = cJSON_GetObjectItem(root, "semantic");//
        out = cJSON_Print(item);
        printf("%s\n", out);free(out);
        printf("%s\n", "获取slots下的cjson对象");
        item = cJSON_GetObjectItem(item, "slots");
        out = cJSON_Print(item);
        printf("%s\n", out);free(out);
        printf("%s\n", "获取name下的cjson对象");
        item = cJSON_GetObjectItem(item, "name");
        out = cJSON_Print(item);
        printf("%s\n", out);free(out);
 
        printf("%s:", item->string);   //看一下cjson对象的结构体中这两个成员的意思
        printf("%s\n", item->valuestring);
                        
 
        printf("\n%s\n", "打印json所有最内层键值对:");
        printjson(root);
        
        cJSON_Delete(root);
    }
}

void construction_test(void)
{
    cJSON * root =  cJSON_CreateObject();
    cJSON * item =  cJSON_CreateObject();
    cJSON * next =  cJSON_CreateObject();
    char *out = NULL;
 
    cJSON_AddItemToObject(root, "rc", cJSON_CreateNumber(0));//根节点下添加
    cJSON_AddItemToObject(root, "operation", cJSON_CreateString("CALL"));
    cJSON_AddItemToObject(root, "service", cJSON_CreateString("telephone"));
    cJSON_AddItemToObject(root, "text", cJSON_CreateString("打电话给张三"));
    cJSON_AddItemToObject(root, "semantic", item);//root节点下添加semantic节点
    cJSON_AddItemToObject(item, "slots", next);//semantic节点下添加item节点
    cJSON_AddItemToObject(next, "name", cJSON_CreateString("张三"));//添加name节点
 
    out = cJSON_Print(root);
    printf("%s\n", out);
    
    free(out);
    
    cJSON_Delete(root);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("deconstruction test:\n\n");
    
    deconstruction_test();
    
    printf("\n\n");
    
    printf("construction test:\n\n");
    
    construction_test();

    printf("\n\n");
    
    return 0;
}
