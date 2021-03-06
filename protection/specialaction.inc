/*

	About: specialaction protection
	Author: ziggi

*/

#if !defined _protection_included
	#error "Please include protection before specialaction"
#endif

#if defined _protection_speaction_included
	#endinput
#endif

#define _protection_speaction_included

/*
	Vars
*/

static
	gPlayerSpecialAction[MAX_PLAYERS char];

/*
	Call function
*/

forward Protection_SpecialAction(playerid);
public Protection_SpecialAction(playerid)
{
	static
		current_action;

	current_action = GetPlayerSpecialAction(playerid);

	if (current_action == SPECIAL_ACTION_DUCK ||
		current_action == SPECIAL_ACTION_ENTER_VEHICLE ||
		current_action == SPECIAL_ACTION_EXIT_VEHICLE) {
		return 0;
	}

	if (current_action != gPlayerSpecialAction{playerid}) {
		if (current_action == SPECIAL_ACTION_NONE) {
			gPlayerSpecialAction{playerid} = SPECIAL_ACTION_NONE;
		} else {
			// set right special action
			if (Protection_GetParamInt(PROTECTION_SPECIALACTION, PROTECTION_COUNTERACTION) && Protection_GetPlayerParamInt(playerid, PROTECTION_SPECIALACTION, PROTECTION_PLAYER_COUNTERACTION)) {
				SetPlayerSpecialAction(playerid, gPlayerSpecialAction{playerid});
			}

			// report
			Protection_GivePlayerWarning(playerid, PROTECTION_SPECIALACTION, "%d != %d", current_action, gPlayerSpecialAction{playerid});
			return 1;
		}
	}

	return 0;
}

/*
	SetPlayerSpecialAction
*/

stock PSpecAct_SetPlayerSpecialAction(playerid, actionid)
{
	gPlayerSpecialAction{playerid} = actionid;
	return SetPlayerSpecialAction(playerid, actionid);
}
#if defined _ALS_SetPlayerSpecialAction
	#undef SetPlayerSpecialAction
#else
	#define _ALS_SetPlayerSpecialAction
#endif

#define SetPlayerSpecialAction PSpecAct_SetPlayerSpecialAction


/*
	GetPlayerSpecialAction
*/

stock PSpecAct_GetPlayerSpecialAction(playerid)
{
	new bool:is_enabled = Protection_GetParamInt(PROTECTION_SPECIALACTION, PROTECTION_ENABLED) != 0;

	if (is_enabled) {
		return gPlayerSpecialAction{playerid};
	}

	return GetPlayerSpecialAction(playerid);
}
#if defined _ALS_GetPlayerSpecialAction
	#undef GetPlayerSpecialAction
#else
	#define _ALS_GetPlayerSpecialAction
#endif

#define GetPlayerSpecialAction PSpecAct_GetPlayerSpecialAction
