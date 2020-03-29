#pragma once
class Actor
{
public:

	//utility functions
	float& GetPosX();
	float& GetPosY();

	float& GetVelX();
	float& GetVelY();

	float& GetSizeX();
	float& GetSizeY();

	float& GetAccelX();
	float& GetAccelY();

	float& GetDirX();
	float& GetDirY();

	void Move(float deltaTime);
protected:
	Actor();
	float mPosX;
	float mPosY;

	float mVelX;
	float mVelY;

	float mSizeX;
	float mSizeY;

	float mAccelerationX;
	float mAccelerationY;

	float mDirX;
	float mDirY;
};
