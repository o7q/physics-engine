#pragma once

#include <optional>
#include <unordered_map>
#include <vector>
#include <cstdint>

#include "particle/particle_link.hpp"
#include "particle/grouped_particle.hpp"

class SparseParticleMap
{
public:
    SparseParticleMap() {}

    void addParticle(Particle &particle, const std::string &groupName);
    void linkParticles(uint64_t i1, uint64_t i2, float linkDistance);

    void createParticleGroup(const std::string &groupName);
    std::optional<uint8_t> getGroupIndexFromName(const std::string &groupName);

    std::unordered_map<uint64_t, GroupedParticle> &getParticles() { return m_particles; }
    std::vector<ParticleLink> &getLinks() { return m_links; }

    size_t getParticleCount() const { return m_particles.size(); }
    uint64_t getNextParticleID() const { return m_nextParticleId; }

    void purgeParticles();
    void purgeParticlesInGroup(const std::string &groupName);
    void purgeLinks();

private:
    void purgeInvalidLinks();

private:
    std::unordered_map<uint64_t, GroupedParticle> m_particles;
    uint64_t m_nextParticleId = 0;
    std::vector<ParticleLink> m_links;

    std::unordered_map<std::string, uint8_t> m_particleGroups;
    uint8_t m_particleGroupIndex = 0;
};
