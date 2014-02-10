#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include <Fission/Core/Systems/ComponentSystem.h>

class MovementSystem : public fsn::ComponentSystem
{
    public:
        MovementSystem(fsn::EntityManager& entityMgr);
        virtual ~MovementSystem();

        void begin(const float dt);
        void processEntity(const fsn::EntityRef& entity, const float dt);
        void end(const float dt);

    private:
};

#endif // MOVEMENTSYSTEM_H
