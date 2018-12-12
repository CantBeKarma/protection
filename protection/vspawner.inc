/*

	Cheat Description: A player is able to use hacks to teleport (unoccupied) vehicles to their location.
	Countermeasure: Set the vehicle's position back to where it should be upon detecting faul play using RakNet.
	Author: CantBeKarma

*/

#if !defined _protection_included
	#error "Please include protection before vspawner"
#endif

#if defined _protection_vspawner_included
	#endinput
#endif

#if !defined PAWNRAKNET_INC_
	#error "Please include Pawn.Raknet before vspawner"
#endif

#define _protection_vspawner_included

/*
	Forwards
*/

forward 
	Float:GetDifference(Float:value1, Float:value2);

/*
	Arrays
*/

new static stock const VFUNC_vTypeArray[] = // Credits to Mike (MP2).
{	
	VTYPE_ROAD, // Landstalker
	VTYPE_ROAD, // Bravura
	VTYPE_ROAD, // Buffalo
	VTYPE_ROAD, // Linerunner
	VTYPE_ROAD, // Perenniel
	VTYPE_ROAD, // Sentinel
	VTYPE_ROAD, // Dumper
	VTYPE_ROAD, // Firetruck
	VTYPE_ROAD, // Trashmaster
	VTYPE_ROAD, // Stretch
	VTYPE_ROAD, // Manana
	VTYPE_ROAD, // Infernus
	VTYPE_ROAD, // Voodoo
	VTYPE_ROAD, // Pony
	VTYPE_ROAD, // Mule
	VTYPE_ROAD, // Cheetah
	VTYPE_ROAD, // Ambulance
	VTYPE_HELI, // Leviathan
	VTYPE_ROAD, // Moonbeam
	VTYPE_ROAD, // Esperanto
	VTYPE_ROAD, // Taxi
	VTYPE_ROAD, // Washington
	VTYPE_ROAD, // Bobcat
	VTYPE_ROAD, // Mr Whoopee (Ice-Cream Truck)
	VTYPE_ROAD, // BF Injection
	VTYPE_HELI, // Hunter
	VTYPE_ROAD, // Permier
	VTYPE_ROAD, // Enforcer
	VTYPE_ROAD, // Securicar
	VTYPE_ROAD, // Banshee
	VTYPE_BOAT, // Predator
	VTYPE_ROAD, // Bus
	VTYPE_ROAD, // Rhino
	VTYPE_ROAD, // Barracks
	VTYPE_ROAD, // Hotknife
	VTYPE_ROAD, // Articulated Trailer 1
	VTYPE_ROAD, // Previon
	VTYPE_ROAD, // Coach
	VTYPE_ROAD, // Cab
	VTYPE_ROAD, // Stallion
	VTYPE_ROAD, // Rumpo
	VTYPE_ROAD, // RC Bandit
	VTYPE_ROAD, // Romero
	VTYPE_ROAD, // Packer
	VTYPE_ROAD, // Monster
	VTYPE_ROAD, // Admiral
	VTYPE_BOAT, // Squallo
	VTYPE_HELI, // Seasparrow
	VTYPE_BIKE, // Pizzaboy
	VTYPE_ROAD, // Tram
	VTYPE_ROAD, // Art Trailer 2
	VTYPE_ROAD, // Turismo
	VTYPE_BOAT, // Speeder
	VTYPE_BOAT, // Reefer
	VTYPE_BOAT, // Tropic
	VTYPE_ROAD, // Flatbed
	VTYPE_ROAD, // Yankee
	VTYPE_ROAD, // Caddy
	VTYPE_ROAD, // Solair
	VTYPE_ROAD, // Topfun
	VTYPE_PLANE, // Skimmer
	VTYPE_BIKE, // PCJ-600
	VTYPE_BIKE, // Faggio
	VTYPE_BIKE, // Freeway
	VTYPE_PLANE, // RC Baron
	VTYPE_HELI, // RC Raider
	VTYPE_ROAD, // Glendale
	VTYPE_ROAD, // Oceanic
	VTYPE_BIKE, // Sanchez
	VTYPE_HELI, // Sparrow
	VTYPE_ROAD, // Patriot
	VTYPE_ROAD, // Quad
	VTYPE_BOAT, // Coastguard
	VTYPE_BOAT, // Dinghy
	VTYPE_ROAD, // Hermes
	VTYPE_ROAD, // Sasbre
	VTYPE_PLANE, // Rustler
	VTYPE_ROAD, // ZR-350
	VTYPE_ROAD, // Walton
	VTYPE_ROAD, // Regina
	VTYPE_ROAD, // Comet
	VTYPE_BIKE, // BMX
	VTYPE_ROAD, // Burrito
	VTYPE_ROAD, // Camper
	VTYPE_BOAT, // Marquis
	VTYPE_ROAD, // Baggage
	VTYPE_ROAD, // Dozer
	VTYPE_HELI, // Maverick
	VTYPE_HELI, // News Heli
	VTYPE_ROAD, // Rancher
	VTYPE_ROAD, // FBI Rancher
	VTYPE_ROAD, // Virgo
	VTYPE_ROAD, // Greenwood
	VTYPE_BOAT, // Jetmax
	VTYPE_ROAD, // Hotring
	VTYPE_ROAD, // Sandking
	VTYPE_ROAD, // Blista Compact
	VTYPE_HELI, // Police Maverick (polmav)
	VTYPE_ROAD, // Boxville
	VTYPE_ROAD, // Benson
	VTYPE_ROAD, // Mesa
	VTYPE_HELI, // RC Goblin
	VTYPE_ROAD, // Hotring
	VTYPE_ROAD, // Hotring
	VTYPE_ROAD, // Bloodring Bander
	VTYPE_ROAD, // Rancher
	VTYPE_ROAD, // Super GT
	VTYPE_ROAD, // Elegant
	VTYPE_ROAD, // Journey
	VTYPE_BIKE, // Bike
	VTYPE_BIKE, // Mountain Bike
	VTYPE_PLANE, // Beagle
	VTYPE_PLANE, // Cropduster
	VTYPE_PLANE, // Stuntplane
	VTYPE_ROAD, // Tanker
	VTYPE_ROAD, // Roadtrain
	VTYPE_ROAD, // Nebula
	VTYPE_ROAD, // Majestic
	VTYPE_ROAD, // Buccaneer
	VTYPE_PLANE, // Shamal
	VTYPE_PLANE, // Hydra
	VTYPE_BIKE, // FCR-900
	VTYPE_BIKE, // NRG-500
	VTYPE_BIKE, // HPV (Cop Bike)
	VTYPE_ROAD, // Cement
	VTYPE_ROAD, // Towtruck
	VTYPE_ROAD, // Fortune
	VTYPE_ROAD, // Cadrona
	VTYPE_ROAD, // FBI Truck
	VTYPE_ROAD, // Willard
	VTYPE_ROAD, // Forklift
	VTYPE_ROAD, // Tractor
	VTYPE_ROAD, // Combine
	VTYPE_ROAD, // Feltzer
	VTYPE_ROAD, // Remington
	VTYPE_ROAD, // Slamvan
	VTYPE_ROAD, // Blade
	VTYPE_TRAIN, // Freight
	VTYPE_TRAIN, // Brownstreak
	VTYPE_ROAD, // Vortex
	VTYPE_ROAD, // Vincent
	VTYPE_ROAD, // Bullet
	VTYPE_ROAD, // Clover
	VTYPE_ROAD, // Sadler
	VTYPE_ROAD, // Firetruck
	VTYPE_ROAD, // Hustler
	VTYPE_ROAD, // Intruder
	VTYPE_ROAD, // Primo
	VTYPE_HELI, // Cargobob
	VTYPE_ROAD, // Tampa
	VTYPE_ROAD, // Sunrise
	VTYPE_ROAD, // Merit
	VTYPE_ROAD, // Utility
	VTYPE_PLANE, // Nevada
	VTYPE_ROAD, // Yosemite
	VTYPE_ROAD, // Windsor
	VTYPE_ROAD, // Monster
	VTYPE_ROAD, // Monster
	VTYPE_ROAD, // Uranus
	VTYPE_ROAD, // Jester
	VTYPE_ROAD, // Sultan
	VTYPE_ROAD, // Stratum
	VTYPE_ROAD, // Elegy
	VTYPE_HELI, // Raindance
	VTYPE_ROAD, // RC Tiger
	VTYPE_ROAD, // Flash
	VTYPE_ROAD, // Tahoma
	VTYPE_ROAD, // Savanna
	VTYPE_ROAD, // Bandito
	VTYPE_TRAIN, // Carriage
	VTYPE_TRAIN, // Carriage
	VTYPE_ROAD, // Kart
	VTYPE_ROAD, // Mower
	VTYPE_ROAD, // Done
	VTYPE_ROAD, // Sweeper
	VTYPE_ROAD, // Broadway
	VTYPE_ROAD, // Tornado
	VTYPE_PLANE, // AT-400
	VTYPE_ROAD, // DFT-30
	VTYPE_ROAD, // Huntley
	VTYPE_ROAD, // Stafford
	VTYPE_BIKE, // BF-400
	VTYPE_ROAD, // Newsvan
	VTYPE_ROAD, // Tug
	VTYPE_ROAD, // Petrol Trailer
	VTYPE_ROAD, // Emperor
	VTYPE_BIKE, // Wayfarer
	VTYPE_ROAD, // Euros
	VTYPE_ROAD, // Hotdog
	VTYPE_ROAD, // Club
	VTYPE_TRAIN, // Freight Box Trailer
	VTYPE_ROAD, // Artic Trailer
	VTYPE_PLANE, // Androm
	VTYPE_PLANE, // Dodo
	VTYPE_ROAD, // RC Cam
	VTYPE_BOAT, // Launch
	VTYPE_ROAD, // LSPD
	VTYPE_ROAD, // SFPD
	VTYPE_ROAD, // LVPD
	VTYPE_ROAD, // Police Ranger
	VTYPE_ROAD, // Picador
	VTYPE_ROAD, // S.W.A.T
	VTYPE_ROAD, // Alpha
	VTYPE_ROAD, // Phoenix
	VTYPE_ROAD, // Glendale Shit
	VTYPE_ROAD, // Sadler Shit
	VTYPE_ROAD, // Baggage
	VTYPE_ROAD, // Baggage
	VTYPE_ROAD, // Stairs
	VTYPE_ROAD, // Boxville
	VTYPE_ROAD, // Plow
	VTYPE_ROAD // Utility Trailer
};

/*
	OnIncomingPacket
*/

public OnIncomingPacket(playerid, packetid, BitStream:bs)
{
	new bool:is_enabled = Protection_GetParamInt(PROTECTION_VEHICLESPAWNER, PROTECTION_ENABLED) != 0;

	if(is_enabled)
	{
		if(packetid == 209)
		{
			new unoccupiedData[PR_UnoccupiedSync];

		    BS_IgnoreBits(bs, 8);
		    BS_ReadUnoccupiedSync(bs, unoccupiedData);
		    BS_ResetReadPointer(bs);

		    // - ANTI-UNOCCUPIED VEHICLE WARP - //
		    new Float:X, Float:Y, Float:Z, Float:Max_Distance_Move = 10.0;
		    GetVehiclePos(unoccupiedData[PR_vehicleId], X, Y, Z);

		    switch (VFUNC_vTypeArray[GetVehicleModel(unoccupiedData[PR_vehicleId])-400])
		    {
		        case VTYPE_ROAD: Max_Distance_Move = 10.0;
		        default: Max_Distance_Move = 20.0;
		    }

		    if(unoccupiedData[PR_position][0] != X || unoccupiedData[PR_position][1] != Y || unoccupiedData[PR_position][2] != Z)
		    {
		        if(GetDifference(unoccupiedData[PR_position][0], X) > Max_Distance_Move 
		        || GetDifference(unoccupiedData[PR_position][1], Y) > Max_Distance_Move 
		        || GetDifference(unoccupiedData[PR_position][2], Z) > Max_Distance_Move) 
		        {
		        	if(Protection_GetParamInt(PROTECTION_VEHICLESPAWNER, PROTECTION_COUNTERMEASURE))
		        	{
		        		// - Set The Right Position - //
			            unoccupiedData[PR_position][0] = X;
			            unoccupiedData[PR_position][1] = Y;
			            unoccupiedData[PR_position][2] = Z;
			            SetVehiclePos(unoccupiedData[PR_vehicleId], X, Y, Z);
		        	}

		        	// - Report - //
		        	Protection_GivePlayerWarning(playerid, PROTECTION_VEHICLESPAWNER, "Vehicle Distance Modified: X: %i meters, Y: %i meters, Z: %i meters.", GetDifference(unoccupiedData[PR_position][0], X), GetDifference(unoccupiedData[PR_position][1], Y), GetDifference(unoccupiedData[PR_position][2], Z));
		        }
		    }
		    // - ANTI-UNOCCUPIED VEHICLE WARP - //

		    BS_SetWriteOffset(bs, 8);
		    BS_WriteUnoccupiedSync(bs, unoccupiedData);
		    BS_ResetWritePointer(bs);
		}
	}

	#if defined vSpawner_OnIncomingPacket
		return vSpawner_OnIncomingPacket(playerid, packetid, BitStream:bs);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnIncomingPacket
	#undef OnIncomingPacket
#else
	#define _ALS_OnIncomingPacket
#endif

#define OnIncomingPacket vSpawner_OnIncomingPacket
#if defined vSpawner_OnIncomingPacket
	forward vSpawner_OnIncomingPacket(playerid, packetid, BitStream:bs);
#endif

/*
	Internal Stocks
*/

static Float:GetDifference(Float:value1, Float:value2)
{
    new 
        Float:difference;
    
    difference = value1-value2;
    if(difference < 0) difference = difference + (difference*-2);
    
    return difference;
}