//ֱ�ӵ�����ע��METHOD
#include "Form.h"
#include "Debug.h"
//������ĵ�һ�������ǹ̶�д�����ڶ������Դ������Ĳ�������̨��
extern int W2_Revise_clear_form(METHOD_message_t* msg, va_list args)
{
	int ifail = ITK_ok;
	char  *optionname = "W2_Revise_clear_form";
	map<int, string> prop_map;
	tag_t new_rev = va_arg(args, tag_t);
	//���������Ӵ������Ĳ���ȡ����
	char* operation = va_arg(args, char*);
	printf("*******************************************************\n");
	printf("*      W2_Revise_clear_form is comming         *\n");
	printf("*******************************************************\n");
	printf("new_rev==============================%d\n", new_rev);
	printf("operation==============================%s\n", operation);
	//�����������/���Ϊ����
	if (strcmp(operation, "Revise") != 0 && strcmp(operation, "SaveAs") != 0) {
		fprintf(stdout, "-----��������/���Ϊ------");
		return ifail;
	}
	fprintf(stdout, "\n-------------------->1<----------------\n");
	tag_t relationTag = NULLTAG;
	//���ҹ�ϵ���ͣ���ϵ����Ҳ��һ�����󣩣���ϵ����IMAN_master_form��һ������������item���ҵ����ű�
	ITKCALL(GRM_find_relation_type("IMAN_master_form", &relationTag));
	fprintf(stdout, "\n-------------------->relationTag=%d<----------------\n", relationTag);
	//-----------ͨ����ϵ����ָ�����͵�Form����
	int rfCount = 0;
	tag_t *rfTags = NULL;
	char form_object_type[WSO_name_size_c + 1];
	//GRM���и���ϵ��ص�ģ��
	//���ҵ�ǰ�ڵ�Ͷ����ӽڵ��tag�͹�ϵ����
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
