#include "using.h"
#include "init.h"
#include "Debug.h"
#pragma warning (disable: 4819)

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************
							程序主函数
*******************************************************************/
	DLLAPI int libusing_register_callbacks()
	{
		int ifail = ITK_ok;
		//注册函数，并非是注册user service函数，其需要另外定义
		ifail = CUSTOM_register_exit(
			"libusing",
			"USER_gs_shell_init_module",
			(CUSTOM_EXIT_ftn_t)CUST_init_module);
		if (ifail == 0) {
			Debug("注册初始化CUST_init_module成功");
		}
		else {
			Debug("注册初始化CUST_init_module失败");
		}
		return ifail;
	}
#ifdef __cplusplus
}
#endif

