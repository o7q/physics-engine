#pragma once

#include <vector>
#include <utility>

#include "particle.hpp"
#include "spring.hpp"

class ParticleWorld
{
public:
    void add(Particle p)
    {
        m_particles.push_back(p);
        ++m_last_particle_index;
    }

    void link(size_t i1, size_t i2, float restLength)
    {
        Spring spring(m_particles, i1, i2, restLength);
        m_springs.push_back(spring);
    }

    std::vector<Particle> &getParticles() { return m_particles; }
    std::vector<Spring> &getSprings() { return m_springs; }
    size_t getLastParticleIndex() { return m_last_particle_index; }

private:
    std::vector<Particle> m_particles;
    std::vector<Spring> m_springs;
    size_t m_last_particle_index = 0;
};