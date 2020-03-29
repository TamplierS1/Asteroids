#include "Actor.h"

float& Actor::GetPosX()
{
	return mPosX;
}

float& Actor::GetPosY()
{
	return mPosY;
}

float& Actor::GetVelX()
{
	return mVelX;
}

float& Actor::GetVelY()
{
	return mVelY;
}

float& Actor::GetSizeX()
{
	return mSizeX;
}

float& Actor::GetSizeY()
{
	return mSizeY;
}

float& Actor::GetAccelX()
{
	return mAccelerationX;
}

float& Actor::GetAccelY()
{
	return mAccelerationY;
}

float& Actor::GetDirX()
{
	return mDirX;
}

float& Actor::GetDirY()
{
	return mDirY;
}

void Actor::Move(float deltaTime)
{
	mVelX = mAccelerationX * deltaTime + mVelX;
	mVelY = mAccelerationY * deltaTime + mVelY;

	mPosX = mVelX * mDirX * deltaTime + mPosX;
	mPosY = mVelY * mDirY * deltaTime + mPosY;

	/*float velocityX = mVelX * dirX * deltaTime;
	float velocityY = mVelY * dirY * deltaTime;

	mPosX += velocityX;
	mPosY += velocityY;*/
}

Actor::Actor()
{
}