#include "Asteroids.h"

Asteroids::Asteroids(unsigned int scrWidth, unsigned int scrHeight, unsigned int pixWidth, unsigned int pixHeight)
{
	sAppName = "Asteroids";

	mScreenWidth = scrWidth;
	mScreenHeight = scrHeight;

	mPixelWidth = pixWidth;
	mPixelHeight = pixHeight;

	mIsGameActive = true;
}

bool Asteroids::OnUserCreate()
{
	mShip = std::make_shared<Ship>(mScreenWidth / 2, mScreenHeight / 2, 200.0f, 200.0f, 50.0f, 50.0f, 10.0f, 10.0f, 5.0f);

	return true;
}

bool Asteroids::OnUserUpdate(float fElapsedTime)
{
	Clear(olc::BLACK);

	ProcessInput(fElapsedTime);

	mShip->Rotate(fElapsedTime, mShip->GetRotDir());
	mShip->Move(fElapsedTime);

	DrawActor(*mShip, olc::WHITE);

	return mIsGameActive;
}

bool Asteroids::Draw(int32_t x, int32_t y, olc::Pixel p)
{
	float wrappedX, wrappedY;
	WrapCoordinates(x, y, wrappedX, wrappedY);
	return olc::PixelGameEngine::Draw(wrappedX, wrappedY, p);
}

void Asteroids::DrawActor(Actor& actor, olc::Pixel color)
{
	for (int i = 0; i < 4; i++)
	{
		int j = (i + 1);

		DrawLine(actor.GetTransformedMatX()[i % 3], actor.GetTransformedMatY()[i % 3],
			actor.GetTransformedMatX()[j % 3], actor.GetTransformedMatY()[j % 3], color);
	}

	/*for (int x = 0; x < actor.GetSizeX(); x++)
		for (int y = 0; y < actor.GetSizeY(); y++)
		{
			float posx = actor.GetPosX() + x;
			float posy = actor.GetPosY() + y;

			WrapCoordinates(posx, posy);

			Draw(posx, posy, color);
		}*/
}

void Asteroids::ProcessInput(float deltaTime)
{
	if (IsFocused())
	{
		//We set ship's directions even though we don't use them here.
		//Instead we use them in OnUserUpdate() because we need to know where to move the ship

		if (GetKey(olc::Key::ESCAPE).bPressed)
			mIsGameActive = false;
		if (GetKey(olc::Key::D).bHeld)
		{
			mShip->ChangeRotation(RIGHT, deltaTime);
		}
		if (GetKey(olc::Key::A).bHeld)
		{
			mShip->ChangeRotation(LEFT, deltaTime);
		}
		if (GetKey(olc::Key::W).bHeld)
		{
			mShip->Thrust();
		}
	}
}

void Asteroids::WrapCoordinates(float inx, float iny, float& ox, float& oy)
{
	ox = inx;
	oy = iny;

	if (inx < 0.0f)									ox = inx + static_cast<float>(mScreenWidth);
	if (inx >= static_cast<float>(mScreenWidth))	ox = inx - static_cast<float>(mScreenWidth);

	if (iny < 0.0f)									oy = iny + static_cast<float>(mScreenHeight);
	if (iny >= static_cast<float>(mScreenHeight))	oy = iny - static_cast<float>(mScreenHeight);
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