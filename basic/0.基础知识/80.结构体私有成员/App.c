//#include "App.h"

typedef struct _tag_Stpublic stpublicObj;
struct _tag_Stpublic
{
    int member1;
    int member2;
};

typedef struct _tag_Stprivate stprivateObj;
struct _tag_Stprivate
{
    int member1;
    int member2;
};

typedef struct _tag_StObj stObj;
struct _tag_StObj
{
    stpublicObj public;
    stprivateObj private;
};

/********************************** 
 * Function :  sCreate
 * Note :创建对象
 * Author: bug菌
 **********************************/ 
stObj * sCreate(int member1,int member2)
{
    static  stObj staticObj;

    staticObj.private.member1 = member1;
    staticObj.private.member2 = member2;

    return &staticObj;
}

/********************************** 
 * Function :  sAdd
 * Note :对象方法
 * Author: bug菌
 **********************************/ 
int sAddprivate(stObj *pObj)
{
    return (pObj->private.member1 + pObj->private.member2);
}

/********************************** 
 * Function :  sAdd
 * Note :对象方法
 * Author: bug菌
 **********************************/ 
int sAddpublic(stObj *pObj)
{
    return (pObj->public.member1 + pObj->public.member2);
}