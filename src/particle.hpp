#pragma once

#include "math_utils.hpp"

class Particle
{
public:
    Particle(Vec2<float> position, float size)
    {
        m_position = position;
        m_position_last = position;
        m_velocity = Vec2<float>(0, 0);
        m_acceleration = Vec2<float>(0, 0);
        m_radius = size;
    }

    void accelerate(Vec2<float> acc)
    {
        m_acceleration = m_acceleration + acc;
    }

    void setVelocity(Vec2<float> vel)
    {
        m_velocity = vel;
    }

    void updatePosition(float dt)
    {
        Vec2<float> temp = m_position;
        m_position = m_position + m_velocity + m_acceleration;

        m_position_last = temp;

        m_velocity = m_position - m_position_last;
        m_acceleration = Vec2<float>(0, 0);
    }

    void setPosition(Vec2<float> position)
    {
        m_position = position;
    }

    void move(Vec2<float> vec)
    {
        m_position = m_position + vec;
    }

    Vec2<float> getPosition() const { return m_position; }
    Vec2<float> getVelocity() const { return m_velocity; }
    float getRadius() const { return m_radius; }

private:
    Vec2<float> m_position;
    Vec2<float> m_position_last;
    Vec2<float> m_velocity;
    Vec2<float> m_acceleration;
    float m_radius = 5.0f;
};