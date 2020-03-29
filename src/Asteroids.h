#pragma once

#include <memory>
#include "olcPixelGameEngine.h"
#include "Ship.h"

class Asteroids :
	public  olc::PixelGameEngine
{
public:
	Asteroids(unsigned int scrWidth, unsigned int scrHeight, unsigned int pixWidth, unsigned int pixHeight);

	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	void ProcessInput(float deltaTime);

	unsigned int GetScreenWidth() const;
	unsigned int GetScreenHeight() const;
	unsigned int GetPixelWidth() const;
	unsigned int GetPixelHeight() const;
private:
	unsigned int mScreenWidth, mScreenHeight, mPixelWidth, mPixelHeight;

	std::shared_ptr<Ship> mShip;
};
