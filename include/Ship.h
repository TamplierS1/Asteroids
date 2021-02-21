#pragma once

#include "Actor.h"
#include "Bullet.h"

static olc::vf2d gDefaultPlayerPos = olc::vf2d(0.0f, 0.0f);
static olc::vf2d gDefaultPlayerVelocity = olc::vf2d(100.0f, 100.0f);
static float gDefaultPlayerSize = 30.0f;
static olc::vf2d gDefaultPlayerAcceleration = olc::vf2d(10.0f, 10.0f);
static float gDefaultPlayerRotationSpeed = 5.0f;

class Ship : public Actor
{
public:
    Ship();
    Ship(olc::vf2d pos, olc::vf2d velocity, float size, olc::vf2d acceleration, float rotSpeed, olc::Pixel color);

    olc::vf2d& GetAcceleration();
    std::vector<Bullet>& GetBullets();

    void Thrust();
    void FireBullet();

    bool& IsDead();

private:
    std::vector<Bullet> mBullets;
    olc::vf2d mAcceleration;

    olc::vf2d mBulletVelocity;

    bool mDead;
};
