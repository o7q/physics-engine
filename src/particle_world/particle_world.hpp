#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

#include "../particle/particle.hpp"
#include "../solver/solver_common.hpp"

class ParticleWorld
{
public:
    ParticleWorld(Bounds2<float> bounds);

    void update(float dt);

    void addParticle(Particle &particle, const std::string &groupName);
    void createParticleGroup(const std::string &groupName);
    void linkParticles(size_t i1, size_t i2, float linkDistance);

    void setGravity(Vec2<float> gravity) { m_gravity = gravity; }

    std::vector<GroupedParticle> &getParticles() { return m_particles; }
    std::vector<ParticleLink> &getLinks() { return m_links; }

    size_t getParticleCount() const { return m_particles.size(); }
    uint8_t getGroupIndex(const std::string &groupName) { return m_particleGroups[groupName]; }
    Bounds2<float> getBounds() const { return m_bounds; }

private:
    std::vector<GroupedParticle> m_particles;
    std::vector<ParticleLink> m_links;

    std::unordered_map<std::string, uint8_t> m_particleGroups;
    uint8_t m_particleGroupIndex = 0;

    std::unordered_map<std::string, std::unique_ptr<Solver>> m_solvers;

    Bounds2<float> m_bounds;

    Vec2<float> m_gravity = Vec2<float>(0.0f, 0.0f);
};
