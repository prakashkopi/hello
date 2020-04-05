// shell2.c
// simple shell example using execvp for a command processing
//
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sysexits.h>
#include <unistd.h>

int main()
{
   char program[80];
   char *args[100];

   pid_t pid;
   int status;
   int i;

   printf("Ready to exec()...\n");

   strcpy(program,"ping");
   args[0]="ping";
   args[1]="-c";
   args[2]="10";
   args[3]="www.utdallas.edu";
   args[4]=NULL;

   printf(" ** program starts ** \n");

   args[2]="3";	// if you like to change -c n to be 04

   pid=fork();
   if (pid == 0) {
	   // child process
	   i=execvp(program,args);
	   // if you see this, then execvp is failed to run
	   printf("i=%d ... did it work?\n",i);

   }
   else if (pid > 0) {
	   // parent waits for child
	if ((pid=waitpid(pid, &status, 0)) < 0)
		fprintf(stderr, " parent: waitpid error: %s\n",
			strerror(errno));
   }
   else {
	   printf("fork fails \n");
   }


   printf(" ** end of program run ** \n");

   return 0;
}
