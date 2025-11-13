#pragma once

#include "solver.hpp"

#include <vector>

#include "../particle/grouped_particle.hpp"

class ParticleOverlapSolver : public Solver
{
public:
    ParticleOverlapSolver(std::vector<GroupedParticle> &particles) : r_particles(particles) {}

protected:
    void update_step(float dt) override;

protected:
    std::vector<GroupedParticle> &r_particles;
};
