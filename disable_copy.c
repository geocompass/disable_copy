#include "postgres.h"
#include "tcop/utility.h"
PG_MODULE_MAGIC;
void _PG_init(void);
void _PG_fini(void);
static ProcessUtility_hook_type prev_ProcessUtility = NULL;
static void disable_copy_utility(PlannedStmt *pstmt,
                                 const char *queryString,
                                 ProcessUtilityContext context,
                                 ParamListInfo params,
                                 QueryEnvironment *queryEnv,
                                 DestReceiver *dest,
                                 char *completionTag);
static void disable_copy_utility(PlannedStmt *pstmt, const char *queryString, ProcessUtilityContext context,
                                 ParamListInfo params,
                                 QueryEnvironment *queryEnv,
                                 DestReceiver *dest,
                                 char *completionTag)
{
    Node *parsetree = pstmt->utilityStmt;
    switch (nodeTag(parsetree))
    {
    case T_CopyStmt:
        ereport(ERROR, (errcode(ERRCODE_INVALID_ROLE_SPECIFICATION), errmsg("Not support copy")));
        break;
    default:
        break;
    }
    if (prev_ProcessUtility)
			prev_ProcessUtility(pstmt, queryString,
								context, params, queryEnv,
								dest, completionTag);
		else
			standard_ProcessUtility(pstmt, queryString,
									context, params, queryEnv,
									dest, completionTag);
}
/*
 *Install the hook 
 */
void _PG_init(void)
{
        prev_ProcessUtility = ProcessUtility_hook;
        ProcessUtility_hook = disable_copy_utility;
}

/*
 * _PG_fini
 * Uninstall the hook.
 */
void _PG_fini(void)
{
        ProcessUtility_hook = prev_ProcessUtility;
}