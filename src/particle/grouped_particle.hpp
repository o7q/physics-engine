#pragma once

#include <cstdint>

#include "particle.hpp"

struct GroupedParticle
{
    GroupedParticle(Particle particle, uint8_t groupIndex) : r_particle(particle),
                                                             m_groupIndex(groupIndex) {}

    Particle &particle() { return r_particle; }
    uint8_t group() { return m_groupIndex; }

private:
    Particle r_particle;
    uint8_t m_groupIndex = 0;
};