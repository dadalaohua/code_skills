#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))

typedef struct {
    unsigned int mask;
    char* info;
} mask_info_t;

mask_info_t mask_buf[] = {
    {IN_ACCESS,         "文件被访问"},
    {IN_MODIFY,         "文件被修改"},
    {IN_ATTRIB,         "文件元数据被修改"},//文件属性被修改
    {IN_CLOSE_WRITE,    "文件被写入并关闭"},//关闭为了写入而打开的文件
    {IN_CLOSE_NOWRITE,  "文件被关闭但未写入"},//关闭以只读方式打开的文件/不可写文件被关闭
    {IN_OPEN,           "文件被打开"},
    {IN_MOVED_FROM,     "文件被移除"},//文件移出到受监控目录之外
    {IN_MOVED_TO,       "文件被移动到"},//将文件移入受监控目录
    {IN_CREATE,         "文件被创建"},//在受监控目录内创建了文件/目录
    {IN_DELETE,         "文件被删除"},//在受监控目录内删除了文件/目录
    {IN_DELETE_SELF,    "监视的文件本身被删除"},//删除受监控目录/文件本身
    {IN_MOVE_SELF,      "监视的文件本身被移动"},//移动受监控目录/文件本身
    {IN_UNMOUNT,        "文件系统被卸载"},//包含对象的文件系统遭卸载
    {IN_CLOSE,          "文件被关闭"},//IN_CLOSE_WRITE | IN_CLOSE_NOWRITE 事件的统称
    {IN_MOVE,           "文件被移动"},//IN_MOVED_FROM | IN_MOVED_TO 事件的统称
    {IN_ONLYDIR,        "只监视目录"},//pathname 不为目录时会失败
    {IN_DONT_FOLLOW,    "不跟踪符号链接"},//不对符号链接解引用
    {IN_MASK_ADD,       "将新的mask添加到已有的掩码中"},//将事件追加到 pathname 的当前监控掩码
    {IN_ISDIR,          "事件是目录"}, //name 中所返回的文件名为路径
    {IN_ONESHOT,        "只监控 pathname 的一个事件"},
    {IN_IGNORED,        "监控项为内核或应用程序所移除"},
    {IN_Q_OVERFLOW,        "事件队列溢出"},
    //{IN_ALL_EVENTS,     "所有事件"}, //以上所有输出事件的统称
};

int main(int argc, char **argv)
{
    int fd, wd;
    char buffer[BUF_LEN];

    fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    //wd = inotify_add_watch(fd, "./tmp", IN_CREATE | IN_DELETE);
    wd = inotify_add_watch(fd, "./tmp", IN_ALL_EVENTS);
    if (wd < 0) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    printf("Watching /tmp for events\n");

    while (1) {
        int len, i = 0;
        len = read(fd, buffer, BUF_LEN);
        if (len < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        while (i < len) {
            struct inotify_event *event = (struct inotify_event *) &buffer[i];
            // if (event->mask & IN_CREATE) {
                // printf("File %s was created\n", event->name);
            // } else if (event->mask & IN_DELETE) {
                // printf("File %s was deleted\n", event->name);
            // }
            
            printf("wd %d mask 0x%x cookie %d len %d name %s\n", event->wd, event->mask, event->cookie, event->len, event->name);
            
            for(int i = 0; i < sizeof(mask_buf)/sizeof(unsigned int); i++) {
                if(event->mask & mask_buf[i].mask) {
                    printf("mask 0x%x info %s\n", mask_buf[i].mask, mask_buf[i].info);
                }
            }
            
            i += EVENT_SIZE + event->len;
        }
    }

    (void) inotify_rm_watch(fd, wd);
    (void) close(fd);

    exit(EXIT_SUCCESS);
}
