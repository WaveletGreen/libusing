#include "Form.h"
#include "common.h"
#include "error_handling.h"
#include "Debug.h"
#include <server_exits/user_server_exits.h>

int CycleBOM(tag_t bomline, char *process_owner, char *arg_status, vector<string> &status_vec, map< string, int > &errMap, logical debug)
{
	tag_t	child_item_tag = NULLTAG, child_rev_tag = NULLTAG, ebom_view = NULLTAG, ebom_bvr = NULLTAG,
		*child_lines = NULL, *status_tag_list = NULL, owning_user = NULLTAG;
	int ifail = ITK_ok, j = 0, itemrev_attr_id = 0, zuhao_attr_id = 0, child_cnt = 0, viewtype_attr_id = 0,
		status_attr_id = 0, status_count = 0;
	char  child_item_id[ITEM_id_size_c + 1] = "", *viewtype_value = NULL, *status_list = NULL,
		child_rev_id[8] = "", user_id[33] = "";

	ITKCALL(ifail = BOM_line_look_up_attribute(bomAttr_itemRevStatus, &status_attr_id));
	ITKCALL(ifail = BOM_line_look_up_attribute(bomAttr_lineItemRevTag, &itemrev_attr_id));
	ITKCALL(ifail = BOM_line_ask_child_lines(bomline, &child_cnt, &child_lines));
	fprintf(stdout, "------------>%d<------------\n", &child_cnt);
	for (int i = 0; i < child_cnt; i++)
	{
		//ITKCALL(ifail = BOM_line_ask_attribute_string(child_lines[k], status_attr_id, &status_list));
		ITKCALL(ifail = BOM_line_ask_attribute_tag(child_lines[i], itemrev_attr_id, &child_rev_tag));
		ITKCALL(AOM_ask_owner(child_rev_tag, &owning_user));
		ITKCALL(SA_ask_user_identifier(owning_user, user_id));
		//获取流程发布状态
		ITKCALL(WSOM_ask_release_status_list(child_rev_tag, &status_count, &status_tag_list));
		ECHO("status_count：%d\n", status_count);
		logical isInculde = false;
		//status_count=0即为发布状态
		if (status_count > 0)
		{
			for (int j = 0; j < status_count; j++)
			{

				char status_type[WSO_name_size_c + 1] = "";
				ITKCALL(CR_ask_release_status_type(status_tag_list[j], status_type));
				if (debug)
					//打印对象状态
					ECHO("----------->>检查状态: %s, 对象发布状态：%s\n", arg_status, status_type);
				//	if (strcmp(process_owner, user_id) == 0)
				//	{
				//		if (isInVec(status_vec, arg_status, 0, status_type)) //>=
				//		{
				//			isInculde = true;
				//		}
				//	}
				//	else if (strcmp(process_owner, user_id) != 0 &&
				//		stricmp(status_type, "TCM Released") != 0)
				//	{
				//		if (isInVec(status_vec, arg_status, 1, status_type)) //>
				//		{
				//			errMap.insert(pair<string, int>(status_type, ERROR_STATUS_ERROR));
				//			isInculde = true;
				//		}
				//	}

				//}
				//if (!isInculde)
				//{
				//	ITKCALL(ITEM_ask_rev_id(child_rev_tag, child_rev_id));
				//	ITKCALL(ITEM_ask_item_of_rev(child_rev_tag, &child_item_tag));
				//	ITKCALL(ITEM_ask_id(child_item_tag, child_item_id));
				//	string errMsg;
				//	errMsg.assign(child_item_id).append("/").append(child_rev_id).append(" 成熟度不符合发布要求");
				//	errMap.insert(pair<string, int>(errMsg, ERROR_STATUS_ERROR));
				//}
			}
		}
		else //working状态
		{
			//提示无状态
			ECHO("无状态, ：process_owner:%s, user_id:%s\n", arg_status, user_id);
			//if (strcmp(process_owner, user_id) != 0)
			//{
			//询问修订版本id
			ITKCALL(ITEM_ask_rev_id(child_rev_tag, child_rev_id));
			//获取版本item对象
			ITKCALL(ITEM_ask_item_of_rev(child_rev_tag, &child_item_tag));
			//获取item的id
			ITKCALL(ITEM_ask_id(child_item_tag, child_item_id));
			string errMsg;
			errMsg.assign(child_item_id).append("\t").append(child_rev_id).append(" 未发布");
			fprintf(stdout, "------->%s<-------", errMsg);
			//插入错误消息
			errMap.insert(pair<string, int>(errMsg, ERROR_STATUS_ERROR));
		}
		//}
		//释放资源
		DOFREE(status_tag_list);
	}
	//子节点递归
	for (int i = 0; i < child_cnt; i++)
	{
		ifail = CycleBOM(child_lines[i], process_owner, arg_status, status_vec, errMap, debug);
	}
	return ifail;
}
//测试用例,其实这不属于任何handler
extern DLLAPI int USER_Log() {
	Debug("测试用例");
	return ITK_ok;
}
//检查item的发布状态，如果BoM下还有没有发布的版本，则不允许通过流程
extern int HZ_Check_BOM_Condition(EPM_rule_message_t msg)
{

	int ifail = ITK_ok, arg_cnt = 0, att_cnt = 0, i, pref_count = 0, bvr_cnt = 0, child_cnt = 0,
		status_attr_id = 0, rev_attr_id = 0, form_count = 0, value_count = 0, n_instances = 0,
		factory_count = 0, num = 0, bvr_count = 0;
	tag_t task_tag = NULLTAG, rootTask_tag = NULLTAG, type_tag = NULLTAG, rev_rule_tag = NULLTAG;
	tag_t *attachments = NULL, *bvrs = NULL, *child_lines = NULL, child_rev_tag = NULLTAG, item_tag = NULLTAG,
		rev_tag = NULLTAG, user = NULLTAG;
	char *arg = NULL, *flag = NULL, *value = NULL, **values = NULL, type_class[WSO_object_type_size_c + 1],
		item_id[ITEM_id_size_c + 1], *argflag = NULL, *argvalue = NULL,
		arg_rev_rule[128] = "", arg_status[128] = "", arg3value[128] = "", arg_debug[10] = "", userid[33] = "";
	tag_t bomWindow = NULLTAG, bom_top_line = NULLTAG, bom_config_rule = NULLTAG;
	map<string, int> errMap;
	vector<string> status_vec;
	//map<string,string> zuhaoMap;
	EPM_decision_t decision = EPM_go;
	logical debug = true;
	ECHO("*************************************************************\n");
	ECHO("*                 HZ_Check_BOM_Condition is comming !            *\n");
	ECHO("*************************************************************\n");
	//获取任务标签
	task_tag = msg.task;
	//如果没有任务，则返回，不允许向下执行
	if (task_tag == NULLTAG)
	{
		ifail = ITK_ok;
		//goto end_handler;
		return EPM_nogo;
	}
	tag_t rootTask = NULLTAG;
	status_vec.clear();
	//获得参数，流程中的参数，暂时用不上
	arg_cnt = TC_number_of_arguments(msg.arguments);
	//获取认为你根节点
	ITKCALL(ifail = EPM_ask_root_task(task_tag, &rootTask_tag));
	//获取根节点的所有者
	ITKCALL(AOM_ask_owner(rootTask_tag, &user));
	//获取所有者的tag
	ITKCALL(SA_ask_user_identifier(user, userid));
	//获取任务的所有下级任务
	ITKCALL(ifail = EPM_ask_attachments(rootTask_tag, EPM_target_attachment, &att_cnt, &attachments));
	if (debug)
		ECHO("DEBUG:   find %d target\n", att_cnt);
	//遍历下级子任务
	for (i = 0; i < att_cnt; i++)
	{
		fprintf(stdout, "------------>1<------------\n");
		//获取子任务的类型
		ITKCALL(WSOM_ask_object_type(attachments[i], type_class));
		//如果不是修订版本/主版本
		fprintf(stdout, "------------>%s<------------\n", &type_class);
		if (((strstr(type_class, "Revision") != NULL) || (strstr(type_class, "revision") != NULL))
			&& (strstr(type_class, "Master") == NULL) && (strstr(type_class, "master") == NULL)
			&& (strstr(type_class, "BOM") == NULL) && (strstr(type_class, "bom") == NULL) && (strstr(type_class, "Bom") == NULL))
		{
			fprintf(stdout, "------------>2<------------\n");
			//获取版本号tag
			rev_tag = attachments[i];
			fprintf(stdout, "------------>输出版本tag=%d<------------\n", rev_tag);
			//获取版本的item对象
			ITKCALL(ITEM_ask_item_of_rev(rev_tag, &item_tag));
			//获取item的id，如00032
			ITKCALL(ITEM_ask_id(item_tag, item_id));
			tag_t	ebom_view = NULLTAG, ebom_bvr = NULLTAG, ebom_window = NULLTAG, ebom_line = NULLTAG,
				dbom_view = NULLTAG, dbom_bvr = NULLTAG;
			//获取bom视图，即使在服务端上也要获取bom视图，视图是item的一个属性
			ifail = getBomView(rev_tag, BOM_VIEWTYPE, &ebom_view, &ebom_bvr, 1);
			//如果没有视图
			if (ebom_view != NULLTAG)
			{
				fprintf(stdout, "------------>3<------------\n");
				//尝试创建视图
				ITKCALL(BOM_create_window(&ebom_window));
				//没有版本规则
				if (rev_rule_tag != NULLTAG) {
					fprintf(stdout, "\n进入设置版本规则----版本规则编号=%d----\n", rev_rule_tag);
					ITKCALL(BOM_set_window_config_rule(ebom_window, rev_rule_tag));
				}
				ITKCALL(BOM_set_window_top_line_bvr(ebom_window, ebom_bvr, &ebom_line));
				//开始回调函数，遍历所有的下级子item
				fprintf(stdout, "------------>4<------------\n");
				CycleBOM(ebom_line, userid, arg_status, status_vec, errMap, debug);
				ITKCALL(BOM_close_window(ebom_window));
			}
		}
		//释放资源
		DOFREE(attachments);
		//调试
		if (debug)
			ECHO("DEBUG:   errMap.size is %d\n", errMap.size());
		if (errMap.size() > 0)
			decision = EPM_nogo;
		else
			decision = EPM_go;
		map<string, int>::iterator err_it;
		//一次性将错误信息打印出来
		for (err_it = errMap.begin(); err_it != errMap.end(); err_it++)
		{
			ECHO("DEBUG:  err_it is %s\n", err_it->first.c_str());
			EMH_store_error_s1(EMH_severity_information, err_it->second, err_it->first.c_str());
		}
		errMap.clear();
		ECHO("\n************************************************************\n");
		ECHO("*					HZ_Check_BOM_Condition is end!				\n");
		ECHO("*************************************************************\n");
		return decision;
	}
	return EPM_go;
}
