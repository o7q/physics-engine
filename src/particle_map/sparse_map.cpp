#include "sparse_map.hpp"

#include <iostream>

void SparseParticleMap::createParticleGroup(const std::string &groupName)
{
    if (getGroupIndexFromName(groupName).has_value())
    {
        std::cout << groupName << ": already a group." << std::endl;
        return;
    }

    m_particleGroups.insert({groupName, m_particleGroupIndex});
    ++m_particleGroupIndex;
}

std::optional<uint8_t> SparseParticleMap::getGroupIndexFromName(const std::string &groupName)
{
    auto it = m_particleGroups.find(groupName);
    if (it == m_particleGroups.end())
    {
        return std::nullopt;
    }
    return it->second;
}

void SparseParticleMap::addParticle(Particle &particle, const std::string &groupName)
{
    if (!getGroupIndexFromName(groupName).has_value())
    {
        std::cout << groupName << ": does not exist!" << std::endl;
        return;
    }

    GroupedParticle gp(particle, m_particleGroups.at(groupName));
    m_particles.insert({m_nextParticleId, gp});

    ++m_nextParticleId;
}

void SparseParticleMap::linkParticles(uint64_t i1, uint64_t i2, float linkDistance)
{
    ParticleLink link(i1, i2, linkDistance);
    m_links.push_back(link);
}

void SparseParticleMap::purgeParticles()
{
    m_particles.clear();
    m_links.clear();
    m_nextParticleId = 0;
}

void SparseParticleMap::purgeParticlesInGroup(const std::string &groupName)
{
    std::optional<uint8_t> groupIndex = getGroupIndexFromName(groupName);

    if (!groupIndex.has_value())
    {
        return;
    }

    for (auto it = m_particles.begin(); it != m_particles.end();)
    {
        GroupedParticle &gp = it->second;

        if (gp.group() == groupIndex.value())
        {
            it = m_particles.erase(it);
        }
        else
        {
            ++it;
        }
    }

    purgeInvalidLinks();
}

void SparseParticleMap::purgeLinks()
{
    m_links.clear();
}

void SparseParticleMap::purgeInvalidLinks()
{
    for (auto it = m_links.begin(); it != m_links.end();)
    {
        if (m_particles.find(it->getI1()) == m_particles.end() ||
            m_particles.find(it->getI2()) == m_particles.end())
        {
            it = m_links.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
