#include "particle_world.hpp"

void ParticleWorld::linkParticles(uint64_t i1, uint64_t i2, float linkDistance)
{
    ParticleLink link(i1, i2, linkDistance);
    m_links.push_back(link);
}
