#pragma once

#include <math.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum RotationDir
{
	LEFT = -1, RIGHT = 1
};

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

	float GetDirX();
	float GetDirY();

	float GetAngle();

	std::vector<float>& GetTransformedMatX();
	std::vector<float>& GetTransformedMatY();

	void Move(float deltaTime);
	void Rotate(float deltaTime, RotationDir dir);
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

	float mAngle;

	std::vector<float> mModelX;
	std::vector<float> mModelY;

	std::vector<float> mTransformedX;
	std::vector<float> mTransformedY;
};
