#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <Fission/Core/Engine.h>
#include <Fission/Core/EntityManager.h>
#include <Fission/Core/ResourceManager.h>
#include <Fission/Core/ComponentTypeManager.h>

#include <Fission/Rendering/RenderManager.h>
#include <Fission/Rendering/Transform.h>

#include <Fission/Input/InputSystem.h>

#include <Fission/Network/Connection.h>
#include <Fission/Network/IntentSystem.h>
#include <Fission/Network/Intent.h>

#include "Velocity.h"
#include "Paddle.h"
#include "Ball.h"
#include "Score.h"

#include "MovementSystem.h"

int main()
{
    // Initialize the resource manager.
    fsn::ResourceManager::init();

    // Register the components with the component type manager
    fsn::ComponentTypeManager::add<fsn::Transform>();
    fsn::ComponentTypeManager::add<fsn::Intent>();
    fsn::ComponentTypeManager::add<Velocity>();
    fsn::ComponentTypeManager::add<Paddle>();
    fsn::ComponentTypeManager::add<Ball>();
    fsn::ComponentTypeManager::add<Score>();

    // Setup the engine, render manager, and fake connection.
    auto engine = new fsn::Engine;
    auto renderMgr = new fsn::RenderManager(800, 600, "Fission Pong Example", 5, NULL);
    auto conn = new fsn::Connection(engine->getEventManager());

    // Setup our systems - only the input systems for now
    auto inputSys = new fsn::InputSystem(engine->getEventManager(), 1.f/60.f, &renderMgr->getWindow());
    auto intentSys = new fsn::IntentSystem(engine->getEventManager(), 1.f/60.f, conn);
    auto moveSys = new MovementSystem(engine->getEventManager(), 1.f/60.f);

    engine->addSystem(inputSys);
    engine->addSystem(intentSys);
    engine->addSystem(moveSys);

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
