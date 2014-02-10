#ifndef PLAYERCONTROLSYSTEM_H
#define PLAYERCONTROLSYSTEM_H

#include <Fission/Core/Systems/ComponentSystem.h>
#include <Fission/Input/IKeyboardListener.h>

class PlayerControlSystem : public fsn::ComponentSystem, public fsn::IKeyboardListener
{
    public:
        PlayerControlSystem(fsn::EntityManager& entityMgr);
        virtual ~PlayerControlSystem();

        void processEntity(const fsn::EntityRef& entity, const float dt);

        bool onKeyPressed(sf::Keyboard::Key key);
        bool onKeyReleased(sf::Keyboard::Key key);

    private:
        bool mKeyW;
        bool mKeyS;
        bool mKeyUp;
        bool mKeyDown;
};

#endif // PLAYERCONTROLSYSTEM_H
