#pragma once

#include "Actor.h"
#include "Bullet.h"

static std::pair<float, float> gDefaultPlayerPos = std::pair<float, float>(0.0f, 0.0f);
static std::pair<float, float> gDefaultPlayerVelocity = std::pair<float, float>(100.0f, 100.0f);
static float gDefaultPlayerSize = 30.0f;
static std::pair<float, float> gDefaultPlayerAcceleration = std::pair<float, float>(10.0f, 10.0f);
static float gDefaultPlayerRotationSpeed = 5.0f;

class Ship : public Actor
{
public:
	Ship();
	Ship(std::pair<float, float> pos, std::pair<float, float> velocity,
		float size, std::pair<float, float> acceleration, float rotSpeed,
		olc::Pixel color);

	std::pair<float, float>& GetAcceleration();
	std::vector<Bullet>& GetBullets();

	void Thrust();
	void FireBullet();

	bool& IsDead();
private:
	std::vector<Bullet> mBullets;
	std::pair<float, float> mAcceleration;

	std::pair<float, float> mBulletVelocity;

	bool mDead;
};
