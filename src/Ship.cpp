#include "Ship.h"

Ship::Ship()
    : Actor()
{
    mPos = gDefaultPlayerPos;
    mVelocity = gDefaultPlayerVelocity;
    mSize = gDefaultPlayerSize;
    mAcceleration = gDefaultPlayerAcceleration;
    mDir = olc::vf2d(0.0f, 0.0f);
    mColor = olc::WHITE;

    mAngle = 0.0f;
    mRotationSpeed = gDefaultPlayerRotationSpeed;

    mNumOfVerts = 3;

    mModelVertices = {olc::vf2d(0.0f, -2.0f), olc::vf2d(-1.0f, +1.0f), olc::vf2d(+1.0f, +1.0f)};

    for (int i = 0; i < mNumOfVerts; i++)
    {
        mTransformedVertices.push_back(olc::vf2d(0.0f, 0.0f));
        mTransformedVertices[i].x += mPos.x;
        mTransformedVertices[i].y += mPos.y;
    }

    mBulletVelocity = olc::vf2d(250.0f, -250.0f);
    mRotDir = RotationDir::RIGHT;
    mDead = false;
}

Ship::Ship(olc::vf2d pos, olc::vf2d velocity, float size, olc::vf2d acceleration, float rotSpeed, olc::Pixel color)
{
    mPos = pos;
    mVelocity = velocity;
    mSize = size;
    mAcceleration = acceleration;
    mDir = olc::vf2d(0.0f, 0.0f);
    mColor = color;

    mAngle = 0.0f;
    mRotationSpeed = rotSpeed;

    mNumOfVerts = 3;

    mModelVertices = {olc::vf2d(0.0f, -2.0f), olc::vf2d(-1.0f, +1.0f), olc::vf2d(+1.0f, +1.0f)};

    mBulletVelocity = olc::vf2d(350.0f, -350.0f);

    for (int i = 0; i < mNumOfVerts; i++)
    {
        mTransformedVertices.push_back(olc::vf2d(0.0f, 0.0f));
        mTransformedVertices[i].x += mPos.x;
        mTransformedVertices[i].y += mPos.y;
    }

    mRotDir = RotationDir::RIGHT;

    mDead = false;
}

olc::vf2d& Ship::GetAcceleration()
{
    return mAcceleration;
}

std::vector<Bullet>& Ship::GetBullets()
{
    return mBullets;
}

void Ship::Thrust()
{
    mVelocity.x += sin(mAngle) * mAcceleration.x;
    mVelocity.y += -cos(mAngle) * mAcceleration.y;
}

void Ship::FireBullet()
{
    Bullet bullet(mPos, mBulletVelocity, mAngle, olc::WHITE);
    mBullets.push_back(bullet);
}

bool& Ship::IsDead()
{
    return mDead;
}