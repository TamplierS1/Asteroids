#pragma once

#include "Actor.h"

static float gDefaultPlayerPosX = 0.0f;
static float gDefaultPlayerPosY = 0.0f;

static float gDefaultPlayerVelX = 100.0f;
static float gDefaultPlayerVelY = 100.0f;

static float gDefaultPlayerSizeX = 30.0f;
static float gDefaultPlayerSizeY = 30.0f;

static float gDefaultPlayerAccelX = 10.0f;
static float gDefaultPlayerAccelY = 10.0f;

class Ship : public Actor
{
public:
	Ship();
	Ship(float posx, float posy, float velx, float vely, float sizex, float sizey, float accelx, float accely);
private:
};
