//
// Created by liam on 5/19/20.
//

#ifndef RPG_SCENE_H
#define RPG_SCENE_H

#include "Events.h"

class Scene
{
public:
    virtual ~Scene() = default;

    virtual Scene* OnUpdate(float delta) = 0;
    virtual Scene* OnEvent(const GameEvent& event) = 0;
    virtual void OnRender() const = 0;
};

#endif // RPG_SCENE_H
