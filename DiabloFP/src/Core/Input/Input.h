#pragma once

#include <iostream>
#include <stdio.h>
#include <Windows.h>

#include "Gameplay/Player.h"
#include "Core/Game.h"
#include "Gameplay/Map/Map.h"

namespace Diablo
{
	class Input
	{
	public:
		static void HandleInput(float aDeltaTime, Map* aMap)
		{
			Player* tempPlayer = Player::Get();

			float tempXPos = tempPlayer->GetXPos();
			float tempYPos = tempPlayer->GetYPos();
			float tempAngle = tempPlayer->GetAngle();
			float tempSpeed = tempPlayer->GetSpeed();

			// Handle CCW Rotation
			if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
				tempAngle -= (tempSpeed * 0.75f) * aDeltaTime;

			// Handle CW Rotation
			if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
				tempAngle += (tempSpeed * 0.75f) * aDeltaTime;

			// Handle Forwards movement & collision
			if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
			{
				tempXPos += sinf(tempAngle) * tempSpeed * aDeltaTime;
				tempYPos += cosf(tempAngle) * tempSpeed * aDeltaTime;
				if (aMap->GetStringMap().c_str()[(int)tempXPos * aMap->GetMapSize() + (int)tempYPos] == '#')
				{
					tempXPos -= sinf(tempAngle) * tempSpeed * aDeltaTime;
					tempYPos -= cosf(tempAngle) * tempSpeed * aDeltaTime;
				}
			}

			// Handle backwards movement & collision
			if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
			{
				tempXPos -= sinf(tempAngle) * tempSpeed * aDeltaTime;
				tempYPos -= cosf(tempAngle) * tempSpeed * aDeltaTime;
				if (aMap->GetStringMap().c_str()[(int)tempXPos * aMap->GetMapSize() + (int)tempYPos] == '#')
				{
					tempXPos += sinf(tempAngle) * tempSpeed * aDeltaTime;
					tempYPos += cosf(tempAngle) * tempSpeed * aDeltaTime;
				}
			}

			tempPlayer->SetXPos(tempXPos);
			tempPlayer->SetYPos(tempYPos);
			tempPlayer->SetAngle(tempAngle);
		}
		static std::string GetInput()
		{
			char tempSelection[255];
			std::cin.getline(tempSelection, 255);

			return std::string(tempSelection);
		}
	};
}