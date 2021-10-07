#ifndef __APP_H__
#define __APP_H__

typedef struct _tag_Stpublic stpublicObj;
struct _tag_Stpublic
{
    int member1;
    int member2;
};

typedef struct _tag_StObj stObj;
struct _tag_StObj
{
    stpublicObj public;
};

//interface
extern stObj * sCreate(int member1,int member2);
extern int sAddprivate(stObj *pObj); 
extern int sAddpublic(stObj *pObj);

#endif