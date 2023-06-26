
#include <stdio.h>
#include <unistd.h>
#include <cerrno>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/wait.h>

void flushPrintf( const char *pStr, ... )
{
	va_list argptr;
    va_start( argptr, pStr );
	vprintf( pStr, argptr );
	fflush(stdout);
	va_end( argptr );
}

char gPadding[ 1024 * 1024 * 32 ] = {1}; //Force 32 megs

int main( int argc, char **argv )
{
    char commandWithArgs[ 256 ] = { 0 };
    snprintf( commandWithArgs, 255, "%s %s", "/mnt/hdisk/ASPh/hack/bin/fba/fba029743_asp", argv[ 1 ] );

    pid_t pid = fork( );
	if( pid < 0 )
	{
		flushPrintf( "fork() failed with error: pid: %d e: %d\r\n", pid, errno );
	}
	// this is the newly created process.
	else if( pid == 0 )
	{
        // This scope is now the child process. The parent proc will never enter this branch.
        
        // call setsid() to move this child process into its own process group where 
        // its group id is the same as its process id. This way, when 'sh' spawns
        // the actual process, both can be killed by the parent process that created this.
        // Otherwise, the parent process would only be able to kill 'sh', and not the process
        // that 'sh' spawned.
        int newgpid = setsid();
        
		//-c simply means "command"
		flushPrintf( "launching %s\r\n", commandWithArgs );
        int result = execl( "/system/bin/sh", "sh", "-c", commandWithArgs, NULL );
        
        // if we got here, execl failed, we're the cloned process, and we need to immediately terminate.
		flushPrintf( "execl() failed with error: r: %d e: %d\r\n", result, errno );
		exit(0);
	}
    else
    {
        int status = 0;
        while( waitpid( pid, &status, 0 ) < 0 )
        {
            if( errno != EINTR ) 
            {
                // The child process exited, so we can stop idling
                break;
            }   
        }
    }

    return 0;
}

