#include "solver.hpp"

#include <cmath>

void Solver::solve_particle_collisions(float dt)
{
    for (size_t i = 0; i < m_particles.size(); ++i)
    {
        Particle &p1 = m_particles[i];
        Vec2<float> p1_pos = p1.getPosition();
        float p1_radius = p1.getRadius();

        for (size_t j = i + 1; j < m_particles.size(); ++j)
        {
            Particle &p2 = m_particles[j];
            Vec2<float> p2_pos = p2.getPosition();
            float p2_radius = p2.getRadius();

            float dx = p1_pos.x - p2_pos.x;
            float dy = p1_pos.y - p2_pos.y;
            float dist = std::sqrt(dx * dx + dy * dy);

            if (dist < p1_radius + p2_radius)
            {
                float overlap = (p1_radius + p2_radius) - dist;
                Vec2<float> normal = (p1_pos - p2_pos) / dist;

                p1_pos = p1_pos + normal * overlap * 0.5f;
                p2_pos = p2_pos - normal * overlap * 0.5f;

                p1.setPosition(p1_pos);
                p2.setPosition(p2_pos);
            }
        }
    }
}

void Solver::solve_boundary_collisions(float dt)
{
    for (Particle &particle : m_particles)
    {
        float radius = particle.getRadius();

        if (particle.getPosition().y + radius > m_bounds.bottom())
        {
            float newY = m_bounds.bottom() - radius;
            Vec2<float> vel = particle.getVelocity(dt);
            vel.y *= -0.1;

            particle.setPosition(Vec2<float>(particle.getPosition().x, newY));
            particle.setVelocity(vel, dt);
        }

        if (particle.getPosition().y - radius < m_bounds.top())
        {
            float newY = m_bounds.top() + radius;
            Vec2<float> newVelY = particle.getVelocity(dt);
            newVelY.y *= -0.1;

            particle.setPosition(Vec2<float>(particle.getPosition().x, newY));
            particle.setVelocity(newVelY, dt);
        }

        if (particle.getPosition().x + radius > m_bounds.right())
        {
            float newX = m_bounds.right() - radius;
            Vec2<float> newVelX = particle.getVelocity(dt);
            newVelX.x *= -0.1;

            particle.setPosition(Vec2<float>(newX, particle.getPosition().y));
            particle.setVelocity(newVelX, dt);
        }

        if (particle.getPosition().x - radius < m_bounds.left())
        {
            float newX = m_bounds.left() + radius;
            Vec2<float> newVelX = particle.getVelocity(dt);
            newVelX.x *= -0.1;

            particle.setPosition(Vec2<float>(newX, particle.getPosition().y));
            particle.setVelocity(newVelX, dt);
        }
    }
}
