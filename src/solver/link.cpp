#include "link.hpp"

void ParticleLinkSolver::update_step(float dt)
{
    for (ParticleLink &link : r_links)
    {
        uint64_t i1 = link.getI1();
        uint64_t i2 = link.getI2();

        Particle &p1 = r_particles.at(i1).particle();
        Particle &p2 = r_particles.at(i2).particle();

        Vec2<float> p1_pos = p1.getPosition();
        Vec2<float> p2_pos = p2.getPosition();

        float dx = p1_pos.x - p2_pos.x;
        float dy = p1_pos.y - p2_pos.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        float overlap = link.getLinkDistance() - dist;

        Vec2<float> normal = (p1_pos - p2_pos) / dist;

        float stiffness = 0.2f;
        p1_pos = p1_pos + normal * overlap * 0.5f * stiffness;
        p2_pos = p2_pos - normal * overlap * 0.5f * stiffness;

        if (!p1.isPinned())
        {
            p1.setPosition(p1_pos);
        }
        if (!p2.isPinned())
        {
            p2.setPosition(p2_pos);
        }
    }
}
