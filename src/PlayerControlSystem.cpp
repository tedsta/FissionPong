#include "PlayerControlSystem.h"

#include "Paddle.h"
#include "Velocity.h"

PlayerControlSystem::PlayerControlSystem(fsn::EntityManager& entityMgr) : fsn::ComponentSystem(entityMgr),
    mKeyW(false), mKeyS(false), mKeyUp(false), mKeyDown(false)
{
    mAspect.all<Paddle, Velocity>();
}

PlayerControlSystem::~PlayerControlSystem()
{
    //dtor
}

void PlayerControlSystem::processEntity(const fsn::EntityRef& entity, const float dt)
{
    auto vel = entity.getComponent<Velocity>();
    auto paddle = entity.getComponent<Paddle>();

    if (paddle->deflectDir == 1)
    {
        if (mKeyW)
            vel->y = -300;
        else if (mKeyS)
            vel->y = 300;
        else
            vel->y = 0;
    }
    else if (paddle->deflectDir == -1)
    {
        if (mKeyUp)
            vel->y = -300;
        else if (mKeyDown)
            vel->y = 300;
        else
            vel->y = 0;
    }
}

bool PlayerControlSystem::onKeyPressed(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::Key::W:
        {
            mKeyW = true;
            break;
        }

        case sf::Keyboard::Key::S:
        {
            mKeyS = true;
            break;
        }

        case sf::Keyboard::Key::Up:
        {
            mKeyUp = true;
            break;
        }

        case sf::Keyboard::Key::Down:
        {
            mKeyDown = true;
            break;
        }

        default:
            break;
    }
}

bool PlayerControlSystem::onKeyReleased(sf::Keyboard::Key key)
{
    switch (key)
    {
        case sf::Keyboard::Key::W:
        {
            mKeyW = false;
            break;
        }

        case sf::Keyboard::Key::S:
        {
            mKeyS = false;
            break;
        }

        case sf::Keyboard::Key::Up:
        {
            mKeyUp = false;
            break;
        }

        case sf::Keyboard::Key::Down:
        {
            mKeyDown = false;
            break;
        }

        default:
            break;
    }
}
