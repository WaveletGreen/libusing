#include "using.h"
#include "init.h"
#include "Debug.h"
#pragma warning (disable: 4819)

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************
							����������
*******************************************************************/
	DLLAPI int libusing_register_callbacks()
	{
		int ifail = ITK_ok;
		//ע�ắ����������ע��user service����������Ҫ���ⶨ��
		ifail = CUSTOM_register_exit(
			"libusing",
			"USER_gs_shell_init_module",
			(CUSTOM_EXIT_ftn_t)CUST_init_module);
		if (ifail == 0) {
			Debug("ע���ʼ��CUST_init_module�ɹ�");
		}
		else {
			Debug("ע���ʼ��CUST_init_moduleʧ��");
		}
		return ifail;
	}
#ifdef __cplusplus
}
#endif

