#pragma once

#include "solver.hpp"

#include <vector>

#include "../particle/grouped_particle.hpp"

class ParticleBoundsSolver : public Solver
{
public:
    ParticleBoundsSolver(std::vector<GroupedParticle> &particles, Bounds2<float> bounds) : r_particles(particles),
                                                                                           m_bounds(bounds) {}

protected:
    void update_step(float dt) override;

protected:
    std::vector<GroupedParticle> &r_particles;
    Bounds2<float> m_bounds;
};
