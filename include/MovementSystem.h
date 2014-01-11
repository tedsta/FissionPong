#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <Fission/Core/System.h>

class MovementSystem : public fsn::System
{
    public:
        MovementSystem(fsn::IEventManager* eventManager, float lockStep);
        ~MovementSystem();

    protected:
        void begin(const float dt);
        void processEntity(fsn::EntityRef* entity, const float dt);
        void end(const float dt);

    private:
};

#endif // MOVEMENTSYSTEM_H
