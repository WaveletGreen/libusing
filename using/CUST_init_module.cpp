#include <server_exits/user_server_exits.h>
#include <tccore/custom.h>
#include <epm/epm.h>
#include "using.h"
#include "BOM.h"
#include "Debug.h"
/*************************************************************************************
							初始化函数
*************************************************************************************/
extern DLLAPI int CUST_init_module(int *decision, va_list args)
{
	int ifail = ITK_ok;
	//允许注册多个注册函数
	*decision = ALL_CUSTOMIZATIONS;

	(ifail = EPM_register_rule_handler("USER_Log", "USER_Log", (EPM_rule_handler_t)USER_Log));
	if (ifail == 0) {
		Debug("注册USER_Log成功");
	}
	else {
		Debug("注册USER_Log失败");
	}

	//(ifail = EPM_register_rule_handler("GetItems", "GetItems", (EPM_rule_handler_t)GetItems));
	//if (ifail == 0) {
	//	printf("--------------->注册GetItems成功\n");
	//}
	//else {
	//	printf("--------------->注册GetItems成功 %d\n", ifail);
	//}
	ifail =Check_WorkFlow();
	if (ifail == 0) {
		Debug("注册Check_WorkFlow成功");
	}
	else {
		Debug("注册Check_WorkFlow成功");
	}
	ifail = Register_revise_msg();
	if (ifail == 0) {
		Debug("注册Register_revise_msg成功");
	}
	else {
		Debug("注册Register_revise_msg成功");
	}
	(ifail = EPM_register_action_handler("HZ_attach_assembly", "HZ_attach_assembly", (EPM_action_handler_t)HZ_attach_assembly));
	if (ifail == 0) {
		Debug("注册HZ_attach_assembly成功");
	}
	else {
		Debug("注册HZ_attach_assembly失败");
	}
	return ifail;
}