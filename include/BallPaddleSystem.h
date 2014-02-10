#ifndef BALLPADDLESYSTEM_H
#define BALLPADDLESYSTEM_H

#include <Fission/Core/Systems/ComponentSystem.h>

class BallPaddleSystem : public fsn::ComponentSystem
{
    public:
        BallPaddleSystem(fsn::EntityManager& entityMgr);

        void processEntity(const fsn::EntityRef& entity, const float dt);

    private:
        fsn::EntityManager& mEntityManager;
};

#endif // BALLPADDLESYSTEM_H
