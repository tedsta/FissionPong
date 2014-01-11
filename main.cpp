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
#include <Fission/Network/IntentSystem.h>
#include <Fission/Network/Intent.h>

#include "Dimensions.h"
#include "Velocity.h"
#include "Paddle.h"
#include "Ball.h"
#include "Score.h"

#include "MovementSystem.h"
#include "PlayerControlSystem.h"

int main()
{
    // Initialize the resource manager.
    fsn::ResourceManager::init();

    // Register the components with the component type manager
    fsn::ComponentTypeManager::add<fsn::Transform>();
    fsn::ComponentTypeManager::add<fsn::Intent>();
    fsn::ComponentTypeManager::add<fsn::Sprite>();
    fsn::ComponentTypeManager::add<Dimensions>();
    fsn::ComponentTypeManager::add<Velocity>();
    fsn::ComponentTypeManager::add<Paddle>();
    fsn::ComponentTypeManager::add<Ball>();
    fsn::ComponentTypeManager::add<Score>();

    // Setup the engine, render manager, and fake connection.
    auto engine = new fsn::Engine;
    auto renderMgr = new fsn::RenderManager(800, 600, "Fission Pong Example", 5, NULL);
    auto conn = new fsn::Connection(engine->getEventManager());

    // Setup our systems - only the input systems for now
    auto spriteSys = new fsn::SpriteRenderSystem(engine->getEventManager(), renderMgr, 1.f/60.f);
    auto inputSys = new fsn::InputSystem(engine->getEventManager(), 1.f/60.f, &renderMgr->getWindow());
    auto intentSys = new fsn::IntentSystem(engine->getEventManager(), 1.f/60.f, conn);
    auto playerSys = new PlayerControlSystem(engine->getEventManager(), 1.f/60.f);
    auto moveSys = new MovementSystem(engine->getEventManager(), 1.f/60.f);

    engine->addSystem(spriteSys);
    engine->addSystem(inputSys);
    engine->addSystem(intentSys);
    engine->addSystem(playerSys);
    engine->addSystem(moveSys);

    auto entityMgr = engine->getEntityManager();

    auto paddle1 = entityMgr->getEntityRef(entityMgr->createEntity());
    paddle1->addComponent(new fsn::Transform(sf::Vector2f(5, 5)));
    paddle1->addComponent(new Dimensions(16, 64));
    paddle1->addComponent(new Velocity);
    paddle1->addComponent(new fsn::Sprite("paddle.png"));
    paddle1->addComponent(new Paddle);
    paddle1->addComponent(new fsn::Intent);

    paddle1->getComponent<fsn::Intent>()->mapKeyToIntent("up", sf::Keyboard::W, fsn::Down);
    paddle1->getComponent<fsn::Intent>()->mapKeyToIntent("down", sf::Keyboard::S, fsn::Down);

    auto paddle2 = entityMgr->getEntityRef(entityMgr->createEntity());
    paddle2->addComponent(new fsn::Transform(sf::Vector2f(renderMgr->getWindow().getSize().x-16-5, 5)));
    paddle2->addComponent(new Dimensions(16, 64));
    paddle2->addComponent(new Velocity);
    paddle2->addComponent(new fsn::Sprite("paddle.png"));
    paddle2->addComponent(new Paddle);
    paddle2->addComponent(new fsn::Intent);

    paddle2->getComponent<fsn::Intent>()->mapKeyToIntent("up", sf::Keyboard::Up, fsn::Down);
    paddle2->getComponent<fsn::Intent>()->mapKeyToIntent("down", sf::Keyboard::Down, fsn::Down);

    // Run the main loop.
    sf::Clock clock;
    while (renderMgr->getWindow().isOpen())
    {
        float dt = clock.getElapsedTime().asSeconds();
        clock.restart();

        conn->update(dt);
        engine->update(dt);
        renderMgr->renderLayers();
    }

    // Deinitialize everything
    delete engine;
    delete renderMgr;
    delete conn;

    return 0;
}
