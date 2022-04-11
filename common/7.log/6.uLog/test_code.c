#include <stdio.h>

#include "ulog.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
void my_console_logger(ulog_level_t severity, char *msg) {
    printf("[%s]: %s\n",
        ulog_level_name(severity),
        msg);
}

void my_file_logger(ulog_level_t severity, char *msg) {
    FILE *fp = fopen("test.log", "a+");
    fprintf(fp, "[%s]: %s\n",
        ulog_level_name(severity),
        msg);
    fclose(fp);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
/**
 * \file
 *
 * \brief uLog: lightweight logging for embedded systems
 *
 * A quick intro by example:
 *
 *     #include "ulog.h"
 *
 *     // To use uLog, you must define a function to process logging messages.
 *     // It can write the messages to a console, to a file, to an in-memory
 *     // buffer: the choice is yours.  And you get to choose the format of
 *     // the message.  This example prints to the console.  One caveat: msg
 *     // is a static string and will be over-written at the next call to ULOG.
 *     // You may print it or copy it, but saving a pointer to it will lead to
 *     // confusion and astonishment.
 *     //
 *     void my_console_logger(ulog_level_t level, const char *msg) {
 *         printf("%s [%s]: %s\n",
 *             get_timestamp(),
 *             ulog_level_name(level),
 *             msg);
 *     }
 *
 *     int main() {
 *         ULOG_INIT();
 *
 *         // log to the console messages that are WARNING or more severe.  You
 *         // can re-subscribe at any point to change the severity level.
 *         ULOG_SUBSCRIBE(my_console_logger, ULOG_WARNING);
 *
 *         // log to a file messages that are DEBUG or more severe
 *         ULOG_SUBSCRIBE(my_file_logger, ULOG_DEBUG);
 *
 *         int arg = 42;
 *         ULOG_INFO("Arg is %d", arg);  // logs to file but not console
 *     }
 */
 
int main(int argc, char* argv[])
{
    int arg = 42;

    ULOG_INIT();

    // log messages with a severity of WARNING or higher to the console.  The
    // user must supply a method for my_console_logger, e.g. along the lines
    // of what is shown above.
    ULOG_SUBSCRIBE(my_console_logger, ULOG_WARNING_LEVEL);

    // log messages with a severity of DEBUG or higher to a file.  The user must
    // provide a method for my_file_logger (not shown here).
    ULOG_SUBSCRIBE(my_file_logger, ULOG_DEBUG_LEVEL);

    ULOG_INFO("Info, arg=%d", arg);        // logs to file but not console
    ULOG_CRITICAL("Critical, arg=%d", arg);  // logs to file and console

    // dynamically change the threshold for a specific logger
    ULOG_SUBSCRIBE(my_console_logger, ULOG_INFO_LEVEL);

    ULOG_INFO("Info, arg=%d", arg);          // logs to file and console

    // remove a logger
    ULOG_UNSUBSCRIBE(my_file_logger);

    ULOG_INFO("Info, arg=%d", arg);          // logs to console only
    
    return 0;
}