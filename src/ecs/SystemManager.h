//
// Created by liam on 5/21/20.
//

#ifndef RPG_SYSTEMMANAGER_H
#define RPG_SYSTEMMANAGER_H

#include "EntityManager.h"

#include <set>
#include <unordered_map>
#include <memory>

class System
{
public:
    std::set<Entity> m_entities;
};

class SystemManager
{
public:
    template <typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        const char* typeName = typeid(T).name();

        assert(m_systems.find(typeName) == m_systems.end() && "Registering system more than once!");

        auto system = std::make_shared<T>();
        m_systems.insert({ typeName, system });

        return system;
    }

    template <typename T>
    void SetSignature(Signature signature)
    {
        const char* typeName = typeid(T).name();

        assert(m_systems.find(typeName) != m_systems.end() && "System used before registered!");

        m_signatures.insert({ typeName, signature });
    }

    void EntityDestroyed(Entity entity)
    {
        for (const auto& pair : m_systems)
        {
            auto const& system = pair.second;

            system->m_entities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature)
    {
        for (const auto& pair : m_systems)
        {
            const auto& type = pair.first;
            const auto& system = pair.second;
            const auto& systemSignature = m_signatures[type];

            if ((entitySignature & systemSignature) == systemSignature)
            {
                system->m_entities.insert(entity);
            }
            else
            {
                system->m_entities.erase(entity);
            }
        }
    }

private:
    std::unordered_map<const char*, Signature> m_signatures;
    std::unordered_map<const char*, std::shared_ptr<System>> m_systems;
};

#endif // RPG_SYSTEMMANAGER_H
