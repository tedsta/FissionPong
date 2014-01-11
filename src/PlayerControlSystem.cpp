#include "PlayerControlSystem.h"

#include <Fission/Network/Intent.h>

#include "Velocity.h"

PlayerControlSystem::PlayerControlSystem(fsn::IEventManager* eventManager, float lockStep) : fsn::System(eventManager, lockStep)
{
    mAspect.all<Velocity, fsn::Intent>();
}

PlayerControlSystem::~PlayerControlSystem()
{
    //dtor
}

void PlayerControlSystem::begin(const float dt)
{
}

void PlayerControlSystem::processEntity(fsn::EntityRef* entity, const float dt)
{
    auto vel = entity->getComponent<Velocity>();
    auto intent = entity->getComponent<fsn::Intent>();

    if (intent->isIntentActive("up"))
        vel->mY = -300;
    else if (intent->isIntentActive("down"))
        vel->mY = 300;
    else
        vel->mY = 0;
}

void PlayerControlSystem::end(const float dt)
{
}
