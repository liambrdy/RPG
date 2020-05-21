//
// Created by liam on 5/21/20.
//

#include "ECS.h"

std::unique_ptr<EntityManager> ECS::m_entityManager;
std::unique_ptr<ComponentManager> ECS::m_componentManager;
std::unique_ptr<SystemManager> ECS::m_systemManager;