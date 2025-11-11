#pragma once

#include "math_utils.hpp"

class Particle
{
public:
    Particle(Vec2<float> position, float radius, float mass)
    {
        m_position = position;
        m_position_last = position;
        m_radius = radius;
        m_mass = mass;
    }

    void update(float dt)
    {
        // verlet integration
        Vec2<float> temp = m_position;
        m_position = m_position + (m_position - m_position_last) + m_acceleration * dt * dt;

        m_position_last = temp;
        m_acceleration = Vec2<float>(0.0f, 0.0f);
    }

    void setPosition(Vec2<float> position)
    {
        m_position = position;
    }

    void setVelocity(Vec2<float> velocity, float dt)
    {
        m_position_last = m_position - velocity * dt;
    }

    void setAcceleration(Vec2<float> acceleration)
    {
        m_acceleration = acceleration;
    }

    void setPinned(bool pinned)
    {
        m_pinned = pinned;
    }

    Vec2<float> getPosition() const { return m_position; }
    Vec2<float> getVelocity(float dt) const { return (m_position - m_position_last) / dt; }
    Vec2<float> getAcceleration() const { return m_acceleration; }
    float getRadius() const { return m_radius; }
    float getMass() const { return m_mass; }
    bool isPinned() const { return m_pinned; }

    void setColor(float r, float g, float b)
    {
        m_color_r = r;
        m_color_g = g;
        m_color_b = b;
    }

    float getColorR() const { return m_color_r; }
    float getColorG() const { return m_color_g; }
    float getColorB() const { return m_color_b; }

private:
    Vec2<float> m_position;
    Vec2<float> m_position_last;
    Vec2<float> m_acceleration = Vec2<float>(0.0f, 0.0f);
    float m_radius = 5.0f;
    float m_mass = 1.0f;

    bool m_pinned = false;

    float m_color_r = 0.0f, m_color_g = 0.0f, m_color_b = 0.0f;
};