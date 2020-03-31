#include "Bullet.h"

Bullet::Bullet(std::pair<float, float> pos, std::pair<float, float> velocity, float playerAngle, olc::Pixel color)
{
	mPos = pos;
	mVelocity = velocity;
	mAngle = playerAngle;
	mColor = color;
	//NOTICE: all other unititialized Actor member variables does not matter, we will not use them
}

void Bullet::MoveBullet(float fElapsedTime)
{
	mPos.first += mVelocity.first * sin(mAngle) * fElapsedTime;
	mPos.second += mVelocity.second * cos(mAngle) * fElapsedTime;
}

bool Bullet::Collision(unsigned int width, unsigned int height)
{
	bool collisionX = mPos.first < 0.0f || mPos.first > width;
	bool collisionY = mPos.second < 0.0f || mPos.second > height;

	return collisionX || collisionY;
}