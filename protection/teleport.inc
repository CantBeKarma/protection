/*

	About: teleport protection
	Author: ziggi

*/

#if !defined _protection_included
	#error "Please include protection before teleport"
#endif

#if !defined _getspawninfo_included
	#error "Please include getspawninfo before teleport"
#endif

#if defined _protection_teleport_included
	#endinput
#endif

#define _protection_teleport_included

/*
	Vars
*/

static
	Float:gPrevPos[MAX_PLAYERS][3],
	Float:gOldPos[MAX_PLAYERS][3];

/*
	Call function
*/

forward Protection_Teleport(playerid);
public Protection_Teleport(playerid)
{
	// calculate distance
	static
		Float:pos_x,
		Float:pos_y,
		Float:pos_z,
		Float:distance_prev,
		Float:distance_old,
		Float:max_distance,
		vehicleid;

	GetPlayerPos(playerid, pos_x, pos_y, pos_z);

	distance_prev = VectorSize(gPrevPos[playerid][0] - pos_x, gPrevPos[playerid][1] - pos_y, 0.0);
	distance_old = VectorSize(gOldPos[playerid][0] - pos_x, gOldPos[playerid][1] - pos_y, 0.0);

	vehicleid = GetPlayerVehicleID(playerid);

	// checks	
	if (vehicleid) {
		max_distance = Protection_GetParamFloat(PROTECTION_TELEPORT, PROTECTION_MAX_VEHICLE_DISTANCE);
	} else {
		max_distance = Protection_GetParamFloat(PROTECTION_TELEPORT, PROTECTION_MAX_DISTANCE);
	}

	if (distance_prev > max_distance && distance_old > max_distance) {
		// set right pos
		if (Protection_GetParamInt(PROTECTION_TELEPORT, PROTECTION_COUNTERACTION) && Protection_GetPlayerParamInt(playerid, PROTECTION_TELEPORT, PROTECTION_PLAYER_COUNTERACTION)) {
			if (vehicleid) {
				SetVehiclePos(vehicleid, gOldPos[playerid][0], gOldPos[playerid][1], gOldPos[playerid][2]);
			} else {
				SetPlayerPos(playerid, gOldPos[playerid][0], gOldPos[playerid][1], gOldPos[playerid][2]);
			}
		}
		
		// report
		Protection_GivePlayerWarning(playerid, PROTECTION_TELEPORT, "%.2f and %.2f > %.2f", distance_prev, distance_old, max_distance);
		return 1;
	}

	// update
	gPrevPos[playerid][0] = pos_x;
	gPrevPos[playerid][1] = pos_y;
	gPrevPos[playerid][2] = pos_z;

	return 0;
}

/*
	OnPlayerSpawn
*/

public OnPlayerSpawn(playerid)
{
	new bool:is_enabled = Protection_GetParamInt(PROTECTION_TELEPORT, PROTECTION_ENABLED) != 0;

	if (is_enabled) {
		static
			Float:si_x,
			Float:si_y,
			Float:si_z;

		GetSpawnInfo(playerid, _, _, si_x, si_y, si_z, _, _, _, _, _, _, _);

		gPrevPos[playerid][0] = si_x;
		gPrevPos[playerid][1] = si_y;
		gPrevPos[playerid][2] = si_z;

		gOldPos[playerid][0] = si_x;
		gOldPos[playerid][1] = si_y;
		gOldPos[playerid][2] = si_z;
	}

	#if defined PTeleport_OnPlayerSpawn
		return PTeleport_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif

#define OnPlayerSpawn PTeleport_OnPlayerSpawn
#if defined PTeleport_OnPlayerSpawn
	forward PTeleport_OnPlayerSpawn(playerid);
#endif

/*
	SetPlayerPos
*/

stock PTeleport_SetPlayerPos(playerid, Float:x, Float:y, Float:z)
{
	new bool:is_enabled = Protection_GetParamInt(PROTECTION_TELEPORT, PROTECTION_ENABLED) != 0;

	if (is_enabled) {
		GetPlayerPos(playerid, gPrevPos[playerid][0], gPrevPos[playerid][1], gPrevPos[playerid][2]);

		gOldPos[playerid][0] = x;
		gOldPos[playerid][1] = y;
		gOldPos[playerid][2] = z;
	}

	return SetPlayerPos(playerid, x, y, z);
}
#if defined _ALS_SetPlayerPos
	#undef SetPlayerPos
#else
	#define _ALS_SetPlayerPos
#endif

#define SetPlayerPos PTeleport_SetPlayerPos

/*
	SetPlayerPosFindZ
*/

stock PTeleport_SetPlayerPosFindZ(playerid, Float:x, Float:y, Float:z)
{
	new bool:is_enabled = Protection_GetParamInt(PROTECTION_TELEPORT, PROTECTION_ENABLED) != 0;

	if (is_enabled) {
		GetPlayerPos(playerid, gPrevPos[playerid][0], gPrevPos[playerid][1], gPrevPos[playerid][2]);

		gOldPos[playerid][0] = x;
		gOldPos[playerid][1] = y;
		gOldPos[playerid][2] = z;
	}

	return SetPlayerPosFindZ(playerid, x, y, z);
}
#if defined _ALS_SetPlayerPosFindZ
	#undef SetPlayerPosFindZ
#else
	#define _ALS_SetPlayerPosFindZ
#endif

#define SetPlayerPosFindZ PTeleport_SetPlayerPosFindZ

/*
	Streamer_UpdateEx
*/

#if PROTECTION_USE_STREAMER
	stock PTeleport_Streamer_UpdateEx(playerid, Float:x, Float:y, Float:z, worldid = -1, interiorid = -1, type = -1, compensatedtime = -1, freezeplayer = 1)
	{
		if (compensatedtime != -1) {
			new bool:is_enabled = Protection_GetParamInt(PROTECTION_TELEPORT, PROTECTION_ENABLED) != 0;

			if (is_enabled) {
				GetPlayerPos(playerid, gPrevPos[playerid][0], gPrevPos[playerid][1], gPrevPos[playerid][2]);

				gOldPos[playerid][0] = x;
				gOldPos[playerid][1] = y;
				gOldPos[playerid][2] = z;
			}
		}

		return Streamer_UpdateEx(playerid, x, y, z, worldid, interiorid, type, compensatedtime, freezeplayer);
	}
	#if defined _ALS_Streamer_UpdateEx
		#undef Streamer_UpdateEx
	#else
		#define _ALS_Streamer_UpdateEx
	#endif

	#define Streamer_UpdateEx PTeleport_Streamer_UpdateEx
#endif

/*
	SetVehiclePos
*/

stock PTeleport_SetVehiclePos(vehicleid, Float:x, Float:y, Float:z)
{
	new bool:is_enabled = Protection_GetParamInt(PROTECTION_TELEPORT, PROTECTION_ENABLED) != 0;

	if (is_enabled) {
		static
			Float:prev_x,
			Float:prev_y,
			Float:prev_z;

		GetVehiclePos(vehicleid, prev_x, prev_y, prev_z);

		foreach (new playerid : Player) {
			if (GetPlayerVehicleID(playerid) == vehicleid) {
				gPrevPos[playerid][0] = prev_x;
				gPrevPos[playerid][1] = prev_y;
				gPrevPos[playerid][2] = prev_z;

				gOldPos[playerid][0] = x;
				gOldPos[playerid][1] = y;
				gOldPos[playerid][2] = z;
			}
		}
	}

	return SetVehiclePos(vehicleid, x, y, z);
}
#if defined _ALS_SetVehiclePos
	#undef SetVehiclePos
#else
	#define _ALS_SetVehiclePos
#endif

#define SetVehiclePos PTeleport_SetVehiclePos

/*
	Functions
*/

stock Protection_GetPlayerPrevPos(playerid, &Float:x, &Float:y, &Float:z)
{
	x = gPrevPos[playerid][0];
	y = gPrevPos[playerid][1];
	z = gPrevPos[playerid][2];
}

stock Protection_GetPlayerOldPos(playerid, &Float:x, &Float:y, &Float:z)
{
	x = gOldPos[playerid][0];
	y = gOldPos[playerid][1];
	z = gOldPos[playerid][2];
}
