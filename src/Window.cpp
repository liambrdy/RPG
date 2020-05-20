//
// Created by liam on 5/19/20.
//

#include "Window.h"

#include <SFML/System/InputStream.hpp>

constexpr unsigned FPS = 60;

Window::Window(unsigned width, unsigned height, const char* title)
    : m_window(sf::VideoMode(width, height), title), m_width(width), m_height(height)
{
    m_window.setVerticalSyncEnabled(true);
    m_window.setFramerateLimit(FPS);
}

void Window::SwapBuffers()
{
    m_window.clear();
    m_window.display();
}

bool Window::HasEventReady(RawEvent& event)
{
    sf::Event e{};
    if (m_window.pollEvent(e))
    {
        event = SFMLEventToRawEvent(e);
        return event != RawEvent::NoEvent;
    }

    event = RawEvent::NoEvent;

    return false;
}