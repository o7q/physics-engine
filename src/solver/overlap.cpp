#include "overlap.hpp"

void ParticleOverlapSolver::update_step(float dt)
{
    for (auto it1 = r_particles.begin(); it1 != r_particles.end(); ++it1)
    {
        Particle &p1 = it1->second.particle();
        Vec2<float> p1_pos = p1.getPosition();
        float p1_radius = p1.getRadius();

        auto it2 = it1;
        ++it2;

        for (; it2 != r_particles.end(); ++it2)
        {
            Particle &p2 = it2->second.particle();
            Vec2<float> p2_pos = p2.getPosition();
            float p2_radius = p2.getRadius();

            float dx = p1_pos.x - p2_pos.x;
            float dy = p1_pos.y - p2_pos.y;
            float dist = std::sqrt(dx * dx + dy * dy);

            if (dist < p1_radius + p2_radius && dist != 0)
            {
                float overlap = (p1_radius + p2_radius) - dist;
                Vec2<float> normal = (p1_pos - p2_pos) / dist;

                p1_pos = p1_pos + normal * overlap * 0.5f;
                p2_pos = p2_pos - normal * overlap * 0.5f;

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
    }
}