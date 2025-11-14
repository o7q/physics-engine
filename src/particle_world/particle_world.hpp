#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <cstdint>
#include <optional>

#include "../particle/particle.hpp"
#include "../particle/grouped_particle.hpp"
#include "../solver/solver_common.hpp"

class ParticleWorld
{
public:
    ParticleWorld(Bounds2<float> bounds);

    void update(float dt);

    void addParticle(Particle &particle, const std::string &groupName);
    void linkParticles(uint64_t i1, uint64_t i2, float linkDistance);

    void createParticleGroup(const std::string &groupName);
    std::optional<uint8_t> getGroupIndexFromName(const std::string &groupName);

    void setGravity(Vec2<float> gravity) { m_gravity = gravity; }

    std::unordered_map<uint64_t, GroupedParticle> &getParticles() { return m_particles; }
    std::vector<ParticleLink> &getLinks() { return m_links; }

    size_t getParticleCount() const { return m_particles.size(); }
    uint64_t getNextParticleID() const { return m_nextParticleId; }
    Bounds2<float> getBounds() const { return m_bounds; }

    void purgeParticles();
    void purgeParticlesInGroup(const std::string &groupName);
    void purgeLinks();
    void purgeInvalidLinks();

private:
    std::unordered_map<uint64_t, GroupedParticle> m_particles;
    uint64_t m_nextParticleId = 0;
    std::vector<ParticleLink> m_links;

    std::unordered_map<std::string, uint8_t> m_particleGroups;
    uint8_t m_particleGroupIndex = 0;

    std::map<std::string, std::unique_ptr<Solver>> m_solvers;

    Bounds2<float> m_bounds;

    Vec2<float> m_gravity = Vec2<float>(0.0f, 0.0f);
};
