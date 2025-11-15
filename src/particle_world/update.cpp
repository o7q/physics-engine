#include "particle_world.hpp"

void ParticleWorld::update(float dt)
{
    for (auto &pair : m_sparseMap.getParticles())
    {
        Particle &p = pair.second.particle();
        p.addAcceleration(m_gravity);
        p.update(dt);
    }

    for (auto &solver : m_solvers)
    {
        solver.second.get()->update(dt);
    }
}
