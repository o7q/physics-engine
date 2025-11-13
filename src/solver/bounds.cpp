#include "bounds.hpp"

void ParticleBoundsSolver::update_step(float dt)
{
    for (GroupedParticle &gp : r_particles)
    {
        Particle &p = gp.particle();

        if (p.isPinned())
        {
            continue;
        }

        float radius = p.getRadius();

        if (p.getPosition().y + radius > m_bounds.bottom())
        {
            float newY = m_bounds.bottom() - radius;
            Vec2<float> newVelY = p.getVelocity(dt);
            newVelY.y *= -0.1;

            p.setPosition(Vec2<float>(p.getPosition().x, newY));
            p.setVelocity(newVelY, dt);
        }

        if (p.getPosition().y - radius < m_bounds.top())
        {
            float newY = m_bounds.top() + radius;
            Vec2<float> newVelY = p.getVelocity(dt);
            newVelY.y *= -0.1;

            p.setPosition(Vec2<float>(p.getPosition().x, newY));
            p.setVelocity(newVelY, dt);
        }

        if (p.getPosition().x + radius > m_bounds.right())
        {
            float newX = m_bounds.right() - radius;
            Vec2<float> newVelX = p.getVelocity(dt);
            newVelX.x *= -0.1;

            p.setPosition(Vec2<float>(newX, p.getPosition().y));
            p.setVelocity(newVelX, dt);
        }

        if (p.getPosition().x - radius < m_bounds.left())
        {
            float newX = m_bounds.left() + radius;
            Vec2<float> newVelX = p.getVelocity(dt);
            newVelX.x *= -0.1;

            p.setPosition(Vec2<float>(newX, p.getPosition().y));
            p.setVelocity(newVelX, dt);
        }
    }
}
