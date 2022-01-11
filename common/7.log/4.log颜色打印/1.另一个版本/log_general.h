#ifndef __LOG_GENERAL_H__
#define __LOG_GENERAL_H__

typedef enum {
    LOG_NONE,       /*!< No log output */
    LOG_ERROR,      /*!< Critical errors, software module can not recover on its own */
    LOG_WARN,       /*!< Error conditions from which recovery measures have been taken */
    LOG_INFO,       /*!< Information messages which describe normal flow of events */
    LOG_DEBUG,      /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    LOG_VERBOSE     /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */
} log_level_t;

//LOG_FMT_ON设置为1时打印log所在的文件名，函数名和行数，0时关闭
#define LOG_FMT_ON      1
//log等级
#define LOG_LOCAL_LEVEL LOG_DEBUG
//log输出接口
#define LOG_WRITE       printf
//log时间戳接口
#define LOG_TIMESTAMP   log_timestamp

// int log_timestamp(void)
// {
    // return 0;
// }

#define LOG_COLOR_BLACK   "30"
#define LOG_COLOR_RED     "31"
#define LOG_COLOR_GREEN   "32"
#define LOG_COLOR_BROWN   "33"
#define LOG_COLOR_BLUE    "34"
#define LOG_COLOR_PURPLE  "35"
#define LOG_COLOR_CYAN    "36"
#define LOG_COLOR(COLOR)  "\033[0;" COLOR "m"
#define LOG_BOLD(COLOR)   "\033[1;" COLOR "m"
#define LOG_RESET_COLOR   "\033[0m"
#define LOG_COLOR_E       LOG_COLOR(LOG_COLOR_RED)
#define LOG_COLOR_W       LOG_COLOR(LOG_COLOR_BROWN)
#define LOG_COLOR_I       LOG_COLOR(LOG_COLOR_GREEN)
#define LOG_COLOR_D
#define LOG_COLOR_V

#if LOG_FMT_ON
#define LOG_FFL     __FILE__, __FUNCTION__, __LINE__
#define LOG_FFL_S   "[%s %s %d]: "
#define LOG_COMMA   ,
#else
#define LOG_FFL
#define LOG_FFL_S
#define LOG_COMMA
#endif

#define LOG_FORMAT(letter, format)  LOG_COLOR_ ## letter #letter " (%u) %s: " LOG_FFL_S format LOG_RESET_COLOR "\n"

#define LOG_LEVEL(level, tag, format, ...) do {                     \
        if (level==LOG_ERROR )          { LOG_WRITE(LOG_FORMAT(E, format), LOG_TIMESTAMP(), tag LOG_COMMA LOG_FFL,##__VA_ARGS__); } \
        else if (level==LOG_WARN )      { LOG_WRITE(LOG_FORMAT(W, format), LOG_TIMESTAMP(), tag LOG_COMMA LOG_FFL,##__VA_ARGS__); } \
        else if (level==LOG_DEBUG )     { LOG_WRITE(LOG_FORMAT(D, format), LOG_TIMESTAMP(), tag LOG_COMMA LOG_FFL,##__VA_ARGS__); } \
        else if (level==LOG_VERBOSE )   { LOG_WRITE(LOG_FORMAT(V, format), LOG_TIMESTAMP(), tag LOG_COMMA LOG_FFL,##__VA_ARGS__); } \
        else                            { LOG_WRITE(LOG_FORMAT(I, format), LOG_TIMESTAMP(), tag LOG_COMMA LOG_FFL,##__VA_ARGS__); } \
    } while(0)

#define LOG_LEVEL_LOCAL(level, tag, format, ...) do {               \
        if ( LOG_LOCAL_LEVEL >= level ) LOG_LEVEL(level, tag, format, ##__VA_ARGS__);\
        } while(0)

#define LOGE( tag, format, ... ) LOG_LEVEL_LOCAL(LOG_ERROR,   tag, format, ##__VA_ARGS__)
#define LOGW( tag, format, ... ) LOG_LEVEL_LOCAL(LOG_WARN,    tag, format, ##__VA_ARGS__)
#define LOGI( tag, format, ... ) LOG_LEVEL_LOCAL(LOG_INFO,    tag, format, ##__VA_ARGS__)
#define LOGD( tag, format, ... ) LOG_LEVEL_LOCAL(LOG_DEBUG,   tag, format, ##__VA_ARGS__)
#define LOGV( tag, format, ... ) LOG_LEVEL_LOCAL(LOG_VERBOSE, tag, format, ##__VA_ARGS__)

#endif