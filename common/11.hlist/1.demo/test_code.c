#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

#define MAX_STRING_LEN 32
#define MAX_HLIST_COUNT 2 //只有“男”、“女”两条哈希链表

typedef struct student
{
    char m_name[MAX_STRING_LEN];
    char m_sex;
    int m_age;
    struct list_head m_list; /*把我们的学生对象组织成双向链表，就靠该节点了*/
    struct hlist_node m_hlist; /*把我们的学生对象组织成哈希链表，就靠该节点了*/
}Student;

/************************************************************************/
/*                                                                      */
/************************************************************************/

static int dbg_flg = 0;

LIST_HEAD(g_student_list);
// 其中g_stu_hlist[0]代表男生；g_stu_hlist[1]代表女生
struct hlist_head g_stu_hlist[MAX_HLIST_COUNT];

//初始化男、女学生的哈希链表 
static void init_hlists(void)
{
    int i = 0;
    for(i=0;i< MAX_HLIST_COUNT;i++){
        INIT_HLIST_HEAD(&g_stu_hlist[i]);
    }
}

static int add_stu(char* name,char sex,int age)
{
    Student *stu,*cur_stu;

    list_for_each_entry(cur_stu,&g_student_list,m_list){ //仅遍历是否有同名学生，所以用该接口
        if(0 == strcmp(cur_stu->m_name,name))
        {
            printf("Error:the name confict!\n");
            return -1;
        }
    }

    stu = (Student *)malloc(sizeof(Student));
    if(!stu)
    {
        printf("malloc mem error!\n");
        return -1;
    }

    memset(stu,0,sizeof(Student));
    strncpy(stu->m_name,name,strlen(name));
    stu->m_sex = sex;
    stu->m_age = age;
    INIT_LIST_HEAD(&stu->m_list);    //初始化宿主结构里的双向链表节点m_list
    INIT_HLIST_NODE(&stu->m_hlist);  //初始化宿主结构里的哈希节点m_hlist

    if(dbg_flg)
        printf("(Add)name:[%s],\tsex:[%c],\tage:[%d]\n",stu->m_name,stu->m_sex,stu->m_age);


    list_add_tail(&stu->m_list,&g_student_list); //将新学生插入到链表尾部，很简单吧

    return 0;
}

static int del_stu(char *name)
{
    Student *cur,*next;
    int ret = -1;
    list_for_each_entry_safe(cur,next,&g_student_list,m_list){ //因为要删除链表的节点，所以必须有带有“safe”的宏接口
        if(0 == strcmp(name,cur->m_name))
        {
                list_del(&cur->m_list);
                printf("(Del)name:[%s],\tsex:[%c],\tage:[%d]\n",cur->m_name,\
                                cur->m_sex,cur->m_age);
                free(cur);
                cur = NULL;
                ret = 0;
                break;
        }
    }
    return ret;
}

static void dump_students(void)
{
    Student *stu;
    int i = 1;
    printf("===================Student List================\n");
    list_for_each_entry(stu,&g_student_list,m_list){ //同样，也仅遍历链表而已
            printf("(%d)name:[%s],\tsex:[%c],\tage:[%d]\n",i++,stu->m_name,\
                    stu->m_sex,stu->m_age);
    }
    printf("===============================================\n");
}

static void dump_hlist(int id)
{
    Student *stu;
    struct hlist_node *i;
    struct hlist_head *head;
    int count = 1;

    if(!(id>=0 && id< MAX_HLIST_COUNT)){
            printf("Invalid id[%d] !\n",id);
            return;
    }
    head = &g_stu_hlist[id];

    printf("===================%s List===================\n",((id == 0)?"Boy":"Girl"));
    //因为该接口只遍历哈希表，并不会插入、删除节点，所以用hlist_for_each_entry()，注意四个入参的类型、作用和意义
    hlist_for_each_entry(stu, i, head,m_hlist){ 
            printf("(%d)name:[%s],\tsex:[%c],\tage:[%d]\n",count++,stu->m_name,\
                    stu->m_sex,stu->m_age);
    }
    printf("==============================================\n");
}

//分别打印男女学生，各自哈希链表上的情况 
static void dump_hlists(void)
{
    dump_hlist(0);
    dump_hlist(1);
}

//按照性别对学生进行分类
static void classify_stu(void)
{
    Student *cur,*next;
    int id = 0;

    list_for_each_entry_safe(cur,next,&g_student_list,m_list){
            //将从cur从g_student_list链表上移下来，但并不会释放cur学生的内存空间，同时对其m_list成员重新初始化
            list_del_init(&cur->m_list);
            if('m' == cur->m_sex){
                    id = 0;
            }
            else if('f' == cur->m_sex){
                    id = 1;
            }
            else{
                    printf("Get error!\n");
                    return;
            }
            //根据id，以m_hlist将学生按性别组织成哈希表
            hlist_add_head(&(cur->m_hlist),&(g_stu_hlist[id]));
    }
    printf("Finished!\n");
}

static void init_system(void)
{
    //初始化男、女学生哈希链表头
    init_hlists();

    /*系统启动初始化时，向链表g_student_list里添加6个学生*/
    add_stu("Tom",'m',18);
    add_stu("Jerry",'f',17);
    add_stu("Alex",'m',18);
    add_stu("Conory",'f',18);
    add_stu("Frank",'m',17);
    add_stu("Marry",'f',17);
}

/*释放所有哈希链表上的内存空间*/
static void clean_up_hlist(void)
{
    int i;
    Student *stu;
    struct hlist_node *cur,*next;

    for(i=0;i< MAX_HLIST_COUNT;i++){
        printf("===================%s List================\n",((i == 0)?"Boy":"Girl"));
        hlist_for_each_entry_safe(stu, cur, next, &(g_stu_hlist[i]), m_hlist){
            hlist_del(&(stu->m_hlist));
            printf("Destroy [%s]\n",stu->m_name);
            free(stu);
        }
        printf("===========================================\n");
    }
}

/*释放双向表上的内存空间*/
static void clean_up_list(void)
{
        Student *stu,*next;
        printf("===========Unclassified Student List===========\n");
        list_for_each_entry_safe(stu,next,&g_student_list,m_list){
                list_del(&stu->m_list);
                printf("Destroy [%s]\n",stu->m_name);
                free(stu);
        }
        printf("===============================================\n");
}

/*因为没有数据库，所以当我们的模块退出时，需要释放内存。*/
static void clean_up(void)
{
    clean_up_list();
    clean_up_hlist();
}

/*模块初始化接口*/
static int student_mgt_init(void)
{
    printf("Student Managment System,Initializing...\n");

    init_system();
    dbg_flg = 1; //从此以后，再调用add_stu()时，都会有有内核打印信息，详见实例训练
    dump_students();

    return 0;
}

static void student_mgt_exit(void)
{
    clean_up();
    printf("System Terminated!\n");
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{  
    student_mgt_init();
    
    dump_hlists();

    classify_stu();
    
    dump_students();
    
    dump_hlists();
    
    add_stu("Bob", 'm', 19);
    
    add_stu("Kity", 'f', 18);
    
    dump_students();
    
    classify_stu();
    
    dump_students();
    
    dump_hlists();
    
    student_mgt_exit();

    return 0;
}