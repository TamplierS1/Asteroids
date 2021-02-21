#include "Actor.h"

olc::vf2d& Actor::GetPos()
{
    return mPos;
}

olc::vf2d& Actor::GetVelocity()
{
    return mVelocity;
}

float& Actor::GetSize()
{
    return mSize;
}

olc::vf2d& Actor::GetDirection()
{
    return mDir;
}

float& Actor::GetAngle()
{
    return mAngle;
}

olc::vf2d Actor::GetTransformedVertex(int number)
{
    return mTransformedVertices[number];
}

unsigned int Actor::GetNumOfVerts()
{
    return mNumOfVerts;
}

olc::Pixel Actor::GetColor() const
{
    return mColor;
}

void Actor::Move(float deltaTime)
{
    mPos.x += mVelocity.x * deltaTime;
    mPos.y += mVelocity.y * deltaTime;

    // translate
    for (int i = 0; i < mNumOfVerts; i++)
    {
        mTransformedVertices[i].x += mPos.x;
        mTransformedVertices[i].y += mPos.y;
    }
}

void Actor::Rotate(float deltaTime)
{
    // rotate
    for (int i = 0; i < mNumOfVerts; i++)
    {
        mTransformedVertices[i].x = mModelVertices[i].x * cos(mAngle) - mModelVertices[i].y * sin(mAngle);
        mTransformedVertices[i].y = mModelVertices[i].x * sin(mAngle) + mModelVertices[i].y * cos(mAngle);
    }
}

void Actor::ChangeRotation(RotationDir dir, float deltaTime)
{
    mAngle += mRotationSpeed * int(dir) * deltaTime;
}

void Actor::Scale(float amount)
{
    for (int i = 0; i < mNumOfVerts; i++)
    {
        mTransformedVertices[i].x *= amount;
    }

    for (int i = 0; i < mNumOfVerts; i++)
    {
        mTransformedVertices[i].y *= amount;
    }
}

Actor::Actor()
{
}

float Actor::GetRotationSpeed()
{
    return mRotationSpeed;
}

RotationDir Actor::GetRotDir()
{
    return mRotDir;
}

Actor::Actor(olc::vf2d pos, olc::vf2d velocity, float size, unsigned int verts, RotationDir rotDir, float rotSpeed,
             std::vector<olc::vf2d> modelVerts, olc::Pixel color)
{
    mNumOfVerts = verts;
    mModelVertices = modelVerts;
    mColor = color;
    mPos = pos;
    mVelocity = velocity;
    mSize = size;
    mDir = olc::vf2d(0.0f, 0.0f);

    mAngle = 0.0f;
    mRotationSpeed = rotSpeed;

    for (int i = 0; i < mNumOfVerts; i++)
    {
        mTransformedVertices.push_back(olc::vf2d(0.0f, 0.0f));
        mTransformedVertices[i].x += mPos.x;
        mTransformedVertices[i].y += mPos.y;
    }

    mRotDir = rotDir;
}