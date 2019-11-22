#pragma once

#include <iostream>
#include <stdio.h>
#include <Windows.h>

#include "Gameplay/Player.h"
#include "Core/Game.h"

namespace Diablo
{
	class Input
	{
	public:
		static void HandleInput(float aDeltaTime, const std::wstring& aMap)
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
				if (aMap.c_str()[(int)tempXPos * 16 + (int)tempYPos] == '#')
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
				if (aMap.c_str()[(int)tempXPos * 16 + (int)tempYPos] == '#')
				{
					tempXPos += sinf(tempAngle) * tempSpeed * aDeltaTime;
					tempYPos += cosf(tempAngle) * tempSpeed * aDeltaTime;
				}
			}

			tempPlayer->SetXPos(tempXPos);
			tempPlayer->SetYPos(tempYPos);
			tempPlayer->SetAngle(tempAngle);
		}
	};
}