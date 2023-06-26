
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
    flushPrintf( "ASP Bootstrapper Commencing\r\n");
    flushPrintf( "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\r\n");

    // turn this process into sh and then FBA - QUI will wait on sh, because it inherits this
    // boot strapper's process id. SH will wait on FBA. The 32 megs will be freed when this process space is wiped
    // to launch sh.
    char commandWithArgs[ 256 ] = { 0 };
    snprintf( commandWithArgs, 255, "%s %s", "/mnt/hdisk/ASPh/hack/bin/fba/fba029743_asp", argv[ 1 ] );
    int result = execl( "/system/bin/sh", "sh", "-c", commandWithArgs, NULL );
    
    // if we got here, execl failed. It should never return.
    flushPrintf( "execl() failed with error: r: %d e: %d\r\n", result, errno );
    flushPrintf( "Bootstrapper exiting!\r\n");
    return 0;
}
