#include <stdarg.h>
#include<stdio.h>
#include <tc/tc.h>
void ECHO(char *format, ...)
{
	//if( !YFJC_OPT_DEBUG )
	//    return; 

	char msg[2048];
	va_list args;

	va_start(args, format);
	vsprintf(msg, format, args);
	va_end(args);

	printf(msg);
	TC_write_syslog(msg);
}