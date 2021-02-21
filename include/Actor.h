#pragma once

#include <math.h>

#include <vector>

#include "olcPixelGameEngine.h"

enum class RotationDir
{
    LEFT = -1,
    RIGHT = 1,
    NONE = 0
};

class Actor
{
public:
    Actor(olc::vf2d pos, olc::vf2d velocity, float size, unsigned int verts, RotationDir rotDir, float rotSpeed,
          std::vector<olc::vf2d> modelVerts, olc::Pixel color);
    // utility functions
    olc::vf2d& GetPos();
    olc::vf2d& GetVelocity();
    float& GetSize();

    olc::vf2d& GetDirection();
    float GetRotationSpeed();
    RotationDir GetRotDir();
    float& GetAngle();
    olc::vf2d GetTransformedVertex(int number);
    unsigned int GetNumOfVerts();
    olc::Pixel GetColor() const;

    virtual void Move(float deltaTime);
    void Rotate(float deltaTime);
    void ChangeRotation(RotationDir dir, float deltaTime);
    void Scale(float amount);

protected:
    Actor();

    olc::vf2d mPos;
    olc::vf2d mVelocity;
    float mSize;
    olc::vf2d mDir;

    std::vector<olc::vf2d> mTransformedVertices;
    std::vector<olc::vf2d> mModelVertices;
    unsigned int mNumOfVerts;

    olc::Pixel mColor;

    float mAngle;
    float mRotationSpeed;
    RotationDir mRotDir;
};
