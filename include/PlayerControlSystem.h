#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include <Fission/Core/System.h>

class PlayerControlSystem : public fsn::System
{
    public:
        PlayerControlSystem(fsn::IEventManager* eventManager, float lockStep);
        virtual ~PlayerControlSystem();

    protected:
        void begin(const float dt);
        void processEntity(fsn::EntityRef* entity, const float dt);
        void end(const float dt);

    private:
};

#endif // PLAYERCONTROLSYSTEM_H
