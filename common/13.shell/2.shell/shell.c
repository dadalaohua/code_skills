#include "stdio.h"
#include "string.h"
#include "shell.h"

static void* args[7][100] = {{0}};

const CALLFUNCTIONTABLE functable[] =
{
    EXPOTRFUNC(LIST,ExternFunc_list, ,�����б�),
    EXPOTRFUNC(circle, showcircle, %c %d,������ʾһ��Բ),
    EXPOTRFUNC(show99, show, %d,%d�˷���),
    EXPOTRFUNC(simp, simplefunction, %s %X %f %c,��ʽ���Ժ���)
};

static unsigned char matchString(const char* str1,const char* str2)
{
    char* ptemp1 = (char*) str1;
    char* ptemp2 = (char*) str2;
    while(*ptemp1 != '\0' || *ptemp2 != '\0')
    {
#if MATCH_CASE_ENABLE==0        
        if(((*ptemp1-*ptemp2) == ('A'-'a') || (*ptemp1-*ptemp2) == ('a'-'A'))&& 
            (*ptemp1>= 'A' && *ptemp1<= 'z' && *ptemp2>= 'A' && *ptemp2<= 'z'))
        {
            ptemp1++;
            ptemp2++;  
        }else if(*ptemp1 != *ptemp2) return 1;
#else
        if(*ptemp1 != *ptemp2) return 1;
#endif
            
        else 
        {
            ptemp1++;
            ptemp2++;            
        }
    }
    if(*ptemp1 == '\0'&& *ptemp2 == '\0')
        return 0;
    else
        return 0xFF;
}

static int ExternFunc_Find(char* funcname)
{
    int size = sizeof(functable)/sizeof(functable[0]);
    
    for(int i = 0; i<size; i++)
    {
        if(matchString(funcname,functable[i].FuncName) == 0)
            return i;
    }
    return -1;
}

void ExternFunc_list(void)
{
    int size = sizeof(functable)/sizeof(functable[0]);
    
    printf("QuickComplet:");
    
    for(int i = 0;i<size;i++)
    {
        printf("\"%s\"",functable[i].FuncName);
        if(i != (size-1))
            printf(",");
    }
    printf("\n\n*---------------------------------------------------------\n");
    
    for(int i = 0; i<size; i++)
    {
        printf(" |    %s(%s);%30s\n",functable[i].FuncName,functable[i].fmt,functable[i].Introduction);
        if(i != size-1)
            printf(" |--------------------------------------------------------\n");
    }
    printf("*---------------------------------------------------------\n");
}

void ExternFunc_excute(char* str)
{
    char* ptemp;
    char ch;
    ptemp = strstr(str," ");
    if(ptemp == NULL)
    {
        ptemp = str+strlen(str);
        ch = *ptemp;
    }
    else
    {
        ch = '\0';
        *ptemp = '\0';
        ptemp++;
    }

    
    int loc = ExternFunc_Find(str); //Ѱ�Һ���
    if(loc == -1)
    {
        printf("%s are not find\n the function list :\n",str);
        ExternFunc_list();
        return ;
    }

    if(ch != '\0')
        *ptemp = ch;
    int success = sscanf(ptemp,functable[loc].fmt,&args[0][1],&args[1][1],&args[2][1],&args[3][1],&args[4][1],&args[5][1]);
    
    //Ϊ���� ���������ַ�������������Э
    int i = 0;
    ptemp = (char*)functable[loc].fmt;
    for(i = 0;i<7;i++)
    {
        if((ptemp=strstr(ptemp,"%")) !=NULL)
        {
            
            if(*(++ptemp) == 's')
                args[i][0] = &args[i][1];
            else if(*ptemp == 'f')
            {
                args[i][0] = args[i][1];
            }else               
                args[i][0] = args[i][1];
        }else break;
    }
    if(i!= success)
    {    
        printf("Err: ����%s ����Ӧ��Ϊ%d��,��ֻ��%d\n",functable[loc].FuncName,i,success);
        return ;
    }
    //���������ĺ���    
    functable[loc].func(args[0][0],args[1][0],args[2][0],args[3][0],args[4][0],args[5][0],args[6][0]);
}



