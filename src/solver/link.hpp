#pragma once

#include "solver.hpp"

#include <unordered_map>

#include "../particle/grouped_particle.hpp"
#include "../particle/particle_link.hpp"

class ParticleLinkSolver : public Solver
{
public:
    ParticleLinkSolver(std::unordered_map<uint64_t, GroupedParticle> &particles, std::vector<ParticleLink> &links) : r_particles(particles),
                                                                                                                     r_links(links) {}

protected:
    void update_step(float dt) override;

protected:
    std::unordered_map<uint64_t, GroupedParticle> &r_particles;
    std::vector<ParticleLink> &r_links;
};
