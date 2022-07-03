#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include "proc_info.h"

static PROCESS_INFO *g_proc_ptr = NULL; 
static int g_proc_num = 0;

/******************* 参数信息 *************************/
static struct proc_info **old_procs, **new_procs;
static int num_old_procs, num_new_procs;
static struct proc_info *free_procs;
static int num_used_procs, num_free_procs;
static int max_procs, delay, iterations, threads;
static struct cpu_info old_cpu, new_cpu;
static pthread_t thread_id;  //线程ID
static int running_flag = 0;

/******************* 本地函数声明 *************************/
static struct proc_info *alloc_proc(void);
static void free_proc(struct proc_info *proc);
static void read_procs(void);
static int read_stat(char *filename, struct proc_info *proc);
static void add_proc(int proc_num, struct proc_info *proc);
static int read_cmdline(char *filename, struct proc_info *proc);
static int read_status(char *filename, struct proc_info *proc);
static void update_procs_state(void);
static struct proc_info *find_old_proc(pid_t pid, pid_t tid);
static void free_old_procs(void);
static int (*proc_cmp)(const void *a, const void *b);
static int proc_cpu_cmp(const void *a, const void *b);
static int proc_vss_cmp(const void *a, const void *b);
static int proc_rss_cmp(const void *a, const void *b);
static int proc_thr_cmp(const void *a, const void *b);
static int numcmp(long long a, long long b);
 
void *sys_info_proc(void *arg)        //系统信息处理线程
{
    num_used_procs = 0;
    num_free_procs = 0;
    max_procs = 0;
    delay = 3;
    iterations = -1;
    proc_cmp = &proc_cpu_cmp;
        
    if (threads && proc_cmp == &proc_thr_cmp)
    {
        fprintf(stderr, "Sorting by threads per thread makes no sense!\n");
        exit(EXIT_FAILURE);
    }
    
    free_procs = NULL;
    num_new_procs = num_old_procs = 0;
    new_procs = old_procs = NULL;
    read_procs();
    
    while(running_flag)
    {
        old_procs = new_procs;
        num_old_procs = num_new_procs;
        memcpy(&old_cpu, &new_cpu, sizeof(old_cpu));
        
        sleep(delay);
        
        read_procs();
        update_procs_state();
        free_old_procs();
    }
    
    return NULL;
}

int sys_proc_info_init(PROCESS_INFO *process_array, int num)    //系统进程信息初始化
{
    if(process_array != NULL && num != 0)
    {
        g_proc_ptr = process_array;
        g_proc_num = num;
    }
    else
    {
        printf("----sys_proc_info_init param fail!!\n");
        return -1;
    }
    
    running_flag = 1;
    int ret = pthread_create(&thread_id, NULL, sys_info_proc, NULL);
    if(ret != 0)
    {
        printf("----create sys_info_proc pthread fail!!\n");
        return -1;
    }
    
    return 0;
}

int sys_proc_info_uninit()    //系统进程信息资源释放
{
    running_flag = 0;
    if(thread_id != 0)
    {
        pthread_join(thread_id, NULL);
    }
}

static struct proc_info *alloc_proc(void)
{
    struct proc_info *proc;
    if (free_procs) 
    {
        proc = free_procs;
        free_procs = free_procs->next;
        num_free_procs--;
    } 
    else 
    {
        proc = malloc(sizeof(*proc));
        if (!proc) 
            printf("Could not allocate struct process_info.\n");
    }
    num_used_procs++;
    return proc;
}
 
static void free_proc(struct proc_info *proc)
{
    proc->next = free_procs;
    free_procs = proc;
    num_used_procs--;
    num_free_procs++;
}
  
static void read_procs(void)
{
    DIR *proc_dir, *task_dir;
    struct dirent *pid_dir, *tid_dir;
    char filename[64];
    FILE *file;
    int proc_num;
    struct proc_info *proc;
    pid_t pid, tid;
    int i;
    proc_dir = opendir("/proc");
    if (!proc_dir) 
        printf("Could not open /proc.\n");

    new_procs = calloc(INIT_PROCS * (threads ? THREAD_MULT : 1), sizeof(struct proc_info *));
    num_new_procs = INIT_PROCS * (threads ? THREAD_MULT : 1);
 
    file = fopen("/proc/stat", "r");
    if (!file)
        printf("Could not open /proc/stat.\n");
    
    fscanf(file, "cpu  %lu %lu %lu %lu %lu %lu %lu", &new_cpu.utime, &new_cpu.ntime, &new_cpu.stime,
            &new_cpu.itime, &new_cpu.iowtime, &new_cpu.irqtime, &new_cpu.sirqtime);
    fclose(file);
    
    proc_num = 0;
    while ((pid_dir = readdir(proc_dir)))
    {
        if (!isdigit(pid_dir->d_name[0]))
            continue;
 
        pid = atoi(pid_dir->d_name);
        struct proc_info cur_proc;
        if (!threads) {
            proc = alloc_proc();
            proc->pid = proc->tid = pid;
            sprintf(filename, "/proc/%d/stat", pid);
            read_stat(filename, proc);
 
            sprintf(filename, "/proc/%d/cmdline", pid);
            read_cmdline(filename, proc);
 
            sprintf(filename, "/proc/%d/status", pid);
            read_status(filename, proc);
  
            proc->num_threads = 0;
        } 
        else 
        {
            sprintf(filename, "/proc/%d/cmdline", pid);
            read_cmdline(filename, &cur_proc);

            sprintf(filename, "/proc/%d/status", pid);
            read_status(filename, &cur_proc);
            
            proc = NULL;
        }
 
        sprintf(filename, "/proc/%d/task", pid);
        task_dir = opendir(filename);
        if (!task_dir) continue;
 
        while ((tid_dir = readdir(task_dir)))
        {
            if (!isdigit(tid_dir->d_name[0]))
                continue;

            if (threads) {
                tid = atoi(tid_dir->d_name);

                proc = alloc_proc();

                proc->pid = pid; proc->tid = tid;

                sprintf(filename, "/proc/%d/task/%d/stat", pid, tid);
                read_stat(filename, proc);

                strcpy(proc->name, cur_proc.name);
                proc->uid = cur_proc.uid;
                proc->gid = cur_proc.gid;

                add_proc(proc_num++, proc);
            } else {
                proc->num_threads++;
            }
        }

        closedir(task_dir);
        
        if (!threads)
            add_proc(proc_num++, proc);
    }

    for (i = proc_num; i < num_new_procs; i++)
        new_procs[i] = NULL;
 
    closedir(proc_dir);
}

static int read_stat(char *filename, struct proc_info *proc)
{
    FILE *file;
    char buf[MAX_LINE], *open_paren, *close_paren;

    file = fopen(filename, "r");
    if (!file) return 1;
    fgets(buf, MAX_LINE, file);
    fclose(file);

    /* Split at first '(' and last ')' to get process name. */
    open_paren = strchr(buf, '(');
    close_paren = strrchr(buf, ')');
    if (!open_paren || !close_paren) return 1;

    *open_paren = *close_paren = '\0';
    strncpy(proc->tname, open_paren + 1, THREAD_NAME_LEN);
    proc->tname[THREAD_NAME_LEN-1] = 0;
    
    /* Scan rest of string. */
    sscanf(close_paren + 1, " %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d "
                 "%lu %lu %*d %*d %*d %*d %*d %*d %*d %lu %ld",
                 &proc->state, &proc->utime, &proc->stime, &proc->vss, &proc->rss);
    return 0;
}

static void add_proc(int proc_num, struct proc_info *proc)
{
    int i;

    if (proc_num >= num_new_procs) {
        new_procs = realloc(new_procs, 2 * num_new_procs * sizeof(struct proc_info *));
        if (!new_procs) 
            printf("Could not expand procs array.\n");
        for (i = num_new_procs; i < 2 * num_new_procs; i++)
            new_procs[i] = NULL;
        num_new_procs = 2 * num_new_procs;
    }
    new_procs[proc_num] = proc;
}

static int read_cmdline(char *filename, struct proc_info *proc)
{
    FILE *file;
    char line[MAX_LINE];

    line[0] = '\0';
    file = fopen(filename, "r");
    if (!file) return 1;
    fgets(line, MAX_LINE, file);
    fclose(file);
    if (strlen(line) > 0) {
        strncpy(proc->name, line, PROC_NAME_LEN);
        proc->name[PROC_NAME_LEN-1] = 0;
    } else
        proc->name[0] = 0;
    return 0;
}

static int read_status(char *filename, struct proc_info *proc)
{
    FILE *file;
    char line[MAX_LINE];
    unsigned int uid, gid;

    file = fopen(filename, "r");
    if (!file) return 1;
    while (fgets(line, MAX_LINE, file)) {
        sscanf(line, "Uid: %u", &uid);
        sscanf(line, "Gid: %u", &gid);
    }
    fclose(file);
    proc->uid = uid; proc->gid = gid;
    return 0;
}

static void update_procs_state(void)
{
    int i=0,j=0;
    struct proc_info *old_proc, *proc;
    unsigned long total_delta_time;
    struct passwd *user;
    struct group *group;
    char *user_str, user_buf[20];
    char *group_str, group_buf[20];

    for (i = 0; i < num_new_procs; i++)
    {
        if (new_procs[i])
        {
            old_proc = find_old_proc(new_procs[i]->pid, new_procs[i]->tid);
            if (old_proc)
            {
                new_procs[i]->delta_utime = new_procs[i]->utime - old_proc->utime;
                new_procs[i]->delta_stime = new_procs[i]->stime - old_proc->stime;
            } 
            else 
            {
                new_procs[i]->delta_utime = 0;
                new_procs[i]->delta_stime = 0;
            }
            new_procs[i]->delta_time = new_procs[i]->delta_utime + new_procs[i]->delta_stime;
        }
    }

    total_delta_time = (new_cpu.utime + new_cpu.ntime + new_cpu.stime + new_cpu.itime
                        + new_cpu.iowtime + new_cpu.irqtime + new_cpu.sirqtime)
                     - (old_cpu.utime + old_cpu.ntime + old_cpu.stime + old_cpu.itime
                        + old_cpu.iowtime + old_cpu.irqtime + old_cpu.sirqtime);

    qsort(new_procs, num_new_procs, sizeof(struct proc_info *), proc_cmp);

    int *state_table = (int *)malloc(g_proc_num*sizeof(int));
    memset(state_table, 0, g_proc_num*sizeof(int));//清空监控程序状态
    
    for (i = 0; i < num_new_procs; i++)
    {
        proc = new_procs[i];
        
        if (!proc || (max_procs && (i >= max_procs)))
            break;
        user  = getpwuid(proc->uid);
        group = getgrgid(proc->gid);
        if (user && user->pw_name) {
            user_str = user->pw_name;
        } else {
            snprintf(user_buf, 20, "%d", proc->uid);
            user_str = user_buf;
        }
        if (group && group->gr_name) {
            group_str = group->gr_name;
        } else {
            snprintf(group_buf, 20, "%d", proc->gid);
            group_str = group_buf;
        }
        
        for(j=0; j<g_proc_num; j++)
        {
            if( !strcmp((char *)&proc->tname, (char *)&g_proc_ptr[j].proc_name) )
            {
                g_proc_ptr[j].cpu = proc->delta_time * 100.0 / total_delta_time; //CPU使用率
                if(proc->pid != g_proc_ptr[j].pid)
                {
                    g_proc_ptr[j].reset_times++;        //程序启动次数
                    g_proc_ptr[j].pid = proc->pid;        //进程ID
                }
                g_proc_ptr[j].vss = proc->vss / 1024;   //虚拟内存
                g_proc_ptr[j].rss = proc->rss * getpagesize() / 1024; //物理内存
                g_proc_ptr[j].thread_num = proc->num_threads;   //线程数
                state_table[j] = 1; //进程信息有效
            }
        }
    }
    
    for(j=0; j<g_proc_num; j++)
    {
        g_proc_ptr[j].state = state_table[j];    //进程状态  0 进程不存在           1进程存在
    }
    
    if(NULL != state_table)
    {
        free(state_table);
        state_table = NULL;
    }
}

static struct proc_info *find_old_proc(pid_t pid, pid_t tid)
{
    int i;
    for (i = 0; i < num_old_procs; i++)
        if (old_procs[i] && (old_procs[i]->pid == pid) && (old_procs[i]->tid == tid))
            return old_procs[i];

    return NULL;
}

static void free_old_procs(void)
{
    int i;
    for (i = 0; i < num_old_procs; i++)
        if (old_procs[i])
            free_proc(old_procs[i]);
    free(old_procs);
}

static int proc_cpu_cmp(const void *a, const void *b)
{
    struct proc_info *pa, *pb;

    pa = *((struct proc_info **)a); pb = *((struct proc_info **)b);

    if (!pa && !pb) return 0;
    if (!pa) return 1;
    if (!pb) return -1;
 
    return -numcmp(pa->delta_time, pb->delta_time);
}
 
static int proc_vss_cmp(const void *a, const void *b)
{
    struct proc_info *pa, *pb;

    pa = *((struct proc_info **)a); pb = *((struct proc_info **)b);

    if (!pa && !pb) return 0;
    if (!pa) return 1;
    if (!pb) return -1;

    return -numcmp(pa->vss, pb->vss);
}
 
static int proc_rss_cmp(const void *a, const void *b)
{
    struct proc_info *pa, *pb;

    pa = *((struct proc_info **)a); pb = *((struct proc_info **)b);

    if (!pa && !pb) return 0;
    if (!pa) return 1;
    if (!pb) return -1;

    return -numcmp(pa->rss, pb->rss);
}
 
static int proc_thr_cmp(const void *a, const void *b)
{
    struct proc_info *pa, *pb;

    pa = *((struct proc_info **)a); pb = *((struct proc_info **)b);

    if (!pa && !pb) return 0;
    if (!pa) return 1;
    if (!pb) return -1;

    return -numcmp(pa->num_threads, pb->num_threads);
}

static int numcmp(long long a, long long b)
{
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}
