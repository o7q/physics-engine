#pragma once

#include <vector>
#include <unordered_map>

#include "particle/grouped_particle.hpp"
#include "utils/math_utils.hpp"

class GridParticleMap
{
public:
    struct Cell
    {
        std::vector<uint64_t> particleIDs;
    };

public:
    GridParticleMap(std::unordered_map<uint64_t, GroupedParticle> &particles,
                    Bounds2<float> bounds,
                    Vec2<unsigned int> divisions) : r_particles(particles),
                                                    m_bounds(bounds),
                                                    m_divisions(divisions)
    {
        m_cells.resize(divisions.x * divisions.y);
    }

    void regenerate();

    std::vector<Cell> &getCells() { return m_cells; }

    Bounds2<float> getBounds() { return m_bounds; }
    Vec2<unsigned int> getDivisions() { return m_divisions; }

private:
    std::unordered_map<uint64_t, GroupedParticle> &r_particles;
    std::vector<Cell> m_cells;

    Bounds2<float> m_bounds;
    Vec2<unsigned int> m_divisions;
};
