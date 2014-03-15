#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <Fission/Core/Engine.h>
#include <Fission/Core/EntityManager.h>
#include <Fission/Core/ResourceManager.h>
#include <Fission/Core/ComponentTypeManager.h>

#include <Fission/Rendering/RenderManager.h>
#include <Fission/Rendering/Transform.h>
#include <Fission/Rendering/Sprite.h>
#include <Fission/Rendering/SpriteRenderSystem.h>

#include <Fission/Input/InputSystem.h>

#include <Fission/Network/Connection.h>

#include "Dimensions.h"
#include "Velocity.h"
#include "Paddle.h"
#include "Ball.h"
#include "Score.h"

#include "MovementSystem.h"
#include "PlayerControlSystem.h"
#include "BallWallSystem.h"
#include "BallPaddleSystem.h"

#include "EntityTags.h"

int main()
{
    // Initialize the resource manager.
    fsn::ResourceManager::init();

    // Register the components with the component type manager
    fsn::ComponentTypeManager::add<fsn::Transform>();
    fsn::ComponentTypeManager::add<fsn::Sprite>();
    fsn::ComponentTypeManager::add<Dimensions>();
    fsn::ComponentTypeManager::add<Velocity>();
    fsn::ComponentTypeManager::add<Paddle>();
    fsn::ComponentTypeManager::add<Ball>();
    fsn::ComponentTypeManager::add<Score>();

    // Setup the engine, render manager, and fake connection.
    fsn::Engine engine;
    auto& entityMgr = engine.getEntityManager();
    fsn::RenderManager renderMgr(800, 600, "Fission Pong Example", 5, NULL);
    fsn::Connection conn(engine.getEventManager());

    // Setup our systems - only the input systems for now
    fsn::SpriteRenderSystem spriteSys(entityMgr, &renderMgr);
    fsn::InputSystem inputSys(&renderMgr.getWindow());
    PlayerControlSystem playerSys(entityMgr);
    MovementSystem moveSys(entityMgr);
    BallWallSystem ballWallSys(entityMgr, renderMgr.getWindow().getSize().x, renderMgr.getWindow().getSize().y);
    BallPaddleSystem ballPaddleSys(entityMgr);

    engine.addSystem(spriteSys);
    engine.addSystem(inputSys);
    engine.addSystem(playerSys);
    engine.addSystem(moveSys);
    engine.addSystem(ballWallSys);
    engine.addSystem(ballPaddleSys);

    inputSys.addKeyboardListener(&playerSys);

    auto paddle1 = entityMgr.createEntityRef(entityMgr.createEntity());
    paddle1.addComponent<fsn::Transform>(sf::Vector2f(5, 5));
    paddle1.addComponent<Dimensions>(16, 96);
    paddle1.addComponent<Velocity>();
    paddle1.addComponent<fsn::Sprite>("paddle.png");
    paddle1.addComponent<Paddle>(1);
    paddle1.setTag(PADDLE);

    auto paddle2 = entityMgr.createEntityRef(entityMgr.createEntity());
    paddle2.addComponent<fsn::Transform>(sf::Vector2f(renderMgr.getWindow().getSize().x-16-5, 5));
    paddle2.addComponent<Dimensions>(16, 96);
    paddle2.addComponent<Velocity>();
    paddle2.addComponent<fsn::Sprite>("paddle.png");
    paddle2.addComponent<Paddle>(-1);
    paddle2.setTag(PADDLE);

    auto ball = entityMgr.createEntityRef(entityMgr.createEntity());
    ball.addComponent<fsn::Transform>(sf::Vector2f(renderMgr.getWindow().getSize().x/2 - 8, renderMgr.getWindow().getSize().y/2 - 8));
    ball.addComponent<Dimensions>(16, 16);
    ball.addComponent<Velocity>(-300, 300);
    ball.addComponent<fsn::Sprite>("ball.png");
    ball.addComponent<Ball>();
    ball.setTag(BALL);

    // Run the main loop.
    sf::Clock clock;
    while (renderMgr.getWindow().isOpen())
    {
        float dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        conn.update();
        engine.update(dt);
        renderMgr.render();
    }

    return 0;
}
