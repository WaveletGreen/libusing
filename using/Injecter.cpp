#include "Debug.h"
#include "RuleHandlerManager.h"
#include "ActionHandlerManager.h"
#include "MethodManager.h"
/*************����ֻע��,ע�᷽�������*******************/
////ע���ȡUser���µ�Items
//extern DLLAPI int GetItems(EPM_rule_message_t msg) {
//	int ifail = ITK_ok;
//	ifail = EPM_register_rule_handler("GetUserItems", "GetUserItems", (EPM_rule_handler_t)HZ_Check_BOM_Condition);
//	if (ifail == 0) {
//		printf("-->>>ע��rule handler ����GetUserItems�ɹ� ---\n");
//	}
//	else {
//		printf("-->>>ע��rule handler ����GetUserItemsʧ�� %d---\n", ifail);
//	}
//	return ifail;
//}

//ע��rule Handler
extern int injectRuleHandler_UserLog() {
	int ifail = ITK_ok;
	(ifail = EPM_register_rule_handler("USER_Log", "USER_Log", (EPM_rule_handler_t)USER_Log));
	if (ifail == 0) {
		Debug("ע��USER_Log�ɹ�");
	}
	else {
		Debug("ע��USER_Logʧ��");
	}
	return ifail;
}
//ע��rule Handler
extern int injectRuleHandler_HZ_Check_BOM_Condition() {
	int ifail = ITK_ok;
	ifail = EPM_register_rule_handler("HZ_Check_BOM_Condition", "HZ_Check_BOM_Condition", (EPM_rule_handler_t)HZ_Check_BOM_Condition);
	if (ifail == 0) {
		Debug("ע��rule handler ����HZ_Check_BOM_Condition�ɹ�");
	}
	else {
		Debug("ע��rule handler ����HZ_Check_BOM_Conditionʧ��");
	}
	return ifail;
}
//ע��action Handler
extern int injectActionHandler_HZ_attach_assembly() {
	int ifail = ITK_ok;
	(ifail = EPM_register_action_handler("HZ_attach_assembly", "HZ_attach_assembly", (EPM_action_handler_t)HZ_attach_assembly));
	if (ifail == 0) {
		Debug("ע��HZ_attach_assembly�ɹ�");
	}
	else {
		Debug("ע��HZ_attach_assemblyʧ��");
	}
	return ifail;
}
//ע��action Handler
extern int injectActionHandler_ActionHandler_Update() {
	int ifail = ITK_ok;
	(ifail = EPM_register_action_handler("ActionHandler_Update", "ActionHandler_Update", (EPM_action_handler_t)ActionHandler_Update));
	if (ifail == 0) {
		Debug("ע��ActionHandler_Update�ɹ�");
	}
	else {
		Debug("ע��ActionHandler_Updateʧ��");
	}
	return ifail;
}
//ע��Method
extern int injectMethod_W2_Revise_clear_form() {
	int status = ITK_ok;
	int err_line = -1;
	METHOD_id_t mth_tag;
	//��һ��item�����Ƶ�ʱ��Ҳ���޸Ĵ����������,ItemRevision Master�ǲ��ҵķ�����
	ITKCALL(status = METHOD_find_method("ItemRevision", ITEM_deep_copy_msg, &mth_tag));
	if (mth_tag.id != 0) {
		//��Ӵ������������������������
		ITKCALL(METHOD_add_action(mth_tag, METHOD_post_action_type, W2_Revise_clear_form, NULL));
		Debug("ע��Register_revise_msg�����ɹ�");
	}
	return status;
}
