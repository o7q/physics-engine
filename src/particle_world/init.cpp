#include "particle_world.hpp"

ParticleWorld::ParticleWorld(Bounds2<float> bounds)
{
    m_bounds = bounds;

    m_solvers.insert({"overlap", std::make_unique<ParticleOverlapSolver>(m_particles)});
    m_solvers.insert({"links", std::make_unique<ParticleLinkSolver>(m_particles, m_links)});
    m_solvers.insert({"bounds", std::make_unique<ParticleBoundsSolver>(m_particles, bounds)});

    m_solvers.at("overlap").get()->setSteps(16);
    m_solvers.at("links").get()->setSteps(16);
    m_solvers.at("bounds").get()->setSteps(1);
}