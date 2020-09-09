#include <stdio.h>
#include <locale.h>
#include <time.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{ 
    time_t currtime;
    struct tm *timer;
    char buffer[80];

    time(&currtime);
    timer = localtime(&currtime);

    printf("Locale is: %s\n", setlocale(LC_ALL, "en_GB.UTF-8"));
    strftime(buffer, 80, "%c", timer);
    printf("Date is: %s\n", buffer);


    printf("Locale is: %s\n", setlocale(LC_ALL, "de_DE.UTF-8"));
    strftime(buffer, 80, "%c", timer );
    printf("Date is: %s\n", buffer);
   
    return 0;
}