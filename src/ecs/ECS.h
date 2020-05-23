//
// Created by liam on 5/21/20.
//

#ifndef RPG_ECS_H
#define RPG_ECS_H

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

#include <memory>

class ECS
{
public:
    static void Init()
    {
        m_entityManager = std::make_unique<EntityManager>();
        m_componentManager = std::make_unique<ComponentManager>();
        m_systemManager = std::make_unique<SystemManager>();
    }

    static Entity CreateEntity() { return m_entityManager->CreateEntity(); }

    static void DestroyEntity(Entity entity)
    {
        m_entityManager->DestroyEntity(entity);
        m_componentManager->EntityDestroyed(entity);
        m_systemManager->EntityDestroyed(entity);
    }

    template <typename T>
    static void RegisterComponent()
    {
        m_componentManager->RegisterComponent<T>();
    }

    template <typename T, typename... P>
    static void AddComponent(Entity entity, P&&... args)
    {
        T component{ args... };
        m_componentManager->AddComponent(entity, component);

        auto signature = m_entityManager->GetSignature(entity);
        signature.set(m_componentManager->GetComponentType<T>(), true);
        m_entityManager->SetSignature(entity, signature);

        m_systemManager->EntitySignatureChanged(entity, signature);
    }

    template <typename T>
    static void RemoveComponent(Entity entity)
    {
        m_componentManager->RemoveComponent<T>(entity);

        auto signature = m_entityManager->GetSignature(entity);
        signature.set(m_componentManager->GetComponentType<T>(), false);
        m_entityManager->SetSignature(entity, signature);

        m_systemManager->EntitySignatureChanged(entity, signature);
    }

    template <typename T>
    static T& GetComponent(Entity entity)
    {
        return m_componentManager->GetComponent<T>(entity);
    }

    template <typename T>
    static ComponentType GetComponentType()
    {
        return m_componentManager->GetComponentType<T>();
    }

    template <typename T>
    static std::shared_ptr<T> RegisterSystem()
    {
        return m_systemManager->RegisterSystem<T>();
    }

    template <typename T>
    static void SetSystemSignature(Signature signature)
    {
        m_systemManager->SetSignature<T>(signature);
    }

private:
    static std::unique_ptr<EntityManager> m_entityManager;
    static std::unique_ptr<ComponentManager> m_componentManager;
    static std::unique_ptr<SystemManager> m_systemManager;
};

#endif // RPG_ECS_H
