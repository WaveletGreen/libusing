#include"emp_bom_check_handler.h"
int getBomView(tag_t rev_tag, char* viewtype, tag_t *bomView, tag_t *bomBVR, int debug);
int CycleBOM(tag_t bomline, char *process_owner, char *arg_status, vector<string> &status_vec, map< string, int > &errMap, logical debug);
int CycleBOM1(tag_t bomline, char *userid, char *status, vector<tag_t> &attach_vec, map< string, int > &errMap, logical debug);

int HZ_Check_BOM_Condition(EPM_rule_message_t msg);
int HZ_attach_assembly(EPM_action_message_t msg);