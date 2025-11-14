#pragma once

#include "solver.hpp"

#include <unordered_map>

#include "../particle/grouped_particle.hpp"

class ParticleOverlapSolver : public Solver
{
public:
    ParticleOverlapSolver(std::unordered_map<uint64_t, GroupedParticle> &particles) : r_particles(particles) {}

protected:
    void update_step(float dt) override;

protected:
    std::unordered_map<uint64_t, GroupedParticle> &r_particles;
};
