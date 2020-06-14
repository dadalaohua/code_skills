#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void sigroutine(int signo)
{
   switch (signo){
   case SIGALRM:
       printf("Catch a signal -- SIGALRM \n");
       signal(SIGALRM, sigroutine);
       break;
   case SIGVTALRM:
       printf("Catch a signal -- SIGVTALRM \n");
       signal(SIGVTALRM, sigroutine);
       break;
   }
   return;
}

int main(int argc, char* argv[])
{ 
   struct itimerval value, ovalue, value2;
   
   printf("process id is %d\n", getpid());
   
   signal(SIGALRM, sigroutine);
   signal(SIGVTALRM, sigroutine);
   
   //每隔一秒发出一个SIGALRM
   value.it_value.tv_sec = 1;
   value.it_value.tv_usec = 0;
   value.it_interval.tv_sec = 1;
   value.it_interval.tv_usec = 0;
   setitimer(ITIMER_REAL, &value, &ovalue);
   
   //每隔0.5秒发出一个SIGVTALRM信号
   value2.it_value.tv_sec = 0;
   value2.it_value.tv_usec = 500000;
   value2.it_interval.tv_sec = 0;
   value2.it_interval.tv_usec = 500000;
   setitimer(ITIMER_VIRTUAL, &value2, &ovalue);
   
   for(;;);

   return 0;
}