#include "Asteroids.h"

Asteroids::Asteroids(unsigned int scrWidth, unsigned int scrHeight, unsigned int pixWidth, unsigned int pixHeight)
{
	sAppName = "Asteroids";

	mScreenWidth = scrWidth;
	mScreenHeight = scrHeight;

	mPixelWidth = pixWidth;
	mPixelHeight = pixHeight;
}

bool Asteroids::OnUserCreate()
{
	mShip = std::make_shared<Ship>(50.0f, 50.0f, 200.0f, 200.0f, 50.0f, 50.0f, 10.0f, 10.0f);
	return true;
}

bool Asteroids::OnUserUpdate(float fElapsedTime)
{
	Clear(olc::BLACK);

	ProcessInput(fElapsedTime);

	mShip->Move(fElapsedTime);

	DrawTriangle(mShip->GetPosX(), mShip->GetPosY(), mShip->GetPosX(),
		mShip->GetPosY() + mShip->GetSizeY(), mShip->GetPosX() + mShip->GetSizeX(), mShip->GetPosY() + mShip->GetSizeY() / 2, olc::WHITE);
	FillTriangle(mShip->GetPosX(), mShip->GetPosY(), mShip->GetPosX(),
		mShip->GetPosY() + mShip->GetSizeY(), mShip->GetPosX() + mShip->GetSizeX(), mShip->GetPosY() + mShip->GetSizeY() / 2, olc::WHITE);

	//DrawRect(mShip->GetPosX(), mShip->GetPosY(), mShip->GetSizeX(), mShip->GetSizeY(), olc::WHITE);
	//FillRect(mShip->GetPosX(), mShip->GetPosY(), mShip->GetSizeX(), mShip->GetSizeY(), olc::WHITE);

	return true;
}

void Asteroids::ProcessInput(float deltaTime)
{
	if (IsFocused())
	{
		if (GetKey(olc::Key::D).bHeld)
		{
			mShip->GetDirX() = 1.0f;
			mShip->GetDirY() = 0.0f;
		}
		if (GetKey(olc::Key::A).bHeld)
		{
			mShip->GetDirX() = -1.0f;
			mShip->GetDirY() = 0.0f;
		}
		if (GetKey(olc::Key::W).bHeld)
		{
			mShip->GetDirX() = 0.0f;
			mShip->GetDirY() = -1.0f;
		}
		if (GetKey(olc::Key::S).bHeld)
		{
			mShip->GetDirX() = 0.0f;
			mShip->GetDirY() = 1.0f;
		}
	}
}

unsigned int Asteroids::GetScreenWidth() const
{
	return mScreenWidth;
}

unsigned int Asteroids::GetScreenHeight() const
{
	return mScreenHeight;
}

unsigned int Asteroids::GetPixelWidth() const
{
	return mPixelWidth;
}

unsigned int Asteroids::GetPixelHeight() const
{
	return mPixelHeight;
}