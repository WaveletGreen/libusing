#include <server_exits/user_server_exits.h>
#include <tccore/custom.h>
#include "Injecter.h"
/*************************************************************************************
							��ʼ������
*************************************************************************************/
extern DLLAPI int CUST_init_module(int *decision, va_list args)
{
	int ifail = ITK_ok;
	//����ע����ע�ắ��
	*decision = ALL_CUSTOMIZATIONS;
	ifail= injectRuleHandler_UserLog();
	//(ifail = EPM_register_rule_handler("GetItems", "GetItems", (EPM_rule_handler_t)GetItems));
	//if (ifail == 0) {
	//	printf("--------------->ע��GetItems�ɹ�\n");
	//}
	//else {
	//	printf("--------------->ע��GetItems�ɹ� %d\n", ifail);
	//}
	ifail =injectRuleHandler_HZ_Check_BOM_Condition();
	ifail = injectActionHandler_HZ_attach_assembly();
	ifail = injectActionHandler_ActionHandler_Update();
	ifail = injectMethod_W2_Revise_clear_form();
	return ifail;
}