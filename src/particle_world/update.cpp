#include "particle_world.hpp"

void ParticleWorld::update(float dt)
{
    for (GroupedParticle &gp : m_particles)
    {
        Particle &p = gp.particle();
        p.addAcceleration(m_gravity);
        p.update(dt);
    }

    for (auto &solver : m_solvers)
    {
        solver.second.get()->update(dt);
    }
}
