#include "Form.h"
using namespace std;


//#ifdef __cplusplus
//extern "C" {
//#endif
//	//������ĵ�һ�������ǹ̶�д�����ڶ������Դ������Ĳ�������̨��
//	int W2_Revise_clear_form(METHOD_message_t* msg, va_list args)
//	{
//		int set_prop_msg;
//		int ifail = ITK_ok, i = 0, j = 0;
//
//		char  rev_type[ITEM_type_size_c + 1],
//			*optionname = "W2_Revise_clear_form"; \
//			map<int, string> prop_map;
//		//int	msgid = va_arg(args,int );
//		//����һ���汾���󣬴Ӵ������Ĳ�����ȡ��
//		tag_t new_rev = va_arg(args, tag_t);
//		//���������Ӵ������Ĳ���ȡ����
//		char*  operation = va_arg(args, char*);
//
//
//		/*tag_t parent_rev = va_arg(args,tag_t );
//		int copyCount = va_arg(args,int );
//		tag_t **obj_tags = va_arg(args,tag_t** );*/
//
//		printf("*******************************************************\n");
//		printf("*      W2_Revise_clear_form is comming         *\n");
//		printf("*******************************************************\n");
//
//		//printf("msgid==============================%d \n",msgid);
//		printf("new_rev==============================%d\n", new_rev);
//		printf("operation==============================%s\n", operation);
//		//printf("parent_rev==============================%u\n",parent_rev);
//		//printf("copyCount==============================%d\n",copyCount);
//
//		//-------------��ȡ��ѡ��(origin+rev_type+_str),itemrev��Form��ϵ��Form���͡����������
//		int option_value_count;
//		char **option_values;
//		//�����������/���Ϊ
//		if (strcmp(operation, "Revise") != 0 && strcmp(operation, "SaveAs") != 0) {
//			return ifail;
//		}
//		//ѯ����ѡ��ɻ����ѡ���ֵ�ĸ�����ֵ
//		//ITKCALL(PREF_ask_char_values(PREF_W2_Revise_clear_form, &option_value_count, &option_values));
//
//		//printf("=====option_value_count======%d\n", option_value_count);
//		//if (option_value_count == 0)
//		//{
//		//	printf("����option������ѡ��%s��\n", PREF_W2_Revise_clear_form);
//		//	return ifail;
//		//}
//		////-----------�������-------
//		//for (j = 1; j <option_value_count; j++)
//		//{
//		//	prop_map.insert(make_pair(j-1, option_values[j]));
//		//}
//
//		//-----------���ҹ�ϵ-----------WTB���ȡ����ֵ,��Ϊmasterform
//		tag_t relationTag = NULLTAG;
//		//ITKCALL (GRM_find_relation_type(option_values[0],&relationTag));
//		//���ҹ�ϵ���ͣ���ϵ����Ҳ��һ�����󣩣���ϵ����IMAN_master_form��һ������������item���ҵ����ű�
//		ITKCALL(GRM_find_relation_type("IMAN_master_form", &relationTag));
//			if (relationTag == NULLTAG)
//			{
//				printf("=====�뽨��%s��ϵ���ͣ�======\n", option_values[0]);
//				return ifail;
//			}
//
//	   //-----------ͨ����ϵ����ָ�����͵�Form����
//		int rfCount = 0;
//		tag_t *rfTags = NULL;
//		char form_object_type[WSO_name_size_c + 1];
//		//GRM���и���ϵ��ص�ģ��
//		//���ҵ�ǰ�ڵ�Ͷ����ӽڵ��tag�͹�ϵ����
//		ITKCALL(GRM_list_secondary_objects_only(new_rev, relationTag, &rfCount, &rfTags));//
//		printf("=====rfCount======%d\n", rfCount);
//
//		for (i = 0; i < rfCount; i++)
//		{
//			//��ȡ����
//			ITKCALL(WSOM_ask_object_type(rfTags[i], form_object_type));
//			printf("=====form_object_type======%s\n", form_object_type);
//			//----------WTBȡ��item��������
//			//if(tc_strcmp(form_object_type,option_values[1]) == 0)
//			{
//				//����ձ�����
//				//������
//				ITKCALL(AOM_lock(rfTags[i]));
//				for (j = 1; j < option_value_count; j++)
//					//---------WTB��ѡ���Ϊ�ڶ���ֵ��Ϊ������
//					//for(j = 2;j < option_value_count; j++)
//				{
//					//д���ԣ�[����1],[����2],[����3]->[����õı�],[������],[����ֵ]
//					ITKCALL(AOM_set_value_string(rfTags[i], option_values[j], ""));
//					//�����
//					ITKCALL(AOM_save(rfTags[i]));
//				}
//				//lock��unlock�ɶԳ���
//				ITKCALL(AOM_unlock(rfTags[i]));
//				//ˢ�±�
//				ITKCALL(AOM_refresh(rfTags[i], true));
//				break;
//			}
//
//		}
//		//�ͷ���Դ
//		MEM_free(option_values);
//		MEM_free(rfTags);
//
//
//		/**/
//		printf("*******************************************************\n");
//		printf("*        W2_Clear_Form_PropValue is end           *\n");
//		printf("*******************************************************\n");
//
//		return ifail;
//	}
//}

int D5DFHM_Clear_Form_PropValue(METHOD_message_t* msg, va_list args)
{
	int ifail = ITK_ok, i = 0, j = 0;

	char  *origin = "DFHM_", *_str = "_Clear_QzInfo",
		*option_name;

	tag_t new_rev = va_arg(args, tag_t);
	char*  operation = va_arg(args, char*);
	tag_t parent_rev = va_arg(args, tag_t);
	int copyCount = va_arg(args, int);
	tag_t **obj_tags = va_arg(args, tag_t**);

	printf("*******************************************************\n");
	printf("*      D5DFHM_Clear_Form_PropValue is comming         *\n");
	printf("*******************************************************\n");

	/*printf("new_rev==============================%d\n",new_rev);
	printf("operation==============================%s\n",operation);
	printf("parent_rev==============================%u\n",parent_rev);
	printf("copyCount==============================%d\n",copyCount);*/

	int paramCount = 0, index = 0;
	BMF_extension_arguments_t *input_args = NULL;
	char DataSetType[BMF_EXTENSION_STRGVAL_size_c + 1];

	ifail = BMF_get_user_params(msg, &paramCount, &input_args);

	if (ifail == ITK_ok && paramCount > 0)
	{
		for (index = 0; index < paramCount; index++)
		{
			tc_strcpy(DataSetType, input_args[index].arg_val.str_value);
			printf("DataSetType=========%s\n", DataSetType);

			option_name = (char*)MEM_alloc(sizeof(char)*(tc_strlen(origin) + tc_strlen(DataSetType) + tc_strlen(_str) + 1));
			tc_strcpy(option_name, origin);
			tc_strcat(option_name, DataSetType);
			tc_strcat(option_name, _str);
			//-------------��ȡ��ѡ��(origin+rev_type+_str),itemrev��Form��ϵ��Form���͡����������
			int option_value_count;
			char **option_values;
			ITKCALL(PREF_ask_char_values(option_name, &option_value_count, &option_values));
			printf("=====option_value_count======%d\n", option_value_count);
			if (option_value_count == 0)
			{
				printf("����option������ѡ��%s��\n", option_name);
				MEM_free(option_name);
				break;
			}
			MEM_free(option_name);

			//-----------���ҹ�ϵ
			tag_t relationTag = NULLTAG;
			ITKCALL(GRM_find_relation_type(option_values[0], &relationTag));
			if (relationTag == NULLTAG)
			{
				printf("=====�뽨��%s��ϵ���ͣ�======\n", option_values[0]);
				break;
			}

			//-----------ͨ����ϵ����ָ�����͵�Form����
			int rfCount = 0;
			tag_t *rfTags = NULL;
			char form_object_type[WSO_name_size_c + 1];
			ITKCALL(GRM_list_secondary_objects_only(new_rev, relationTag, &rfCount, &rfTags));//
			printf("=====rfCount======%d\n", rfCount);

			for (i = 0; i < rfCount; i++)
			{
				ITKCALL(WSOM_ask_object_type(rfTags[i], form_object_type));
				printf("=====form_object_type======%s\n", form_object_type);
				if (tc_strcmp(form_object_type, option_values[1]) == 0)
				{
					ITKCALL(AOM_lock(rfTags[i]));
					for (j = 2; j < option_value_count; j++)
					{
						ITKCALL(AOM_set_value_string(rfTags[i], option_values[j], ""));
						ITKCALL(AOM_save(rfTags[i]));
					}
					ITKCALL(AOM_unlock(rfTags[i]));
					ITKCALL(AOM_refresh(rfTags[i], true));
					break;
				}

			}
			MEM_free(option_values);
			MEM_free(rfTags);
		}
		MEM_free(input_args);
	}

	/**/
	printf("*******************************************************\n");
	printf("*        D5DFHM_Clear_Form_PropValue is end           *\n");
	printf("*******************************************************\n");

	return ifail;
}