#include <spdlog/spdlog.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>

constexpr unsigned W = 800, H = 600;
constexpr unsigned FRAME_RATE = 60;

int main()
{
    spdlog::info("Hello {0}", "World");

    sf::RenderWindow window(sf::VideoMode(W, H), "RPG");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(FRAME_RATE);

    ImGui::SFML::Init(window);

    sf::Clock deltaTime;

    sf::CircleShape circle(100.0f);
    circle.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const auto timeElapsed = deltaTime.restart();
        ImGui::SFML::Update(window, timeElapsed);

        ImGui::Begin("Debug");
        ImGui::Text("Frame time: %f", static_cast<double>(timeElapsed.asSeconds()));
        ImGui::End();

        window.clear();

        window.draw(circle);

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}