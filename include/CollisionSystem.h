#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <Fission/Core/System.h>

class CollisionSystem : public fsn::System
{
    public:
        CollisionSystem(fsn::IEventManager* eventManager, float lockStep);
        ~CollisionSystem();
    protected:
        void begin(const float dt);
        void processEntity(fsn::EntityRef* entity, const float dt);
        void end(const float dt);
    private:
};

#endif // COLLISIONSYSTEM_H
