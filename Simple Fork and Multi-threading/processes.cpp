//******************************************************************************
//**  File: processes.cpp
//**  Author: Michael Ji
//******************************************************************************
#include <sys/types.h>   // for fork, wait
#include <sys/wait.h>    // for wait
#include <unistd.h>      // for fork, pipe, dup, close
#include <stdio.h>       // for NULL, perror
#include <iostream>      // for cout
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[]) //**argv
{
	int RD = 0;
	int WR = 1;
	int fdsProcess[2];
	int fdsMatched[2];
	int pid;
	if ( pipe(fdsProcess) < 0) //pipe
    { 
        perror( "pipe error" ); exit(1); 
    }

    if ( pipe(fdsMatched) < 0) //pipe
    { 
        perror( "pipe error" ); exit(1); 
    }

	//fork child
    if ( ( pid = fork( ) ) < 0 )
    {
        perror( "fork error");
        exit(1);
    }

	if (pid == 0) //child
	{
		int pid2;
		//fork grandchild
    	if ((pid2 = fork()) < 0) 
    	{
        	perror( "fork error" );
        	exit(1);
    	}
		if (pid2 == 0) //grandchild
		{
			int pid3;
			//fork great grand child
			if ( ( pid3 = fork( ) ) < 0 ) 
			{
				perror( "fork error" );
				exit(1);
			}

			if (pid3 == 0)//great grand child
			{
				close(fdsProcess[RD]);
				close(fdsProcess[WR]);
				dup2(fdsMatched[RD], RD);	//open process matches
				close(fdsMatched[WR]);
				execlp("wc", "wc", "-l", (char*)0);
				wait(NULL);

			}
			else //grandchild
			{
				dup2(fdsProcess[RD], RD);	//open read all process
				close(fdsProcess[WR]);
				close(fdsMatched[RD]);
				dup2(fdsMatched[WR], WR);	//open write in grep argv from process
				execlp("grep", "grep", argv[1], (char*)0);
				wait(NULL);
			}
		}
		else //child
		{
			close(fdsProcess[RD]);
			dup2(fdsProcess[WR],WR);	//open writein all processes
			close(fdsMatched[RD]);
			close(fdsMatched[WR]);
			execlp("ps", "ps", "-A", (char*) 0);
			wait(NULL);
		}
	}
	else //parent
	{
		wait(NULL);	// wait
	}
	return 0;
}
