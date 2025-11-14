#pragma once

#include "solver.hpp"

#include <unordered_map>

#include "../particle/grouped_particle.hpp"

class ParticleBoundsSolver : public Solver
{
public:
    ParticleBoundsSolver(std::unordered_map<uint64_t, GroupedParticle> &particles, Bounds2<float> bounds) : r_particles(particles),
                                                                                                            m_bounds(bounds) {}

protected:
    void update_step(float dt) override;

protected:
    std::unordered_map<uint64_t, GroupedParticle> &r_particles;
    Bounds2<float> m_bounds;
};
