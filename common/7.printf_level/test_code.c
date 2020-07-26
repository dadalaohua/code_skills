#include <stdio.h>

int use_debug;

#define LOG_DEBUG(fmt,args...)  do{if(use_debug>=4)printf("MCU-D:"fmt,##args);}while(0)
#define LOG_INFO(fmt,args...)   do{if(use_debug>=3)printf("MCU-I:"fmt,##args);}while(0)
#define LOG_NOTICE(fmt,args...) do{if(use_debug>=2)printf("MCU-N:"fmt,##args);}while(0)
#define LOG_WARN(fmt,args...)   do{if(use_debug>=1)printf("MCU-W:"fmt,##args);}while(0)
#define LOG_ERR(fmt,args...)    do{if(use_debug>=0)printf("MCU-E:"fmt,##args);}while(0)
#define LOG_ANY(fmt,args...)    do{printf(fmt,##args);}while(0)
#define LOG_RUN(fmt,args...)    do{if(use_debug==-1)printf("MCU-R:"fmt,##args);}while(0)

#define LOG_BUG(exp) do \
{ \
    if((exp)) \
    printf("MCU:bug %s+%d," #exp "\n",__FUNCTION__,__LINE__); \
}while(0)

int main(int argc, char* argv[])
{ 
    int i;

    for(i = 0; i < 5; i++)
    {
        use_debug = i;
    
        printf("use_debug = %d\n", i);
        
        printf("\n");
        LOG_DEBUG("test printf\n");
        LOG_INFO("test printf\n");
        LOG_NOTICE("test printf\n");
        LOG_WARN("test printf\n");
        LOG_ERR("test printf\n");
        LOG_ANY("test printf\n");
        LOG_RUN("test printf\n");
        printf("\n");
    }
    
    use_debug = -1;

    printf("use_debug = -1\n");
    
    printf("\n");
    LOG_DEBUG("test printf\n");
    LOG_INFO("test printf\n");
    LOG_NOTICE("test printf\n");
    LOG_WARN("test printf\n");
    LOG_ERR("test printf\n");
    LOG_ANY("test printf\n");
    LOG_RUN("test printf\n");
    printf("\n");
    
    return 0;
}