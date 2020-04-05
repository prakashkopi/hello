/* pipe with ping command via execvp & file redirection with dup */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  int fds[2];
  int child[2];
  char *argv[5];

   pid_t parentpid = getpid();
   pid_t pid1;
   pid_t pid2;

  pipe(fds);

// child process1 to process the result of ping command

pid1=fork();

if (pid1 == 0)
  {
    close(fds[1]);
    close(STDIN_FILENO);
    dup(fds[0]);
          /* redirect standard input to fds[0] */

	int c;

  while ((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF) {
			fprintf(stderr, "write error\n");
			exit(1);
		}

	if (ferror(stdin)) {
		fprintf(stderr, "read error\n");
		exit(1);
	}

	exit(0);

  }

// child process2 to get ping command and its output to STDOUT

pid2 = fork();

if (pid2 == 0)
  {
    close(fds[0]);
    close(STDOUT_FILENO);
    dup(fds[1]);
    argv[0] = "/bin/ping";
    argv[1] = "www.utdallas.edu";
    argv[2] = "-c";
    argv[3] = "3";
    argv[4] = NULL;

    execv(argv[0], argv);
    exit(-2);
  }

// All done
  close(fds[0]);
  close(fds[1]);

  wait(child);
  wait(child+1);

  return 0;
}
