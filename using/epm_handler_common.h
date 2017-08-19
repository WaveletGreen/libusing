/**
* @addtogroup			handler
* @{
*/

/**
* @file					epm_handler_common.h
* @brief				handler functions declation
* @date					2011/4/12
* @author				Ray
* @history
* ===================================================================================
* Date					Name				Description
* 12-Apr-2011			Ray				created
*/


#ifndef EPM_HANDLER_COMMON
#define EPM_HANDLER_COMMON

#include <epm/epm.h>
#include <string>
#include <map>


#ifdef __cplusplus
extern "C" {
#endif


	using namespace std;


#define TC_specification	"IMAN_specification"
	//#define NX_3W_DATASET_TYPE		"UGMASTER"
	//#define NX_2W_DATASET_TYPE		"UGPART"
	//#define DATASET_REF_TYPE		"UGPART"

	////将流程信息签入版本属性上去
	//int qtmc_sign_ir(EPM_action_message_t msg);




	//user service 
	//int itk_set_bypass(void *retValType);

#ifdef __cplusplus
}
#endif

#endif 


/**
* @}
*/