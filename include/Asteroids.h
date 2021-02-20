#pragma once

#include <algorithm>
#include <memory>

#include "Ship.h"
#include "olcPixelGameEngine.h"

enum GAME_STATE
{
    MENU,
    ACTIVE,
    GAMEOVER
};

struct Menu
{
    std::pair<float, float> mFirstBoxPos;
    std::pair<float, float> mFirstBoxSize;

    std::pair<float, float> mSecondBoxPos;
    std::pair<float, float> mSecondBoxSize;

    std::string mFirstBoxText;
    std::string mSecondBoxText;
};

class Asteroids : public olc::PixelGameEngine
{
public:
    Asteroids(unsigned int scrWidth, unsigned int scrHeight, unsigned int pixWidth, unsigned int pixHeight);

    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

    virtual bool Draw(int32_t x, int32_t y, olc::Pixel p) override;
    void DrawActor(Actor &actor, olc::Pixel color);
    // check collision between a point and a circle
    bool CheckCollisions(std::pair<float, float> circlePos, float circleRad, std::pair<float, float> pointPos);
    void ProcessInput(float deltaTime);
    bool IsMouseHovered(std::pair<float, float> pos, std::pair<float, float> size);
    // takes as input a set of coordinates and transforms them if they are out of
    // the screen
    void WrapCoordinates(float inx, float iny, float &ox, float &oy);
    void CreateNewAsteroid(float rotAngle, int parentIndex);
    void NewLevel();
    unsigned int GetScreenWidth() const;
    unsigned int GetScreenHeight() const;
    unsigned int GetPixelWidth() const;
    unsigned int GetPixelHeight() const;

private:
    unsigned int mScreenWidth, mScreenHeight, mPixelWidth, mPixelHeight;

    std::shared_ptr<Ship> mShip;
    std::vector<std::shared_ptr<Actor>> mAsteroids;
    std::vector<std::shared_ptr<Actor>> mNewAsteroids;
    bool mIsGameActive;

    GAME_STATE mState;

    Menu mMenu;

    int mScore = 0;
};
