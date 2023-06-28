/*
* Menyoo PC - Grand Theft Auto V single-player trainer mod
* Copyright (C) 2019  MAFINS
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*/
#include "MainMenu.h"

#include "..\macros.h"

#include "..\Menu\Menu.h"
#include "..\Menu\Routine.h"

#include "..\Natives\natives2.h"
#include "..\Scripting\Game.h"
#include "..\Scripting\GTAplayer.h"
//#include "..\Scripting\GTAentity.h"
#include "..\Scripting\GTAped.h"

using namespace std;

namespace sub
{
	// Are these basic (FiveM) player options allowed on 5mods?

	void PlayersSub_()
	{
		AddTitle("Players (FiveM)");

		for (int i = 0; i < GAME_PLAYERCOUNT; i++)
		{
			if (NETWORK_IS_PLAYER_ACTIVE(i))
			{
				bool bPlayerPressed = false;
				int server_id = invoke<int>(0x4D97BCC7, i);

				string name = GET_PLAYER_NAME(i), space = " ID: (", finish = ")";
				string final = name + space + std::to_string(server_id) + finish;

				AddOption(final, bPlayerPressed, nullFunc, SUB::PLAYERSSUBAMENU, true);

				if (bPlayerPressed)
				{
					Static_240 = i;
					Static_241 = GET_PLAYER_PED(Static_240); // Store ped
					Static_239 = GET_PLAYER_NAME(Static_240); // Store name
					//Menu::SetSub_new(SUB::PLAYERSSUBAMENU); // Change submenu to 'PlayersSubAMenu_'
				}
			}
		}
	}

	void PlayersSubAMenu_()
	{

		if (!NETWORK_IS_PLAYER_ACTIVE(Static_240)) { 
			Game::Print::PrintBottomCentre("This player has left or is out of range.");
			Menu::SetSub_previous();
		};

		bool bSetWp = false;
		bool bTeleportTo = false;
		bool bSpectateOn = false;
		bool bSpectateOff = false;

		AddTitle(Static_239); // Title = player name
		AddOption("Set Waypoint To Player", bSetWp);
		AddLocal("Spectate Player", loop_spectate_player == Static_240, bSpectateOn, bSpectateOff); // Spectate Player
		AddOption("Teleport To Player (Menyoo FiveM exclusivity)", bTeleportTo);

		if (bSpectateOn)
		{
			loop_spectate_player = Static_240;
			if (NETWORK_IS_IN_SPECTATOR_MODE()) {
				for (int i = 0; i < GAME_PLAYERCOUNT; i++)
				{
					if (!NETWORK_IS_PLAYER_ACTIVE(i)) continue;
					const Ped _ped = GET_PLAYER_PED(i);
					if (!DOES_ENTITY_EXIST(_ped)) continue;
					NETWORK_SET_IN_SPECTATOR_MODE_EXTENDED(0, _ped, 1);
					NETWORK_SET_IN_SPECTATOR_MODE(false, _ped);
				}
			}
			const Ped ped = GET_PLAYER_PED(loop_spectate_player);
			if (DOES_ENTITY_EXIST(ped))
			{
				STAT_SET_BOOL(GET_HASH_KEY("MPPLY_CAN_SPECTATE"), true, true);
				NETWORK_SET_IN_SPECTATOR_MODE(true, ped);
			}
		}
		if (bSpectateOff)
		{
			for (int i = 0; i < GAME_PLAYERCOUNT; i++)
			{
				if (!NETWORK_IS_PLAYER_ACTIVE(i)) continue;
				const Ped ped = GET_PLAYER_PED(i);
				if (!DOES_ENTITY_EXIST(ped)) continue;
				NETWORK_SET_IN_SPECTATOR_MODE_EXTENDED(0, ped, 1);
				NETWORK_SET_IN_SPECTATOR_MODE(false, ped);
			}
			NETWORK_SET_ACTIVITY_SPECTATOR(false);
			loop_spectate_player = -1;
		}

		if (bSetWp)
		{
			if (Static_240 != PLAYER_ID()) {
				const int ped = Static_241;
				if (!IS_PED_INJURED(ped))
				{
					const Vector3& pos = GET_ENTITY_COORDS(ped, false);
					SET_NEW_WAYPOINT(pos.x, pos.y);
				}
				else
				{
					SET_WAYPOINT_OFF();
				}
			}
			else Game::Print::PrintBottomCentre("You can't set a waypoint on yourself.");
		}

		if (bTeleportTo) 
		{
			if (Static_240 != PLAYER_ID()) {
				if (DOES_ENTITY_EXIST(Static_241))
				{
					const Ped localPed = PLAYER_PED_ID();
					const Vehicle vehicle = GET_VEHICLE_PED_IS_IN(localPed, false);
					const Vector3 pos = GET_ENTITY_COORDS(Static_241, false);

					if (vehicle != 0 && GET_PED_IN_VEHICLE_SEAT(vehicle, -1, true) == localPed)
						SET_PED_COORDS_KEEP_VEHICLE(localPed, pos.x, pos.y, pos.z);
					else SET_ENTITY_COORDS(localPed, pos.x, pos.y, pos.z, true, true, true, false);
				}
			}
			else Game::Print::PrintBottomCentre("You can't teleport on yourself.");
		}

	}

}




