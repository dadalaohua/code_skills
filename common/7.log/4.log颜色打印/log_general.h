#ifndef __LOG_GENERAL_H__
#define __LOG_GENERAL_H__

#define LOG_NONE            0   /*!< No log output */
#define LOG_ERROR           1   /*!< Critical errors, software module can not recover on its own */
#define LOG_WARN            2   /*!< Error conditions from which recovery measures have been taken */
#define LOG_INFO            3   /*!< Information messages which describe normal flow of events */
#define LOG_DEBUG           4   /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
#define LOG_VERBOSE         5   /*!< Bigger chunks of debugging information, or frequent messages which can potentially flood the output. */

//LOG_FMT_ON设置为1时打印log所在的文件名，函数名和行数，0时关闭
#define LOG_FMT_ON          0
//log等级
#define LOG_LOCAL_LEVEL     LOG_DEBUG
//log输出接口
#define LOG_WRITE           printf
//log时间戳接口
#define LOG_TIMESTAMP       log_timestamp

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

#if LOG_LOCAL_LEVEL >= LOG_ERROR
#define LOGE( tag, format, ... ) LOG_WRITE(LOG_FORMAT(E, format), LOG_TIMESTAMP(), tag LOG_COMMA LOG_FFL,##__VA_ARGS__)
#else
#define LOGE( tag, format, ... )
#endif

#if LOG_LOCAL_LEVEL >= LOG_WARN
#define LOGW( tag, format, ... ) LOG_WRITE(LOG_FORMAT(W, format), LOG_TIMESTAMP(), tag LOG_COMMA LOG_FFL,##__VA_ARGS__)
#else
#define LOGW( tag, format, ... )
#endif

#if LOG_LOCAL_LEVEL >= LOG_INFO
#define LOGI( tag, format, ... ) LOG_WRITE(LOG_FORMAT(I, format), LOG_TIMESTAMP(), tag LOG_COMMA LOG_FFL,##__VA_ARGS__)
#else
#define LOGI( tag, format, ... )
#endif

#if LOG_LOCAL_LEVEL >= LOG_DEBUG
#define LOGD( tag, format, ... ) LOG_WRITE(LOG_FORMAT(D, format), LOG_TIMESTAMP(), tag LOG_COMMA LOG_FFL,##__VA_ARGS__)
#else
#define LOGD( tag, format, ... )
#endif

#if LOG_LOCAL_LEVEL >= LOG_VERBOSE
#define LOGV( tag, format, ... ) LOG_WRITE(LOG_FORMAT(V, format), LOG_TIMESTAMP(), tag LOG_COMMA LOG_FFL,##__VA_ARGS__)
#else
#define LOGV( tag, format, ... )
#endif

#endif