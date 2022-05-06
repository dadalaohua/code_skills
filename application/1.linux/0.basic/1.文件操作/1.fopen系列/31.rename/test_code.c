#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    int ret;
    
    //将名为old_filename的文件或目录重命名为new_filename
    ret = rename("old_filename", "new_filename");
    
    if(ret < 0) 
        perror("rename error:");
    
    return 0;
}