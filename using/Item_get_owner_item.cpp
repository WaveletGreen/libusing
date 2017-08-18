//获取对象名下的item，根据referencr获取tag
#include "common.h"
#include <epm/signoff.h>
#include <sa/sa.h>
#include <tccore/item.h>
#include <tccore/aom.h>
#include "error_handling.h"
#include <tccore\aom_prop.h>
/**
放一些具体的执行方法
*/
int GetUserItems(EPM_rule_message_t msg) {
	fprintf(stdout, "\n-------Get User Bom-------\n");
	tag_t user_tag = NULLTAG;//用户id
	tag_t rev_tag = NULLTAG;//
	tag_t item_tag = NULLTAG;//
	tag_t home_folder_tag = NULLTAG;//根目录
	tag_t task_tag = NULLTAG;//任务节点
	tag_t rootTask_tag = NULLTAG;//任务根节点
	int att_cnt;
	char item_id[129], userid[33];
	tag_t *attachments;
	task_tag = msg.task;
	fprintf(stdout, "---task.tag=%s----", task_tag);
	EPM_ask_root_task(task_tag, &rootTask_tag);//获取任务根节点
	AOM_ask_owner(rootTask_tag, &user_tag);//获取任务的所有者
	SA_ask_user_identifier(user_tag, userid);//获取所有者的tag，即id
	//获取任务上的附属节点
	EPM_ask_attachments(rootTask_tag, EPM_target_attachment, &att_cnt, &attachments);
	//遍历这些节点，这里应该用递归比较好
	for (int i = 0; i < att_cnt; i++)
	{
		rev_tag = attachments[i];
		ITEM_ask_item_of_rev(rev_tag, &item_tag);
		ITEM_ask_id(item_tag, item_id);
		fprintf(stdout, "\n %s", item_id);
	}
	return ITK_ok;
}

int set_prop_msg(METHOD_message_t* msg, va_list args)
{
	int ifail = ITK_ok, i = 0, j = 0, form_count = 0;
	tag_t item_tag = NULLTAG, rev = NULLTAG, master_form_rel_type = NULLTAG,
		master_form = NULLTAG, *form_list = NULL;
	char obj_type[WSO_name_size_c + 1] = "", *value = NULL;


	master_form = msg->object;
	CALL(WSOM_ask_object_type(master_form, obj_type));
	printf("=============type is %s\n", obj_type);
	CALL(AOM_ask_value_string(master_form, "user_data_1", &value));
	printf("ask property =%s!\n", value);

	return ITK_ok;
}
