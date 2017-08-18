//��ȡ�������µ�item������referencr��ȡtag
#include "common.h"
#include <epm/signoff.h>
#include <sa/sa.h>
#include <tccore/item.h>
#include <tccore/aom.h>
#include "error_handling.h"
#include <tccore\aom_prop.h>
/**
��һЩ�����ִ�з���
*/
int GetUserItems(EPM_rule_message_t msg) {
	fprintf(stdout, "\n-------Get User Bom-------\n");
	tag_t user_tag = NULLTAG;//�û�id
	tag_t rev_tag = NULLTAG;//
	tag_t item_tag = NULLTAG;//
	tag_t home_folder_tag = NULLTAG;//��Ŀ¼
	tag_t task_tag = NULLTAG;//����ڵ�
	tag_t rootTask_tag = NULLTAG;//������ڵ�
	int att_cnt;
	char item_id[129], userid[33];
	tag_t *attachments;
	task_tag = msg.task;
	fprintf(stdout, "---task.tag=%s----", task_tag);
	EPM_ask_root_task(task_tag, &rootTask_tag);//��ȡ������ڵ�
	AOM_ask_owner(rootTask_tag, &user_tag);//��ȡ�����������
	SA_ask_user_identifier(user_tag, userid);//��ȡ�����ߵ�tag����id
	//��ȡ�����ϵĸ����ڵ�
	EPM_ask_attachments(rootTask_tag, EPM_target_attachment, &att_cnt, &attachments);
	//������Щ�ڵ㣬����Ӧ���õݹ�ȽϺ�
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
