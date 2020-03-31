#include "Ship.h"

Ship::Ship() : Actor()
{
	mPos = gDefaultPlayerPos;
	mVelocity = gDefaultPlayerVelocity;
	mSize = gDefaultPlayerSize;
	mAcceleration = gDefaultPlayerAcceleration;
	mDir = std::pair<float, float>(0.0f, 0.0f);
	mColor = olc::WHITE;

	mAngle = 0.0f;
	mRotationSpeed = gDefaultPlayerRotationSpeed;

	mNumOfVerts = 3;

	mModelVertices = { std::pair<float, float>(0.0f, -2.0f), std::pair<float, float>(-1.0f, +1.0f), std::pair<float, float>(+1.0f, +1.0f) };

	for (int i = 0; i < mNumOfVerts; i++)
	{
		mTransformedVertices.push_back(std::pair<float, float>(0.0f, 0.0f));
		mTransformedVertices[i].first += mPos.first;
		mTransformedVertices[i].second += mPos.second;
	}

	mBulletVelocity = std::make_pair(250.0f, -250.0f);
	mRotDir = RIGHT;
}

Ship::Ship(std::pair<float, float> pos, std::pair<float, float> velocity,
	float size, std::pair<float, float> acceleration, float rotSpeed,
	olc::Pixel color)
{
	mPos = pos;
	mVelocity = velocity;
	mSize = size;
	mAcceleration = acceleration;
	mDir = std::pair<float, float>(0.0f, 0.0f);
	mColor = color;

	mAngle = 0.0f;
	mRotationSpeed = rotSpeed;

	mNumOfVerts = 3;

	mModelVertices = { std::pair<float, float>(0.0f, -2.0f), std::pair<float, float>(-1.0f, +1.0f), std::pair<float, float>(+1.0f, +1.0f) };

	mBulletVelocity = std::make_pair(350.0f, -350.0f);

	for (int i = 0; i < mNumOfVerts; i++)
	{
		mTransformedVertices.push_back(std::pair<float, float>(0.0f, 0.0f));
		mTransformedVertices[i].first += mPos.first;
		mTransformedVertices[i].second += mPos.second;
	}

	mRotDir = RIGHT;
}

std::pair<float, float>& Ship::GetAcceleration()
{
	return mAcceleration;
}

std::vector<Bullet>& Ship::GetBullets()
{
	return mBullets;
}

void Ship::Thrust()
{
	mVelocity.first += sin(mAngle) * mAcceleration.first;
	mVelocity.second += -cos(mAngle) * mAcceleration.second;
}

void Ship::FireBullet()
{
	Bullet bullet(mPos, mBulletVelocity, mAngle, olc::WHITE);
	mBullets.push_back(bullet);
}