
#include  <fcntl.h>                              //
#include  <stdio.h>                              //
#include  <stdlib.h>                             //
#include  <string.h>                             //
#include  <sys/types.h>                          //
#include  <sys/wait.h>                           //
#include  <sys/stat.h>                           //
#include  <termios.h>                            //
#include  <unistd.h>                             //


#define WRITE_END 1
#define READ_END 0

int main(int argc, char* argv[])                 //
{                                                //




	pid_t pid;
	int fd[2];
	
	pipe(fd);
	pid = fork();
	
	if(pid==0)
	{
	    dup2(fd[WRITE_END], STDOUT_FILENO);
	    close(fd[READ_END]);
	    close(fd[WRITE_END]);
	    execlp("ls", "ls", "-l", (char*) NULL);
	    fprintf(stderr, "Failed to execute '%s'\n", "ls");
	    exit(1);
	}
	else
	{
	    pid=fork();
	
	    if(pid==0)
	    {
	        dup2(fd[READ_END], STDIN_FILENO);
	        close(fd[WRITE_END]);
	        close(fd[READ_END]);
	        execlp("wc", "wc", NULL,(char*) NULL);
	        fprintf(stderr, "Failed to execute '%s'\n", "wc");
	        exit(1);
	    }
	    else
	    {
	        int status;
	        close(fd[READ_END]);
	        close(fd[WRITE_END]);
	        waitpid(pid, &status, 0);
	    }
	}

}





