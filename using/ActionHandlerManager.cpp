#include "Debug.h"
#include "common.h"
#include "error_handling.h"
extern int CycleBOM_ActionHandler(tag_t bomline, char *userid, char *status, vector<tag_t> &attach_vec, map< string, int > &errMap, logical debug)
{
	tag_t	child_item_tag = NULLTAG, child_rev_tag = NULLTAG, ebom_view = NULLTAG, ebom_bvr = NULLTAG,
		*child_lines = NULL, *status_tag_list = NULL, last_rev = NULLTAG, owning_user = NULLTAG;
	int ifail = ITK_ok, j = 0, itemrev_attr_id = 0, zuhao_attr_id = 0, child_cnt = 0, viewtype_attr_id = 0,
		status_attr_id = 0, status_count = 0;
	char  child_item_id[ITEM_id_size_c + 1] = "", *viewtype_value = NULL, *status_list = NULL,
		child_rev_id[8] = "", user_id[33] = "";

	ITKCALL(ifail = BOM_line_look_up_attribute(bomAttr_itemRevStatus, &status_attr_id));
	ITKCALL(ifail = BOM_line_look_up_attribute(bomAttr_lineItemRevTag, &itemrev_attr_id));
	ITKCALL(ifail = BOM_line_ask_child_lines(bomline, &child_cnt, &child_lines));
	for (int i = 0; i < child_cnt; i++)
	{//测试
		Debug("CycleBOM1__1");
		//ITKCALL(ifail = BOM_line_ask_attribute_string(child_lines[k], status_attr_id, &status_list));
		ITKCALL(ifail = BOM_line_ask_attribute_tag(child_lines[i], itemrev_attr_id, &child_rev_tag));
		ITKCALL(AOM_ask_owner(child_rev_tag, &owning_user));
		ITKCALL(SA_ask_user_identifier(owning_user, user_id));
		if (debug)
			ECHO("process user_id is %s, object owner is %s\n", userid, user_id);
		if (strcmp(userid, user_id) == 0)
		{
			//测试
			Debug("CycleBOM1__2");
			ITKCALL(WSOM_ask_release_status_list(child_rev_tag, &status_count, &status_tag_list));
			logical isInculde = false;
			if (status_count > 0)
			{
				//测试
				Debug("CycleBOM1__3");
				for (int j = 0; j < status_count; j++)
				{
					char status_type[WSO_name_size_c + 1] = "";
					ITKCALL(CR_ask_release_status_type(status_tag_list[j], status_type));
					if (debug)
						ECHO("指定状态:%s, 对象发布状态：%s\n", status, status_type);
					if (stricmp(status_type, status) == 0)
					{

						//测试
						Debug("CycleBOM1__4");
						int last_status_count = 0;
						tag_t *last_status_tag_list = NULL, new_child_rev = NULLTAG;
						ITKCALL(ITEM_ask_item_of_rev(child_rev_tag, &child_item_tag));
						ITKCALL(ITEM_ask_latest_rev(child_item_tag, &last_rev));
						ITKCALL(WSOM_ask_release_status_list(last_rev, &last_status_count, &last_status_tag_list));
						if (last_status_count == 0)
						{
							attach_vec.push_back(last_rev);
							if (debug)
								ECHO("add last_rev");
						}
						else
						{
							//POM_AM__set_application_bypass(true);
							//ITKCALL( ITEM_create_rev(child_item_tag, NULL, &new_child_rev ));
							ITKCALL(ITEM_copy_rev(last_rev, NULL, &new_child_rev));
							ITKCALL(AOM_save(new_child_rev));
							ITKCALL(AOM_unlock(new_child_rev));
							attach_vec.push_back(new_child_rev);
							if (debug)
								ECHO("add new_child_rev");
						}
						DOFREE(last_status_tag_list);
						
					}
				} //for
			}
			else
			{
				attach_vec.push_back(child_rev_tag);
				if (debug)
					ECHO("add self");
			}
			DOFREE(status_tag_list);
		}
	}
	for (int i = 0; i < child_cnt; i++)
	{
		ifail = CycleBOM_ActionHandler(child_lines[i], userid, status, attach_vec, errMap, debug);
	}
	return ifail;
}
//具体的处理方法
extern int HZ_attach_assembly(EPM_action_message_t msg)
{

	int ifail = ITK_ok, arg_cnt = 0, att_cnt = 0, i;
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
	//获得所有目标对象下挂载的对象
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
				CycleBOM_ActionHandler(ebom_line, userid, arg_status, attach_vec, errMap, debug);
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

extern int CycleBOM_ActionHandler_Update(tag_t bomline, char *userid, char *status, vector<tag_t> &attach_vec, map< string, int > &errMap, logical debug)
{
	tag_t	child_item_tag = NULLTAG, child_rev_tag = NULLTAG, ebom_view = NULLTAG, ebom_bvr = NULLTAG,
		*child_lines = NULL, *status_tag_list = NULL, last_rev = NULLTAG, owning_user = NULLTAG;
	int ifail = ITK_ok, j = 0, itemrev_attr_id = 0, zuhao_attr_id = 0, child_cnt = 0, viewtype_attr_id = 0,
		status_attr_id = 0, status_count = 0;
	char  child_item_id[ITEM_id_size_c + 1] = "", *viewtype_value = NULL, *status_list = NULL,
		child_rev_id[8] = "", user_id[33] = "";

	ITKCALL(ifail = BOM_line_look_up_attribute(bomAttr_itemRevStatus, &status_attr_id));
	ITKCALL(ifail = BOM_line_look_up_attribute(bomAttr_lineItemRevTag, &itemrev_attr_id));
	ITKCALL(ifail = BOM_line_ask_child_lines(bomline, &child_cnt, &child_lines));
	for (int i = 0; i < child_cnt; i++)
	{//测试
		Debug("CycleBOM1__1");
		//ITKCALL(ifail = BOM_line_ask_attribute_string(child_lines[k], status_attr_id, &status_list));
		ITKCALL(ifail = BOM_line_ask_attribute_tag(child_lines[i], itemrev_attr_id, &child_rev_tag));
		ITKCALL(AOM_ask_owner(child_rev_tag, &owning_user));

		
		ITKCALL(SA_ask_user_identifier(owning_user, user_id));

		if (debug)
			ECHO("process user_id is %s, object owner is %s\n", userid, user_id);
		if (strcmp(userid, user_id) == 0)
		{
			//测试
			Debug("CycleBOM1__2");
			ITKCALL(WSOM_ask_release_status_list(child_rev_tag, &status_count, &status_tag_list));
			logical isInculde = false;
			if (status_count > 0)
			{
				//测试
				Debug("CycleBOM1__3");
				for (int j = 0; j < status_count; j++)
				{
					char status_type[WSO_name_size_c + 1] = "";
					ITKCALL(CR_ask_release_status_type(status_tag_list[j], status_type));
					//该版本已发布
					if (debug)
						ECHO("指定状态:%s, 对象发布状态：%s\n", status, status_type);
					//版本没有发布
					if (stricmp(status_type, "TCM Released") == 0)
					{
						////测试
						//Debug("CycleBOM1__4");
						//int last_status_count = 0;
						//tag_t *last_status_tag_list = NULL, new_child_rev = NULLTAG;
						Debug(child_rev_tag);
						ITKCALL(ITEM_ask_item_of_rev(child_rev_tag, &child_item_tag));
						ITKCALL(ITEM_ask_latest_rev(child_item_tag, &last_rev));
						char* itemName = NULL;
						char* itemID=NULL;
						Debug("到这里");
						ITEM_ask_rev_id(child_item_tag, itemID);
						ITEM_ask_rev_name(child_item_tag, itemName);
						Debug(user_id);
						Debug(itemName);
						Debug(itemID);
						Debug("版本已发布");
					}
				} //for
			}
			else
			{
				attach_vec.push_back(child_rev_tag);
				if (debug)
					ECHO("add self");
			}
			DOFREE(status_tag_list);
		}
	}
	for (int i = 0; i < child_cnt; i++)
	{
		ifail = CycleBOM_ActionHandler(child_lines[i], userid, status, attach_vec, errMap, debug);
	}
	return ifail;
}
extern int ActionHandler_Update(EPM_action_message_t msg)
{
	int ifail = ITK_ok, arg_cnt = 0, att_cnt = 0, i;
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
				CycleBOM_ActionHandler_Update(ebom_line, userid, arg_status, attach_vec, errMap, debug);
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

