//
// Created by liam on 5/19/20.
//

#ifndef RPG_EVENTS_H
#define RPG_EVENTS_H

#include <SFML/Window/Event.hpp>

enum class RawEvent
{
    NoEvent,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Space,
    Escape,
    WindowClose
};

enum class GameEvent
{
    Left,
    Right,
    Up,
    Down,
    JumpSelect,
    Select,
    PauseBack,
    MustQuit
};

RawEvent SFMLEventToRawEvent(const sf::Event& event);

#endif // RPG_EVENTS_H
