#include "solver.hpp"

#include <cmath>

void Solver::solve_particle_collisions()
{
    for (size_t i = 0; i < m_particles.size(); ++i)
    {
        Particle& particle = m_particles[i];

        for (size_t j = i + 1; j < m_particles.size(); ++j)
        {
            Particle& particle2 = m_particles[j];
            Vec2<float> collision_axis = particle.getPosition() - particle2.getPosition();
            float dist = std::sqrt(collision_axis.x * collision_axis.x + collision_axis.y * collision_axis.y);
            float min_dist = particle.getRadius() + particle2.getRadius();

            if (dist < min_dist)
            {
                Vec2<float> n = collision_axis / dist;
                float delta = min_dist - dist;
                particle.move(n * delta * 0.5f);
                particle2.move(n * delta * -0.5f);
            }
        }
    }
}

void Solver::solve_boundary_collisions()
{
    for (Particle &particle : m_particles)
    {
        float radius = particle.getRadius();

        if (particle.getPosition().y + radius > m_bounds.bottom())
        {
            float newY = m_bounds.bottom() - radius;
            particle.setPosition(Vec2<float>(particle.getPosition().x, newY));

            Vec2<float> vel = particle.getVelocity();
            vel.y *= -0.9;
            particle.setVelocity(vel);
        }

        if (particle.getPosition().y - radius < m_bounds.top())
        {
            float newY = m_bounds.top() + radius;
            particle.setPosition(Vec2<float>(particle.getPosition().x, newY));

            Vec2<float> vel = particle.getVelocity();
            vel.y *= -0.9;
            particle.setVelocity(vel);
        }

        if (particle.getPosition().x + radius > m_bounds.right())
        {
            float newX = m_bounds.right() - radius;
            particle.setPosition(Vec2<float>(newX, particle.getPosition().y));

            Vec2<float> vel = particle.getVelocity();
            vel.x *= -0.9;
            particle.setVelocity(vel);
        }

        if (particle.getPosition().x - radius < m_bounds.left())
        {
            float newX = m_bounds.left() + radius;
            particle.setPosition(Vec2<float>(newX, particle.getPosition().y));

            Vec2<float> vel = particle.getVelocity();
            vel.x *= -0.9;
            particle.setVelocity(vel);
        }
    }
}
