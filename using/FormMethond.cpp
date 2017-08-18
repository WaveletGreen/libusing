#include "Form.h"
using namespace std;


//#ifdef __cplusplus
//extern "C" {
//#endif
//	//括号里的第一个参数是固定写法，第二个可以传进来的参数（后台）
//	int W2_Revise_clear_form(METHOD_message_t* msg, va_list args)
//	{
//		int set_prop_msg;
//		int ifail = ITK_ok, i = 0, j = 0;
//
//		char  rev_type[ITEM_type_size_c + 1],
//			*optionname = "W2_Revise_clear_form"; \
//			map<int, string> prop_map;
//		//int	msgid = va_arg(args,int );
//		//定义一个版本对象，从传进来的参数中取出
//		tag_t new_rev = va_arg(args, tag_t);
//		//操作名，从传进来的参数取出来
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
//		//-------------读取首选项(origin+rev_type+_str),itemrev与Form关系、Form类型、清空属性名
//		int option_value_count;
//		char **option_values;
//		//如果不是升版/另存为
//		if (strcmp(operation, "Revise") != 0 && strcmp(operation, "SaveAs") != 0) {
//			return ifail;
//		}
//		//询问首选项，可获得首选项的值的个数和值
//		//ITKCALL(PREF_ask_char_values(PREF_W2_Revise_clear_form, &option_value_count, &option_values));
//
//		//printf("=====option_value_count======%d\n", option_value_count);
//		//if (option_value_count == 0)
//		//{
//		//	printf("请在option中配置选项%s！\n", PREF_W2_Revise_clear_form);
//		//	return ifail;
//		//}
//		////-----------获得属性-------
//		//for (j = 1; j <option_value_count; j++)
//		//{
//		//	prop_map.insert(make_pair(j-1, option_values[j]));
//		//}
//
//		//-----------查找关系-----------WTB变更取消此值,都为masterform
//		tag_t relationTag = NULLTAG;
//		//ITKCALL (GRM_find_relation_type(option_values[0],&relationTag));
//		//查找关系类型（关系类型也是一个对象），关系名称IMAN_master_form是一个常量，可在item下找到几张表
//		ITKCALL(GRM_find_relation_type("IMAN_master_form", &relationTag));
//			if (relationTag == NULLTAG)
//			{
//				printf("=====请建立%s关系类型！======\n", option_values[0]);
//				return ifail;
//			}
//
//	   //-----------通过关系查找指定类型的Form对象
//		int rfCount = 0;
//		tag_t *rfTags = NULL;
//		char form_object_type[WSO_name_size_c + 1];
//		//GRM所有跟关系相关的模块
//		//查找当前节点和二级子节点的tag和关系对象
//		ITKCALL(GRM_list_secondary_objects_only(new_rev, relationTag, &rfCount, &rfTags));//
//		printf("=====rfCount======%d\n", rfCount);
//
//		for (i = 0; i < rfCount; i++)
//		{
//			//获取类型
//			ITKCALL(WSOM_ask_object_type(rfTags[i], form_object_type));
//			printf("=====form_object_type======%s\n", form_object_type);
//			//----------WTB取消item类型限制
//			//if(tc_strcmp(form_object_type,option_values[1]) == 0)
//			{
//				//想清空表单属性
//				//锁定表单
//				ITKCALL(AOM_lock(rfTags[i]));
//				for (j = 1; j < option_value_count; j++)
//					//---------WTB首选项改为第二个值起为属性名
//					//for(j = 2;j < option_value_count; j++)
//				{
//					//写属性，[参数1],[参数2],[参数3]->[所获得的表单],[属性名],[属性值]
//					ITKCALL(AOM_set_value_string(rfTags[i], option_values[j], ""));
//					//保存表单
//					ITKCALL(AOM_save(rfTags[i]));
//				}
//				//lock和unlock成对出现
//				ITKCALL(AOM_unlock(rfTags[i]));
//				//刷新表单
//				ITKCALL(AOM_refresh(rfTags[i], true));
//				break;
//			}
//
//		}
//		//释放资源
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
			//-------------读取首选项(origin+rev_type+_str),itemrev与Form关系、Form类型、清空属性名
			int option_value_count;
			char **option_values;
			ITKCALL(PREF_ask_char_values(option_name, &option_value_count, &option_values));
			printf("=====option_value_count======%d\n", option_value_count);
			if (option_value_count == 0)
			{
				printf("请在option中配置选项%s！\n", option_name);
				MEM_free(option_name);
				break;
			}
			MEM_free(option_name);

			//-----------查找关系
			tag_t relationTag = NULLTAG;
			ITKCALL(GRM_find_relation_type(option_values[0], &relationTag));
			if (relationTag == NULLTAG)
			{
				printf("=====请建立%s关系类型！======\n", option_values[0]);
				break;
			}

			//-----------通过关系查找指定类型的Form对象
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