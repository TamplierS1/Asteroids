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

	mAngle = 0.0f;
	mRotationSpeed = gDefaultPlayerRotationSpeed;

	mModelX = { 0.0f, -25.0f, +25.0f };
	mModelY = { -55.0f, +25.0f, +25.0f };

	mTransformedX = { 0.0f, 0.0f, 0.0f };
	mTransformedY = { 0.0f, 0.0f, 0.0f };

	//translate
	for (int i = 0; i < 3; i++)
	{
		mTransformedX[i] += mPosX;
		mTransformedY[i] += mPosY;
	}

	mRotDir = RIGHT;
}

Ship::Ship(float posx, float posy, float velx, float vely, float sizex, float sizey, float accelx, float accely, float rotSpeed)
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

	mAngle = 0.0f;
	mRotationSpeed = rotSpeed;

	mModelX = { 0.0f, -25.0f, +25.0f };
	mModelY = { -55.0f, +25.0f, +25.0f };

	mTransformedX = { 0.0f, 0.0f, 0.0f };
	mTransformedY = { 0.0f, 0.0f, 0.0f };

	//translate
	for (int i = 0; i < 3; i++)
	{
		mTransformedX[i] += mPosX;
		mTransformedY[i] += mPosY;
	}

	mRotDir = RIGHT;
}

void Ship::Thrust()
{
	mVelX += sin(mAngle) * mAccelerationX;
	mVelY += -cos(mAngle) * mAccelerationY;
}

void Ship::ChangeRotation(RotationDir dir, float deltaTime)
{
	mAngle += mRotationSpeed * dir * deltaTime;
}

float Ship::GetRotationSpeed()
{
	return mRotationSpeed;
}

RotationDir Ship::GetRotDir()
{
	return mRotDir;
}