#include "common.h"
#include <epm/signoff.h>
extern DLLAPI int USER_Log();
//extern int GetItems(EPM_rule_message_t msg);
int Check_WorkFlow();
int GetUserItems(EPM_rule_message_t msg);
extern int Register_revise_msg(void);
int set_prop_msg(METHOD_message_t* msg, va_list args);
