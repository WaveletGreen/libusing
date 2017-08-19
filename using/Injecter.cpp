#include "Debug.h"
#include "RuleHandlerManager.h"
#include "ActionHandlerManager.h"
#include "MethodManager.h"
/*************这里只注册,注册方法另外放*******************/
////注册获取User名下的Items
//extern DLLAPI int GetItems(EPM_rule_message_t msg) {
//	int ifail = ITK_ok;
//	ifail = EPM_register_rule_handler("GetUserItems", "GetUserItems", (EPM_rule_handler_t)HZ_Check_BOM_Condition);
//	if (ifail == 0) {
//		printf("-->>>注册rule handler 函数GetUserItems成功 ---\n");
//	}
//	else {
//		printf("-->>>注册rule handler 函数GetUserItems失败 %d---\n", ifail);
//	}
//	return ifail;
//}

//注册rule Handler
extern int injectRuleHandler_UserLog() {
	int ifail = ITK_ok;
	(ifail = EPM_register_rule_handler("USER_Log", "USER_Log", (EPM_rule_handler_t)USER_Log));
	if (ifail == 0) {
		Debug("注册USER_Log成功");
	}
	else {
		Debug("注册USER_Log失败");
	}
	return ifail;
}
//注册rule Handler
extern int injectRuleHandler_HZ_Check_BOM_Condition() {
	int ifail = ITK_ok;
	ifail = EPM_register_rule_handler("HZ_Check_BOM_Condition", "HZ_Check_BOM_Condition", (EPM_rule_handler_t)HZ_Check_BOM_Condition);
	if (ifail == 0) {
		Debug("注册rule handler 函数HZ_Check_BOM_Condition成功");
	}
	else {
		Debug("注册rule handler 函数HZ_Check_BOM_Condition失败");
	}
	return ifail;
}
//注册action Handler
extern int injectActionHandler_HZ_attach_assembly() {
	int ifail = ITK_ok;
	(ifail = EPM_register_action_handler("HZ_attach_assembly", "HZ_attach_assembly", (EPM_action_handler_t)HZ_attach_assembly));
	if (ifail == 0) {
		Debug("注册HZ_attach_assembly成功");
	}
	else {
		Debug("注册HZ_attach_assembly失败");
	}
	return ifail;
}
//注册action Handler
extern int injectActionHandler_ActionHandler_Update() {
	int ifail = ITK_ok;
	(ifail = EPM_register_action_handler("ActionHandler_Update", "ActionHandler_Update", (EPM_action_handler_t)ActionHandler_Update));
	if (ifail == 0) {
		Debug("注册ActionHandler_Update成功");
	}
	else {
		Debug("注册ActionHandler_Update失败");
	}
	return ifail;
}
//注册Method
extern int injectMethod_W2_Revise_clear_form() {
	int status = ITK_ok;
	int err_line = -1;
	METHOD_id_t mth_tag;
	//当一个item被复制的时候，也是修改触发这个方法,ItemRevision Master是查找的方法名
	ITKCALL(status = METHOD_find_method("ItemRevision", ITEM_deep_copy_msg, &mth_tag));
	if (mth_tag.id != 0) {
		//添加处理函数，后操作，操作函数名
		ITKCALL(METHOD_add_action(mth_tag, METHOD_post_action_type, W2_Revise_clear_form, NULL));
		Debug("注册Register_revise_msg函数成功");
	}
	return status;
}
