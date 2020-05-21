//
// Created by liam on 5/20/20.
//

#ifndef RPG_RESOURCEMANAGER_H
#define RPG_RESOURCEMANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

#include <unordered_map>
#include <string>

class ResourceManager
{
public:
    static void Shutdown();

    static sf::Texture LoadTexture(const std::string& name, const std::string& filePath);
    static sf::Font LoadFont(const std::string& name, const std::string& filePath);

    static sf::Texture GetTexture(const std::string& name);
    static sf::Font GetFont(const std::string& name);
private:
    static std::unordered_map<std::string, sf::Texture> s_textures;
    static std::unordered_map<std::string, sf::Font> s_fonts;
};

#endif // RPG_RESOURCEMANAGER_H
