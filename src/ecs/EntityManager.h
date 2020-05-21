//
// Created by liam on 5/21/20.
//

#ifndef RPG_ENTITYMANAGER_H
#define RPG_ENTITYMANAGER_H

#include <array>
#include <bitset>
#include <queue>

#include <cassert>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager
{
public:
    EntityManager()
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            m_availableEntities.push(entity);
        }
    }

    Entity CreateEntity()
    {
        assert(m_livingEntityCount < MAX_ENTITIES && "Too many entities in existence!");

        Entity id = m_availableEntities.front();
        m_availableEntities.pop();
        ++m_livingEntityCount;

        return id;
    }

    void DestroyEntity(Entity entity)
    {
        assert(entity < MAX_ENTITIES && "Entity is out of range!");

        m_signatures[entity].reset();

        m_availableEntities.push(entity);
        --m_livingEntityCount;
    }

    void SetSignature(Entity entity, Signature signature)
    {
        assert(entity < MAX_ENTITIES && "Entity out of range!");

        m_signatures[entity] = signature;
    }

    Signature GetSignature(Entity entity) const { return m_signatures[entity]; }

private:
    std::queue<Entity> m_availableEntities{};
    std::array<Signature, MAX_ENTITIES> m_signatures{};

    uint32_t m_livingEntityCount{};
};

#endif // RPG_ENTITYMANAGER_H
