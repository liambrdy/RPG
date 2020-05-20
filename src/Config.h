//
// Created by liam on 5/19/20.
//

#ifndef RPG_CONFIG_H
#define RPG_CONFIG_H

#include "Events.h"

#include <map>
#include <tuple>

class Config
{
public:
    static void Init();

    static bool ParseEvent(const RawEvent& rawEvent, GameEvent& gameEvent);

    static std::pair<unsigned, unsigned> GetWindowDimensions() { return s_windowDimensions; }

private:
    static std::map<RawEvent, GameEvent> s_bindings;
    static std::pair<unsigned, unsigned> s_windowDimensions;
};

#endif // RPG_CONFIG_H
