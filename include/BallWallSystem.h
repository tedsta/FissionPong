#ifndef BALLWALLSYSTEM_H
#define BALLWALLSYSTEM_H

#include <Fission/Core/Systems/ComponentSystem.h>

class BallWallSystem : public fsn::ComponentSystem
{
    public:
        BallWallSystem(fsn::EntityManager& entityMgr, int screenWidth, int screenHeight);

        void processEntity(const fsn::EntityRef& entity, const float dt);

    private:
        int mScreenWidth;
        int mScreenHeight;
};

#endif // BALLWALLSYSTEM_H
