//直接调用以注册METHOD
#include "Form.h"
#include "Debug.h"
//括号里的第一个参数是固定写法，第二个可以传进来的参数（后台）
extern int W2_Revise_clear_form(METHOD_message_t* msg, va_list args)
{
	int ifail = ITK_ok;
	char  *optionname = "W2_Revise_clear_form";
	map<int, string> prop_map;
	tag_t new_rev = va_arg(args, tag_t);
	//操作名，从传进来的参数取出来
	char* operation = va_arg(args, char*);
	printf("*******************************************************\n");
	printf("*      W2_Revise_clear_form is comming         *\n");
	printf("*******************************************************\n");
	printf("new_rev==============================%d\n", new_rev);
	printf("operation==============================%s\n", operation);
	//如果不是升版/另存为操作
	if (strcmp(operation, "Revise") != 0 && strcmp(operation, "SaveAs") != 0) {
		fprintf(stdout, "-----不是升版/另存为------");
		return ifail;
	}
	fprintf(stdout, "\n-------------------->1<----------------\n");
	tag_t relationTag = NULLTAG;
	//查找关系类型（关系类型也是一个对象），关系名称IMAN_master_form是一个常量，可在item下找到几张表
	ITKCALL(GRM_find_relation_type("IMAN_master_form", &relationTag));
	fprintf(stdout, "\n-------------------->relationTag=%d<----------------\n", relationTag);
	//-----------通过关系查找指定类型的Form对象
	int rfCount = 0;
	tag_t *rfTags = NULL;
	char form_object_type[WSO_name_size_c + 1];
	//GRM所有跟关系相关的模块
	//查找当前节点和二级子节点的tag和关系对象
	ITKCALL(GRM_list_secondary_objects_only(new_rev, relationTag, &rfCount, &rfTags));//
	printf("=====rfCount======%d\n", rfCount);
	ITKCALL(WSOM_ask_object_type(rfTags[0], form_object_type));
	printf("=====form_object_type======%s\n", form_object_type);
	{
		ITKCALL(AOM_lock(rfTags[0]));
		{
			ITKCALL(AOM_set_value_string(rfTags[0], "item_comment", ""));
			ITKCALL(AOM_set_value_string(rfTags[0], "previous_version_id", ""));
			ITKCALL(AOM_set_value_string(rfTags[0], "project_id", ""));
			ITKCALL(AOM_set_value_string(rfTags[0], "serial_number", ""));
			ITKCALL(AOM_set_value_string(rfTags[0], "user_data_1", ""));
			ITKCALL(AOM_set_value_string(rfTags[0], "user_data_2", ""));
			ITKCALL(AOM_set_value_string(rfTags[0], "user_data_3", ""));
			ITKCALL(AOM_save(rfTags[0]));
		}
		ITKCALL(AOM_unlock(rfTags[0]));
		ITKCALL(AOM_refresh(rfTags[0], true));
	}
	MEM_free(rfTags);
	printf("*******************************************************\n");
	printf("*        W2_Clear_Form_PropValue is end           *\n");
	printf("*******************************************************\n");
	return ifail;
}
