//
// Created by liam on 5/19/20.
//

#ifndef RPG_WINDOW_H
#define RPG_WINDOW_H

#include <string>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Events.h"

class Window
{
public:
    Window(unsigned width, unsigned height, const char* title);
    ~Window() = default;

    void SwapBuffers();

    bool HasEventReady(RawEvent& event);

private:
    sf::RenderWindow m_window;
    unsigned m_width, m_height;
};

#endif // RPG_WINDOW_H
