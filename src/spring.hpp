#pragma once

#include <vector>
#include <cmath>

#include "particle.hpp"

class Spring
{
public:
    Spring(std::vector<Particle> &particles, size_t i1, size_t i2, float restLength) : r_particles(particles)
    {
        setI1(i1);
        setI2(i2);
        m_restLength = restLength;
    }

    void setI1(size_t i1)
    {
        m_i1 = i1;
    }

    void setI2(size_t i2)
    {
        m_i2 = i2;
    }

    void update()
    {
        size_t size = r_particles.size();
        if (m_i1 >= size || m_i2 >= size)
        {
            return;
        }

        Particle &p1 = r_particles[m_i1];
        Particle &p2 = r_particles[m_i2];

        Vec2<float> p1_pos = p1.getPosition();
        Vec2<float> p2_pos = p2.getPosition();

        float dx = p1_pos.x - p2_pos.x;
        float dy = p1_pos.y - p2_pos.y;
        float dist = std::sqrt(dx * dx + dy * dy);

        float overlap = m_restLength - dist;

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

private:
    size_t m_i1, m_i2;
    std::vector<Particle> &r_particles;
    float m_restLength = 1.0f;
};