#include "CollisionSystem.h"

#include <Fission/Rendering/Transform.h>
#include "Dimensions.h"


CollisionSystem::CollisionSystem(fsn::IEventManager* eventManager, float lockStep) : fsn::System(eventManager, lockStep)
{
    mAspect.all<fsn::Transform, Dimensions>();
}

CollisionSystem::~CollisionSystem()
{
    //dtor
}

void CollisionSystem::begin(const float dt)
{

}
void CollisionSystem::processEntity(fsn::EntityRef* entity, const float dt)
{
    auto transform = entity->getComponent<fsn::Transform>();
    auto dimensions = entity->getComponent<Dimensions>();

    for( auto entity : getActiveEntities() ){

    }
}
void CollisionSystem::end(const float dt)
{

}
