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
    mMenu = {olc::vf2d(static_cast<float>(mScreenWidth) / 2.0f, static_cast<float>(mScreenHeight) / 2.0f),
             olc::vf2d(40.0f, 15.0f),
             olc::vf2d(static_cast<float>(mScreenWidth) / 2.0f, static_cast<float>(mScreenHeight) / 2.0f + 20.0f),
             olc::vf2d(40.0f, 15.0f),
             "Start",
             "Exit"};

    mShip = std::make_shared<Ship>(olc::vf2d(mScreenWidth / 4, mScreenHeight / 4), olc::vf2d(50.0f, 50.0f), 16.0f,
                                   olc::vf2d(10.0f, 10.0f), 5.0f, olc::WHITE);

    mState = MENU;

    std::vector<olc::vf2d> astModel;
    int astVerts = 10;
    for (int i = 0; i < astVerts; i++)
    {
        srand(time(NULL));
        float radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.4 + 0.8f;
        float a = ((float)i / (float)astVerts) * 6.28318;
        astModel.push_back(olc::vf2d(radius * sin(a), radius * cos(a)));
    }

    std::shared_ptr<Actor> asteroid
        = std::make_shared<Actor>(olc::vf2d(100.0f, 100.0f), olc::vf2d(50.0f, 50.0f), 128.0f, 10, RotationDir::RIGHT,
                                  5.0f, astModel, olc::YELLOW);

    mAsteroids.push_back(asteroid);

    return true;
}

bool Asteroids::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLACK);

    ProcessInput(fElapsedTime);

    if (mState == ACTIVE)
    {
        // update and draw ship
        mShip->Rotate(fElapsedTime);
        mShip->Scale(mShip->GetSize());
        mShip->Move(fElapsedTime);

        WrapCoordinates(mShip->GetPos().x, mShip->GetPos().y, mShip->GetPos().x, mShip->GetPos().y);
        DrawActor(*mShip, mShip->GetColor());

        // update asteroids
        for (int i = 0; i < mAsteroids.size(); i++)
        {
            mAsteroids[i]->GetAngle() += 0.5f * fElapsedTime;
            mAsteroids[i]->Rotate(fElapsedTime);
            mAsteroids[i]->Scale(mAsteroids[i]->GetSize());
            mAsteroids[i]->Move(fElapsedTime);
            WrapCoordinates(mAsteroids[i]->GetPos().x, mAsteroids[i]->GetPos().y, mAsteroids[i]->GetPos().x,
                            mAsteroids[i]->GetPos().y);
            DrawActor(*mAsteroids[i], mAsteroids[i]->GetColor());

            if (CheckCollisions(mAsteroids[i]->GetPos(), mAsteroids[i]->GetSize(), mShip->GetPos()))
            {
                mShip->IsDead() = true;
                mState = GAMEOVER;
            }
        }

        // update and draw bullets
        for (int i = 0; i < mShip->GetBullets().size(); i++)
        {
            Bullet* bullet = &mShip->GetBullets()[i];

            bullet->MoveBullet(fElapsedTime);

            for (int j = 0; j < mAsteroids.size(); j++)
            {
                // we pass GetSize().x because for an asteroid (a circle basically) GetSize().y is the same
                if (CheckCollisions(mAsteroids[j]->GetPos(), mAsteroids[j]->GetSize(), bullet->GetPos()))
                {
                    mScore += 100;
                    // we are moving bullet off screen to have it deleted later
                    bullet->GetPos().x = -100.0f;

                    if (mAsteroids[j]->GetSize() > 32.0f)
                    {
                        // create two half-sized child asteroids
                        srand(time(NULL));
                        float angle1 = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 6.283185f;
                        float angle2 = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * 6.283185f;

                        CreateNewAsteroid(angle1, j);
                        CreateNewAsteroid(angle2, j);
                    }
                    mAsteroids[j]->GetPos().x = -100.0f;
                    mAsteroids[j]->GetPos().y = -100.0f;
                }
            }

            // delete any bullets that are off screen
            if (mShip->GetBullets().size() > 0)
            {
                auto j = std::remove_if(mShip->GetBullets().begin(), mShip->GetBullets().end(), [&](Bullet b) {
                    return b.GetPos().x < 1 || b.GetPos().y < 1 || b.GetPos().x >= mScreenWidth
                           || b.GetPos().y >= mScreenHeight;
                });

                if (j != mShip->GetBullets().end())
                {
                    mShip->GetBullets().erase(j);
                }
            }

            // delete any asteroids that are off screen
            if (mAsteroids.size() > 0)
            {
                // we check only x axis because we move destroyed asteroids off screen by x axis
                auto j = std::remove_if(mAsteroids.begin(), mAsteroids.end(), [&](std::shared_ptr<Actor> a) {
                    return a->GetPos().x < 1 || a->GetPos().x >= mScreenWidth;
                });

                if (j != mAsteroids.end())
                {
                    mAsteroids.erase(j);
                }
            }
            DrawCircle(bullet->GetPos().x, bullet->GetPos().y, 2.0f, bullet->GetColor());
        }

        // copy asteroids from mNewAsteroids to mAsteroids
        for (int i = 0; i < mNewAsteroids.size(); i++)
        {
            mAsteroids.push_back(mNewAsteroids[i]);
            mNewAsteroids.erase(mNewAsteroids.begin() + i);
        }

        DrawString(20.0f, 20.0f, "Score: " + std::to_string(mScore), olc::GREEN);
        if (mAsteroids.empty())
        {
            mScore += 1000;

            NewLevel();
        }
    }
    else if (mState == MENU)
    {
        DrawString(mMenu.mFirstBoxPos.x, mMenu.mFirstBoxPos.y, mMenu.mFirstBoxText, olc::WHITE);
        DrawString(mMenu.mSecondBoxPos.x, mMenu.mSecondBoxPos.y, mMenu.mSecondBoxText, olc::WHITE);
    }
    else if (mState == GAMEOVER)
    {
        DrawString(mMenu.mFirstBoxPos.x - mMenu.mFirstBoxSize.x * 2, mMenu.mFirstBoxPos.y - mMenu.mFirstBoxSize.y,
                   "You Died", olc::DARK_RED, 3);
    }
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
        DrawLine(actor.GetTransformedVertex(i % n).x, actor.GetTransformedVertex(i % n).y,
                 actor.GetTransformedVertex(j % n).x, actor.GetTransformedVertex(j % n).y, color);
    }
}

bool Asteroids::CheckCollisions(olc::vf2d circlePos, float circleRad, olc::vf2d pointPos)
{
    // distance between a point and a circle
    return sqrt((pointPos.x - circlePos.x) * (pointPos.x - circlePos.x)
                + (pointPos.y - circlePos.y) * (pointPos.y - circlePos.y))
           < circleRad;
}

void Asteroids::ProcessInput(float deltaTime)
{
    if (IsFocused())
    {
        // We set ship's directions even though we don't use them here.
        // Instead we use them in OnUserUpdate() because we need to know where to move the ship

        if (GetKey(olc::Key::ESCAPE).bPressed) mIsGameActive = false;
        if (IsMouseHovered(mMenu.mFirstBoxPos, mMenu.mFirstBoxSize))
        {
            if (GetMouse(0).bReleased)
            {
                mState = ACTIVE;
            }
        }
        if (IsMouseHovered(mMenu.mSecondBoxPos, mMenu.mSecondBoxSize))
        {
            if (GetMouse(0).bReleased)
            {
                mIsGameActive = false;
            }
        }
        if (GetKey(olc::Key::SPACE).bReleased)
        {
            mShip->FireBullet();
        }
        if (GetKey(olc::Key::D).bHeld)
        {
            mShip->ChangeRotation(RotationDir::RIGHT, deltaTime);
        }
        if (GetKey(olc::Key::A).bHeld)
        {
            mShip->ChangeRotation(RotationDir::LEFT, deltaTime);
        }
        if (GetKey(olc::Key::W).bHeld)
        {
            mShip->Thrust();
        }
    }
}

bool Asteroids::IsMouseHovered(olc::vf2d pos, olc::vf2d size)
{
    return GetMouseX() >= pos.x && GetMouseX() < pos.x + size.x && GetMouseY() >= pos.y && GetMouseY() < pos.y + size.y;
}

void Asteroids::WrapCoordinates(float inx, float iny, float& ox, float& oy)
{
    ox = inx;
    oy = iny;

    if (inx < 0.0f) ox = inx + static_cast<float>(mScreenWidth);
    if (inx >= static_cast<float>(mScreenWidth)) ox = inx - static_cast<float>(mScreenWidth);

    if (iny < 0.0f) oy = iny + static_cast<float>(mScreenHeight);
    if (iny >= static_cast<float>(mScreenHeight)) oy = iny - static_cast<float>(mScreenHeight);
}

void Asteroids::CreateNewAsteroid(float rotAngle, int parentIndex)
{
    std::vector<olc::vf2d> astModel;
    int astVerts = mAsteroids[parentIndex]->GetNumOfVerts();
    for (int i = 0; i < astVerts; i++)
    {
        float radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.4 + 0.8f;
        float a = ((float)i / (float)astVerts) * 6.28318;
        astModel.push_back(olc::vf2d(radius * sin(a), radius * cos(a)));
    }

    std::shared_ptr<Actor> asteroid = std::make_shared<Actor>(
        mAsteroids[parentIndex]->GetPos(),
        olc::vf2d(mAsteroids[parentIndex]->GetVelocity().x * sin(rotAngle),
                  mAsteroids[parentIndex]->GetVelocity().y * cos(rotAngle)),
        static_cast<int>(mAsteroids[parentIndex]->GetSize()) >> 1, astVerts, mAsteroids[parentIndex]->GetRotDir(),
        mAsteroids[parentIndex]->GetRotationSpeed(), astModel, mAsteroids[parentIndex]->GetColor());

    /*WrapCoordinates(asteroid->GetPos().x, asteroid->GetPos().y, asteroid->GetPos().x,
     * asteroid->GetPos().y);*/
    asteroid->GetAngle() = rotAngle;
    mNewAsteroids.push_back(asteroid);
}

void Asteroids::NewLevel()
{
    std::vector<olc::vf2d> astModel;
    int astVerts = 10;
    for (int i = 0; i < astVerts; i++)
    {
        srand(time(NULL));
        float radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.4 + 0.8f;
        float a = ((float)i / (float)astVerts) * 6.28318;
        astModel.push_back(olc::vf2d(radius * sin(a), radius * cos(a)));
    }

    std::shared_ptr<Actor> asteroid = std::make_shared<Actor>(
        olc::vf2d(100.0f * sin(mShip->GetAngle() - 3.14159 / 2.0f), 100.0f * cos(mShip->GetAngle() - 3.14159 / 2.0f)),
        olc::vf2d(50.0f * sin(mShip->GetAngle()), 50.0f * cos(mShip->GetAngle())), 128.0f, 10, RotationDir::RIGHT, 5.0f,
        astModel, olc::YELLOW);
    std::shared_ptr<Actor> asteroid1 = std::make_shared<Actor>(
        olc::vf2d(100.0f * sin(mShip->GetAngle() - 3.14159 / 2.0f), 100.0f * cos(mShip->GetAngle() - 3.14159 / 2.0f)),
        olc::vf2d(50.0f * sin(-mShip->GetAngle()), 50.0f * cos(-mShip->GetAngle())), 128.0f, 10, RotationDir::RIGHT,
        5.0f, astModel, olc::YELLOW);

    mAsteroids.push_back(asteroid);
    mAsteroids.push_back(asteroid1);
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