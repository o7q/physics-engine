#include "grid_map.hpp"

void GridParticleMap::regenerate()
{
    for (auto &pair : r_particles)
    {
        GroupedParticle &gp = pair.second;
        Vec2<float> pos = gp.particle().getPosition();
        unsigned int grid_x = (pos.x - m_bounds.left()) / m_divisions.x;
        unsigned int grid_y = (pos.y - m_bounds.right()) / m_divisions.y;

        unsigned int cell_index = index_2d_to_1d(grid_x, grid_y, m_divisions.x);

        m_cells[cell_index].particleIDs.push_back(gp.group());
    }
}
