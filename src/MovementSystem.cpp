#include "MovementSystem.h"

#include <iostream>
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
    for (auto entity : getActiveEntities())
        std::cout << entity->getID() << std::endl;
}

void MovementSystem::processEntity(fsn::EntityRef* entity, const float dt)
{
    //return;

    auto transform = entity->getComponent<fsn::Transform>();
    auto vel = entity->getComponent<Velocity>();

    transform->move(vel->mX, vel->mY);
}

void MovementSystem::end(const float dt)
{
    std::cout << "done\n";
}
