#include <stdio.h>
#include <mntent.h>
#include <errno.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
程序内获取文件系统挂载信息
相当于
cat /etc/mtab
或者
cat/proc/mounts

使用mntent提供的方便函数：
FILE *setmntent(const char *filename, const char *type);
struct mntent *getmntent(FILE *filep);
int endmntent(FILE *filep);

（1）setmntent用来打开/etc/mtab或者同样格式的table文件
        参数 filename为table文件的路径（例如/etc/mtab），参数type为打开文件的模式（与open类型，例如"r"为只读打开,"w"只写,"r+"读写等）
        成功时，返回FILE指针（用于mntent操作），失败时返回NULL

（2）getmntent用来读取文件的每一行，解析每一行的参数到mntent结构，mntent结构的存储空间是静态分配的（不需要free），结构的值会在下一次getmntent时被覆盖
         mntent结构定义：
    struct mntent
    {
        char *mnt_fsname;           // name of mounted file system  文件系统对应的设备路径或者服务器地址
        char *mnt_dir;              // file system path prefix      文件系统挂载到的系统路径
        char *mnt_type;             // mount type (see mntent.h)    文件系统类型: ufs, nfs, 等
        char *mnt_opts;             // mount options (see mntent.h) 文件系统挂载参数，以逗号分隔
        int mnt_freq;               // dump frequency in days       文件系统备份频率（以天为单位）
        int mnt_passno;             // pass number on parallel fsck 开机fsck的顺序，如果为0，不会进行check
    };
    
    参数filep是setmntent返回的FILE指针
    成功时返回指向mntent的指针，错误时返回NULL
    
（3）endmntent用来关闭打开的table文件，总是返回1

其他
值得注意的是getmntent是不可重入函数，如果一个程序中多个地方同时调用getmntent，可能会得不到想要的结果，那么可以用getmntent_r函数来替代， 原型如下：

struct mntent *getmntent_r(FILE *fp, struct mntent *mntbuf, char *buf, int buflen);

getmntent_r会把数据存放在用户提供的内存中(mntbuf)，而不是由系统管理。

addmntent(FILE *fp, const struct mntent *mnt) 可以在fp指向的文件追加最后一行数据。
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char *filename = "/proc/mounts";
    // char *filename = "/etc/mtab";
    // char *filename = "/etc/fstab";
    FILE *mntfile;
    struct mntent *mntent;
    
    mntfile = setmntent(filename, "r");
    if (!mntfile) {
        printf("Failed to read mtab file, error [%s]\n",
                        strerror(errno));
        return -1;
    }
    
    while((mntent = getmntent(mntfile)))
            printf("%s, %s, %s, %s, %d, %d\n",
                            mntent->mnt_fsname,
                            mntent->mnt_dir,
                            mntent->mnt_type,
                            mntent->mnt_opts,
                            mntent->mnt_freq,
                            mntent->mnt_passno);
    
    endmntent(mntfile);
    return 0;
}
