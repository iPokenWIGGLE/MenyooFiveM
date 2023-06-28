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
#include "..\Scripting\Game.h"

#include "..\Natives\natives2.h"

namespace sub
{
	void MainMenu()
	{
		AddTitle("MENYOO FIVEM");

		AddBreak("Enhanced for FiveM by JustGod");
		AddOption("Players (FiveM Support)", null, FiveM_Alert, SUB::PLAYERSSUB, true);
		AddOption("Player Options", null, nullFunc, SUB::PLAYEROPS, true);
		AddOption("Vehicle Options", null, nullFunc, SUB::VEHICLEOPS, true);
		AddOption("Teleport Options", null, nullFunc, SUB::TELEPORTOPS, true);
		AddOption("Weapon Options", null, nullFunc, SUB::WEAPONOPS, true);
		AddOption("Weather Options", null, nullFunc, SUB::WEATHEROPS, true);
		AddOption("Time Options", null, nullFunc, SUB::TIMEOPS, true);
		AddOption("Object Spooner", null, nullFunc, SUB::SPOONER_MAIN, true);
		//AddOption("Lighting Options", null, nullFunc, SUB::OBJECTSPAWNER_LIGHTINGOPS);
		AddOption("Misc Options", null, nullFunc, SUB::MISCOPS, true);
		AddOption("Settings", null, nullFunc, SUB::SETTINGS, true);

		Static_240 = PLAYER_ID();
		Static_241 = PLAYER_PED_ID();
		Static_239 = GET_PLAYER_NAME(Static_240);
		Static_242 = GET_PLAYER_GROUP(Static_240);

	};

	void FiveM_Alert() {
		Game::Print::PrintBottomCentre("This option may be broken. Please report it to JustGod.");
	};

}




