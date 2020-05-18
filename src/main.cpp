#include <spdlog/spdlog.h>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

constexpr unsigned W = 800, H = 600;
constexpr unsigned FRAME_RATE = 60;

int main()
{
	spdlog::info("Hello {0}", "World");

	sf::RenderWindow window(sf::VideoMode(W, H), "RPG");
	window.setFramerateLimit(FRAME_RATE);

	ImGui::SFML::Init(window);

	sf::Clock deltaTime;

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
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();

	return 0;
}