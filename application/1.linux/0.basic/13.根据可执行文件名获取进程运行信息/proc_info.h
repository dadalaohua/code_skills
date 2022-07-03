/******************************************************************************
*** 文 件 名    : proc_info.h
*** 作   者     : fangye
*** 生成日期    : 2019年3月 星期二
*** 功能描述    : 获取系统进程信息
*******************************************************************************/
#ifndef __PROC_INFO_H__
#define __PROC_INFO_H__
 
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define PROC_NAME_LEN 64
#define THREAD_NAME_LEN 32
#define MAX_LINE 256
#define INIT_PROCS 50
#define THREAD_MULT 8

struct cpu_info {
    unsigned long utime, ntime, stime, itime;
    unsigned long iowtime, irqtime, sirqtime;
};

struct proc_info {
    struct proc_info *next;
    pid_t pid;
    pid_t tid;
    uid_t uid;
    gid_t gid;
    char name[PROC_NAME_LEN];
    char tname[THREAD_NAME_LEN];
    char state;
    unsigned long utime;
    unsigned long stime;
    unsigned long delta_utime;
    unsigned long delta_stime;
    unsigned long delta_time;
    long vss;
    long rss;
    int num_threads;
    char policy[32];
};

struct proc_list {
    struct proc_info **array;
    int size;
};

typedef struct _PROCESS_INFO
{
    char proc_name[PROC_NAME_LEN];
    int state;          //运行状态  0未运行    1运行中
    int thread_num;     //线程数
    long vss;           //虚拟内存
    long rss;           //物理内存
    int pid;            //进程ID
    int reset_times;    //启动次数
    double cpu;         //CPU使用率
}PROCESS_INFO;

extern int sys_proc_info_init();    //系统进程信息初始化
extern int sys_proc_info_uninit();  //系统进程信息资源释放

#ifdef __cplusplus
}
#endif /* __cplusplus */
 
#endif /* __PROC_INFO_H__ */