#include <server_exits/user_server_exits.h>
#include <tccore/custom.h>
#include <epm/epm.h>
#include "using.h"
#include "BOM.h"
#include "Debug.h"
/*************************************************************************************
							��ʼ������
*************************************************************************************/
extern DLLAPI int CUST_init_module(int *decision, va_list args)
{
	int ifail = ITK_ok;
	//����ע����ע�ắ��
	*decision = ALL_CUSTOMIZATIONS;

	(ifail = EPM_register_rule_handler("USER_Log", "USER_Log", (EPM_rule_handler_t)USER_Log));
	if (ifail == 0) {
		Debug("ע��USER_Log�ɹ�");
	}
	else {
		Debug("ע��USER_Logʧ��");
	}

	//(ifail = EPM_register_rule_handler("GetItems", "GetItems", (EPM_rule_handler_t)GetItems));
	//if (ifail == 0) {
	//	printf("--------------->ע��GetItems�ɹ�\n");
	//}
	//else {
	//	printf("--------------->ע��GetItems�ɹ� %d\n", ifail);
	//}
	ifail =Check_WorkFlow();
	if (ifail == 0) {
		Debug("ע��Check_WorkFlow�ɹ�");
	}
	else {
		Debug("ע��Check_WorkFlow�ɹ�");
	}
	ifail = Register_revise_msg();
	if (ifail == 0) {
		Debug("ע��Register_revise_msg�ɹ�");
	}
	else {
		Debug("ע��Register_revise_msg�ɹ�");
	}
	(ifail = EPM_register_action_handler("HZ_attach_assembly", "HZ_attach_assembly", (EPM_action_handler_t)HZ_attach_assembly));
	if (ifail == 0) {
		Debug("ע��HZ_attach_assembly�ɹ�");
	}
	else {
		Debug("ע��HZ_attach_assemblyʧ��");
	}
	return ifail;
}