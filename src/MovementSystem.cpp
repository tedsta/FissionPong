#include "MovementSystem.h"

#include <Fission/Rendering/Transform.h>

#include "Velocity.h"

MovementSystem::MovementSystem(fsn::IEventManager* eventManager, float lockStep) : fsn::System(eventManager, lockStep)
{
    mAspect.all<fsn::Transform, Velocity>();
}

MovementSystem::~MovementSystem()
{
    //dtor
}

void MovementSystem::begin(const float dt)
{
}

void MovementSystem::processEntity(fsn::EntityRef* entity, const float dt)
{
    auto transform = entity->getComponent<fsn::Transform>();
    auto vel = entity->getComponent<Velocity>();

    transform->move(vel->mX, vel->mY);
}

void MovementSystem::end(const float dt)
{
}
