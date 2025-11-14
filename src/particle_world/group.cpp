#include "particle_world.hpp"

#include <iostream>

void ParticleWorld::createParticleGroup(const std::string &groupName)
{
    if (getGroupIndexFromName(groupName).has_value())
    {
        std::cout << groupName << ": already a group." << std::endl;
        return;
    }

    m_particleGroups.insert({groupName, m_particleGroupIndex});
    ++m_particleGroupIndex;
}

std::optional<uint8_t> ParticleWorld::getGroupIndexFromName(const std::string &groupName)
{
    auto it = m_particleGroups.find(groupName);
    if (it == m_particleGroups.end())
    {
        return std::nullopt;
    }
    return it->second;
}
