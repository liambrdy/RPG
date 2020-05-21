//
// Created by liam on 5/19/20.
//

#ifndef RPG_GAME_H
#define RPG_GAME_H

#include "Scene.h"

class Game : public Scene
{
public:
    Game();
    ~Game() override;

    Scene* OnUpdate(float delta) override;
    Scene* OnEvent(const GameEvent& event) override;
    void OnRender() const override;
};

#endif // RPG_GAME_H
