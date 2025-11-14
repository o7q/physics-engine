#pragma once

#include <cstdint>

struct ParticleLink
{
public:
    ParticleLink(uint64_t i1, uint64_t i2, float linkDistance)
    {
        setI1(i1);
        setI2(i2);
        m_linkDistance = linkDistance;
    }

    void setI1(uint64_t i1) { m_i1 = i1; }
    void setI2(uint64_t i2) { m_i2 = i2; }
    uint64_t getI1() const { return m_i1; }
    uint64_t getI2() const { return m_i2; }

    float getLinkDistance() const { return m_linkDistance; }

private:
    uint64_t m_i1, m_i2;
    float m_linkDistance = 1.0f;
};