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
    mAspect.all<fsn::Transform, Dimensions, Velocity, Ball>();
}

void BallPaddleSystem::processEntity(const fsn::EntityRef& entity, const float dt)
{
    auto transform = entity.getComponent<fsn::Transform>();
    auto dim = entity.getComponent<Dimensions>();
    auto vel = entity.getComponent<Velocity>();
    auto ball = entity.getComponent<Ball>();

    auto paddleEntities = mEntityManager.getEntitiesWithTag(PADDLE);

    for (auto& paddleEnt : paddleEntities)
    {
        auto pTransform = paddleEnt.getComponent<fsn::Transform>();
        auto pDim = paddleEnt.getComponent<Dimensions>();
        auto paddle = paddleEnt.getComponent<Paddle>();


        if (transform->getPosition().x+dim->x > pTransform->getPosition().x && transform->getPosition().x < pTransform->getPosition().x+pDim->x &&
            transform->getPosition().y+dim->y > pTransform->getPosition().y && transform->getPosition().y < pTransform->getPosition().y+pDim->y)
        {
            vel->x = 300*paddle->deflectDir;
        }
    }
}
