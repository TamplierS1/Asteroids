#include "Ship.h"

Ship::Ship()
{
	mPosX = gDefaultPlayerPosX;
	mPosY = gDefaultPlayerPosY;

	mVelX = gDefaultPlayerVelX;
	mVelY = gDefaultPlayerVelY;

	mSizeX = gDefaultPlayerSizeX;
	mSizeY = gDefaultPlayerSizeY;

	mAccelerationX = gDefaultPlayerAccelX;
	mAccelerationY = gDefaultPlayerAccelY;

	mDirX = 0.0f;
	mDirY = 0.0f;
}

Ship::Ship(float posx, float posy, float velx, float vely, float sizex, float sizey, float accelx, float accely)
{
	mPosX = posx;
	mPosY = posy;

	mVelX = velx;
	mVelY = vely;

	mSizeX = sizex;
	mSizeY = sizey;

	mAccelerationX = accelx;
	mAccelerationY = accely;

	mDirX = 0.0f;
	mDirY = 0.0f;
}