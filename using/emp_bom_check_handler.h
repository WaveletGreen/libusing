#pragma once
#pragma warning (disable: 4996) 
#pragma warning (disable: 4819) 

/**
* @headerfile			tcua Í·ÎÄ¼þ
*/
#include <tc\tc_macros.h>
#include <tc\emh.h>
#include <tc\preferences.h>
#include <property\propdesc.h>
#include <epm\epm.h>
#include <epm\epm_toolkit_tc_utils.h>
#include <tccore\item.h>
#include <tccore\grmtype.h>
#include <tccore\grm.h>
#include <tccore\imantype.h>
#include <sa\am.h>
#include <sa\sa.h>
#include <tccore\aom.h>
#include <tccore\aom_prop.h>
#include <property\prop_errors.h>
#include <tccore\workspaceobject.h>
#include <qry\qry.h>
#include <bom\bom_attr.h>
#include <bom\bom.h>
#include <epm\signoff.h>
#include <pom\pom\pom.h>
#include <pom\pom\pom_errors.h>
#include <fclasses\tc_date.h>
#include <epm\cr.h>
#include <cfm\cfm.h>

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include <string>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
using namespace std;

/**
* @headerfile			user's header files
*/

#include "epm_handler_common.h"
#include "error_handling.h"

#define BOM_VIEWTYPE "view"
void ECHO(char *format, ...);
