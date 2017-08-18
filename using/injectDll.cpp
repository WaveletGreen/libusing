#include<stdio.h>
#include <epm/signoff.h>
#include <tccore/tc_msg.h>
#include <tccore/item_msg.h>
#include "common.h"
#include "BOM.h"
#include "Debug.h"
/*************这里只放注册函数*******************/

#ifdef __cplusplus
extern "C" {
#endif
	//括号里的第一个参数是固定写法，第二个可以传进来的参数（后台）
	int W2_Revise_clear_form(METHOD_message_t* msg, va_list args)
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
					ITKCALL(AOM_set_value_string(rfTags[0],"user_data_1", ""));
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
}
//注册dll用例
extern DLLAPI int USER_Log() {
	Debug("测试用例");
	return ITK_ok;
}
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


extern int Check_WorkFlow() {
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

//直接调用以注册METHOD
extern int Register_revise_msg(void)
{
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
//具体的处理方法
extern int HZ_attach_assembly(EPM_action_message_t msg)
{

	int ifail = ITK_ok, arg_cnt = 0, att_cnt = 0,i;
	tag_t task_tag = NULLTAG, rootTask_tag = NULLTAG, type_tag = NULLTAG, rev_rule_tag = NULLTAG;
	tag_t *attachments = NULL, *bvrs = NULL, *child_lines = NULL, child_rev_tag = NULLTAG, item_tag = NULLTAG,
		rev_tag = NULLTAG;
	char *arg = NULL, *flag = NULL, *value = NULL, **values = NULL, type_class[WSO_object_type_size_c + 1],
		item_id[ITEM_id_size_c + 1], *argflag = NULL, *argvalue = NULL,
		arg_rev_rule[128] = "", arg_status[128] = "", arg3value[128] = "", arg_debug[10] = "", userid[33] = "";

	int attachment_types = 0;
	logical is_bypass = false;
	logical debug = true;
	tag_t bomWindow = NULLTAG, bom_top_line = NULLTAG, bom_config_rule = NULLTAG;
	map<string, int> errMap;
	vector<tag_t> attach_vec;
	EPM_decision_t decision = EPM_go;

	ECHO("*************************************************************\n");
	ECHO("*                 HZ_attach_assembly is comming !            *\n");
	ECHO("*************************************************************\n");

	ECHO("POM_AM__set_application_bypass\n");
	//测试
	Debug(msg.data);
	task_tag = msg.task;
	if (task_tag == NULLTAG)
	{
		ifail = ITK_ok;
		return ifail;
	}
	tag_t rootTask = NULLTAG;
	tag_t user = NULLTAG;
	ITKCALL(ifail = EPM_ask_root_task(task_tag, &rootTask_tag));

	ITKCALL(AOM_ask_owner(rootTask_tag, &user));

	ITKCALL(SA_ask_user_identifier(user, userid));
	ECHO("userid:%s\n", userid);
	//获得所有目标对象
	ITKCALL(ifail = EPM_ask_attachments(rootTask_tag, EPM_target_attachment, &att_cnt, &attachments));
	if (debug)
		ECHO("DEBUG:   find %d target\n", att_cnt);
	for (i = 0; i < att_cnt; i++)
	{
		//测试
		Debug("11");
		ITKCALL(WSOM_ask_object_type(attachments[i], type_class));
		if (((strstr(type_class, "Revision") != NULL) || (strstr(type_class, "revision") != NULL))
			&& (strstr(type_class, "Master") == NULL) && (strstr(type_class, "master") == NULL)
			&& (strstr(type_class, "BOM") == NULL) && (strstr(type_class, "bom") == NULL) && (strstr(type_class, "Bom") == NULL))
		{
			//测试
			Debug("12");
			rev_tag = attachments[i];
			ITKCALL(ITEM_ask_item_of_rev(rev_tag, &item_tag));
			ITKCALL(ITEM_ask_id(item_tag, item_id));
			tag_t	ebom_view = NULLTAG, ebom_bvr = NULLTAG, ebom_window = NULLTAG, ebom_line = NULLTAG,
				dbom_view = NULLTAG, dbom_bvr = NULLTAG;
			ifail = getBomView(rev_tag, BOM_VIEWTYPE, &ebom_view, &ebom_bvr, 1);

			if (ebom_view != NULLTAG)
			{
				//测试
				Debug("13");
				ITKCALL(BOM_create_window(&ebom_window));
				if (rev_rule_tag != NULLTAG)
					ITKCALL(BOM_set_window_config_rule(ebom_window, rev_rule_tag));
				ITKCALL(BOM_set_window_top_line_bvr(ebom_window, ebom_bvr, &ebom_line));
				CycleBOM1(ebom_line, userid, arg_status, attach_vec, errMap, debug);
				ITKCALL(BOM_close_window(ebom_window));
			}
		}

	}
	DOFREE(attachments);
	if (debug)
		ECHO("\nDEBUG:   attach_vec.size=%d\n", attach_vec.size());
	attachment_types = EPM_target_attachment;
	for (i = 0; i < attach_vec.size(); i++)
	{
		ITKCALL(EPM_add_attachments(rootTask_tag, 1, &(attach_vec[i]), &attachment_types));
	}
	if (debug)
		ECHO("DEBUG:   errMap.size is %d\n", errMap.size());
	//释放资源
	attach_vec.clear();
	errMap.clear();
	ECHO("\n************************************************************\n");
	ECHO("*					HZ_attach_assembly is end!					 *\n");
	ECHO("*************************************************************\n");
	return ITK_ok;
}