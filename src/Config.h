//
// Created by liam on 5/19/20.
//

#ifndef RPG_CONFIG_H
#define RPG_CONFIG_H

#include "Events.h"

#include <map>
#include <tuple>

struct ConfigFileData
{
    std::pair<unsigned, unsigned> windowDimensions;
    bool vsync;
    unsigned FPS;
};

class Config
{
public:
    static void Init();

    static bool ParseEvent(const RawEvent& rawEvent, GameEvent& gameEvent);

    static ConfigFileData LoadConfigFile(const std::string& filePath);

    static std::pair<unsigned, unsigned> GetWindowDimensions() { return s_data.windowDimensions; }
    static bool GetVSyncEnabled() { return s_data.vsync; }
    static unsigned GetMaxFPS() { return s_data.FPS; }

private:
    static std::map<RawEvent, GameEvent> s_bindings;
    static ConfigFileData s_data;
};

#endif // RPG_CONFIG_H
