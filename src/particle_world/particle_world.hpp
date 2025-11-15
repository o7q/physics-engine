#pragma once

#include <map>
#include <memory>

#include "particle_map/sparse_map.hpp"
#include "particle_map/grid_map.hpp"

#include "particle/particle.hpp"
#include "particle/grouped_particle.hpp"
#include "solver/solver_common.hpp"

class ParticleWorld
{
public:
    ParticleWorld(Bounds2<float> bounds,
                  Vec2<unsigned int> sim_divisions = Vec2<unsigned int>(10, 10)) : m_gridMap(m_sparseMap.getParticles(), bounds, sim_divisions)
    {
        m_solvers.insert({"overlap", std::make_unique<ParticleOverlapSolver>(m_sparseMap.getParticles())});
        m_solvers.insert({"links", std::make_unique<ParticleLinkSolver>(m_sparseMap.getParticles(), m_sparseMap.getLinks())});
        m_solvers.insert({"bounds", std::make_unique<ParticleBoundsSolver>(m_sparseMap.getParticles(), bounds)});

        m_solvers.at("overlap").get()->setSteps(16);
        m_solvers.at("links").get()->setSteps(16);
        m_solvers.at("bounds").get()->setSteps(1);
    }

    SparseParticleMap &particles() { return m_sparseMap; }
    GridParticleMap &grid() { return m_gridMap; }

    void update(float dt);

    void setGravity(Vec2<float> gravity) { m_gravity = gravity; }

private:
    SparseParticleMap m_sparseMap;
    GridParticleMap m_gridMap;
    std::map<std::string, std::unique_ptr<Solver>> m_solvers;

    Vec2<float> m_gravity = Vec2<float>(0.0f, 0.0f);
};
