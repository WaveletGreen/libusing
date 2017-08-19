#include "Debug.h"
#include "error_handling.h"

void ECHO(char *format, ...)
{
	//if( !YFJC_OPT_DEBUG )
	//    return; 

	char msg[2048];
	va_list args;

	va_start(args, format);
	vsprintf(msg, format, args);
	va_end(args);

	printf(msg);
	TC_write_syslog(msg);
}
int getBomView(tag_t rev_tag, char* viewtype, tag_t *bomView, tag_t *bomBVR, int debug)
{
	int ifail = ITK_ok, rcode = 0, count = 0, i = 0, j = 0, p = 0, q = 0, length = 0, child_cnt = 0,
		bvr_count = 0, n = 0, bom_attr_id = 0, itemid_attr_id = 0, revid_attr_id = 0, view_count = 0,
		itemrev_attr_id = 0, qty_attr_id = 0, seq_attr_id = 0, child_bvr_count = 0, factory_count = 0;

	tag_t  item = NULLTAG, new_bom_line = NULLTAG, folder = NULLTAG, *bomview_list = NULL, *bvr_list = NULL,
		p_rev_tag = NULLTAG, bom_view = NULLTAG, bvr = NULLTAG, child_item_tag = NULLTAG, view_type = NULLTAG,
		mbom_bvr = NULLTAG, ebom_bvr = NULLTAG, ebom_view = NULLTAG, mbom_view = NULLTAG;
	char object_type[WSO_object_type_size_c + 1] = "", *value = NULL;


	*bomBVR = NULLTAG;
	*bomView = NULLTAG;
	ITKCALL(ITEM_rev_list_bom_view_revs(rev_tag, &bvr_count, &bvr_list));
	if (bvr_count > 0)
	{
		mbom_bvr = NULLTAG;
		for (i = 0; i < bvr_count; i++)
		{
			ITKCALL(PS_ask_bom_view_of_bvr(bvr_list[i], &bom_view));

			ITKCALL(PS_ask_bom_view_type(bom_view, &view_type));
			//ITKCALL( PS_find_view_type(bom_view, &view_type));
			char *view_type_name = NULL;
			ITKCALL(PS_ask_view_type_name(view_type, &view_type_name));
			if (debug)
				ECHO("\nDEBUG:   view_type_name=%s\n", view_type_name);

			if (tc_strcmp(view_type_name, viewtype) == 0)
			{
				*bomBVR = bvr_list[i];
				*bomView = bom_view;
			}
			DOFREE(view_type_name);
		}
	}
	DOFREE(bvr_list);
	return ifail;
}
