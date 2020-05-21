//
// Created by liam on 5/19/20.
//

#include "Config.h"

#include <algorithm>
#include <fstream>

#include <spdlog/spdlog.h>

std::map<RawEvent, GameEvent> Config::s_bindings;
ConfigFileData Config::s_data{};

void Config::Init()
{
    s_bindings[RawEvent::Escape] = GameEvent::PauseBack;
    s_bindings[RawEvent::Space] = GameEvent::JumpSelect;
    s_bindings[RawEvent::A] = GameEvent::Left;
    s_bindings[RawEvent::D] = GameEvent::Right;
    s_bindings[RawEvent::W] = GameEvent::Up;
    s_bindings[RawEvent::S] = GameEvent::Down;

    s_data = LoadConfigFile("config");
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

ConfigFileData Config::LoadConfigFile(const std::string& filePath)
{
    ConfigFileData data{};

    std::ifstream file(filePath);
    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
            if (line[0] == '#' || line.empty())
            {
                continue;
            }

            auto delimiterPos = line.find('=');
            auto name = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 1);

            if (name == "windowWidth")
            {
                data.windowDimensions.first = static_cast<unsigned>(std::atoi(value.c_str()));
            }
            else if (name == "windowHeight")
            {
                data.windowDimensions.second = static_cast<unsigned>(std::atoi(value.c_str()));
            }
            else if (name == "vsync")
            {
                int numVsync = std::atoi(value.c_str());
                if (numVsync <= 1 && numVsync >= 0)
                {
                    data.vsync = numVsync;
                }
            }
            else if (name == "fps")
            {
                data.FPS = static_cast<unsigned>(std::atoi(value.c_str()));
            }
        }
    }
    else
    {
        spdlog::error("Failed to load config file!");
    }

    return data;
}