#include <bom\bom.h>
#include <epm\signoff.h>
#ifndef SIMPLE_ERR_H_INCLUDED
#define SIMPLE_ERR_H_INCLUDED

#define BOM_VIEWTYPE "view"

using namespace std;

#define BUFSIZE				512
//
#define HANDLER_ARGUMENT_ERROR					EMH_USER_error_base + 1
#define ERROR_STATUS_ERROR				EMH_USER_error_base + 2

#define DOFREE(obj)								\
{												\
	if(obj)										\
	{											\
		MEM_free(obj);							\
		obj = NULL;								\
	}											\
}

//#define ECHO(X)      printf X;
#define SYS_LOG(X)   IMAN_write_syslog X;
#define LOG_ECHO(X)  printf X; IMAN_write_syslog X;
/*!
* \def CALL(x)
* 打印错误信息
*/
#define CALL(x) {               \
	int stat;                     \
	char *err_string;             \
	if( (stat = (x)) != ITK_ok)   \
	{                             \
	EMH_ask_error_text (stat, &err_string);              \
	LOG_ECHO( ("ERROR: %d ERROR MSG: %s.\n",stat, err_string) )	\
	LOG_ECHO( ("Function: %s FILE: %s LINE: %d\n", #x, __FILE__, __LINE__ ) )	\
	MEM_free (err_string);   \
	return (stat);          \
	}                         \
}

/*!
* \def DO(x)
* 打印错误信息
*/
#define DO(x) {             \
	int stat;                     \
	char *err_string;             \
	if( (stat = (x)) != POM_ok)   \
	{                             \
	EMH_ask_error_text (stat, &err_string);              \
	printf ("ERROR: %d ERROR MSG: %s.\n", stat, err_string);        \
	printf ("Function: %s FILE: %s LINE: %d\n",#x, __FILE__, __LINE__);             \
	MEM_free (err_string);   \
	}                         \
}

/*!
* \def CALLRNULL(x)
* 打印错误信息
*/
#define CALLRNULL(x) {              \
	int stat;                     \
	char *err_string;             \
	if( (stat = (x)) != ITK_ok)   \
	{                             \
	EMH_ask_error_text (stat, &err_string);              \
	printf ("ERROR: %d ERROR MSG: %s.\n", stat, err_string);        \
	printf ("Function: %s FILE: %s LINE: %d\n",#x, __FILE__, __LINE__);             \
	MEM_free (err_string);   \
	return ((char *)NULL);  \
	}                         \
}

/*!
* \def CALL2(x)
* 打印错误信息
*/
#define CALL2(x) { \
	int stat, n_ifails, *serverities, *ifails, err_count;  \
	char *err_string, **texts;                             \
	if( (stat = (x)) != ITK_ok)                            \
	{                                                      \
	printf ("Function: %s FILE: %s LINE: %d\n",#x, __FILE__, __LINE__);             \
	EMH_ask_errors( &n_ifails, (const int**)(&serverities), (const int**)(&ifails), (const char***)(&texts)  );\
	for( err_count=0; err_count<n_ifails; err_count++ ) \
		{                                                   \
		printf( "ERROR: %d ERROR MSG: %s.\n", ifails[i], texts[i] );              \
		}                                                   \
		MEM_free( serverities );                            \
		MEM_free( ifails );                                 \
		MEM_free( texts );                                  \
		return (stat);                                      \
	}                                                       \
}                                                           \

#define CHECK_FILE(x,ret) { \
	FILE *stream = NULL;	\
	if( (stream = fopen(x,"rb")) == NULL ) {	\
	printf( "%s doesn't exists, please check!\n", x );		\
	IMAN_write_syslog( "%s doesn't exists, please check!\n", x)	;	\
	ret = -1;	\
	}	\
	else {	\
	fclose(stream);	\
	stream = NULL;	\
	ret = 0;	\
	}	\
}	\


#define CHECK_FILE_NOT_EXISTS(x,ret) { \
	FILE *stream = NULL;	\
	if( (stream = fopen(x,"rb")) != NULL ) {	\
	fclose(stream);	\
	stream = NULL;	\
	printf( "%s exists, please check!\n", x );		\
	IMAN_write_syslog( "%s exists, please check!\n", x)	;	\
	ret = -1;	\
	}	\
	else {	\
	ret = 0;	\
	}	\
}	\

#endif  
