#include "Actor.h"

std::pair<float, float>& Actor::GetPos()
{
	return mPos;
}

std::pair<float, float>& Actor::GetVelocity()
{
	return mVelocity;
}

float& Actor::GetSize()
{
	return mSize;
}

std::pair<float, float>& Actor::GetDirection()
{
	return mDir;
}

float& Actor::GetAngle()
{
	return mAngle;
}

std::pair<float, float> Actor::GetTransformedVertex(int number)
{
	return mTransformedVertices[number];
}

unsigned int Actor::GetNumOfVerts()
{
	return mNumOfVerts;
}

olc::Pixel Actor::GetColor() const
{
	return mColor;
}

void Actor::Move(float deltaTime)
{
	mPos.first += mVelocity.first * deltaTime;
	mPos.second += mVelocity.second * deltaTime;

	//translate
	for (int i = 0; i < mNumOfVerts; i++)
	{
		mTransformedVertices[i].first += mPos.first;
		mTransformedVertices[i].second += mPos.second;
	}
}

void Actor::Rotate(float deltaTime)
{
	//rotate
	for (int i = 0; i < mNumOfVerts; i++)
	{
		mTransformedVertices[i].first = mModelVertices[i].first * cos(mAngle) - mModelVertices[i].second * sin(mAngle);
		mTransformedVertices[i].second = mModelVertices[i].first * sin(mAngle) + mModelVertices[i].second * cos(mAngle);
	}
}

void Actor::ChangeRotation(RotationDir dir, float deltaTime)
{
	mAngle += mRotationSpeed * dir * deltaTime;
}

void Actor::Scale(float amount)
{
	for (int i = 0; i < mNumOfVerts; i++)
	{
		mTransformedVertices[i].first *= amount;
	}

	for (int i = 0; i < mNumOfVerts; i++)
	{
		mTransformedVertices[i].second *= amount;
	}
}

Actor::Actor()
{
}

float Actor::GetRotationSpeed()
{
	return mRotationSpeed;
}

RotationDir Actor::GetRotDir()
{
	return mRotDir;
}

Actor::Actor(std::pair<float, float> pos, std::pair<float, float> velocity,
	float size, unsigned int verts, RotationDir rotDir, float rotSpeed,
	std::vector<std::pair<float, float>> modelVerts, olc::Pixel color)
{
	mNumOfVerts = verts;
	mModelVertices = modelVerts;
	mColor = color;
	mPos = pos;
	mVelocity = velocity;
	mSize = size;
	mDir = std::pair<float, float>(0.0f, 0.0f);

	mAngle = 0.0f;
	mRotationSpeed = rotSpeed;

	for (int i = 0; i < mNumOfVerts; i++)
	{
		mTransformedVertices.push_back(std::pair<float, float>(0.0f, 0.0f));
		mTransformedVertices[i].first += mPos.first;
		mTransformedVertices[i].second += mPos.second;
	}

	mRotDir = RIGHT;
}