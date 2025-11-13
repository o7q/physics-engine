#include "particle_world.hpp"

void ParticleWorld::addParticle(Particle &particle, const std::string &groupName)
{
    if (!m_particleGroups.count(groupName))
    {
        std::cout << groupName << ": does not exist!" << std::endl;
        return;
    }

    GroupedParticle gp(particle, m_particleGroups[groupName]);
    m_particles.push_back(gp);
}

void ParticleWorld::linkParticles(size_t i1, size_t i2, float linkDistance)
{
    ParticleLink link(i1, i2, linkDistance);
    m_links.push_back(link);
}

void ParticleWorld::createParticleGroup(const std::string &groupName)
{
    if (m_particleGroups.count(groupName))
    {
        std::cout << groupName << ": already a group." << std::endl;
        return;
    }

    m_particleGroups.insert({groupName, m_particleGroupIndex});
    ++m_particleGroupIndex;
}
