#include "MovementSystem.h"

#include <iostream>
#include <Fission/Rendering/Transform.h>

#include "Velocity.h"

MovementSystem::MovementSystem(fsn::EntityManager& entityMgr) : fsn::ComponentSystem(entityMgr)
{
    all<fsn::Transform, Velocity>();
}

MovementSystem::~MovementSystem()
{
    //dtor
}

void MovementSystem::begin(const float dt)
{
}

void MovementSystem::processEntity(const fsn::EntityRef& entity, const float dt)
{
    auto& transform = entity.getComponent<fsn::Transform>();
    auto& vel = entity.getComponent<Velocity>();

    transform.move(static_cast<float>(vel.x)*dt, static_cast<float>(vel.y)*dt);
}

void MovementSystem::end(const float dt)
{
}
