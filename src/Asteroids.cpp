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
	mShip = std::make_shared<Ship>(std::pair<float, float>(mScreenWidth / 4, mScreenHeight / 4),
		std::pair<float, float>(50.0f, 50.0f), 16.0f, std::pair<float, float>(10.0f, 10.0f), 5.0f, olc::WHITE);

	/*mShip = std::make_shared<Ship>(std::pair<float, float>(15.0f, 15.0f),
		std::pair<float, float>(10.0f, 10.0f), std::pair<float, float>(15.0f, 15.0f), std::pair<float, float>(5.0f, 5.0f), 5.0f, olc::WHITE);*/

	std::vector<std::pair<float, float>> astModel;
	int astVerts = 10;
	for (int i = 0; i < astVerts; i++)
	{
		float radius = 1.0f;
		float a = ((float)i / (float)astVerts) * 6.28318;
		astModel.push_back(std::pair<float, float>(radius * sin(a), radius * cos(a)));
	}

	std::shared_ptr<Actor> asteroid = std::make_shared<Actor>(std::pair<float, float>(100.0f, 100.0f), std::pair<float, float>(100.0f, 100.0f),
		64.0f, 10, RIGHT, 5.0f, astModel, olc::RED);

	mAsteroids.push_back(asteroid);

	return true;
}

bool Asteroids::OnUserUpdate(float fElapsedTime)
{
	Clear(olc::BLACK);

	ProcessInput(fElapsedTime);

	//update and draw ship
	mShip->Rotate(fElapsedTime);
	mShip->Scale(mShip->GetSize());
	mShip->Move(fElapsedTime);

	WrapCoordinates(mShip->GetPos().first, mShip->GetPos().second, mShip->GetPos().first, mShip->GetPos().second);
	DrawActor(*mShip, mShip->GetColor());

	//update asteroids
	for (int i = 0; i < mAsteroids.size(); i++)
	{
		mAsteroids[i]->Rotate(fElapsedTime);
		mAsteroids[i]->Scale(mAsteroids[i]->GetSize());
		mAsteroids[i]->Move(fElapsedTime);
		WrapCoordinates(mAsteroids[i]->GetPos().first, mAsteroids[i]->GetPos().second, mAsteroids[i]->GetPos().first, mAsteroids[i]->GetPos().second);
		DrawActor(*mAsteroids[i], mAsteroids[i]->GetColor());
	}

	//update and draw bullets
	for (int i = 0; i < mShip->GetBullets().size(); i++)
	{
		Bullet* bullet = &mShip->GetBullets()[i];

		bullet->MoveBullet(fElapsedTime);

		for (int j = 0; j < mAsteroids.size(); j++)
		{
			//we pass GetSize().first because for an asteroid (a circle basically) GetSize().second is the same
			if (CheckCollisions(mAsteroids[j]->GetPos(), mAsteroids[j]->GetSize(), bullet->GetPos()))
			{
				//we are moving bullet off screen to have it deleted later
				bullet->GetPos().first = -100.0f;

				if (mAsteroids[i]->GetSize() > 4)
				{
					//create two half-sized child asteroids

					float angle1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 6.28321;
					float angle2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 6.28321;

					CreateNewAsteroid(angle1, i);
					CreateNewAsteroid(angle2, i);

					mAsteroids[i]->GetSize() = 2;
				}
				mAsteroids[i]->GetPos().first = -100.0f;
			}
		}

		//delete any bullets that are off screen
		if (mShip->GetBullets().size() > 0)
		{
			auto j = std::remove_if(mShip->GetBullets().begin(), mShip->GetBullets().end(),
				[&](Bullet b) {return b.GetPos().first < 1 || b.GetPos().second < 1 ||
				b.GetPos().first >= mScreenWidth || b.GetPos().second >= mScreenHeight; });

			if (j != mShip->GetBullets().end())
			{
				mShip->GetBullets().erase(j);
			}
		}

		//delete any asteroids that are off screen
		if (mAsteroids.size() > 0)
		{
			//we check only x axis because we move destroyed asteroids off screen by x axis
			auto j = std::remove_if(mAsteroids.begin(), mAsteroids.end(),
				[&](std::shared_ptr<Actor> a) {return a->GetPos().first < 1 ||
				a->GetPos().first >= mScreenWidth; });

			if (j != mAsteroids.end())
			{
				mAsteroids.erase(j);
			}
		}
		DrawCircle(bullet->GetPos().first, bullet->GetPos().second, 2.0f, bullet->GetColor());
	}

	//copy asteroids from mNewAsteroids to mAsteroids
	for (int i = 0; i < mNewAsteroids.size(); i++)
	{
		mAsteroids.push_back(mNewAsteroids[i]);
	}

	DrawString(20.0f, 20.0f, "Bullets: " + std::to_string(mShip->GetBullets().size()), olc::GREEN);
	DrawString(20.0f, 40.0f, "Asteroids: " + std::to_string(mAsteroids.size()), olc::GREEN);
	DrawString(20.0f, 60.0f, "Asteroid 1 size: " + std::to_string(mAsteroids[0]->GetSize()), olc::GREEN);
	DrawString(120.0f, 20.0f, "Ship x: " + std::to_string(mShip->GetPos().first) + "\n\n" + "Ship y: " +
		std::to_string(mShip->GetPos().second), olc::GREEN);
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
	int n = actor.GetNumOfVerts();
	for (int i = 0; i < n + 1; i++)
	{
		int j = i + 1;
		DrawLine(actor.GetTransformedVertex(i % n).first, actor.GetTransformedVertex(i % n).second,
			actor.GetTransformedVertex(j % n).first, actor.GetTransformedVertex(j % n).second, color);
	}
}

bool Asteroids::CheckCollisions(std::pair<float, float> circlePos, float circleRad, std::pair<float, float> pointPos)
{
	//distance between a point and a circle
	return sqrt((pointPos.first - circlePos.first) * (pointPos.first - circlePos.first) +
		(pointPos.second - circlePos.second) * (pointPos.second - circlePos.second)) < circleRad;
}

void Asteroids::ProcessInput(float deltaTime)
{
	if (IsFocused())
	{
		//We set ship's directions even though we don't use them here.
		//Instead we use them in OnUserUpdate() because we need to know where to move the ship

		if (GetKey(olc::Key::ESCAPE).bPressed)
			mIsGameActive = false;
		if (GetKey(olc::Key::SPACE).bReleased)
		{
			mShip->FireBullet();
		}
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

void Asteroids::CreateNewAsteroid(float rotAngle, int parentIndex)
{
	std::vector<std::pair<float, float>> astModel;
	int astVerts = mAsteroids[parentIndex]->GetNumOfVerts();
	for (int i = 0; i < astVerts; i++)
	{
		float radius = 1.0f;
		float a = ((float)i / (float)astVerts) * 6.28318;
		astModel.push_back(std::pair<float, float>(radius * sin(a), radius * cos(a)));
	}

	std::shared_ptr<Actor> asteroid = std::make_shared<Actor>(mAsteroids[parentIndex]->GetPos(), mAsteroids[parentIndex]->GetVelocity(),
		mAsteroids[parentIndex]->GetSize() / 2, astVerts, mAsteroids[parentIndex]->GetRotDir(),
		mAsteroids[parentIndex]->GetRotationSpeed(), astModel, mAsteroids[parentIndex]->GetColor());

	asteroid->GetAngle() = rotAngle;
	mNewAsteroids.push_back(asteroid);
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