#include <catch2/catch.hpp>

#include "core/Config.h"
#include "core/Events.h"
#include "scenes/Game.h"

#include "ecs/ECS.h"

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

TEST_CASE("ECS", "[tests]")
{
    ECS::Init();

    struct TestComponent
    {
        float a, b, c;
    };
    struct AnotherComponent
    {
        float mul;
    };
    ECS::RegisterComponent<AnotherComponent>();
    ECS::RegisterComponent<TestComponent>();

    class TestSystem : public System
    {
    public:
        void Update()
        {
            for (const auto& entity : m_entities)
            {
                auto& test = ECS::GetComponent<TestComponent>(entity);
                auto& another = ECS::GetComponent<AnotherComponent>(entity);

                test.a *= another.mul;
                test.b *= another.mul;
                test.c *= another.mul;
            }
        }
    };

    auto system = ECS::RegisterSystem<TestSystem>();

    Signature signature{};
    signature.set(ECS::GetComponentType<TestComponent>(), true);
    signature.set(ECS::GetComponentType<AnotherComponent>(), true);
    ECS::SetSystemSignature<TestSystem>(signature);

    Entity entity = ECS::CreateEntity();
    ECS::AddComponent<TestComponent>(entity, { 12, 11, -2 });

    Entity anotherEntity = ECS::CreateEntity();
    ECS::AddComponent<TestComponent>(anotherEntity, { 0, 1, 2 });
    ECS::AddComponent<AnotherComponent>(anotherEntity, { 2 });

    system->Update();

    auto component = ECS::GetComponent<TestComponent>(entity);
    REQUIRE(component.a == 12);
    REQUIRE(component.b == 11);
    REQUIRE(component.c == -2);

    auto anotherComponent = ECS::GetComponent<TestComponent>(anotherEntity);
    REQUIRE(anotherComponent.a == 0);
    REQUIRE(anotherComponent.b == 2);
    REQUIRE(anotherComponent.c == 4);

    ECS::DestroyEntity(entity);
    ECS::DestroyEntity(anotherEntity);
}