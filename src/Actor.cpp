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

float Actor::GetDirX()
{
	return mDirX;
}

float Actor::GetDirY()
{
	return mDirY;
}

float Actor::GetAngle()
{
	return mAngle;
}

std::vector<float>& Actor::GetTransformedMatX()
{
	return mTransformedX;
}

std::vector<float>& Actor::GetTransformedMatY()
{
	return mTransformedY;
}

void Actor::Move(float deltaTime)
{
	mPosX += mVelX * deltaTime;
	mPosY += mVelY * deltaTime;

	//translate
	for (int i = 0; i < 3; i++)
	{
		mTransformedX[i] += mPosX;
		mTransformedY[i] += mPosY;
	}
}

void Actor::Rotate(float deltaTime, RotationDir dir)
{
	//rotate
	for (int i = 0; i < 3; i++)
	{
		mTransformedX[i] = mModelX[i] * cos(mAngle) - mModelY[i] * sin(mAngle);
		mTransformedY[i] = mModelX[i] * sin(mAngle) + mModelY[i] * cos(mAngle);
	}
}

Actor::Actor()
{
}