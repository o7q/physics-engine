#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "particle_world/particle_world.hpp"

class Window
{
public:
    Window(int width, int height);

private:
    void drawParticleWorld(ParticleWorld& particleWorld);

private:
    sf::RenderWindow m_window;
    float m_dt;
};