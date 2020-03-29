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

	virtual bool Draw(int32_t x, int32_t y, olc::Pixel p) override;
	void DrawActor(Actor& actor, olc::Pixel color);
	void ProcessInput(float deltaTime);
	//takes as input a set of coordinates and transforms them if they are out of the screen
	void WrapCoordinates(float inx, float iny, float& ox, float& oy);

	unsigned int GetScreenWidth() const;
	unsigned int GetScreenHeight() const;
	unsigned int GetPixelWidth() const;
	unsigned int GetPixelHeight() const;
private:
	unsigned int mScreenWidth, mScreenHeight, mPixelWidth, mPixelHeight;

	std::shared_ptr<Ship> mShip;

	bool mIsGameActive;
};
