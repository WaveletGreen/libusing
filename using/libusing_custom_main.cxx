#include "init.h"
#include "Debug.h"
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
			Debug("��ʼ��CUST_init_module�ɹ�");
		}
		else {
			Debug("��ʼ��CUST_init_moduleʧ��");
		}
		return ifail;
	}
#ifdef __cplusplus
}
#endif

