#include <spdlog/spdlog.h>

#include <SFML/System/Clock.hpp>

#include "scenes/Game.h"
#include "scenes/Scene.h"

#include "renderer/Window.h"

#include "core/Config.h"

int main()
{
    spdlog::set_level(spdlog::level::trace);

    Config::Init();

    auto [w, h] = Config::GetWindowDimensions();
    Window window(w, h, "RPG");

    Scene* scene = new Game();

    sf::Clock delta;

    for (;;)
    {
        window.SwapBuffers();

        RawEvent event;
        if (window.HasEventReady(event))
        {
            GameEvent gameEvent;
            if (Config::ParseEvent(event, gameEvent))
            {
                scene = scene->OnEvent(gameEvent);

                if (scene == nullptr)
                {
                    return 0;
                }
            }
        }

        scene = scene->OnUpdate(delta.restart().asSeconds());
        if (scene == nullptr)
        {
            return 0;
        }
    }
}