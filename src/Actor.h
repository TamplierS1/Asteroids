#pragma once

#include <math.h>
#include <vector>
#include "olcPixelGameEngine.h"

enum RotationDir
{
	LEFT = -1, RIGHT = 1, NONE = 0
};

class Actor
{
public:
	Actor(std::pair<float, float> pos, std::pair<float, float> velocity,
		float size, unsigned int verts, RotationDir rotDir, float rotSpeed,
		std::vector<std::pair<float, float>> modelVerts, olc::Pixel color);
	//utility functions
	std::pair<float, float>& GetPos();
	std::pair<float, float>& GetVelocity();
	float& GetSize();

	std::pair<float, float>& GetDirection();
	float GetRotationSpeed();
	RotationDir GetRotDir();
	float& GetAngle();
	std::pair<float, float> GetTransformedVertex(int number);
	unsigned int GetNumOfVerts();
	olc::Pixel GetColor() const;

	virtual void Move(float deltaTime);
	void Rotate(float deltaTime);
	void ChangeRotation(RotationDir dir, float deltaTime);
	void Scale(float amount);

protected:
	Actor();

	std::pair<float, float> mPos;
	std::pair<float, float> mVelocity;
	float mSize;
	std::pair<float, float> mDir;

	std::vector<std::pair<float, float>> mTransformedVertices;
	std::vector<std::pair<float, float>> mModelVertices;
	unsigned int mNumOfVerts;

	olc::Pixel mColor;

	float mAngle;
	float mRotationSpeed;
	RotationDir mRotDir;
};
