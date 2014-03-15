#include "BallPaddleSystem.h"

#include <Fission/Rendering/Transform.h>

#include "Ball.h"
#include "Dimensions.h"
#include "Velocity.h"
#include "Paddle.h"

#include "EntityTags.h"

BallPaddleSystem::BallPaddleSystem(fsn::EntityManager& entityMgr) : fsn::ComponentSystem(entityMgr),
    mEntityManager(entityMgr)
{
    all<fsn::Transform, Dimensions, Velocity, Ball>();
}

void BallPaddleSystem::processEntity(const fsn::EntityRef& entity, const float dt)
{
    auto& transform = entity.getComponent<fsn::Transform>();
    auto& dim = entity.getComponent<Dimensions>();
    auto& vel = entity.getComponent<Velocity>();

    sf::Vector2f ballPos = transform.getPosition()-transform.getOrigin();

    auto& paddleEntities = mEntityManager.getEntitiesWithTag(PADDLE);

    for (auto& paddleEnt : paddleEntities)
    {
        auto& pTransform = paddleEnt.getComponent<fsn::Transform>();
        auto& pDim = paddleEnt.getComponent<Dimensions>();
        auto& paddle = paddleEnt.getComponent<Paddle>();

        sf::Vector2f paddlePos = pTransform.getPosition()-pTransform.getOrigin();

        if (ballPos.x+dim.x > paddlePos.x && ballPos.x < paddlePos.x+pDim.x &&
            ballPos.y+dim.y > paddlePos.y && ballPos.y < paddlePos.y+pDim.y)
        {
            vel.x = 300*paddle.deflectDir;
        }
    }
}
