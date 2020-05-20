//
// Created by liam on 5/19/20.
//

#include "Config.h"

constexpr unsigned DEFAULT_WIDTH = 800, DEFAULT_HEIGHT = 600;

std::map<RawEvent, GameEvent> Config::s_bindings;
std::pair<unsigned, unsigned> Config::s_windowDimensions = { DEFAULT_WIDTH, DEFAULT_HEIGHT };

void Config::Init()
{
    s_bindings[RawEvent::Escape] = GameEvent::PauseBack;
    s_bindings[RawEvent::Space] = GameEvent::JumpSelect;
    s_bindings[RawEvent::A] = GameEvent::Left;
    s_bindings[RawEvent::D] = GameEvent::Right;
    s_bindings[RawEvent::W] = GameEvent::Up;
    s_bindings[RawEvent::S] = GameEvent::Down;
}

bool Config::ParseEvent(const RawEvent& rawEvent, GameEvent& gameEvent)
{
    if (s_bindings.count(rawEvent) > 0)
    {
        gameEvent = s_bindings[rawEvent];
    }
    else if (rawEvent == RawEvent::WindowClose)
    {
        gameEvent = GameEvent::MustQuit;
    }
    else
    {
        return false;
    }

    return true;
}