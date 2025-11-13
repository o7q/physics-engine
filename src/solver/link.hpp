#pragma once

#include "solver.hpp"

#include <vector>

#include "../particle/grouped_particle.hpp"
#include "../particle/particle_link.hpp"

class ParticleLinkSolver : public Solver
{
public:
    ParticleLinkSolver(std::vector<GroupedParticle> &particles, std::vector<ParticleLink> &links) : r_particles(particles),
                                                                                                    r_links(links) {}

protected:
    void update_step(float dt) override;

protected:
    std::vector<GroupedParticle> &r_particles;
    std::vector<ParticleLink> &r_links;
};
