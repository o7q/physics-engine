#include "particle_world.hpp"

#include <iostream>

void ParticleWorld::addParticle(Particle &particle, const std::string &groupName)
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

void ParticleWorld::linkParticles(uint64_t i1, uint64_t i2, float linkDistance)
{
    ParticleLink link(i1, i2, linkDistance);
    m_links.push_back(link);
}
