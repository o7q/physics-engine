#include "particle_world.hpp"

void ParticleWorld::purgeParticles()
{
    m_particles.clear();
    m_links.clear();
    m_nextParticleId = 0;
}

void ParticleWorld::purgeParticlesInGroup(const std::string &groupName)
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

void ParticleWorld::purgeLinks()
{
    m_links.clear();
}

void ParticleWorld::purgeInvalidLinks()
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
