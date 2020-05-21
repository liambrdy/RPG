#include <catch2/catch.hpp>

#include "Config.h"
#include "Events.h"
#include "Game.h"
#include "ResourceManager.h"

TEST_CASE("Config File", "[test]")
{
    SECTION("Reading directly from file")
    {
        auto data = Config::LoadConfigFile("config");

        REQUIRE(data.windowDimensions.first > 0);
        REQUIRE(data.windowDimensions.second > 0);

        REQUIRE(data.FPS > 0);
    }

    SECTION("Initialize Config")
    {
        Config::Init();

        auto [w, h] = Config::GetWindowDimensions();
        REQUIRE(w > 0);
        REQUIRE(h > 0);

        REQUIRE(Config::GetMaxFPS() > 0);
    }

    SECTION("Parsing raw events to game events")
    {
        RawEvent event = RawEvent::A;
        GameEvent gameEvent;

        Config::ParseEvent(event, gameEvent);
        REQUIRE(gameEvent == GameEvent::Left);

        event = RawEvent::WindowClose;
        Config::ParseEvent(event, gameEvent);
        REQUIRE(gameEvent == GameEvent::MustQuit);

        event = RawEvent::Space;
        Config::ParseEvent(event, gameEvent);
        REQUIRE(gameEvent == GameEvent::JumpSelect);
    }
}

TEST_CASE("Events", "[test]")
{
    SECTION("SFML event to raw events")
    {
        sf::Event event{};
        event.type = sf::Event::KeyPressed;
        event.key.code = sf::Keyboard::A;

        REQUIRE(SFMLEventToRawEvent(event) == RawEvent::A);

        event.type = sf::Event::MouseButtonPressed;
        REQUIRE(SFMLEventToRawEvent(event) == RawEvent::NoEvent);

        event.key.code = sf::Keyboard::Home;
        REQUIRE(SFMLEventToRawEvent(event) == RawEvent::NoEvent);
    }
}

TEST_CASE("Scenes", "[tests]")
{
    Scene* scene = new Game();

    GameEvent event = GameEvent::Left;
    scene = scene->OnEvent(event);
    REQUIRE(scene != nullptr);

    event = GameEvent::MustQuit;
    scene = scene->OnEvent(event);
    REQUIRE(scene == nullptr);
}

TEST_CASE("ResourceManager", "[tests]")
{

    {
        auto texture = ResourceManager::LoadTexture("checkerboard", "assets/textures/checkerboard.png");
        REQUIRE(texture.getSize().x > 0);
        REQUIRE(texture.getSize().y > 0);

        texture = ResourceManager::GetTexture("checkerboard");
        REQUIRE(texture.getSize().x > 0);
        REQUIRE(texture.getSize().y > 0);
    }

    SECTION("Loading fonts")
    {
        auto font = ResourceManager::LoadFont("hack", "assets/fonts/hack.ttf");
        REQUIRE(!font.getInfo().family.empty());

        font = ResourceManager::GetFont("hack");
        REQUIRE(!font.getInfo().family.empty());
    }

    SECTION("Shutdown resource manager")
    {
        ResourceManager::Shutdown();

        auto texture = ResourceManager::GetTexture("checkerboard");
        REQUIRE(texture.getSize().x == 0);
        REQUIRE(texture.getSize().y == 0);

        auto font = ResourceManager::GetFont("hack");
        REQUIRE(font.getInfo().family.empty());
    } SECTION("Loading textures")
}