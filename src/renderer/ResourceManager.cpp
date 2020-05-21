//
// Created by liam on 5/20/20.
//

#include "ResourceManager.h"

#include <spdlog/spdlog.h>

std::unordered_map<std::string, sf::Texture> ResourceManager::s_textures;
std::unordered_map<std::string, sf::Font> ResourceManager::s_fonts;

void ResourceManager::Shutdown()
{
    s_textures.clear();
    s_fonts.clear();
}

sf::Texture ResourceManager::GetTexture(const std::string& name)
{
    if (s_textures.find(name) == s_textures.end())
    {
        spdlog::error("Failed to get loaded texture: {0}", name);

        return sf::Texture{};
    }

    return s_textures[name];
}

sf::Font ResourceManager::GetFont(const std::string& name)
{
    if (s_fonts.find(name) == s_fonts.end())
    {
        spdlog::error("Failed to get loaded font: {0}", name);

        return sf::Font{};
    }

    return s_fonts[name];
}

sf::Texture ResourceManager::LoadTexture(const std::string& name, const std::string& filePath)
{
    if (s_textures.find(name) != s_textures.end())
    {
        return GetTexture(name);
    }

    sf::Texture texture;
    if (texture.loadFromFile(filePath))
    {
        s_textures[name] = texture;
        return texture;
    }

    spdlog::error("Failed to load texture: {0}", filePath);

    return sf::Texture{};
}

sf::Font ResourceManager::LoadFont(const std::string& name, const std::string& filePath)
{
    if (s_fonts.find(name) != s_fonts.end())
    {
        return GetFont(name);
    }

    sf::Font font;
    if (font.loadFromFile(filePath))
    {
        s_fonts[name] = font;
        return font;
    }

    spdlog::error("Failed to load font: {0}", filePath);

    return sf::Font{};
}
