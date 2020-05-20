//
// Created by liam on 5/19/20.
//

#include "Game.h"

Game::Game() {}

Game::~Game() {}

Scene* Game::OnUpdate(float delta)
{
    (void)delta;

    return this;
}

Scene* Game::OnEvent(const GameEvent& event)
{
    switch (event)
    {
        case GameEvent::MustQuit:
        {
            delete this;
            return nullptr;
        }
        default:
            break;
    }

    return this;
}

void Game::OnRender() const {}
