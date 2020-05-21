//
// Created by liam on 5/19/20.
//

#include "Events.h"

RawEvent SFMLEventToRawEvent(const sf::Event& event)
{
    if (event.type == sf::Event::EventType::KeyPressed)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::A:
                return RawEvent::A;
            case sf::Keyboard::B:
                return RawEvent::B;
            case sf::Keyboard::C:
                return RawEvent::C;
            case sf::Keyboard::D:
                return RawEvent::D;
            case sf::Keyboard::E:
                return RawEvent::E;
            case sf::Keyboard::F:
                return RawEvent::F;
            case sf::Keyboard::G:
                return RawEvent::G;
            case sf::Keyboard::H:
                return RawEvent::H;
            case sf::Keyboard::I:
                return RawEvent::I;
            case sf::Keyboard::J:
                return RawEvent::J;
            case sf::Keyboard::K:
                return RawEvent::K;
            case sf::Keyboard::L:
                return RawEvent::L;
            case sf::Keyboard::M:
                return RawEvent::M;
            case sf::Keyboard::N:
                return RawEvent::N;
            case sf::Keyboard::O:
                return RawEvent::O;
            case sf::Keyboard::P:
                return RawEvent::P;
            case sf::Keyboard::Q:
                return RawEvent::Q;
            case sf::Keyboard::R:
                return RawEvent::R;
            case sf::Keyboard::S:
                return RawEvent::S;
            case sf::Keyboard::T:
                return RawEvent::T;
            case sf::Keyboard::U:
                return RawEvent::U;
            case sf::Keyboard::V:
                return RawEvent::V;
            case sf::Keyboard::W:
                return RawEvent::W;
            case sf::Keyboard::X:
                return RawEvent::X;
            case sf::Keyboard::Y:
                return RawEvent::Y;
            case sf::Keyboard::Z:
                return RawEvent::Z;
            case sf::Keyboard::Space:
                return RawEvent::Space;
            case sf::Keyboard::Escape:
                return RawEvent::Escape;
            default:
                return RawEvent::NoEvent;
        }
    }
    else if (event.type == sf::Event::Closed)
    {
        return RawEvent::WindowClose;
    }

    return RawEvent::NoEvent;
}