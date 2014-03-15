#include "BallWallSystem.h"

#include <Fission/Rendering/Transform.h>

#include "Ball.h"
#include "Dimensions.h"
#include "Velocity.h"

BallWallSystem::BallWallSystem(fsn::EntityManager& entityMgr, int screenWidth, int screenHeight) : fsn::ComponentSystem(entityMgr),
    mScreenWidth(screenWidth), mScreenHeight(screenHeight)
{
    all<fsn::Transform, Dimensions, Velocity, Ball>();
}

void BallWallSystem::processEntity(const fsn::EntityRef& entity, const float dt)
{
    auto& transform = entity.getComponent<fsn::Transform>();
    auto& dim = entity.getComponent<Dimensions>();
    auto& vel = entity.getComponent<Velocity>();
    auto& ball = entity.getComponent<Ball>();

    if (transform.getPosition().x < 0) // hit left
    {
        vel.x = 300;
    }
    else if (transform.getPosition().x + dim.x > mScreenWidth)
    {
        vel.x = -300;
    }

    if (transform.getPosition().y < 0) // hit left or right wall
    {
        vel.y = 300;
    }
    else if (transform.getPosition().y + dim.y > mScreenHeight)
    {
        vel.y = -300;
    }
}
